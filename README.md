# ProDex IoT Tasks: Spring 2026

**Name:** YOUR NAME
**Roll No.:** YOUR ROLL NO.
**Department / Year:** YOUR DEPARTMENT, YEAR
**Platform:** Arduino Uno on Tinkercad Circuits

---

## Repository Structure

```
.
├── README.md
├── Task1_ColourSorter/
│   ├── task1_colour_sorter.ino
│   ├── screenshots/
│   └── notes.md
├── Task2_SolarTracker/
│   ├── task2_solar_tracker.ino
│   ├── screenshots/
│   └── notes.md
└── Task3_MorseMessenger/
    ├── task3_morse_messenger.ino
    ├── screenshots/
    └── notes.md
```

## Submission Summary

| Task | Title | Tinkercad Link | Code |
|------|-------|----------------|------|
| 1 | Automatic Object Sorting System | [Open simulation](PASTE_TINKERCAD_LINK_1) | [.ino](Task1_ColourSorter/task1_colour_sorter.ino) |
| 2 | Dual-Axis Solar Tracking System | [Open simulation](PASTE_TINKERCAD_LINK_2) | [.ino](Task2_SolarTracker/task2_solar_tracker.ino) |
| 3 | Morse Messenger (IR) | [Open simulation](PASTE_TINKERCAD_LINK_3) | [.ino](Task3_MorseMessenger/task3_morse_messenger.ino) |

> All Tinkercad links are shared publicly so they open without login.

---

## Task 1: Factory-Based Product Inspection (Colour Sorter)

**Goal:** Identify red, green and blue objects on a conveyor and route each one to the correct bin.

**Components:**
- Arduino Uno
- TCS3200 colour sensor
- DC motor with motor driver (conveyor)
- Servo motor (diverter)

**How it works:**
1. The DC motor runs the conveyor belt.
2. The TCS3200 reads the object's red, green and blue frequencies.
3. The readings are compared against calibrated values to decide the colour.
4. The servo rotates the diverter to the matching bin.
5. The count for each bin is updated and printed on the Serial Monitor.

**Pin connections:**

| Component | Arduino Pin |
|-----------|-------------|
| TCS3200 S0, S1, S2, S3 | FILL IN |
| TCS3200 OUT | FILL IN |
| Motor driver IN1, IN2, EN | FILL IN |
| Servo signal | FILL IN |

**Additional functionality:** DESCRIBE ANY EXTRAS (e.g. unknown-colour handling, calibration routine, LED indicators)

**Output evidence:** see `Task1_ColourSorter/screenshots/`

---

## Task 2: Smart Solar Power Generation (Dual-Axis Tracker)

**Goal:** Detect the direction of the strongest signal and adjust the panel on two axes using two servos.

**Components:**
- Arduino Uno
- NUMBER ultrasonic distance sensors (HC-SR04)
- 2 servo motors (horizontal and vertical)

**How it works:**
1. The ultrasonic sensors measure distance from different directions.
2. The readings are compared to work out which way the panel should turn.
3. One servo moves the panel left or right, the other tilts it up or down.
4. When the difference falls within the set threshold, movement stops to keep tracking stable.

**Pin connections:**

| Component | Arduino Pin |
|-----------|-------------|
| Ultrasonic sensors (TRIG / ECHO) | FILL IN |
| Horizontal servo | FILL IN |
| Vertical servo | FILL IN |

**Note on sensor choice:** The task brief specifies 4 LDRs for light detection. This build uses ultrasonic distance sensors instead. EXPLAIN YOUR REASON HERE.

**Additional functionality:** DESCRIBE ANY EXTRAS

**Output evidence:** see `Task2_SolarTracker/screenshots/`

---

## Task 3: Morse Messenger (IR-Based Optical Communication)

**Goal:** Convert short and long hand detections into dots and dashes, decode them into text, and play the message back with light and sound.

**Components:**
- Arduino Uno
- IR sensor
- LED
- Buzzer

**How it works:**
1. The IR sensor detects a hand in front of it.
2. `millis()` measures how long the detection lasts: a short press is a dot, a long press is a dash.
3. A pause marks the end of a letter, and a lookup table converts the pattern into a character.
4. The decoded letter is printed on the Serial Monitor.
5. The stored message is played back with the LED and buzzer as short and long flashes and beeps.

**Pin connections:**

| Component | Arduino Pin |
|-----------|-------------|
| IR sensor OUT | FILL IN |
| LED | FILL IN |
| Buzzer | FILL IN |

**Timing thresholds:** dot below THRESHOLD ms, dash above THRESHOLD ms, letter gap above GAP ms

**Additional functionality:** DESCRIBE ANY EXTRAS

**Output evidence:** see `Task3_MorseMessenger/screenshots/`

---

## Further Applications and Real-World Adaptation

### Task 1: Colour Sorter
- Quality control in manufacturing, such as colour mismatch or defect detection
- Grading fruit and grain by ripeness in food processing
- Sorting plastics, glass and paper in recycling plants
- Routing colour-coded parcels in logistics
- **Real-world adaptation:** ambient-light shielding, periodic recalibration, camera-based machine vision for shape and defects, and live production dashboards over IoT.

### Task 2: Dual-Axis Tracker
- Utility-scale solar farms, where tracking can raise output by roughly 20-40% over fixed panels
- Satellite dish and antenna alignment
- Pan-tilt cameras that follow a target
- Robotics sensor heads that adjust orientation automatically
- **Real-world adaptation:** for actual solar tracking, ultrasonic sensors would be replaced or supplemented by LDRs or photodiodes. Ultrasonic sensing is still useful for obstacle and shading detection. Real systems also add wind-stow protection, weather sensing, a night sleep mode, and sun-position calculations.

### Task 3: Morse Messenger
- Assistive communication for people with limited mobility using a single switch
- Emergency SOS signalling without a network
- Optical and Li-Fi style short-range data transfer
- Line-of-sight signalling where radio is restricted
- **Real-world adaptation:** adaptive timing per user, noise and false-trigger filtering, support for numbers and punctuation, and message encryption.

---

## How to Run

1. Open the Tinkercad link for the task.
2. Click **Start Simulation**.
3. Open the **Serial Monitor** (baud rate: 9600) to view output.
4. Interact with the circuit as described in each task section.

To use the code locally, open the `.ino` file in the Arduino IDE and upload it to an Arduino Uno wired as per the pin tables above.

## Acknowledgements

- [Arduino documentation](https://docs.arduino.cc/)
- [TCS3200 tutorial, Last Minute Engineers](https://lastminuteengineers.com/tcs3200-color-sensor-arduino-tutorial/)
- [Servo motor guide, Arduino](https://docs.arduino.cc/learn/electronics/servo-motors/)
- [Morse code, Wikipedia](https://en.wikipedia.org/wiki/Morse_code)
