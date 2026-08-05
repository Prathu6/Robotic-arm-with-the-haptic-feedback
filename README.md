# Robotic-arm-with-the-haptic-feedback

## Project Overview

This project enables intuitive real-time control of a 5-DOF robotic arm using a wearable haptic glove. Hand and wrist movements are captured using IMU and flex sensors, processed by an ESP32, and transmitted to the robotic arm. The system also provides haptic feedback to improve operator interaction.

The project demonstrates embedded firmware development, custom PCB design, sensor interfacing, motor control, and hardware-software integration.

## Features

- Real-time robotic arm control
- Haptic feedback glove
- 5-DOF robotic arm
- Wireless communication
- Servo motor control
- IMU-based motion tracking
- Flex sensor finger tracking
- Custom PCB
- Web-based control dashboard

## System Architecture

Haptic Glove
     │
MPU6050 + Flex Sensors
     │
ESP32
     │ Wi-Fi
     ▼
ESP32 Controller
     │
PCA9685
     │
Servo Motors
     │
Robotic Arm
![System Architecture](<robotic arm .png>)

## 🧩 Project Modules

### 1️⃣ Haptic Glove (Operator Side)

The glove serves as the primary input device of the system.

It captures the operator's hand movements and wrist orientation using multiple sensors and converts them into motion commands for the robotic arm.

### Features
Hand gesture detection
Wrist orientation tracking
Finger bending detection
Haptic vibration feedback
Wireless communication

### Components Used
ESP32
MPU6050 IMU
Flex Sensors
Vibration Motors
Li-ion Battery
Custom PCB

### 2️⃣ Robotic Hand (Hand up to Wrist)

The robotic hand mirrors the movement of the operator's hand.

This section includes the mechanical design, embedded control, and actuator integration responsible for replicating wrist and finger motion.

Features
Finger actuation
Wrist movement
Servo motor control
Embedded firmware
Mechanical assembly
Custom PCB integration

### 3️⃣ Manipulator (Arm Section)

The manipulator represents the complete robotic arm responsible for shoulder, elbow, and base movement.

Its purpose is to extend the robotic hand into a fully functional 5-DOF robotic arm capable of performing manipulation tasks.

Planned Features
Base rotation
Shoulder joint
Elbow joint
Wrist rotation
Object manipulation

## ⚠️ Current Project Status

### Project Progress

| Module | Status |
|--------|--------|
| Haptic Glove | ✅ Completed |
| Robotic Hand (Up to Wrist) | ✅ Completed |
| Manipulator Section | 🚧 Under Development |

### Important Note:

The current version of this project includes a fully functional haptic glove and a robotic hand developed up to the wrist section.

The manipulator (base, shoulder, and elbow assembly) is still under development and has not yet been integrated with the completed system.

Future updates will include the complete manipulator, inverse kinematics, improved motion planning, and full-system integration.

## ⚙️ Working Principle
Step 1 — Motion Capture

The operator wears the haptic glove.

Flex sensors/potentiometer detect finger bending while MPU6050 sensors continuously measure wrist orientation.

Step 2 — Data Processing

The ESP32 reads all sensor values, filters the data, maps the angles, and converts them into motion commands.

Step 3 — Wireless Communication

The processed commands are transmitted wirelessly to the robotic hand controller.

Step 4 — Motion Replication

Servo motors reproduce the operator's wrist and finger movements in real time.

Step 5 — Haptic Feedback

When interaction is detected, vibration motors on the glove provide tactile feedback, allowing the operator to feel basic contact information.

## 🛠 Technologies Used

Hardware
ESP32
MPU6050 IMU
Flex Sensors
Servo Motors
PCA9685 Servo Driver
Custom PCB
Li-ion Battery
Software
Embedded C++
Arduino Framework
VS Code
Git & GitHub
KiCad / EasyEDA
Fusion 360

## 🚀 Future Scope

Complete 5-DOF manipulator
Inverse Kinematics implementation
Force feedback system
ROS 2 integration
Camera-assisted object tracking
Computer vision-based object detection
Wireless latency optimization
Mobile application support
Improved sensor fusion algorithms

## 📌 Project Vision

This project is more than just a robotic arm.

It is an attempt to create a natural bridge between human motion and robotic manipulation using embedded systems, intelligent sensing, and custom hardware.

Every PCB, every line of firmware, every CAD model, and every prototype has been built as a step toward creating a more intuitive human-machine interaction system.
