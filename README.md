# 6-DOF Wi-Fi Controlled Robotic Arm

> **Design and development of an ESP32-based 6-DOF robotic arm with wireless control for simplified and accessible robotic operation.**

## 📌 Overview

This project is a **6 Degrees of Freedom (6-DOF) robotic arm prototype** integrating mechanical design, servo actuation, embedded control, and wireless communication.

The project was inspired by my exposure to **industrial robotics during my FANUC internship**. This experience motivated me to develop and fabricate a robotic arm prototype of my own while exploring a simpler and more accessible approach to robotic control.

The developed system uses an **ESP32 microcontroller** as the central control unit. A Wi-Fi-enabled web interface allows the robotic arm to be operated using a **mobile phone or computer**, eliminating the need for a dedicated physical controller.

The primary objective was to develop a functional robotic manipulator that is **precise, efficient, accessible, and economical**, while gaining practical experience in mechanical engineering, electronics, embedded systems, and robotic motion control.

---

## 🎯 Engineering Problem

Conventional robotic systems can involve dedicated controllers and relatively complex operating procedures, making them less accessible for basic educational and small-scale applications.

This project addresses the following engineering challenge:

> **How can a robotic arm be controlled easily and wirelessly while maintaining controlled and repeatable movement using an affordable embedded control system?**

---

## 💡 Proposed Solution

An **ESP32-based wireless control architecture** was developed to simplify robotic-arm operation.

The user can control the robotic arm through a web-based interface using a mobile phone or computer.

### Control Functions

* Individual joint control
* Servo angle adjustment
* Speed adjustment
* Home-position control
* Motion recording
* Motion playback
* Wireless operation

The ESP32 receives commands through Wi-Fi and generates the corresponding **PWM signals** to control the six servo motors.

---

## ⚙️ Key Features

* **6 Degrees of Freedom (6-DOF)**
* **ESP32-based control system**
* **Wi-Fi-enabled operation**
* **Web-based control interface**
* **Individual joint control**
* **PWM-based servo positioning**
* **Adjustable motion speed**
* **Home-position initialization**
* **Motion recording and playback**
* **External regulated power supply**
* **Compact mechanical structure**
* **Economical prototype design**

---

## 🏗️ System Architecture

```text
             ┌─────────────────────┐
             │   Mobile / Computer │
             │   Web Control UI    │
             └──────────┬──────────┘
                        │
                      Wi-Fi
                        │
                        ▼
             ┌─────────────────────┐
             │        ESP32        │
             │ Control & Processing│
             └──────────┬──────────┘
                        │
                  PWM Signals
                        │
          ┌─────────────┼─────────────┐
          ▼             ▼             ▼
       Servo 1       Servo 2 ...   Servo 6
          │             │             │
          └─────────────┼─────────────┘
                        ▼
              6-DOF Robotic Arm
```

### Control Flow

**User Input → Wi-Fi → ESP32 → PWM → Servo Motors → Mechanical Motion**

---

## 🔩 Mechanical System

The robotic arm consists of a **6-DOF mechanical structure** with six individually actuated movements:

| Joint       | Function                 |
| ----------- | ------------------------ |
| Base        | Rotation                 |
| Shoulder    | Vertical movement        |
| Elbow       | Arm extension/retraction |
| Wrist Pitch | Wrist positioning        |
| Wrist Roll  | Wrist rotation           |
| Gripper     | Object gripping          |

The mechanical structure forms the physical framework supporting the servo motors, joints, links, wiring, and end-effector.

The gripper enables the arm to **grasp, hold, and release lightweight objects**.

---

## 🔌 Electronic System

### Main Components

* **ESP32 Microcontroller**
* **6 Servo Motors**
* **Lithium-ion Battery**
* **DC-DC Buck Converter**
* **Boost Converter**
* **4700 µF Electrolytic Capacitors**
* **TP4056 Charging Module**
* **8.4 V Battery Charger**
* **Power Switch**
* **Supporting Wiring and Connectors**

The ESP32 acts as the main control and communication unit, while the six servo motors provide actuation for the six degrees of freedom.

---

## ⚡ Power Management

A dedicated power system is used to provide stable power to the servo motors.

The battery supply is regulated using a **buck converter**, providing approximately **6 V** for the servo motors.

A **4700 µF, 25 V electrolytic capacitor** is used for voltage stabilization and to help handle transient current demand from the servo motors.

A common ground is maintained between the ESP32 and the servo power supply for reliable PWM signal operation.

---

## 🌐 Wireless Control Interface

The ESP32 hosts a local web-based control interface.

The interface allows the user to control:

* Base rotation
* Shoulder movement
* Elbow movement
* Wrist pitch
* Wrist roll
* Gripper operation
* Movement speed
* Home position
* Recording
* Playback

The system can be operated using a **mobile phone or computer with a web browser**, without requiring a dedicated physical controller.

---

## 📷 Project Photos

The complete project photos are available in this repository:

*Project_Gallery*

---


## ✅ Engineering Outcomes

The project demonstrates the practical integration of:

### Mechanical Engineering

* Robotic mechanisms
* Joint and link design
* Six degrees of freedom
* End-effector design
* Mechanical motion

### Electronics

* Servo motor actuation
* PWM control
* Voltage regulation
* Power stabilization

### Embedded Systems

* ESP32-based control
* Real-time command processing
* Motion control

### Wireless Communication

* Wi-Fi communication
* Web-based control
* Remote operation

The prototype successfully demonstrates controlled movement of six servo-driven joints together with wireless web-based operation.


---

## 📄 Project Documentation

The complete project report is available in this repository:

**`report/Robotic_Arm_Project_Report.pdf`**

The report contains the project background, literature survey, working principle, equipment description, applications, cost estimation, conclusion, and supporting documentation.

---

## 👨‍🔧 Project Motivation

This project represents my transition from **observing industrial robotic systems during my FANUC internship** to independently designing and developing a functional robotic-arm prototype.

Rather than attempting to replicate an industrial robot, the project focuses on understanding its fundamental engineering principles and developing a simplified architecture that combines:

**Mechanical Design + Electronics + Embedded Control + Wireless Communication**

---

## 📚 Project Report

**Project Title:**
*Design and Fabrication of a 6-DOF Robotic Arm using ESP32*

**Project Type:** Mechanical Engineering Prototype

**Primary Technologies:** ESP32 • Servo Motors • PWM • Wi-Fi • Web-Based Control

**Estimated Total Cost:** ₹15,000

---

> **An engineering prototype exploring robotic motion, embedded control, and wireless operation through the integration of mechanical and electronic systems.**
