// C++ code
//
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}

#include <Servo.h>

// ---------- Pins ----------
const int TRIG_TL = 2,  ECHO_TL = 3;
const int TRIG_TR = 4,  ECHO_TR = 5;
const int TRIG_BL = 6,  ECHO_BL = 7;
const int TRIG_BR = 8,  ECHO_BR = 11;
const int PAN_PIN  = 9;
const int TILT_PIN = 10;
const int LED_PIN  = 13;

// ---------- Tuning ----------
const int MAX_DIST    = 100;  // cm, anything farther is treated as "no object"
const int MIN_SIGNAL  = 10;   // min strength to say an object is present
const int THRESHOLD   = 8;    // dead band in "strength" units (about cm)
const int STEP        = 1;    // degrees per update
const int LOOP_DELAY  = 40;   // ms between updates

const int PAN_MIN = 10,  PAN_MAX = 170;
const int TILT_MIN = 20, TILT_MAX = 160;

int offTL = 0, offTR = 0, offBL = 0, offBR = 0;   // calibration offsets

Servo panServo, tiltServo;
int panPos = 90, tiltPos = 90;

// Distance in cm; returns MAX_DIST if nothing is detected
int readDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 30000UL);   // 30 ms timeout
  if (duration == 0) return MAX_DIST;
  int cm = duration * 0.034 / 2;
  return constrain(cm, 0, MAX_DIST);
}

// Averaged "strength": closer object gives a higher value
int readStrength(int trig, int echo) {
  long sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += readDistance(trig, echo);
    delay(10);               // pause so echoes don't overlap
  }
  return MAX_DIST - (int)(sum / 3);
}

// Calibration: with the object at equal distance from all sensors,
// record offsets so every sensor reads the same
void calibrate() {
  int tl = readStrength(TRIG_TL, ECHO_TL);
  int tr = readStrength(TRIG_TR, ECHO_TR);
  int bl = readStrength(TRIG_BL, ECHO_BL);
  int br = readStrength(TRIG_BR, ECHO_BR);
  int avg = (tl + tr + bl + br) / 4;

  if (avg >= MIN_SIGNAL) {           // only calibrate if an object is present
    offTL = avg - tl;  offTR = avg - tr;
    offBL = avg - bl;  offBR = avg - br;
    Serial.println("Calibration done.");
  } else {
    Serial.println("No object at startup: calibration skipped.");
  }
}

void setup() {
  Serial.begin(9600);
  int trigs[] = {TRIG_TL, TRIG_TR, TRIG_BL, TRIG_BR};
  int echos[] = {ECHO_TL, ECHO_TR, ECHO_BL, ECHO_BR};
  for (int i = 0; i < 4; i++) {
    pinMode(trigs[i], OUTPUT);
    pinMode(echos[i], INPUT);
  }
  pinMode(LED_PIN, OUTPUT);

  panServo.attach(PAN_PIN);
  tiltServo.attach(TILT_PIN);
  panServo.write(panPos);
  tiltServo.write(tiltPos);
  delay(1000);
  calibrate();
}

void loop() {
  int tl = readStrength(TRIG_TL, ECHO_TL) + offTL;
  int tr = readStrength(TRIG_TR, ECHO_TR) + offTR;
  int bl = readStrength(TRIG_BL, ECHO_BL) + offBL;
  int br = readStrength(TRIG_BR, ECHO_BR) + offBR;

  int top    = (tl + tr) / 2;
  int bottom = (bl + br) / 2;
  int left   = (tl + bl) / 2;
  int right  = (tr + br) / 2;

  int vertDiff  = top - bottom;    // + means object is closer on top
  int horizDiff = left - right;    // + means object is closer on left

  bool objectPresent = max(max(tl, tr), max(bl, br)) >= MIN_SIGNAL;
  bool stable = true;

  if (objectPresent) {
    // ----- Horizontal axis -----
    if (abs(horizDiff) > THRESHOLD) {
      panPos += (horizDiff > 0) ? STEP : -STEP;   // flip signs if reversed
      panPos = constrain(panPos, PAN_MIN, PAN_MAX);
      panServo.write(panPos);
      stable = false;
    }
    // ----- Vertical axis -----
    if (abs(vertDiff) > THRESHOLD) {
      tiltPos += (vertDiff > 0) ? STEP : -STEP;
      tiltPos = constrain(tiltPos, TILT_MIN, TILT_MAX);
      tiltServo.write(tiltPos);
      stable = false;
    }
  }

  digitalWrite(LED_PIN, (objectPresent && stable) ? HIGH : LOW);

  // ----- Status -----
  Serial.print("TL:"); Serial.print(tl);
  Serial.print(" TR:"); Serial.print(tr);
  Serial.print(" BL:"); Serial.print(bl);
  Serial.print(" BR:"); Serial.print(br);
  Serial.print(" | H:"); Serial.print(horizDiff);
  Serial.print(" V:"); Serial.print(vertDiff);
  Serial.print(" | Pan:"); Serial.print(panPos);
  Serial.print(" Tilt:"); Serial.print(tiltPos);
  if (!objectPresent)  Serial.println(" | NO OBJECT");
  else if (stable)     Serial.println(" | LOCKED");
  else                 Serial.println(" | TRACKING");

  delay(LOOP_DELAY);
}