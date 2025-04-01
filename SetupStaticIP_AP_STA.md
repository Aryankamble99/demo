```mermaid
flowchart TD
    A((Start)) --> B["Log: Setting Up Static WiFi"]
    B --> C["Set Hostname & Disable Persistent Storage"]
    C --> D["Read CONFIG_PIN"]
    
    D -->|Low| E["Set NetworkMode = NW_AP"]
    E --> F["Enable Access Point Mode"]
    F --> G["Start AP with SSID & Password"]
    G --> H["Log: AP IP Address"]
    H --> I["C_WiFi_APOn = 1"]
    I --> Z((End))
    
    D -->|High| J["Set NetworkMode = NW_STA"]
    J --> K["Enable Station Mode"]
    K --> L["Validate Static IP, Gateway, Subnet, DNS"]
    
    L -->|Valid| M["Set Static IP using WiFi.config()"]
    L -->|Invalid| N["Log Error & Use DHCP"]
    
    M --> O["WiFi.begin(SSID, Password)"]
    N --> O
    
    O --> P["Attempt WiFi Connection (Max 5 tries)"]
    
    P -->|Connected| Q["C_WiFi_STAOn = 1"]
    Q --> R["Log: Connected & Show IP Address"]
    R --> Z
    
    P -->|Failed| S["C_WiFi_STAOn = 0"]
    S --> T["Log: Failed to Connect"]
    T --> Z((End))
