# MSP430-IoT_Car_ECE306
### ECE 306 (Introduction to Embedded Systems) Project

### **📝 Overview**
This project involved the system integration and firmware development of an autonomous robotic platform centered on the **MSP430FR2355 (FRAM)** microcontroller. The system bridges bare-metal embedded control with IoT connectivity by utilizing an **ESP32** co-processor to enable **TCP/IP** remote steering alongside a **PID-based** autonomous mode.

The project focused on high-speed sensor acquisition, asynchronous wireless communication, and real-time control logic to navigate complex environments while maintaining a live network link for manual override.

---
### **⚠️ Academic Integrity & Disclaimer**
This repository is intended for **professional portfolio review only**. The contents represent my original work and system integration for ECE 306. 
* **For Students:** Use of this code for course assignments may violate your university's Academic Integrity policy.
* **Liability:** The author is not responsible for any academic consequences or system damage resulting from the use of this software.
* **Copyright:** © 2026 Luca Daloia. All rights reserved.
---
### **🛠 Hardware Specifications**
* **MCU:** MSP430FR2355
* **Wireless:** ESP32
* **Motors:** Dual DC Motors
* **Sensors:** IR Emitter/Dual-Detector Array
* **Actuators:** Dual H-Bridge Drivers
* **Interface:** Thumbwheel, Buttons/Switches, and LCD Character Display

---
### **📂 Project Structure**
#### **Firmware (C / MSP430)**
* `main.c`: Primary entry point and system initialization.
* `state_machine.c`: Core logic governing transitions between Autonomous, Manual, and IoT modes.
* `UCA_Interrupts.c`: Low-level UART ISRs utilizing **Circular (Ring) Buffers** for non-blocking I/O.
* `movement.c`: Differential steering and speed control logic for DC motors.
* `clocks.c` / `ports.c` / `timers.c`: Peripheral hardware abstraction and clock tree configuration.
* `ADC.c`: Multi-channel sampling of the IR detector array for real-time error detection.
* `LCD.c`: Custom driver for real-time status and telemetry display.
#### **Tools (Python / IoT)**
* `306TCPV2.py`: I developed a custom **Tkinter-based** TCP terminal to send remote steering packets and monitor hardware telemetry.
---
### **⚙️ Technical Highlights**
#### **1. Asynchronous UART Stack**
To ensure the robot remained responsive during high-speed IoT data bursts, **I developed** a serial communication stack utilizing **Circular (Ring) Buffers** (implemented in `UCA_Interrupts.c`). This architecture decouples physical byte reception from message parsing, preventing data loss and CPU stalling during wireless telemetry.

#### **2. Hierarchical State Machine**
The firmware architecture relies on a robust **State Machine** (`state_machine.c`) that interprets commands like `^####CTTTT`. This allows the robot to safely interrupt autonomous line-following when a priority manual command is received from the Python TCP Client.

#### **3. Differential IR Sensing & PID**
The navigation system utilizes a single **IR emitter paired with dual detectors**. By comparing analog voltage drops via the 10-bit ADC, the firmware calculates a precise error value fed into a **PID loop** to adjust PWM signals, ensuring smooth tracking.

---
**Author:** Luca Daloia  
**Project Date:** Spring 2026  
**Course:** ECE 306 
