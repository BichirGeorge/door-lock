# door-lock
## **Introduction**  
This project is inspired by the scene in *The Amazing Spider-Man*, where Peter Parker uses a custom lock for his room. That concept gave me the idea to design a smart door lock system, integrating multiple technologies.  

The smart lock offers a variety of unlocking options. By incorporating RFID authentication, a PIN system, and environmental monitoring, it serves as a practical for home security.  

---

## **General Description**  

---

## **Hardware Design**  
### **Components**  
- ESP32
- 4x4 Matrix Keypad 
- RC522 RFID Module 
- MG90S Servo Motor
- LCD1602 with I2C Interface 
- DHT22 Sensor  
- Pasive Buzzer (3.3V)
- Push Button  
- Jumper Wires 

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
