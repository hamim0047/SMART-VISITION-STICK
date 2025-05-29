#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Your WiFi credentials
const char* ssid = "Amin";
const char* password = "Sayeed@1999";

// Telegram BOT Token (from BotFather)
#define BOT_TOKEN "7507034683:AAFgmLtYWn5vXEJIY-qj6t2O7tbiUXOZgqA"

// Your chat ID
String chat_id = "7736501349";

// Initialize the client and the bot
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

// GPS setup
TinyGPSPlus gps;
SoftwareSerial ss(D1, D2); // RX (to GPS TX at D2), TX (to GPS RX at D1)

// Button, vibration sensor, water level sensor, and buzzer pin
const int vibrationPin = D5;   // Vibration sensor
const int buttonPin = D6;      // Button
const int waterSensorPin = D7; // Water level sensor
const int buzzerPin = D8;      // Buzzer pin
int vibrationState = LOW;
int buttonState = LOW;
int waterSensorState = LOW;

void setup() {
    Serial.begin(115200);
    ss.begin(9600); // Initialize GPS module baud rate
    WiFi.begin(ssid, password);

    // Connect to Wi-Fi
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to Wi-Fi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Set pins as input/output
    pinMode(vibrationPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP); // Button uses INPUT_PULLUP for stability
    pinMode(waterSensorPin, INPUT);    // Set water sensor pin as input
    pinMode(buzzerPin, OUTPUT);         // Set buzzer pin as output
    digitalWrite(buzzerPin, LOW);       // Buzzer initially off

    // Send a test message
    bot.sendMessage(chat_id, "Stick monitoring started!", "");
}

void loop() {
    // Read vibration sensor, button state, and water sensor state
    vibrationState = digitalRead(vibrationPin);
    buttonState = digitalRead(buttonPin);
    waterSensorState = digitalRead(waterSensorPin); // Read water sensor state

    // Handle GPS data
    while (ss.available()) {
        char c = ss.read();
        gps.encode(c); // Feed data into the GPS library
    }

    // Check for vibration
    if (vibrationState == HIGH) {
        sendAlertToTelegram("Alert: The stick has fallen!");
        delay(5000); // Avoid multiple notifications
    }

    // Check if the button is pressed
    if (buttonState == LOW) { // Button pressed (LOW because of INPUT_PULLUP)
        sendLocationToTelegram();
        delay(5000); // Avoid multiple messages
    }

    // Check for water detection and trigger buzzer if detected
    if (waterSensorState == HIGH) { // Assuming HIGH indicates water detected
        triggerBuzzer(); // Trigger the buzzer
        delay(5000); // Avoid multiple notifications
    }

    // Run Telegram bot in case you need to process incoming messages
    bot.longPoll = 0;
}

// Function to send a message to Telegram
void sendAlertToTelegram(String message) {
    Serial.println("Sending alert to Telegram...");
    client.setInsecure();
    if (client.connect("api.telegram.org", 443)) {
        String url = "/bot" + String(BOT_TOKEN) + "/sendMessage?chat_id=" + chat_id + "&text=" + message;
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: api.telegram.org\r\n" +
                     "Connection: close\r\n\r\n");
        delay(500);
        while (client.available()) {
            String line = client.readStringUntil('\n');
            Serial.println(line);
        }
    } else {
        Serial.println("Connection failed");
    }
}

// Function to send GPS location to Telegram
void sendLocationToTelegram() {
    if (gps.location.isValid()) {
        String latitude = String(gps.location.lat(), 6);
        String longitude = String(gps.location.lng(), 6);
        String locationMessage = "Danger! Location: https://maps.google.com/?q=" + latitude + "," + longitude;
        sendAlertToTelegram(locationMessage);
    } else {
        Serial.println("GPS signal not found!");
        sendAlertToTelegram("GPS signal not found!");
    }
}

// Function to trigger the buzzer when water is detected
void triggerBuzzer() {
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
    delay(1000);                    // Buzzer on for 1 second
    digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
    Serial.println("Buzzer alert triggered for water detection.");
}



