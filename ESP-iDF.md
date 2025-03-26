# HOW TO CREATE PROJECT  
---  
1. Open VS Code
2. New Project
   1. check in search bar ESP-IDF v5.1.4 and Enter
3. Enter Project Details
   1. Choose ESP-IDF Board - **ESP-WROVER-KIT 3.3V**
4. Click on Create Template
**NOTE - Under main --> Cmakelist --> Add header files which you are going to use in your project/if you create any header file**
5. Press F1 / "idf.py menuconfig" use cammand for open *menuconfig*
6. left side tab you get *sdkcongif* go into that and change ***Config FREERTOS HZ to 1000;* bydefault it is 100**
7. Again open menuconfig use **5**
8. Check various properties:
   1. Autostart Arduino setup & loop on boot --> it include void loop and void setup **Based on project req**
   2. Serial Flasher Configuration
      1. Set Flash SPI Speed = 80
      2. set Flash Size = 16 MB
   3. Partition Table --> create once for one project, it contain Memory Architecture
   4. componant Configuration
      1. Log output -
           1. verbose (contain detail info)
           2. debug (use for testing)
           3. info (data)
           4. warning
           5. error  
 
      
