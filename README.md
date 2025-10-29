# Temperature-Detector

**Temperature-Controlled Colour-Changing Lighting System Based on Arduino MKR WiFi 1010 and MQTT Architecture**

---

## Project Overview

This project employs an Arduino MKR WiFi 1010 microprocessor and a DHT22 temperature sensor to construct an automated temperature-controlled lighting system. It automatically adjusts light colour based on real-time temperature readings and facilitates remote information transmission between the microprocessor and Vespera via the MQTT protocol. Furthermore, the system can switch between different brightness modes to accommodate varying requirements.


---

## Inspiration

This concept stems from an exploration of how we perceive temperature—not merely as a numerical value, but as a sensory experience.
Instead of showing numbers on a screen, this project visualizes temperature as color — turning data into emotion，fostering a spiritual resonance between humanity and nature. Warm tones reflect comfort or intensity, while cool hues bring calmness, echoing nature’s own moods.

---
## Concept sketches

![48c1a1bfb2a75ff964f960df79d2c4d3](https://github.com/user-attachments/assets/09779cfc-8c3e-4dbb-a6b2-59d1960c3978)




---
## Features 

* Real-time temperature sensing match to smooth color transition across light spectrum on Vespera

* Mode switching to accommodate varying brightness requirements


---
## Hardware requirements & connection
| Component | 
| --------- | 
| Arduino MKR WiFi 1010    | 
| DHT22     |
| Self-lock Switch| 

<img width="1838" height="908" alt="屏幕截图 2025-10-29 005900" src="https://github.com/user-attachments/assets/cc8b72a4-df7f-4a2d-8d03-7be95bbca8ca" />


 *When the switch is pressed (LOW), the system enters night mode with dimmed lighting.*


---

## Project file 

| file | description |
| --------- | --------- |
| DHT22-_test    | sensor test programme |
| Integrated_system   |The code used in final prototype，added control procedures with sensors and switches, along with temperature-colour conversion functions|
| mkr1010_mqtt_simple| Wi-Fi & MQTT connection process; colour code definition| 


---

## Demonstration 

**Appearance display**


![d23d20b59819054902dd59bd8081ee33](https://github.com/user-attachments/assets/1eb257d0-4366-412b-99a8-5d61b6454694)






---

## Future Improvements

* Use temperature sensors with higher refresh rates and resolutions such as DHT11 and BME280
* Optimising the temperature-colour conversion function enables smoother colour transitions.
* Add ambient “breathing” animation when temperature is stable

