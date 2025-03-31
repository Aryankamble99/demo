flowchart TD
    A((Start)) --> B{WiFi Connected?}
    B -->|Yes| C((Exit))
    B --> |No| D[Wifi.begin - SSID,Password]
    D --> E["Log: Connecting to SSID"]
    E --> F{WiFi.isConnected?}
    F -->|Yes| G["Set C_WiFi_STAOn = 1"]
    G --> H["Log: Connected to SSID"]
    H --> I["Log: Show IP Address"]
    I --> J((Exit))
    F -->|No| K["Set C_WiFi_STAOn = 0"]
    K --> L["Log: Failed to connect"]
    L --> M((Exit))
