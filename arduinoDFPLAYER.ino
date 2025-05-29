#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial espSerial(5, 6); // RX, TX (Connect to ESP32-CAM Serial1 pins)
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX (Connect to DFPlayer module)
DFRobotDFPlayerMini myDFPlayer;

String receivedLabel = ""; // To store the received object label

// Function prototype declaration
void playSound(String label);

void setup() {
  // Begin Serial communication with ESP32-CAM
  espSerial.begin(115200); // Match this with the ESP32-CAM Serial1 baud rate
  Serial.begin(115200);

  // Begin communication with the DFPlayer
  mySoftwareSerial.begin(9600);
  
  // Debug print to check DFPlayer initialization
  Serial.println("Checking DFPlayer communication...");
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  // Use software serial to communicate with DFPlayer
    Serial.println(F("Unable to begin DFPlayer module!"));
    while(true); // If DFPlayer initialization fails, halt the execution
  }
  
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(20);  // Set volume level (0-30)
}

void loop() {
  Serial.print("label received: ");
  if (espSerial.available()) {
  char c = espSerial.read();  // Read a character from espSerial

  Serial.print(c);  // Debug: Print each received character

  if (c == '\n') {
    Serial.print("Full label received: ");
    Serial.println(receivedLabel);

    // Play sound based on received label
    playSound(receivedLabel);

    receivedLabel = "";  // Clear label string for next label
  } else {
    receivedLabel += c;  // Append each character to the label string
  }
}

}

// Function to play sound based on the object label
void playSound(String label) {
  if (label == "Bottle") {
    myDFPlayer.play(1);  // Play audio file 0001.mp3 for 'Bottle'
  }
  else if (label == "Mobile") {
    myDFPlayer.play(2);  // Play audio file 0002.mp3 for 'Mobile'
  }
  else if (label == "Dustbin") {
    myDFPlayer.play(3);  // Play audio file 0003.mp3 for 'Dustbin'
  }
  else if (label == "Pot_hole") {
    myDFPlayer.play(4);  // Play audio file 0004.mp3 for 'Pot-hole'
  }
  else {
    Serial.println("Unknown label, no sound to play.");
  }
}