#ifndef EEPROM_CONFIG
#define EEPROM_CONFIG

#include "Arduino.h"
#include "Arduino.h"
#include "EEPROM.h"


__packed typedef struct
{
  unsigned int E_CHIP_ID;
  char E_PANELNO[10];
  char E_SSID[20];
  char E_WPSWD[20];
  char E_DHCP;
  char E_MYIP[20];
  char E_GW[20];
  char E_NM[20];
  char E_DNS[20];
  char E_MYSSID[20];
  char E_MYPSWD[20];
  char E_MQTT_SERVER[20];  //"192.168.2.22"
  unsigned int E_MQTT_PORT;
  char E_MQTT_USER[20];
  char E_MQTT_PASS[20];
  char E_MQTT_KEEPALIVE[20]; // Not used
  unsigned int E_IR_REPEAT;
  unsigned int E_AC_MODEL;
  char E_AC_MODE;
  char E_AC_SPEED;
  char E_AC_SWING;
  char E_AC_TEMP;
  char E_IR_FLAG;
  char E_AHT2415C_FLAG;
  char E_HOSTNAME[20];
  unsigned int E_SLAVEID;
  unsigned int E_BAUDRATE;
  unsigned int E_PARITY;
  

} MYCONF_IP;

extern MYCONF_IP MyConf;

extern char d_c;
extern word d_w;
extern unsigned int d_i;
extern unsigned long d_l;
extern char d_st[5];

#define D_CHAR 'C'
#define D_WORD 'W'  
#define D_LONG 'L'
#define D_INT 'I'
#define D_STR 'S'
#define D_BIN 'B'

__packed struct PROTOCOL_CMD_HNDL {
  char command;
  char Type;
  char Len;
  char *VChar;
  __packed word *VWord;
  __packed unsigned int *VLong;
  char *VStr;
  __packed char ParaName[17];
  char Settable;
};

#define MAX_OTHER_PARA 27
extern const struct PROTOCOL_CMD_HNDL OtherSysPara[MAX_OTHER_PARA+1];


// extern "C" {

    int writeEEPROM(int , int , char *);
    int readEEPROM(int , int , char *);
    char* getParameter(int , char *);
    char *setParameter(int, char *);
    void writeDefaultValue(void);
    void printMyConfigValue(void);
// }

#endif
