#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ESP32Servo.h>
#include <SPI.h>
#include <MFRC522.h>

/* define hardware pins */
#define SS_PIN 4  
#define RST_PIN 15
#define BTN_PIN 5
#define SERVO_PIN 17
#define DHT22_PIN 16
#define ROWS_KEYPAD 4
#define COLS_KEYPAD 4
#define LCD_COLUMNS 16
#define LCD_ROWS 2   

/* servo motor */
Servo servo1;                
/* rfid reader */   
MFRC522 rfid(SS_PIN, RST_PIN);

/* keypad configuration */
char keyMap[ROWS_KEYPAD][COLS_KEYPAD] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

/* row and column pins for keypad */
uint8_t rowPins[ROWS_KEYPAD] = {13, 12, 14, 27};
uint8_t colPins[COLS_KEYPAD] = {26, 25, 33, 32};

/* lcd cursor position */
uint8_t LCD_CursorPosition = 0; 

/* password for access */
String Password = "134679";  

/* stores user input (for pin code) */   
String InputStr = "";           

/* stores authorized RFIDs */
String authorizedRFIDs = "7a5a3b80;";

Keypad keypad = Keypad(makeKeymap(keyMap), rowPins, colPins, ROWS_KEYPAD, COLS_KEYPAD); /* keypad object */
LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, LCD_ROWS); /* lcd object */
DHT dht22(DHT22_PIN, DHT22); /* temp sensor */

/* timers for tasks */
unsigned long lastKeypadTime = 0; 
unsigned long lastRFIDTime = 0; 
unsigned long lastTempTime = 0; 

/* max temperature outside */
#define max_temperature 50.0

void setup() {
  /* configure button pin as input */
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.begin(115200);

  /* initialize SPI communication */
  SPI.begin();
  /* initialize RFID reader */
  rfid.PCD_Init();

  /* attach servo motor */
  servo1.attach(SERVO_PIN);       
  /* initialize temperature sensor */
  dht22.begin();                  
  /* init lcd */ 
  lcd.init();                    
  lcd.backlight();                
  lcd.clear();
  lcd.setCursor(0, 0);
  /* message */
  lcd.print("Enter Password:");

  displayHelp();
}

void loop() {
  /* current time */
  unsigned long currentMillis = millis(); 

  /* check keypad input every 100 ms */
  if (currentMillis - lastKeypadTime >= 100) {
    lastKeypadTime = currentMillis;
    readKeypad();
  }

  /* check rfid every 500 ms */
  if (currentMillis - lastRFIDTime >= 500) {
    lastRFIDTime = currentMillis;
    readRFID();
  }

  /* check temperature every 2s */
  if (currentMillis - lastTempTime >= 2000) {
    lastTempTime = currentMillis;
    readTemperature();
  }

  /* check if button is pressed */
  checkButtonPress();

  /* handle serial commands */
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    SerialCommands(command);
  }
}

/* handle serial commands */
void SerialCommands(String command) {
  if (command == "1") { 
    addNewRFID();
  } else if (command == "2") {
    displayAuthorizedRFIDs();
  } else if (command == "3") {
    Serial.println("Manually opening the door...");
    openDoor();
     /* display available commands */
  } else if (command == "help") {
    displayHelp();
  } else {
    Serial.println("Invalid option. Type 'help' to see available commands.");
  }
}

/* function to display the help menu */
void displayHelp() {
  Serial.println("Available commands:");
  Serial.println("1. Add a new RFID");
  Serial.println("2. Display authorized RFIDs");
  Serial.println("3. Open door manually");
  Serial.println("help - Show this help menu");
}

/* function to display the list of authorized RFIDs */
void displayAuthorizedRFIDs() {
  Serial.println("\nAuthorized RFIDs:");
  if (authorizedRFIDs.length() == 0) {
    Serial.println("No RFIDs authorized.");
  } else {
    String rfid = "";
    for (char c : authorizedRFIDs) {
      if (c == ';') {
        Serial.println(rfid);
        rfid = "";
      } else {
        rfid += c;
      }
    }
  }
}

/* function to check if button is pressed */
void checkButtonPress() {
  /* open door if button is pressed */
  if (digitalRead(BTN_PIN) == LOW) {
    lcd.clear();
    lcd.print("Button Access");
    openDoor();
    resetSystem();
  }
}

void readKeypad() {
  /* read key from keypad */
  char key = keypad.getKey();
  if (key) {
    /* reset on D */
    if (key == 'D') {
      resetSystem();
      return;
    }

    /* add key to input */
    InputStr += key; 
    lcd.setCursor(LCD_CursorPosition++, 1);
    lcd.print(key);

    /* check password */
    if (LCD_CursorPosition == Password.length()) {
      if (InputStr == Password) {
        lcd.clear();
        lcd.print("Access Granted!");
        openDoor();
      } else {
        lcd.clear();
        lcd.print("Wrong Password!");
      }
      resetSystem();
    }
  }
}

/* function to read RFID  */
void readRFID() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    /* get RFID UID */
    String rfidUID = getRFID();
    Serial.println("RFID UID: " + rfidUID);

    if (isAuthorizedRFID(rfidUID)) {
      lcd.clear();
      lcd.print("RFID Access OK");
      openDoor();
    } else {
      lcd.clear();
      lcd.print("Access Denied");
      delay(2000);
      displayHelp();
      lcd.clear();
      lcd.print("More info in");
      lcd.setCursor(0, 1);
      lcd.print("Serial Monitor");
      delay(2000);
    }
    /* to prevent repeated re-detection of our card */
    rfid.PICC_HaltA();
    resetSystem();
  }
}

/* function to read and display temperature */
void readTemperature() {
  /* read temperature in celsius */
  float tempC = dht22.readTemperature();
  lcd.setCursor(10, 1);
  lcd.print(tempC, 1);
  lcd.print("C");
  /* if the temperature is too high, the door will open */
  if (tempC > max_temperature) {
    Serial.println("High temperature detected! Opening the door...");
    lcd.clear();
    lcd.print("Temp High! Open");
    openDoor();
    resetSystem();
  }
}

/* function to open the door */
void openDoor() {
  /* open the door for 5 seconds*/
  servo1.write(45);
  delay(5000);

  /* close the door */
  servo1.write(0);
}

/* function to get RFID UID as a string */
String getRFID() {
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    content += String(rfid.uid.uidByte[i], HEX);
  }
  return content;
}

/* function to check if rfid is in the list of authorized rfids */
bool isAuthorizedRFID(String rfidUID) {
  return authorizedRFIDs.indexOf(rfidUID + ";") >= 0;
}

/* function to add a new RFID to the authorized list */
void addNewRFID() {
  lcd.clear();
  lcd.print("Enter new RFID");
  Serial.println("Waiting for new RFID...");

  /* continuously waits for an RFID card to be presented to the reader */
  while (true) {
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
      String newRFID = getRFID();
      authorizedRFIDs += newRFID + ";";
      Serial.println("New RFID added: " + newRFID);
      lcd.clear();
      lcd.print("RFID Added!");
      resetSystem();
      return;
    }
  }
}

/* function to reset the system to its initial state */
void resetSystem() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  LCD_CursorPosition = 0;
  InputStr = "";
}

