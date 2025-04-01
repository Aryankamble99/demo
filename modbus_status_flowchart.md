```mermaid 
graph TD;
    A[Start] --> B[Execute Modbus Task]
    B --> C[Check if Slave ID, Baudrate, or Parity Changed]
    
    C -- Yes --> D[Update Serial Settings & Restart Modbus]
    D --> E[Save New Parameters to EEPROM]
    E --> F[Set F_SaveModbus = True]
    
    C -- No --> G[Check & Update AC Parameters]
    
    G -- AC Parameter Changed --> H[Update AC Variable]
    H --> I[Log & Save Parameter]
    I --> F
    
    G -- No Change --> J[Check & Update Relay States]
    
    J -- Relay State Changed --> K[Turn Relay On/Off]
    K --> L[Update Relay State Variable]
    
    J -- No Change --> M[Update Sensor Data in Modbus Registers]
    
    M --> N[Check If AC Command Needs Resending]
    
    N -- Yes --> O[Reset Command Register & Set ACvals = 1]
    O --> P[Save Modbus Configuration if Needed]
    
    P -- F_SaveModbus is True --> Q[Set C_SaveModbus = 1]
    
    P --> R[Update AC Settings]
    
    R --> S[End]

