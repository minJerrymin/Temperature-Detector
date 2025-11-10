# Temperature-Detector — “Feeling the Natural Mood”

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
**Initial idea**
![48c1a1bfb2a75ff964f960df79d2c4d3](https://github.com/user-attachments/assets/09779cfc-8c3e-4dbb-a6b2-59d1960c3978)

**System Workflow Logic**
![6fa406836d73512d698146f7e9db0fd3](https://github.com/user-attachments/assets/994fd4e2-f1f4-448c-8c33-49fb9b2ec53b)




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

![298bb52ad01cd176cb6e1e3b82093a35](https://github.com/user-attachments/assets/9d475e72-16c5-4bcc-bb57-78c8529db38f)

![d15d88450b7323079f6bb0023cbe8176](https://github.com/user-attachments/assets/b8dbf99f-6797-456c-90eb-b06dc66c2f4f)

![88d33af95364d043f44f6be090248ab5](https://github.com/user-attachments/assets/130926f2-6cbb-460d-9313-1cf44c3443fd)

**Luminaire Color Grid**

[download demo video](demonstration.mp4)








---

## Possible future Improvements

* Use temperature sensors with higher refresh rates and resolutions.
* Optimising the temperature-colour conversion function enables smoother colour transitions.
* Add ambient “breathing” animation when temperature is stable

