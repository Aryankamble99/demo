flowchart TD
    A((Start)) --> B["Log: NetworkMode, C_WiFi_APOn, C_WiFi_STAOn"]
    B --> C{Check i}
    
    C -->|1 (AP Mode)| D["Get AP connected devices"]
    D --> E["Log: AP IP & Devices Connected"]
    E --> Z((End))
    
    C -->|2 (STA Mode)| F["Get WiFi STA Status"]
    F --> G{WiFi Status?}
    
    G -->|WL_CONNECTED| H["Log: WiFi is Connected"]
    H --> I["Blink GREEN (50ms on/50ms off)"]
    I --> Z
    
    G -->|WL_IDLE_STATUS| J["Log: WiFi is Idle"]
    J --> K["Blink GREEN (100ms on/10ms off)"]
    K --> Z
    
    G -->|Not Connected| L["Log: WiFi Not Connected"]
    L --> M["Blink GREEN (10ms on/10ms off)"]
    M --> N["Log: IP Address"]
    N --> Z
    
    C -->|Default| O["Perform AP and STA checks"]
    O --> P["Get AP Connected Devices"]
    P --> Q["Log: AP IP & Devices Connected"]
    Q --> R["Get WiFi STA Status"]
    R --> G
    
    Z((End))
