
/*

    Make all Global var declarations, #defines and version info in this header file

*/
#ifndef VER_MGMT
#define VER_MGMT


/*

    Release Notes:

    _4_WLIR:
        Version: 1.03 - 27-09-2024
            1. AC remote learning code added.
            2. Removed IAQ, COSENSOR and 1WIRE code, R0 Value.
            3. OTA is not available for this version.
            4. Writing Defaults if Chip ID is not found in EEPROM.
            5. Configuration page opens at /config and indexpage added at /.

        Version: 1.04 (Whenever Created)
            1.


    _16_WLIR:
        Version: 1.01 - 27-09-2024
            1. ESP IR Blaster Code with OTA feature Added
            2. OTA Page can be accessed on 8081 port. Upload and Download functionality added.  

        Version: 1.02 (Whenever created)
            1.


    _16_WMDIR:
        Version: 1.01
            1. Configurations is similar to 4WLIR Model 1.03 Version with added data sharing over MODBUS
            2. MODBUS Connection parameters are configurable in EEPROM
            3. OTA wrbpage can be accessed on 8081 port.

        Version: 1.02 (Whenever created)
            1.


    _16_ECOIR: Special Release for Eco Energy Project
        Version: 1.01
            1. Configurations are similar to 16WMDIR 1.01.
            2. MODBUS Parameters are configurable in EEPROM
            3. OTA webpage on 8081 port.

        Version: 1.02 
            1. Added Holding Register 18 to resend the same IR command
            2. Added AC params select dropdown on Relay and AC Control Webpage
            3. Added a configuration hotspot mode


*/

/******************************************************************************************************/

#define _4_WLIR 1
#define _16_WLIR 2
#define _16_WMDIR 3
#define _16_ECOIR 4
#define _4_ECOIR 5

#define PRODUCT_CODE _16_ECOIR

// #define ENABLE_REMOTE_LOG


/******************************************************************************************************/

#ifdef PRODUCT_CODE 

    #if PRODUCT_CODE == _4_WLIR

        const char Version[] = "1.03";
        const char Model[] = "4WLIR";

    #elif PRODUCT_CODE == _16_WLIR

        const char Version[] = "1.01";
        const char Model[] = "16WLIR";

        #define ENABLE_OTA
    
    #elif PRODUCT_CODE == _16_WMDIR

        const char Version[] = "1.01";
        const char Model[] = "16WMDIR";

        #define ENABLE_MODBUS
        #define ENABLE_OTA
    
    #elif PRODUCT_CODE == _16_ECOIR

        const char Version[] = "1.02";
        const char Model[] = "ECOIR";

        #define ENABLE_MODBUS
        #define ENABLE_OTA

    #elif PRODUCT_CODE == _4_ECOIR

        const char Version[] = "0.01";
        const char Model[] = "4ECOIR";

        #define ENABLE_MODBUS
    
    #else
    
        const char Version[] = "";
        const char Model[] = "";
    
    #endif

#endif

/******************************************************************************************************/

/* Custom Logging Definitions */

#define LOGI(tag, format, ...) esp_log_write(ESP_LOG_INFO, tag, LOG_FORMAT(I, format), esp_log_timestamp(), tag __VA_OPT__(, ) __VA_ARGS__)
#define LOGE(tag, format, ...) esp_log_write(ESP_LOG_ERROR, tag, LOG_FORMAT(E, format), esp_log_timestamp(), tag __VA_OPT__(, ) __VA_ARGS__)
#define LOGW(tag, format, ...) esp_log_write(ESP_LOG_WARN, tag, LOG_FORMAT(W, format), esp_log_timestamp(), tag __VA_OPT__(, ) __VA_ARGS__)
#define LOGD(tag, format, ...) esp_log_write(ESP_LOG_DEBUG, tag, LOG_FORMAT(D, format), esp_log_timestamp(), tag __VA_OPT__(, ) __VA_ARGS__)
#define LOGV(tag, format, ...) esp_log_write(ESP_LOG_VERBOSE, tag, LOG_FORMAT(V, format), esp_log_timestamp(), tag __VA_OPT__(, ) __VA_ARGS__)



#endif