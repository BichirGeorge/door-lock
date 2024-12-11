# Door lock
## **Introduction**  
This project is inspired by the scene in *The Amazing Spider-Man*, where Peter Parker uses a custom lock for his room. That concept gave me the idea to design a smart door lock system, integrating multiple technologies.  

The smart lock offers a variety of unlocking options. By incorporating RFID authentication, a PIN system, and environmental monitoring, it serves as a practical for home security.  

---

## **General Description**  
![image](https://github.com/user-attachments/assets/83b4a5b7-d232-4fd6-acaa-2fd1f797689b)


---

## **Hardware Design**  
### **Components**  
- ESP32
- 4x4 Matrix Keypad 
- RC522 RFID Module 
- MG90S Servo Motor
- LCD1602 with I2C Interface 
- DHT22 Sensor  
- Passive Buzzer (3.3V)
- Push Button  
- Jumper Wires 

### **Circuit Diagram**  
![image](https://github.com/user-attachments/assets/7184c504-508c-4e1a-8a41-bd99377868ae)

### **Bill Of Materials
| Component             | Source                                                                                                                                                       | Datasheet |
| --------------------- |:------------------------------------------------------------------------------------------------------------------------------------------------------------:| ---------:|
| esp-wroom-32          | [Placă de Dezvoltare ESP32 cu WiFi și Bluetooth 4.2](https://www.optimusdigital.ro/ro/placi-cu-bluetooth/4371-placa-de-dezvoltare-esp32-cu-wifi-i-bluetooth-42.html?search_query=ESP32+&results=28)|[esp-wroom-32.pdf](https://github.com/user-attachments/files/18102841/esp-wroom-32_datasheet_en.pdf)|
| 4x4 Keypad            | [Tastatura matriceala 4x4 cu conector pin de tip mama](https://www.optimusdigital.ro/ro/senzori-senzori-de-atingere/470-tastatura-matriceala-4x4-cu-conector-pin-de-tip-mama.html?search_query=4x4+keypad&results=4) |[4x4-Matrix-Keypad.pdf](https://github.com/user-attachments/files/18102987/27899-4x4-Matrix-Membrane-Keypad-v1.2.pdf)|
| RC522 RFID Module     | [Modul RFID RC522](https://www.optimusdigital.ro/ro/wireless-rfid/67-modul-cititor-rfid-mfrc522.html?search_query=rfid+rc522&results=5)|[RC522.pdf](https://github.com/user-attachments/files/18102988/RC522.pdf)|
| MG90S Servo Motor     | [Servomotor MG90S](https://www.optimusdigital.ro/ro/motoare-servomotoare/271-servomotor-mg90s.html?search_query=mg90s&results=1)|[MG90S.pdf](https://github.com/user-attachments/files/18102995/MG90S_Tower-Pro.pdf)|
| LCD1602 I2C           | [LCD 1602 cu Interfata I2C si Backlight Albastru](https://www.optimusdigital.ro/ro/optoelectronice-lcd-uri/2894-lcd-cu-interfata-i2c-si-backlight-albastru.html?search_query=lcd+i2c&results=17)                |           |
| DHT22 Sensor          | [Senzor de Temperatură și Umiditate DHT22/AM2302B](https://www.optimusdigital.ro/ro/senzori-senzori-de-temperatura/3157-senzor-de-temperatura-i-umiditate-dht22am2302b.html?search_query=dht22&results=6)        |           |
| Passive Buzzer (3.3V) | [Buzzer Pasiv de 3.3V sau 3V](https://www.optimusdigital.ro/ro/audio-buzzere/12247-buzzer-pasiv-de-33v-sau-3v.html?search_query=buzzer+3&results=62)                                        |           |
| Push Button           | [Buton cu Capac Pătrat Negru](https://www.optimusdigital.ro/ro/butoane-i-comutatoare/1117-buton-cu-capac-patrat-negru.html?search_query=buton&results=215)                                  |           |

---

## **Software Design**  
The code is written in the Arduino IDE and includes the following functionalities:  
- Keypad Input: Detects and validates PIN input.  
- RFID Authentication: Reads and verifies card IDs.  
- Servo Control: Unlocks or locks based on input.  
- Timeout Handling: Resets the system after inactivity.  
- Error Feedback: Activates the buzzer.  
- DHT22 Monitoring: ----.  

### **Libraries Used**  
- **Keypad Library** for keypad input.  
- **Adafruit LCD I2C Library** for LCD1602.  
- **MFRC522 Library** for RFID functionality.  
- **DHT Sensor Library** for DHT22 temperature and humidity readings.  

---

## **Results**  

---

## **Conclusions**  

---

## **Journal**  

---

## **Resources**  
