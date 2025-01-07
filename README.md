# Door lock
## **Introduction**  
This project is inspired by the scene in *The Amazing Spider-Man*, where Peter Parker uses a custom lock for his room. That concept gave me the idea to design a smart door lock system, integrating multiple technologies.  

The smart lock offers a variety of unlocking options. By incorporating RFID authentication, a PIN system, and environmental monitoring, it serves as a practical for home security.  

---

## **General Description**  

### **Block diagram** 
![image](https://github.com/user-attachments/assets/4b978700-277b-4383-a625-a903e852e739)

---

## **Hardware Design**  
### **Components**  
- ESP32
- 4x4 Matrix Keypad 
- RC522 RFID Module 
- MG90S Servo Motor
- LCD1602 with I2C Interface 
- DHT22 Sensor
- Push Button  
- Jumper Wires 

### **Circuit Diagram**  
![image](https://github.com/user-attachments/assets/fa638d1b-7151-4399-ab14-fe481dd94a80)

### **Bill Of Materials**
|#|Quantity| Component             | Source                                                                                                                                                       | Datasheet |
|--|--------| --------------------- |:------------------------------------------------------------------------------------------------------------------------------------------------------------:| ---------:|
|1|1| esp-wroom-32          | [Placă de Dezvoltare ESP32 cu WiFi și Bluetooth 4.2](https://www.optimusdigital.ro/ro/placi-cu-bluetooth/4371-placa-de-dezvoltare-esp32-cu-wifi-i-bluetooth-42.html?search_query=ESP32+&results=28)|[esp-wroom-32.pdf](https://github.com/user-attachments/files/18102841/esp-wroom-32_datasheet_en.pdf)|
|2|1| 4x4 Keypad            | [Tastatura matriceala 4x4 cu conector pin de tip mama](https://www.optimusdigital.ro/ro/senzori-senzori-de-atingere/470-tastatura-matriceala-4x4-cu-conector-pin-de-tip-mama.html?search_query=4x4+keypad&results=4) |[4x4-Matrix-Keypad.pdf](https://github.com/user-attachments/files/18102987/27899-4x4-Matrix-Membrane-Keypad-v1.2.pdf)|
|3|1| RC522 RFID Module     | [Modul RFID RC522](https://www.optimusdigital.ro/ro/wireless-rfid/67-modul-cititor-rfid-mfrc522.html?search_query=rfid+rc522&results=5)|[RC522.pdf](https://github.com/user-attachments/files/18102988/RC522.pdf)|
|4|1| MG90S Servo Motor     | [Servomotor MG90S](https://www.optimusdigital.ro/ro/motoare-servomotoare/271-servomotor-mg90s.html?search_query=mg90s&results=1)|[MG90S.pdf](https://github.com/user-attachments/files/18102995/MG90S_Tower-Pro.pdf)|
|5|1| LCD1602 I2C           | [LCD 1602 cu Interfata I2C si Backlight Albastru](https://www.optimusdigital.ro/ro/optoelectronice-lcd-uri/2894-lcd-cu-interfata-i2c-si-backlight-albastru.html?search_query=lcd+i2c&results=17)|[I2C_1602_LCD.pdf](https://github.com/user-attachments/files/18103080/I2C_1602_LCD.pdf)|
|6|1| DHT22 Sensor          | [Senzor de Temperatură și Umiditate DHT22/AM2302B](https://www.optimusdigital.ro/ro/senzori-senzori-de-temperatura/3157-senzor-de-temperatura-i-umiditate-dht22am2302b.html?search_query=dht22&results=6)|[DHT22/AM2302.pdf](https://github.com/user-attachments/files/18103083/Digital%2Bhumidity%2Band%2Btemperature%2Bsensor%2BAM2302.pdf)|
|7|1| Push Button           | [Buton cu Capac Pătrat Negru](https://www.optimusdigital.ro/ro/butoane-i-comutatoare/1117-buton-cu-capac-patrat-negru.html?search_query=buton&results=215)                                  |     -     |

### **Hardware Functionality Description**
| **Device**            | **Pin Function**          | **GPIO Pin(s)**             | **Power Supply**     |
|-----------------------|---------------------------|-----------------------------|----------------------|
| **RFID RC522**        | SDA (Serial Data)         | GPIO 4                      | 3.3V, GND            |
|                       | RST (Reset)               | GPIO 15                     | 3.3V, GND            |
|                       | SCK (Serial Clock)        | GPIO 18                     | 3.3V, GND            |
|                       | MOSI (Master Out Slave In)| GPIO 23                     | 3.3V, GND            |
|                       | MISO (Master In Slave Out)| GPIO 19                     | 3.3V, GND            |
| **4x4 Keypad**        | Row 1                     | GPIO 13                     | 3.3V, GND            |
|                       | Row 2                     | GPIO 12                     | 3.3V, GND            |
|                       | Row 3                     | GPIO 14                     | 3.3V, GND            |
|                       | Row 4                     | GPIO 27                     | 3.3V, GND            |
|                       | Column 1                  | GPIO 26                     | 3.3V, GND            |
|                       | Column 2                  | GPIO 25                     | 3.3V, GND            |
|                       | Column 3                  | GPIO 33                     | 3.3V, GND            |
|                       | Column 4                  | GPIO 32                     | 3.3V, GND            |
| **DHT22 Sensor**      | Data                      | GPIO 16                     | 3.3V, GND            |
| **Servo Motor**       | Control (PWM)             | GPIO 17                     | 5V, GND              |
| **Push Button**       | State                     | GPIO 5                      | GND                  |
| **LCD 1602 (I2C)**    | SDA (Data)                | GPIO 21                     | 5V, GND              |
|                       | SCL (Clock)               | GPIO 22                     | 5V, GND              |

---

## **Software Design**  
The code is written in the Arduino IDE and includes the following functionalities:  
- Keypad Input: Detects and validates PIN input.  
- RFID Authentication: Reads and verifies card IDs.  
- Servo Control: Unlocks or locks based on input.  
- Timeout Handling: Resets the system after inactivity.  
- DHT22 Monitoring: Displays the temperature and opens the door if it gets too hot.

### **Libraries Used**  
- **Keypad Library** - for keypad input.  
- **Adafruit LCD I2C Library** - for LCD1602.  
- **MFRC522 Library** - for RFID functionality.  
- **DHT Sensor Library** - for DHT22 temperature and humidity readings.  
- **SPI** - for SPI communication (used for RFID).
- **ESP32Servo** - for controlling servo motors with the ESP32. 
---

## **Results**  
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/VQCF18vdndk/0.jpg)](https://www.youtube.com/watch?v=VQCF18vdndk)
---

## **Conclusions**  
I learned how to integrate RFID, PIN, and sensors with the ESP32, improving my skills in hardware-software interaction and creating a secure system. 

---

## **Journal**  

---

## **Resources**  
