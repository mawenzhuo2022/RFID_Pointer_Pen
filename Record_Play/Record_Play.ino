/*
  Demo: Bluetooth audio recorder with detailed debug logs.
  - Receives commands via Bluetooth (RECORD, STOP, PLAY)
  - Records ~0.6s audio from A0 (mic) to a small RAM buffer
  - Plays it back via PWM on pin D9
  - LED on D13 blinks once on receiving a command, and stays lit while recording/playing
  - Added debug logs in readBluetooth() and state updates for troubleshooting

  NOTE:
  1) For real usage, the memory is too small to store much audio on an ATmega328P.
  2) This code is strictly for demonstration and debugging.
*/

#include <SoftwareSerial.h>

// -------------------------  Hardware Pins  -------------------------
#define BT_RX_PIN   2     // Arduino RX to BT TX
#define BT_TX_PIN   3     // Arduino TX to BT RX
#define LED_PIN    13     // Status LED
#define MIC_PIN    A0     // Microphone (audio out) input
#define SPK_PIN     9     // Speaker output (PWM pin)

// -------------------------  Bluetooth  -------------------------
SoftwareSerial btSerial(BT_RX_PIN, BT_TX_PIN);

// We accumulate incoming characters here
String inputString = "";
bool stringComplete = false;

// -------------------------  Audio Buffer  -------------------------
// Reduced size so it fits in ATmega328P (2KB RAM). ~1s @1kHz
#define MAX_SAMPLES 1000
byte audioBuffer[MAX_SAMPLES];

int recordIndex = 0;  
int playIndex   = 0;  

// -------------------------  State Machine  -------------------------
enum AudioState {
  IDLE,
  RECORDING,
  PLAYING
};

AudioState currentState = IDLE;

// For ~1kHz sampling/playback
unsigned long lastAudioMillis = 0;
const unsigned long SAMPLE_INTERVAL_MS = 1; // 1ms => ~1k samples/sec

// -------------------------  Setup  -------------------------
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  pinMode(SPK_PIN, OUTPUT);
  analogWrite(SPK_PIN, 0); // Speaker off initially

  Serial.begin(9600);
  // Make sure the baud rate here matches your BT module's setting
  btSerial.begin(115200);

  Serial.println("=== [DEBUG] Bluetooth Audio Recorder Ready. ===");
  btSerial.println("Bluetooth Audio Recorder Ready.");
}

// -------------------------  Main Loop  -------------------------
void loop() {
  // 1) Handle incoming Bluetooth data / parse commands
  readBluetooth();

  // 2) Handle Audio State Machine (record or playback)
  updateAudioState();

  // 3) Forward anything from USB Serial to Bluetooth (optional)
  while (Serial.available()) {
    char c = (char)Serial.read();
    btSerial.write(c);
  }
}

// -------------------------  Read Bluetooth  -------------------------
void readBluetooth() {
  // Read every character available from the software serial
  while (btSerial.available()) {
    char c = (char)btSerial.read();
    // Debug log: show the character we got
    Serial.print("[DEBUG] BT char received: '");
    if (c == '\n') Serial.print("\\n");
    else if (c == '\r') Serial.print("\\r");
    else Serial.print(c);
    Serial.println("'");

    // Build up the command string until we see a newline or CR
    if (c == '\n' || c == '\r') {
      stringComplete = true;
    } else {
      inputString += c;
    }
  }

  // If we detected a full command, let's process it
  if (stringComplete) {
    // Clean the command string
    String cmd = cleanupString(inputString);

    Serial.print("[DEBUG] Full raw command: '");
    Serial.print(inputString);
    Serial.println("'");

    Serial.print("[DEBUG] Cleaned command: '");
    Serial.print(cmd);
    Serial.println("'");

    // Blink LED once to show we got something
    blinkOnce(LED_PIN, 50);

    // Match commands
    if (cmd == "RECORD") {
      startRecording();
    } 
    else if (cmd == "STOP") {
      stopAudio();
    } 
    else if (cmd == "PLAY") {
      startPlayback();
    } 
    else {
      Serial.print("[DEBUG] Unknown command: ");
      Serial.println(cmd);
      btSerial.print("Unknown command: ");
      btSerial.println(cmd);
    }

    // Clear for next command
    inputString = "";
    stringComplete = false;
  }
}

// -------------------------  Update Audio State  -------------------------
void updateAudioState() {
  unsigned long currentMillis = millis();

  switch (currentState) {
    case RECORDING: {
      if (currentMillis - lastAudioMillis >= SAMPLE_INTERVAL_MS) {
        lastAudioMillis = currentMillis;

        if (recordIndex < MAX_SAMPLES) {
          // 10-bit read => shift right 2 => 8-bit
          int raw = analogRead(MIC_PIN) >> 2;
          audioBuffer[recordIndex++] = (byte)raw;
        } else {
          Serial.println("[DEBUG] Buffer full! Stopping recording...");
          stopAudio();
        }
      }
    } break;

    case PLAYING: {
      if (currentMillis - lastAudioMillis >= SAMPLE_INTERVAL_MS) {
        lastAudioMillis = currentMillis;

        if (playIndex < recordIndex) {
          analogWrite(SPK_PIN, audioBuffer[playIndex]);
          playIndex++;
        } else {
          Serial.println("[DEBUG] Playback finished. Stopping...");
          stopAudio();
        }
      }
    } break;

    case IDLE:
    default:
      // No active audio process
      break;
  }
}

// -------------------------  Start Recording  -------------------------
void startRecording() {
  Serial.println("[DEBUG] Command: START RECORDING");
  btSerial.println("Start Recording...");

  recordIndex = 0;
  // LED on
  digitalWrite(LED_PIN, HIGH);

  lastAudioMillis = millis();
  currentState = RECORDING;
}

// -------------------------  Stop (Recording or Playing)  -------------------------
void stopAudio() {
  if (currentState == PLAYING) {
    analogWrite(SPK_PIN, 0);
  }
  currentState = IDLE;
  digitalWrite(LED_PIN, LOW);

  Serial.println("[DEBUG] Command: STOP audio");
  btSerial.println("Stop audio");
}

// -------------------------  Start Playback  -------------------------
void startPlayback() {
  if (recordIndex == 0) {
    Serial.println("[DEBUG] No audio recorded, can't PLAY.");
    btSerial.println("No audio recorded yet!");
    return;
  }
  Serial.println("[DEBUG] Command: START PLAYBACK");
  btSerial.println("Start Playback...");

  playIndex = 0;
  digitalWrite(LED_PIN, HIGH);

  lastAudioMillis = millis();
  currentState = PLAYING;
}

// -------------------------  Utility: Blink Once  -------------------------
void blinkOnce(uint8_t pin, unsigned long durationMs) {
  digitalWrite(pin, HIGH);
  delay(durationMs);
  digitalWrite(pin, LOW);
  delay(durationMs);
}

// -------------------------  Utility: Clean Up String  -------------------------
String cleanupString(const String &input) {
  String trimmed = input;
  trimmed.trim();

  String clean = "";
  for (int i = 0; i < trimmed.length(); i++) {
    char ch = trimmed.charAt(i);
    // Keep only printable ASCII
    if (ch >= 32 && ch <= 126) {
      clean += ch;
    }
  }
  return clean;
}
