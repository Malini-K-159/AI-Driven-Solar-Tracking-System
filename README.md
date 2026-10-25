# AI Driven Solar Tracking System

Arduino UNO prototype with two LDR sensors and a servo motor. This repository contains a baseline tracking sketch, hardware setup notes, sample *illustrative* readings, and manual test cases.

## Hardware
- Arduino UNO (ATmega328P)
- Two LDRs, each in a voltage divider with a suitable fixed resistor (e.g. 10 kΩ)
- Servo motor with an appropriate power supply and common ground
- Solar panel and movable mounting frame

## Connections
- Left voltage divider output -> A0
- Right voltage divider output -> A1
- Servo signal -> D9
- Servo power -> suitable regulated supply; connect servo ground to Arduino ground

## Setup
1. Install Arduino IDE and select **Arduino UNO** and the correct port.
2. Open `AI_Driven_Solar_Tracking.ino`.
3. Ensure the standard `Servo` library is available.
4. Connect the hardware with power off; verify servo power requirements.
5. Upload the sketch and open Serial Monitor at **9600 baud**.
6. Test each LDR independently and check that servo movement goes toward the brighter sensor. Reverse motor directions in code if the mechanics require it.
7. Tune `threshold` and `stepSize` for your sensors and frame.

## Design limitations
This is a syntax-corrected baseline based on the submitted code, **not a validated full Q-learning agent**. It updates two Q-like values but does not use them to select actions. The current reward (`abs(left-right)`) is not a measure of tracking improvement. `lastImprovement` tracks large sensor differences rather than measured improvement. The fallback runs after 60 seconds without such a reading; it is not the hourly fail-safe described in the project concept. Avoid running unattended until the mechanics, end stops, and recovery behavior are tested.

## Documentation
See `docs/architecture.md`, `tests/manual_tests.md`, and `data/sample_readings.csv`.

## License
MIT License; see `LICENSE`.
