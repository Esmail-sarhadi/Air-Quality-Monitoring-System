# Smart Air Quality Monitoring System 🌟

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Overview 📝

A comprehensive IoT-based air quality monitoring system built with ESP32. Features a modern, responsive web dashboard for real-time monitoring of various air quality parameters including temperature, humidity, CO, LPG, and CO2 levels.

## Features ⭐

### Hardware Capabilities 🛠️
- Temperature and humidity monitoring (DHT11)
- Carbon Monoxide detection (MQ7)
- LPG gas detection (MQ9)
- CO2 level monitoring (MQ135)
- Real-time sensor data processing
- WiFi connectivity

### Web Dashboard 🌐
- Modern, responsive design with glass-morphism UI
- Real-time data updates
- Interactive cards with hover effects
- Status indicators for different pollutant levels
- Animated value changes
- Connection status monitoring
- Mobile-friendly interface

## Hardware Requirements 📌

- ESP32 Development Board
- DHT11 Temperature & Humidity Sensor
- MQ7 Carbon Monoxide Sensor
- MQ9 LPG Gas Sensor
- MQ135 Air Quality Sensor
- Jumper Wires
- Power Supply

## Pin Configuration 🔌

```
DHT_PIN    -> GPIO32 (Temperature/Humidity Sensor)
MQ135_PIN  -> GPIO34 (CO2 Sensor)
MQ9_PIN    -> GPIO33 (LPG Sensor)
MQ7_PIN    -> GPIO35 (CO Sensor)
```

## Software Dependencies 📚

### ESP32 Libraries
- WiFi.h
- WebServer.h
- SPIFFS.h
- ArduinoJson.h
- DHT.h

### Web Dashboard Dependencies
- Animate.css
- Google Fonts (Vazirmatn)

## Installation & Setup 🔧

1. Clone the repository:
   ```bash
   git clone https://github.com/YourUsername/air-quality-monitor.git
   ```

2. Install required Arduino libraries through the Arduino IDE Library Manager

3. Configure WiFi credentials in the ESP32 code:
   ```cpp
   const char* ssid = "Your_SSID";
   const char* password = "Your_Password";
   ```

4. Upload the web interface files to SPIFFS:
   - Create a 'data' folder in your project
   - Copy index.html into the data folder
   - Use the ESP32 Sketch Data Upload tool

5. Upload the code to your ESP32

## Web Interface Features 🎨

### Real-time Monitoring
- Temperature (°C)
- Relative Humidity (%)
- Carbon Monoxide (PPM)
- LPG Gas (PPM)
- Carbon Dioxide (PPM)
- Overall Air Quality Status

### Status Indicators
- Good: Safe levels 😊
- Fair: Warning levels 😐
- Poor: Dangerous levels 😷
- Very Poor: Critical levels 🤢

## Sensor Thresholds 📊

### CO2 Levels (PPM)
- Good: < 100
- Fair: 100-250
- Poor: 250-500
- Very Poor: > 500

### Other Parameters
- Customizable thresholds for CO and LPG
- Real-time status updates based on sensor readings

## API Endpoints 🌐

- `/` - Serves the main dashboard
- `/sensor-data` - Returns JSON with current sensor readings
- `/styles.css` - CSS styles
- `/script.js` - JavaScript functions

## Contributing 🤝

Contributions are welcome! Please feel free to submit a Pull Request.

## Author ✍️

**Your Name**
- GitHub: [@YourUsername](https://github.com/YourUsername)

## License 📄

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments 🙏

- Thanks to the ESP32 community
- Web design inspired by modern glass-morphism trends
- Special thanks to all contributors

---
⭐ Don't forget to star this repo if you find it helpful!
