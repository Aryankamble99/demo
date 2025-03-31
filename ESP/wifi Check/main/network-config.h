#ifndef NETWORK_CONFIG
#define NETWORK_CONFIG

#include "input-config.h"

#define NW_AP 1
#define NW_STA 2
#define NW_AP_STA 3

extern byte NetworkMode;
extern byte C_WiFi_STAOn;
extern byte C_WiFi_APOn;
extern int wifiSTAStatus;
extern int No_Of_Channel;
extern byte C_MAC[6];
extern String C_MACStr;

// extern "C" {

    void SetupStaticIP_AP_STA();
    void SetupWiFi_AP_STA();
    void ShowWiFiStatus(int);
    void PollWiFi_STA(void);
    bool enableConfigHotspot();
    
// }

#endif