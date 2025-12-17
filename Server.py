from flask import Flask, jsonify, render_template
import serial, json, threading

app = Flask(__name__)

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

latest_data = {
    "temp": 0,
    "humidity": 0,
    "bpm": 0,
    "running": 0,
    "Buttonstate": 0
}

def read_serial():
    global latest_data
    while True:
        try:
            line = ser.readline().decode().strip()
            if line.startswith("{") and line.endswith("}"):
                latest_data = json.loads(line)
        except:
            pass

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/data")
def data():
    return jsonify(latest_data)

if __name__ == "__main__":
    t = threading.Thread(target=read_serial)
    t.daemon = True
    t.start()

    app.run(host="0.0.0.0", port=5000)
