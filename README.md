
# Haptic Gloves v1

**Category:** Hardware + Firmware + VR Integration  
**Author:** Het Patel  
**Version:** v1  
**Started:** November 2024  
**Status:** In Development  

---

## 📘 Overview
Haptic Gloves v1 is an ESP32-based glove system designed to simulate touch feedback and hand motion tracking for VR or robotics applications.  
It combines **flex sensors**, **vibration motors**, and **Bluetooth communication** to provide real-time finger tracking and tactile response.

---

## 🧩 Features
- Finger tracking using flex sensors (analog input via ESP32)
- Haptic feedback through vibration motors
- Wireless Bluetooth communication
- Compatible with Unity or Unreal Engine for VR input
- Modular design (easy to upgrade each finger module)
- Open firmware for calibration and tuning

---

## ⚙️ Hardware Components
| Component | Description |
|------------|-------------|
| ESP32 | Main microcontroller (WiFi + Bluetooth) |
| Flex Sensors | Finger bend detection |
| Vibration Motors | Haptic feedback output |
| Li-ion Battery | Portable power source |
| MOSFET Drivers | Motor control circuit |
| 3D Printed Glove Frame | Mounting structure |

---

## 🧠 Firmware
Firmware is written in **Arduino (C++)** using the **ESP32 framework**.  
The system reads analog input from flex sensors, maps them to finger angles, and sends data over Bluetooth.

> The code is stored in `/firmware/` directory.

---

## 🧪 Progress Log
You can view all development updates in:  
👉 [progress_log.md](progress_log.md)

---

## 📸 Media
Hardware photos, wiring diagrams, and test videos are in:  
👉 `/media/` and `/docs/` folders.

---

## 🧭 Future Improvements
- Integrate IMU (MPU6050) for full hand rotation tracking  
- Optimize firmware for lower latency  
- Add force feedback (active resistance control)  
- Create Unity plugin for direct hand input mapping  

---

## 🧑‍💻 Author
**Het Patel**  
Explorer of hardware, AI, and physics.  
Focused on building devices that bridge real and virtual worlds.  

---

## ⚖️ License
This project is open-source under the **MIT License** — feel free to use and modify it for your own builds.
