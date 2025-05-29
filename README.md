# 👁️‍🗨️ Smart Vision Stick #
The Smart Vision Stick is an innovative assistive device designed to enhance the mobility, awareness, and safety of visually impaired individuals. Leveraging modern sensors and IoT technologies, this smart stick provides real-time obstacle detection, speech feedback, fall alerts, and GPS tracking to empower safer navigation in dynamic environments.

## 🧠 Overview ##
Traditional white canes are limited in functionality. The Smart Vision Stick enhances their utility by incorporating:

* Real-time object detection
* Audio feedback through Text-to-Speech
* Water puddle and wet surface detection
* Fall detection with emergency alerts
* GPS-based live location sharing

## ⚙️ Key Features ##
### 🔍 Object Detection with ESP32-CAM ###
Uses a camera module to detect objects in front of the user and identify obstacles not easily noticeable by touch.
### 🗣️ Text-to-Speech (TTS) ###
Audibly communicates detected objects to the user using the DFPlayer Mini and a speaker, enhancing situational awareness.
### 💧 Water Level Detection ###
Detects puddles or wet surfaces using a water sensor and alerts users via a buzzer to avoid slipping hazards.
### ⚠️ Fall Detection ###
Detects sudden vibrations indicating a fall using a vibration sensor, and sends alerts to a predefined number using Telegram Bot via ESP8266.
### 📍 GPS Tracking ###
Tracks the real-time location using a GPS module and sends live updates to caregivers through a Telegram Bot.

## Key Component ##
|  Component       | Description                        |
|------------------|-----------------------------------|
| ESP32-CAM        | Used for object detection          |
| DFPlayer Mini    | Plays audio for text-to-speech     |
| GPS Module       | Tracks real-time location          |
| Water Sensor     | Detects puddles or wet surfaces    |
| Vibration Sensor | Detects stick falling              |
| ESP8266          | Sends alerts via Telegram          |


## 🖼️ Images & Results ##
Device Overview

Object Detection
Object identified using ESP32-CAM and TTS feedback given.

Emergency Alert
Fall or emergency triggers Telegram Bot to send location and alert to caregiver.

Fall Detection
Telegram Bot sends fall alert upon vibration detection.

## 📽️ Demo Video Drive Link ##
https://drive.google.com/drive/folders/1-13hRNUz3HE2Cwgp30zrie-Xn70yubLq 

## 📁 Folder Structure ##

<pre><code> 
  Smart-Vision-Stick/ 
  ├── esp32-cam-object-detection.ino/
  ├── arduinoDFPLAYER.ino/
  ├── Vibration_gps_water.ino/
  ├── updated_for_espCAM.ino/
  ├── Audio/ 
  ├── images_of_bottle_final_object/ 
  ├── images_of_dustbin_object/ 
  ├── README.md 
</code></pre>

## 🚀 Future Enhancements ##
* Add obstacle classification (e.g., "person", "car", "stair").
* Include ultrasonic depth sensing for terrain assessment.
* Use GSM module as an alternative to Wi-Fi-based alerts.
* Optimize energy consumption for longer battery life.

