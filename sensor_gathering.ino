#include <dht.h>  // DHTLib by Rob Tillaart

// ===============================
// PIN DEFINITIONS
// ===============================
#define TEMP_N_HUMIDITY_SENSEOR_PIN 3
#define TILT_SWITCH_PIN 4
#define HEARTBEAT_SENSOR_PIN 0
#define BUTTONPIN 2


// ===============================
// CONSTANTS
// ===============================
#define SENSOR_READ_INTERVAL_MS 50
#define TILT_COUNT_WINDOW_MS 3000
#define IS_RUNNING_TILT_COUNT_THRESHOLD 10

// ===============================
// GLOBAL OBJECTS & VARIABLES
// ===============================
dht DHT;

int tiltChangeCount = 0;
int lastTiltState;
int isRunning = 0;
unsigned long windowStartTime = 0;

float temp;
float humidity;
int buttonstate = 0;
// --- HEARTBEAT VARIABLES ---
#define samp_siz 4
#define rise_threshold 4

float reads[samp_siz];
float sum = 0;
long ptr = 0;

float last_avg = 0;
float before = 0;

bool rising = false;
int rise_count = 0;

float first = 800, second = 800, third = 800;
long last_beat = 0;

float heartbeatBpm = 0;

void setup() {
  pinMode(HEARTBEAT_SENSOR_PIN, INPUT);
  pinMode(TEMP_N_HUMIDITY_SENSEOR_PIN, INPUT);
  pinMode(TILT_SWITCH_PIN, INPUT_PULLUP);
  pinMode(BUTTONPIN,INPUT);
  lastTiltState = digitalRead(TILT_SWITCH_PIN);
  
  for (int i = 0; i < samp_siz; i++) reads[i] = 0;

  Serial.begin(9600);
  while (!Serial) {}

  Serial.println("Serial initialized");
  last_beat = millis();
}

void loop() {

  // ==========================================================
  // 1) READ DHT11 SENSOR
  // ==========================================================
  int chk = DHT.read11(TEMP_N_HUMIDITY_SENSEOR_PIN);
  buttonstate = digitalRead(BUTTONPIN);
  if (chk == 0) { 
    temp = DHT.temperature;
    humidity = DHT.humidity;
  }

  // ==========================================================
  // 2) HEARTBEAT DETECTION (runs every loop)
  // ==========================================================
  float reader = 0;
  int n = 0;
  long start = millis();
  long now;

  // 20 ms averaging (removes 50/60Hz noise)
  do {
    reader += analogRead(HEARTBEAT_SENSOR_PIN);
    n++;
    now = millis();
  } while (now < start + 20);

  reader /= n;

  // Moving average of last 4 samples
  sum -= reads[ptr];
  sum += reader;
  reads[ptr] = reader;
  ptr = (ptr + 1) % samp_siz;

  float avg = sum / samp_siz;

  // --- Detect rising slope ---
  if (avg > before) {
    rise_count++;

    if (!rising && rise_count > rise_threshold) {
      rising = true;

      // Calculate time between beats
      long beatInterval = millis() - last_beat;
      last_beat = millis();

      // shift values
      third = second;
      second = first;
      first = beatInterval;

      // Weighted BPM average
      heartbeatBpm = 60000.0 / (0.4 * first + 0.3 * second + 0.3 * third);
      heartbeatBpm += 30;
    }
  } else {
    // Reset rise detection
    rise_count = 0;
    rising = false;
  }

  before = avg;

  // ==========================================================
  // 3) TILT SWITCH RUNNING DETECTION
  // ==========================================================
  int currentTiltState = digitalRead(TILT_SWITCH_PIN);

  if (currentTiltState != lastTiltState) {
    tiltChangeCount++;
    lastTiltState = currentTiltState;
  }

  unsigned long currentTime = millis();

  if (currentTime - windowStartTime >= TILT_COUNT_WINDOW_MS) {
    isRunning = tiltChangeCount >= IS_RUNNING_TILT_COUNT_THRESHOLD;
    tiltChangeCount = 0;
    windowStartTime = currentTime;

    sendSensorResults();
  }

  delay(SENSOR_READ_INTERVAL_MS);
}

void sendSensorResults() {
  Serial.print("{\"temp\":");
  Serial.print(temp);
  Serial.print(", \"humidity\":");
  Serial.print(humidity);
  Serial.print(", \"bpm\":");
  Serial.print(heartbeatBpm);
  Serial.print(", \"running\":");
  Serial.print(isRunning);
  Serial.print(", \"Buttonstate\":");
  Serial.print(buttonstate);
  Serial.println("}");
}
