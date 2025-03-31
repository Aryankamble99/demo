#include <stdio.h>
#include "eeprom-conf.h"
#include "chip-info.h"
#include "ver-mgmt.h"

#define MAX_EEPROM_BYTES 512

static const char *TAG = "EEPROM";

MYCONF_IP MyConf;

char d_c;
word d_w;
unsigned int d_i;
unsigned long d_l;
char d_st[5];

// #define MAX_OTHER_PARA 31 - Moved to eeprom-conf.h
const struct PROTOCOL_CMD_HNDL OtherSysPara[] = {
  { 0, D_STR, 10, &d_c, &d_w, &d_i, MyConf.E_PANELNO, "Panel Number", 1 },
  { 1, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_SSID, "WiFI SSID", 1 },
  { 2, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_WPSWD, "WiFi PSWD", 1 },
  { 3, D_CHAR, 3, &MyConf.E_DHCP, &d_w, &d_i, d_st, "DHCP", 1 },
  { 4, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_MYIP, "Device IP", 1 },
  { 5, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_GW, "Gateway", 1 },
  { 6, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_NM, "Subnet", 1 },
  { 7, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_DNS, "DNS", 1 },
  { 8, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_MYSSID, "AP Name", 1 },
  { 9, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_MYPSWD, "AP PSWD", 1 },
  { 10, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_MQTT_SERVER, "MQTT Server", 1 },
  { 11, D_INT, 10, &d_c, &d_w, &MyConf.E_MQTT_PORT, d_st, "MQTT Port", 1 },
  { 12, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_MQTT_USER, "MQTT Username", 1 },
  { 13, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_MQTT_PASS, "MQTT Password", 1 },
  { 14, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_MQTT_KEEPALIVE, "MQTT Keepalive", 1 },
  { 15, D_INT, 3, &d_c, &d_w, &MyConf.E_IR_REPEAT, d_st, "IR Repeat", 1 },
  { 16, D_INT, 3, &d_c, &d_w, &MyConf.E_AC_MODEL, d_st, "AC Make Model", 1 },
  { 17, D_CHAR, 3, &MyConf.E_AC_MODE, &d_w, &d_i, d_st, "AC Mode", 1 },
  { 18, D_CHAR, 3, &MyConf.E_AC_SPEED, &d_w, &d_i, d_st, "AC Speed", 1 },
  { 19, D_CHAR, 3, &MyConf.E_AC_SWING, &d_w, &d_i, d_st, "AC Swing", 1 },
  { 20, D_CHAR, 3, &MyConf.E_AC_TEMP, &d_w, &d_i, d_st, "AC Temperature", 1 },
  { 21, D_CHAR, 3, &MyConf.E_IR_FLAG, &d_w, &d_i, d_st, "IR FLAG", 1 },
  { 22, D_CHAR, 3, &MyConf.E_AHT2415C_FLAG, &d_w, &d_i, d_st, "AHT2415C FLAG", 1 },
  { 23, D_STR, 20, &d_c, &d_w, &d_i, MyConf.E_HOSTNAME, "HOSTNAME", 1 },
  { 24, D_INT, 10, &d_c, &d_w, &MyConf.E_SLAVEID, d_st, "Slave ID", 1 },
  { 25, D_INT, 10, &d_c, &d_w, &MyConf.E_BAUDRATE, d_st, "Baudrate", 1 },
  { 26, D_INT, 10, &d_c, &d_w, &MyConf.E_PARITY, d_st, "Parity", 1 },
  { 27, D_INT, 20, &d_c, &d_w, &MyConf.E_CHIP_ID, d_st, "CHIP_ID", 1 }  //Keep this last and keep MAX_OTHER_PARA equal to this index
};

int writeEEPROM(int loc, int count, char *data) {
  int i;
  if (loc + count > MAX_EEPROM_BYTES)
    return (-1);
  for (i = 0; i < count; i++) {
    EEPROM.write(i + loc, data[i]);
    delay(10);
    yield();  // Watchdog to avoid restart....
  }
  EEPROM.commit();
  return (count);
}

int readEEPROM(int loc, int count, char *data) {
  int i;
  char x;
  if (loc + count > MAX_EEPROM_BYTES)
    return (-1);
  for (i = 0; i < count; i++) {
    x = EEPROM.read(i + loc);
    data[i] = x;
  }
  return (count);
}

char *getParameter(int pos, char *str) {
  switch (OtherSysPara[pos].Type) {
    case D_BIN:
    case D_CHAR:
      sprintf(str, "%d", *OtherSysPara[pos].VChar);
      break;
    case D_WORD:
      sprintf(str, "%d", *OtherSysPara[pos].VWord);
      break;
    case D_LONG:
    case D_INT:
      sprintf(str, "%d", *OtherSysPara[pos].VLong);
      break;
    case D_STR:
      sprintf(str, "%s", OtherSysPara[pos].VStr);
      break;
  }
  return (str);
}

char *setParameter(int pos, char *str) {
  switch (OtherSysPara[pos].Type) {
    case D_BIN:
    case D_CHAR:
      *OtherSysPara[pos].VChar = (char)atoi(str);
      break;
    case D_WORD:
      *OtherSysPara[pos].VWord = (word)atoi(str);
      break;
    case D_LONG:
    case D_INT:
      *OtherSysPara[pos].VLong = (int)atoi(str);
      break;
    case D_STR:
      strncpy(OtherSysPara[pos].VStr, str, OtherSysPara[pos].Len);
      break;
  }
  return (str);
}

/*--------------------------------------------------------------------------*/

// https://tinkerman.cat/post/eeprom-rotation-for-esp8266-and-esp32/

void writeDefaultValue(void) {
  strncpy(MyConf.E_PANELNO, "111111", 10);
  strncpy(MyConf.E_SSID, "iAM-RnD", 20);
  strncpy(MyConf.E_WPSWD, "1234567890", 20);
  MyConf.E_DHCP = 1;
  strncpy(MyConf.E_MYIP, "", 20);
  strncpy(MyConf.E_GW, "", 20);
  strncpy(MyConf.E_NM, "255.255.255.0", 20);
  strncpy(MyConf.E_DNS, "192.168.1.139", 20);
  strncpy(MyConf.E_MYSSID, "ESP-ENERGY", 20);
  strncpy(MyConf.E_MYPSWD, "12345678", 20);
  strncpy(MyConf.E_MQTT_SERVER, "10.129.2.43", 20);
  MyConf.E_IR_REPEAT = 3;
  MyConf.E_AC_MODEL = 1;
  MyConf.E_AC_MODE = 1;
  MyConf.E_AC_SPEED = 2;
  MyConf.E_AC_SWING = 1;
  MyConf.E_AC_TEMP = 24;
  MyConf.E_MQTT_PORT = 1883;
  strncpy(MyConf.E_MQTT_USER, "admin", 20);
  strncpy(MyConf.E_MQTT_PASS, "admin123", 20);
  strncpy(MyConf.E_MQTT_KEEPALIVE, "60", 20);
  MyConf.E_IR_FLAG = 1;
  MyConf.E_AHT2415C_FLAG = 5;
  strncpy(MyConf.E_HOSTNAME, "ESP-IR-Blaster", 20);
  MyConf.E_SLAVEID = 1;
  MyConf.E_BAUDRATE = 9600;
  MyConf.E_PARITY = 1;
  MyConf.E_CHIP_ID = C_Chip;
  writeEEPROM(0, sizeof(MyConf), (char *)&MyConf);
}  // end of WriteDefaultValue  loop

void printMyConfigValue(void) {
  LOGI(TAG, "Configurations:\n\
  Panel Number: %s\n\
  SSID: %s\n\
  Password: %s\n\
  DHCP: %d\n\
  IP: %s\n\
  NW: %s\n\
  GW: %s\n\
  DNS: %s\n\
  MQTT SERVER: %s\n\
  MQTT PORT: %d\n\
  MQTT USER: %s\n\
  MQTT PASS: %s\n\
  IR FLAG: %c\n\
  AHT2415C FLAG: %c\n\
  HOSTNAME: %s\n\
  AC MODEL: %c\n\
  AC MODE: %c\n\
  AC SWING: %c\n\
  AC SPEED: %c\n\
  AC TEMPERATURE: %c\n\
  SLAVEID: %d\n\
  BAUDRATE: %d\n\
  PARITY:%d\n\
  ",
       MyConf.E_PANELNO,
       MyConf.E_SSID,
       MyConf.E_WPSWD,
       MyConf.E_DHCP,
       MyConf.E_MYIP,
       MyConf.E_NM,
       MyConf.E_GW,
       MyConf.E_DNS,
       MyConf.E_MQTT_SERVER,
       MyConf.E_MQTT_PORT,
       MyConf.E_MQTT_USER,
       MyConf.E_MQTT_PASS,
       MyConf.E_IR_FLAG,
       MyConf.E_AHT2415C_FLAG,
       MyConf.E_HOSTNAME,
       MyConf.E_AC_MODEL,
       MyConf.E_AC_MODE,
       MyConf.E_AC_SWING,
       MyConf.E_AC_SPEED,
       MyConf.E_AC_TEMP,
       MyConf.E_SLAVEID,
       MyConf.E_BAUDRATE,
       MyConf.E_PARITY
        );
}
