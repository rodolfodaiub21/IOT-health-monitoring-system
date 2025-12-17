# IoT Health Monitoring System

An IoT-based health monitoring system that collects real-time data from multiple sensors and displays it on a web dashboard.  
The system monitors **heart rate**, **temperature**, **humidity**, and **tilt/movement**, using an embedded device and a **Flask-based web server** for visualization.

---

## 🚀 Features

- ❤️ Heartbeat (pulse) monitoring  
- 🌡️ Temperature monitoring  
- 💧 Humidity monitoring  
- 📐 Tilt / movement detection  
- 🌐 Web dashboard built with HTML  
- 🔄 Real-time data updates via Flask backend  

---

## 🗂️ Project Structure

```text
IOT-health-monitoring-system/
│
├── sensor_gathering/
│   └── (sensor reading and data transmission code)
│
│
├── Server.py
│   └── Flask backend server
│
├── index.html
│   └── Web dashboard interface
│
└── README.md
