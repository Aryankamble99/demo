# Wifi Disconnection Problem
---  
## Network Issues / WiFi Beacon Lost / Roaming Issue  
1. sometimes wifi may appear connected (cached status), but it is not actually authenticated or routed due to weak signal or loss of beacon.  
A "beacon timeout" issue in ESP32 Wi-Fi, where the ESP32 loses its connection due to not receiving beacon frames from the access point, can be addressed by checking the **power saving mode,** **signal strength,** and **Wi-Fi channel,** or by trying different connection methods

***Solutions***  
  1. Try disabling or adjusting power-saving modes in your ESP32 code **(e.g., WIFI_PS_MIN_MODEM or WIFI_PS_MAX_MODEM).** 
Example: In ESPHome, you can set **power_save_mode: NONE**
  2. 1. Move the ESP32 closer to the access poin
     2. Ensure the antenna is properly connected and in good condition
     3. Consider using an external antenna for better signal reception  

 ### Step 1: Properly Detect Disconnection

Instead of WiFi.status(), check the actual ping response or IP address validity.  

Modify PollWiFi_STA()  

```cpp
void PollWiFi_STA(void)   
{  
  if (WiFi.status() != WL_CONNECTED || WiFi.localIP().toString() == "0.0.0.0") {  
    LOGE(TAG, "WiFi Disconnected! Attempting to reconnect...");  
   
    WiFi.disconnect(); 
    delay(100);  
    WiFi.begin(MyConf.E_SSID, MyConf.E_WPSWD);  
    
    int retries = 10;   
    while (WiFi.status() != WL_CONNECTED && retries-- > 0) {    
      delay(500);   
      LOGI(TAG, "Reconnecting... [%d tries left]", retries);  
    }  
    
    if (WiFi.status() == WL_CONNECTED) {    
      LOGI(TAG, "Reconnected! IP: %s", WiFi.localIP().toString().c_str());    
    } else {    
      LOGE(TAG, "Reconnection failed.");    
    }   
  }   
}     
```
How It Works :  
- Checks both WiFi.status() and WiFi.localIP().
- Forces WiFi.disconnect() before reconnecting.
- Retries 10 times before giving up.
  
```cpp
WiFi.localIP().toString() == "0.0.0.0"
```
- Even if WiFi.status() says "connected", the ESP32 might not have a valid IP
- WiFi.localIP() returns the current IP address.
- .toString() converts it into a human-readable string.
- If it returns "0.0.0.0", it means no IP was assigned, which indicates a network failure.

```cpp
WiFi.disconnect();  
delay(100);  
```
-Force Disconnect Before Reconnect  
-Ensures clean re-connection without leftover data     


  ---  
  
### Step 2: Force Auto Reconnect

Enable Auto Reconnect in setup()

```cpp
WiFi.setAutoReconnect(true);
WiFi.persistent(true);
```    
---

### Step 3: Add a Watchdog Timer (Optional)

If WiFi disconnects for too long, restart ESP32.

```cpp
static unsigned long lastConnectionCheck = millis();

if (WiFi.status() != WL_CONNECTED) {
  if (millis() - lastConnectionCheck > 60000) {  // 1 min timeout
    LOGE(TAG, "Restarting ESP32 due to WiFi failure...");
    ESP.restart();
  }
} else {
  lastConnectionCheck = millis(); // Reset timer if connected
}
```     

---  

### Step 4: Automatically Restart ESP Periodically  
---   
## Other Issues  
**1. Power Supply**  
Ensure the ESP32 is getting sufficient and stable power. Try a different power source or USB cable.    
**2. Antenna Issues**  
If you are using an external antenna, ensure it is connected properly and the jumper 0K resistor is in the proper position for the desired antenna  
 
**3. Low DHCP IP Pool**       (check with IT team)     
Pool: 192.168.1.100 to 192.168.1.110  
only 11 IPs available.  



