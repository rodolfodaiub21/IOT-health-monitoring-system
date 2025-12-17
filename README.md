# IoT Health Monitoring System

An Internet of Things (IoT)–based health monitoring system that collects real-time physiological and environmental data and displays it on a web dashboard. The system monitors **heart rate**, **temperature**, **humidity**, and **tilt/movement** using embedded sensors and sends the data to a server for visualization and analysis.

---

## Features

- ❤️ **Heart Rate Monitoring** – Measures pulse/heartbeat in real time  
- 🌡️ **Temperature Monitoring** – Tracks ambient or body temperature  
- 💧 **Humidity Monitoring** – Measures environmental humidity  
- 📐 **Tilt Detection** – Detects movement or abnormal posture using a tilt sensor  
- 🌐 **Web Dashboard** – Displays live sensor data through a web-based interface  
- 📡 **Real-Time Data Transmission** – Sensor data is sent continuously to the server  

---

## 🛠️ System Architecture

The system is composed of three main components:

1. **Embedded Device (IoT Node)**  
   - Collects sensor data (heartbeat, temperature, humidity, tilt)
   - Sends data to the server over the network

2. **Backend Server**  
   - Receives sensor data
   - Processes and stores incoming measurements
   - Exposes endpoints for the dashboard

3. **Web Dashboard**  
   - Displays real-time and historical data
   - Allows remote monitoring of health metrics

---

## 🔌 Hardware Components

- Microcontroller Arduino and Raspberry PI
- Heartbeat (Pulse) Sensor
- Temperature & Humidity Sensor (e.g., DHT series)
- Tilt Sensor
- Power supply and wiring components

---

## 💻 Software Stack

- **Embedded Programming:** C/Arduino framework  
- **Backend:** Python (Flask)  
- **Frontend:** HTML & CSS
- **Communication:** HTTP / Serial / Wi-Fi  

---

