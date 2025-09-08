import csv, time
from pathlib import Path
import paho.mqtt.client as mqtt
from plyer import notification

AIO_USERNAME = "YOUR_AIO_USERNAME"
AIO_KEY = "YOUR_AIO_KEY"
FEEDS = ["smoke_raw", "air_quality_pct", "alarm"]
AIO_HOST = "io.adafruit.com"
AIO_PORT = 1883

CSV_PATH = Path("smoke_log.csv")

def ensure_csv_header():
    exists = CSV_PATH.exists()
    with CSV_PATH.open("a", newline="") as f:
        w = csv.writer(f)
        if not exists: w.writerow(["timestamp", "feed", "value"])

def on_connect(client, userdata, flags, rc):
    for feed in FEEDS: client.subscribe(f"{AIO_USERNAME}/feeds/{feed}")

def on_message(client, userdata, msg):
    payload = msg.payload.decode("utf-8").strip()
    ts = time.strftime("%Y-%m-%d %H:%M:%S")
    feed = msg.topic.split("/")[-1]
    with CSV_PATH.open("a", newline="") as f:
        csv.writer(f).writerow([ts, feed, payload])
    if feed == "alarm" and payload == "1":
        notification.notify(title="Smoke Detector ALERT", message="Threshold exceeded!", timeout=5)
    print(f"[{ts}] {feed}: {payload}")

def main():
    ensure_csv_header()
    client = mqtt.Client()
    client.username_pw_set(AIO_USERNAME, AIO_KEY)
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(AIO_HOST, AIO_PORT, 60)
    client.loop_forever()

if __name__ == "__main__":
    main()
