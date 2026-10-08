# AVR2560-FirmwareStack

A modular bare-metal firmware stack for the **ATmega2560**, developed in **Embedded C** using direct register-level programming. This project implements reusable drivers for GPIO, timers, PWM, ADC, sensors, displays, interrupts, and other embedded peripherals.

---

## 🎯 Project Objective

The main objective of this project is to develop a structured and reusable **ATmega2560 driver framework** without relying on Arduino libraries.

The project focuses on:

- Direct register-level programming
- Modular `.h` and `.c` driver architecture
- Reusable peripheral APIs
- Hardware abstraction
- Peripheral-level testing
- Understanding the ATmega2560 architecture
- Developing firmware practices used in professional embedded systems

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
| Libraries | No Arduino framework |

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
