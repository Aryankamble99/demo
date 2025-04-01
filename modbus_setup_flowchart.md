```mermaid
flowchart TD
    A((Start)) --> B["Log: Setting up AP Mode for Configuration"]
    B --> C["Set NetworkMode = NW_AP"]
    C --> D["Start WiFi AP with SSID & Password"]
    D --> E["Log: AP IP Address"]
    E --> F["Enable AP Mode (C_WiFi_APOn = 1)"]
    F --> G["Get & Log MAC Address"]
    G --> H["Log: Waiting for Client to Connect"]
    
    H --> I{Check Connected Clients}
    
    I -->|Client Connected| J["Log: Client has connected"]
    J --> K["Return true"]
    K --> Z((End))
    
    I -->|No Client| L["Check 1-Minute Timer"]
    
    L -->|Timer Expired| M["Log: No Client; Disabling Hotspot"]
    M --> N["Turn Off WiFi"]
    N --> O["Return false"]
    O --> Z
    
    L -->|Timer Running| P["Log: Still Waiting"]
    P --> H 
