# Smoke Detector Using IoT 🚨

An Internet of Things (IoT)-enabled smoke and gas detection system using **ESP8266 (NodeMCU)** and **MQ-2 sensor**. The system continuously monitors air quality, detects unusual smoke/gas levels, and sends data to the cloud for visualization and remote monitoring.  

---

## ✨ Features
- Real-time smoke and gas monitoring with MQ-2 sensor  
- Local buzzer + LED alarm system  
- Sends data to **Adafruit IO** via MQTT  
- Remote dashboard for live monitoring and historical data  
- Python client for logging data and desktop notifications  

---

## 🛠️ Hardware
- ESP8266 NodeMCU  
- MQ-2 Gas/Smoke Sensor  
- Buzzer  
- LED + 220Ω resistor  
- Jumper wires + Breadboard  

---

## ⚡ Wiring
- **MQ-2 Sensor**
  - AO → A0 (NodeMCU)  
  - VCC → 3V3  
  - GND → G  

- **Buzzer**
  - + → D5  
  - - → G  

- **LED**
  - Anode → D6 via 220Ω resistor  
  - Cathode → G  

---

## 📷 Wiring Diagram
![Wiring Diagram](docs/wiring_diagram.png)

---

## ☁️ Cloud Setup (Adafruit IO)
1. Sign up at [Adafruit IO](https://io.adafruit.com/).  
2. Create feeds:
   - `smoke_raw`  
   - `air_quality_pct`  
   - `alarm`  
   - (Optional) `smoke_threshold`  
3. Copy your **AIO Username** and **AIO Key**.  

---

## 💻 Firmware (ESP8266)
Code is in [`firmware/esp8266_mq2_smoke_detector.ino`](firmware/esp8266_mq2_smoke_detector.ino).  

**Setup in Arduino IDE:**
1. Install ESP8266 board support via Boards Manager.  
2. Install `Adafruit MQTT Library`.  
3. Open the `.ino` file, set your WiFi & Adafruit IO credentials.  
4. Upload to NodeMCU.  

---

## 🐍 Python Client
Code is in [`client/monitor_client.py`](client/monitor_client.py).  

**Install dependencies:**
```bash
pip install paho-mqtt plyer matplotlib
Run:
python client/monitor_client.py
✔ Logs data to smoke_log.csv
✔ Sends desktop notifications on alarms
✔ Can plot live air quality data

📂 Repository Structure

smoke-detector-iot/
│
├── firmware/                        # Arduino code for ESP8266
│   └── esp8266_mq2_smoke_detector.ino
│
├── client/                          # Python client for monitoring
│   └── monitor_client.py
│
├── docs/                            # Documentation files
│   └── wiring_diagram.png
│
├── .gitignore                       # Ignore build/OS files
├── .gitattributes                   # Force GitHub to count Arduino + Python
├── README.md                        # Full project documentation


💻 Installation

1. Clone the Repository

git clone https://github.com/your-username/smoke-detector-iot.git
cd smoke-detector-iot


---

2. Arduino Firmware (ESP8266)

1. Open Arduino IDE.


2. Go to File → Open and select:



firmware/esp8266_mq2_smoke_detector.ino

3. Install required libraries:

Adafruit MQTT Library

ESP8266 Board Support (via Boards Manager)



4. Edit the .ino file and set your WiFi credentials and Adafruit IO credentials:



#define WIFI_SSID     "YOUR_WIFI_SSID"
#define WIFI_PASS     "YOUR_WIFI_PASSWORD"
#define AIO_USERNAME "YOUR_AIO_USERNAME"
#define AIO_KEY      "YOUR_AIO_KEY"

5. Select Board → NodeMCU 1.0 (ESP-12E) and the correct Port.


6. Click Upload to flash the firmware to your ESP8266.




---

3. Python Client

1. Make sure you have Python 3.x installed.


2. Install required libraries:



pip install paho-mqtt plyer matplotlib

3. Edit the Python file with your Adafruit IO credentials:



AIO_USERNAME = "YOUR_AIO_USERNAME"
AIO_KEY = "YOUR_AIO_KEY"

4. Run the client:



python client/monitor_client.py

Logs data to smoke_log.csv.

Shows desktop notifications when smoke/gas threshold is exceeded.

Optional live plotting of air quality readings.



---

4. Adafruit IO Setup

1. Sign up at Adafruit IO.


2. Create feeds:

smoke_raw

air_quality_pct

alarm



3. Copy your AIO Username and AIO Key into both the Arduino sketch and Python client.
