# Embedded-Controlled-Car-blackbox
# Bluetooth-Controlled Car with Embedded Black Box System

## Description

A Bluetooth-controlled car using the **Arduino RP2040** with manual and auto modes. Manual mode supports **multi-speed control** via Bluetooth commands (HC-05) sent from a custom mobile app. Auto mode allows the car to navigate freely, detect collisions using an **IR sensor**, stop, change direction, and log critical real-time data. The system records:

- **Speed and acceleration** (MPU6050)
- **Angular velocity** (MPU6050)
- **Environmental data**: Temperature and humidity

Upon collision, it triggers alerts via a **buzzer and LED**, simulating a black box system by storing relevant data for analysis. Motion is powered by a **lithium battery** and managed through **DC motors controlled by an H-bridge**, enabling smooth operation.

## Features

- **Manual Mode**: Mobile app control with commands:
  - `f`: Move forward
  - `b`: Move backward
  - `r`: Turn right
  - `S`: Stop
  - Multi-speed control: Pressing `f` multiple times increases speed.
- **Auto Mode**: Autonomous navigation with collision detection and response.
- **Data Logging**: Real-time recording of motion and environmental data.
- **Collision Alerts**: LED and buzzer activation upon collision.
- **Power Supply**: Lithium battery for stable operation.

## Hardware Components

- **Arduino RP2040**: Microcontroller
- **HC-05**: Bluetooth module
- **MPU6050**: Accelerometer and gyroscope
- **IR Sensor**: Collision detection
- **Temperature and Humidity Sensors**: Environmental monitoring
- **DC Motors**: Controlled via an H-bridge
- **LED and Buzzer**: Visual and audio alerts
- **Lithium Battery**: Power supply

## Software

- **Programming Language**: MicroPython/C++
- **Mobile App**: Sends Bluetooth commands for manual control
- **Collision Detection Algorithm**: Proximity sensing using the IR sensor
- **Data Storage**: Logs sensor data during collision events
- **Motor Control**: PWM-based motion control

## Setup Instructions

1. Connect all components to the Arduino RP2040 as per the circuit diagram.
2. Upload the program to the RP2040 using MicroPython or C++.
3. Pair the HC-05 Bluetooth module with the mobile app.
4. Use the app to control the car manually or set it to auto mode.
5. Monitor real-time data and observe the collision alerts.

## Future Improvements

- Integration of **GPS** for location tracking.
- **Wireless data transmission** for remote monitoring.
- Enhanced enclosures for real-world applications.

## Acknowledgments

This project was conducted at the **German University in Cairo**, showcasing practical applications of embedded systems in vehicle monitoring and safety.

---

**Keywords**: Arduino RP2040, Bluetooth, Embedded Systems, Collision Detection, Black Box, MPU6050, Vehicle Monitoring.

