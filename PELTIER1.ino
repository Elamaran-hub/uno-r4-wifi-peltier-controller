#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2                        // digital pin connected to Temp sensor DATA
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
  sensors.begin();                           // start the Temp sensor
  pinMode(9, OUTPUT); 

  //For LCD    
    lcd.init();         // Initialize the LCD
  lcd.backlight();    // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("Peltier Control");
  delay(2000);
  lcd.clear();
}
void loop() {
  sensors.requestTemperatures();             // sensor to reads temperature
  float tempC = sensors.getTempCByIndex(0); // get temperature in °C

  // Decide desired voltage for Peltier
  float desiredVoltage = 4.0;  // Can give anything 4,8,12V
  int pwmValue = (int)((desiredVoltage / 12.0) * 255); // PWM calculation formula (0-255)

  analogWrite(9, pwmValue); // send PWM(from arduino) to MOSFET
// Map temp to voltage-like deflection
float voltageDeflection = (tempC / 50.0) * 5.0;  // 50°C = 5V full scale

//Printing on Serial Monitor
Serial.print("Temp: ");
Serial.print(tempC);
Serial.print(" C, ");
Serial.print("Voltage deflection: ");
Serial.println(voltageDeflection);
delay(1000); 
  //Display on LCD
   lcd.setCursor(0, 0);
   lcd.print("Hi,No issues");
  lcd.setCursor(0, 1);
     lcd.print("voidloop working");
     delay(2000);
     lcd.clear();
    lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print((char)223);       // for degree symbol           
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("VoltDef: ");
  lcd.print(voltageDeflection, 2);
  lcd.print("V");
  delay(1500);
}