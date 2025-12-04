#include <WiFiS3.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
#define PELTIER_PIN 9

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float desiredVoltage = 8.0; // Default 6V
float tempC = 0.0;

WiFiServer server(80);

// AP credentials
char ssid[] = "Peltier_Control_AP";
char pass[] = "12345678"; // at least 8 chars

void setup() {
  Serial.begin(9600);
  sensors.begin();
  lcd.init();
  lcd.backlight();

  pinMode(PELTIER_PIN, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Starting Wifi...");
  delay(3500);
  // Start Access Point
  if (WiFi.beginAP(ssid, pass) != WL_AP_LISTENING) {
    Serial.println("AP failed!");
    lcd.setCursor(0, 1);
    lcd.print("AP Failed!");
    while (true);
  }

  IPAddress ip = WiFi.localIP();
  Serial.print("AP started! IP: ");
  Serial.println(ip);
  lcd.clear();
  lcd.print("AP: ");
  lcd.print(ssid);
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.print(ip);

  server.begin();
  delay(15000);
  lcd.clear();
}

void loop() {
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);

  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("slider=") != -1) {
      int index = request.indexOf("slider=") + 7;
      String valueStr = request.substring(index);
      int sliderValue = valueStr.toInt();
      desiredVoltage = (sliderValue / 100.0) * 12.0;
    }

    // Apply PWM
    int pwmValue = (int)((desiredVoltage / 12.0) * 255);
    analogWrite(PELTIER_PIN, pwmValue);

    // HTML Page
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<html><head><title>Peltier Control</title>");
    client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
    client.println("</head><body style='text-align:center;font-family:Arial;'>");
    client.println("<h2>Peltier Voltage Control</h2>");
    client.print("<p>Temperature: ");
    client.print(tempC);
    client.println(" °C</p>");
    client.print("<p>Voltage: ");
    client.print(desiredVoltage);
    client.println(" V</p>");
    client.println("<form action='/' method='get'>");
    client.print("<input type='range' name='slider' min='0' max='100' value='");
    client.print((int)((desiredVoltage / 12.0) * 100));
    client.println("' onchange='this.form.submit()' style='width:80%;'>");
    client.println("</form>");
    client.println("</body></html>");
    client.stop();
  }

  // LCD Display
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(tempC, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Volt:");
  lcd.print(desiredVoltage, 1);
  lcd.print("V    ");

  delay(1000);
}
