# AVR2560-FirmwareStack

A modular bare-metal firmware stack for the **ATmega2560**, developed in **Embedded C** using direct register-level programming.

This project implements reusable, register-level drivers for GPIO, timers, displays, sensors, and other embedded peripherals without relying on the Arduino framework.

---

## 🎯 Project Objective

The main objective of this project is to develop a structured and reusable **ATmega2560 driver framework** using bare-metal Embedded C.

The project focuses on:

- Direct register-level programming
- Modular `.h` and `.c` driver architecture
- Reusable peripheral APIs
- Hardware abstraction
- Peripheral-level testing
- Understanding the ATmega2560 architecture
- Developing firmware practices used in professional embedded systems
- Building a scalable driver framework for future embedded projects

---

## 👥 Contributors

This project is collaboratively developed by three members.

| # | Contributor | Primary Contribution | GitHub |
|---|---|---|---|
| 1 | **Harineash T** | GPIO Driver | [@harineash](https://github.com/harineash) |
| 2 | **Deepika P** | Timer Driver | [@deepi2win-lang](https://github.com/deepi2win-lang) |
| 3 | **Manoranjan K** | Seven-Segment Display Driver | [@manoranjank-eng](https://github.com/manoranjank-eng) |

### Contribution Areas

#### 1. Harineash T — GPIO

Responsible for the development and implementation of the **GPIO driver**, including:

- GPIO port configuration
- Input/output configuration
- Register-level GPIO control
- Pin manipulation
- GPIO testing and validation

GitHub: [github.com/harineash](https://github.com/harineash)

---

#### 2. Deepika P — Timer

Responsible for the development and implementation of the **Timer driver**, including:

- Timer register configuration
- Timer operating modes
- Timer control
- Timing functionality
- Timer testing and validation

GitHub: [github.com/deepi2win-lang](https://github.com/deepi2win-lang)

---

#### 3. Manoranjan K — Seven-Segment Display

Responsible for the development and implementation of the **Seven-Segment Display driver**, including:

- Seven-segment initialization
- Digit mapping
- Segment control
- Multi-digit display handling
- Display testing and validation

GitHub: [github.com/manoranjank-eng](https://github.com/manoranjank-eng)

---

## 🛠️ Target Platform

| Parameter | Details |
|---|---|
| Microcontroller | ATmega2560 |
| Architecture | AVR 8-bit |
| Programming Language | Embedded C |
| Programming Style | Bare-Metal / Register-Level |
| Compiler | AVR-GCC |
| IDE | MPLAB X / AVR-compatible IDE |
| Framework | No Arduino Framework |

---

## 📂 Project Structure

```text
AVR2560-FirmwareStack/
│
├── README.md
├── LICENSE
├── Makefile
│
├── include/
│   ├── define.h
│   ├── gpio.h
│   ├── switch.h
│   ├── led.h
│   ├── seven_segment.h
│   ├── timer.h
│   ├── pwm.h
│   ├── adc.h
│   ├── ultrasonic.h
│   ├── ir_sensor.h
│   ├── keypad.h
│   ├── external_interrupt.h
│   ├── lcd.h
│   └── motor_servo.h
│
├── src/
│   ├── define.c
│   ├── gpio.c
│   ├── switch.c
│   ├── led.c
│   ├── seven_segment.c
│   ├── timer.c
│   ├── pwm.c
│   ├── adc.c
│   ├── ultrasonic.c
│   ├── ir_sensor.c
│   ├── keypad.c
│   ├── external_interrupt.c
│   ├── lcd.c
│   └── motor_servo.c
│
├── examples/
│   ├── gpio/
│   ├── switch/
│   ├── led/
│   ├── seven_segment/
│   ├── timer/
│   ├── pwm/
│   ├── adc/
│   ├── ultrasonic/
│   ├── ir_sensor/
│   ├── keypad/
│   ├── external_interrupt/
│   ├── lcd/
│   └── motor_servo/
│
└── docs/
    ├── architecture.md
    ├── register_map.md
    └── driver_usage.md
```

---

## ⚙️ Development Approach

The firmware stack follows a modular driver architecture.

```text
Application
     │
     ▼
Example / Application Code
     │
     ▼
Peripheral Driver API
     │
     ├── GPIO
     ├── Timer
     ├── Seven-Segment
     ├── PWM
     ├── ADC
     ├── Sensors
     └── Other Peripherals
     │
     ▼
ATmega2560 Hardware Registers
```

Each peripheral is designed as an independent driver with its own:

- Header file (`.h`)
- Source file (`.c`)
- Example implementation
- Hardware-level testing

This structure allows drivers to be reused across different embedded applications.

---

## 🔧 Implemented Drivers

| Driver | Status | Contributor |
|---|---|---|
| GPIO | 🚧 In Development | Harineash T |
| Timer | 🚧 In Development | Deepika P |
| Seven-Segment Display | 🚧 In Development | Manoranjan K |
| Switch | 🔲 Planned | Team |
| LED | 🔲 Planned | Team |
| PWM | 🔲 Planned | Team |
| ADC | 🔲 Planned | Team |
| Ultrasonic | 🔲 Planned | Team |
| IR Sensor | 🔲 Planned | Team |
| Keypad | 🔲 Planned | Team |
| External Interrupt | 🔲 Planned | Team |
| LCD | 🔲 Planned | Team |
| Motor / Servo | 🔲 Planned | Team |

> Driver status can be updated as each module is completed and tested.

---

## 🧩 Driver Architecture

Each driver follows a common structure:

```text
Driver
│
├── Header File
│   └── peripheral.h
│
├── Source File
│   └── peripheral.c
│
└── Example
    └── peripheral_test.c
```

For example:

```text
GPIO
├── include/gpio.h
├── src/gpio.c
└── examples/gpio/

Timer
├── include/timer.h
├── src/timer.c
└── examples/timer/

Seven-Segment
├── include/seven_segment.h
├── src/seven_segment.c
└── examples/seven_segment/
```

---

## 💻 Programming Philosophy

This project intentionally avoids high-level Arduino APIs such as:

```c
digitalWrite();
digitalRead();
pinMode();
delay();
```

Instead, the drivers directly interact with the ATmega2560 hardware registers.

Example:

```c
#define DDRF  (*(volatile unsigned char*)0x30)
#define PORTF (*(volatile unsigned char*)0x31)

DDRF = 0xFF;
PORTF = 0x01;
```

This approach provides a better understanding of:

- Microcontroller registers
- Memory-mapped I/O
- GPIO architecture
- Timers and counters
- Peripheral configuration
- Hardware abstraction
- Embedded firmware development

---

## 🧪 Testing

Each driver is tested independently before integration into the complete firmware stack.

Testing includes:

- Register configuration verification
- Hardware output verification
- Peripheral functionality testing
- Boundary-condition testing
- Integration testing

Example test applications are maintained under:

```text
examples/
```

---

## 🚀 Future Development

The framework is designed to be expanded with additional ATmega2560 peripherals and embedded interfaces.

Planned modules include:

- PWM
- ADC
- UART
- SPI
- I2C
- LCD
- Keypad
- Ultrasonic sensor
- IR sensor
- External interrupts
- Servo motor
- DC motor control
- Communication interfaces
  

The long-term goal is to develop a complete **reusable bare-metal firmware stack for the ATmega2560**.

---

## 📚 Documentation

Additional technical documentation will be maintained under:

```text
docs/
```

Planned documentation includes:

- `architecture.md` — Firmware architecture
- `register_map.md` — ATmega2560 register references
- `driver_usage.md` — Driver APIs and usage examples

---

## 📜 License

This project is developed for educational and embedded-systems development purposes.

See the [LICENSE](LICENSE) file for more information.

---

## 👨‍💻 Development Team

### Harineash T
GPIO Driver Developer  
[GitHub](https://github.com/harineash)

### Deepika P
Timer Driver Developer  
[GitHub](https://github.com/deepi2win-lang)

### Manoranjan K
Seven-Segment Display Driver Developer  
[GitHub](https://github.com/manoranjank-eng)

---

**AVR2560-FirmwareStack**  
*Building reusable bare-metal firmware, one driver at a time.*
