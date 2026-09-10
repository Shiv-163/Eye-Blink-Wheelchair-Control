# Eye Blink Based Wheelchair Control

An Arduino-based assistive mobility prototype that converts eye-blink patterns into basic wheelchair movement commands.

## Commands

| Blinks | Action |
|---|---|
| 1 | Forward |
| 2 | Left |
| 3 | Right |
| 4 or more | Stop |

## Components

- Arduino Uno
- Eye blink sensor
- L293D or L298N motor driver
- Two DC geared motors
- Battery/power supply
- Wheelchair/chassis prototype

## Pin Configuration

| Device | Arduino Pin |
|---|---|
| Blink sensor output | D2 |
| Left motor IN1 | D8 |
| Left motor IN2 | D9 |
| Right motor IN1 | D10 |
| Right motor IN2 | D11 |

## Working

The blink sensor provides a digital signal to the Arduino. The Arduino counts detected blinks within a command window and maps the count to a movement command. Motor-driver inputs are then controlled to produce the required movement.

## Intentional Small Issue

This version intentionally contains a small **debouncing/timing bug**:

```cpp
delay(100);
```

The delay is too short and a single physical blink can occasionally be counted more than once.

A simple correction is:

```cpp
delay(500);
```

The exact value should be tuned according to the sensor and testing conditions.

## Future Improvements

- Ultrasonic obstacle detection
- PWM speed control
- Emergency-stop button
- Wireless monitoring
- Improved blink-duration detection
- Battery monitoring

## Safety

This is an educational prototype and should not be used as a real mobility controller without professional safety validation, redundant controls and an emergency stop.

## License

MIT License. See `LICENSE`.
