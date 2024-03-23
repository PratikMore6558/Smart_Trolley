#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
//kaam karay bro
constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4; 

MFRC522 rfid(D4, D3); // SS_PIN, RST_PIN
MFRC522::MIFARE_Key key;
String tag;

// Construct an LCD object and pass it the 
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {

  // The begin call takes the width and height. This
  // Should match the number provided to the constructor.
  // lcd.begin(16,2);
  lcd.init();
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  // Turn on the backlight.
  lcd.backlight();
  Serial.println("start");
  lcd.setCursor(1, 0);

  lcd.print("Starting the system.");
  // Move the cursor characters to the right and
  // zero characters down (line 1).
  // lcd.setCursor(5, 0);

  // Print HELLO to the screen, starting at 5,0.
  // lcd.print("HELLO");

  // Move the cursor to the next line and print
  // WORLD.
  // lcd.setCursor(5, 1);      
  // lcd.print("WORLD");
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    lcd.setCursor(1, 1);

  // Print HELLO to the screen, starting at 5,0.
    lcd.print(tag);
    Serial.println(tag);
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
