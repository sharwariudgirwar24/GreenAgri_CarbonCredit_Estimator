# GreenAgri — Carbon Credit Estimation System

An IoT + Machine Learning based prototype that estimates how much carbon a farm or industry is saving or emitting, and shows it on a simple dashboard as "carbon credits."

---

## What This Project Does

1. **Sensors** collect real-world data (soil moisture, temperature, gas levels, etc.)
2. **ESP32** sends this data to the cloud (Firebase)
3. An **ML model** uses this data to predict carbon emitted/saved
4. A **dashboard** shows this as an easy-to-read carbon credit score

```
Sensors → ESP32 → Firebase → ML Model → Carbon Credit Score → Dashboard
```

---

## Why This Project

Right now, checking carbon credits needs manual audits or expensive satellite/scientific models. Small farmers can't easily access this. This project builds a **low-cost, automated** alternative using basic sensors and ML.

---

## Project Modules

- **Module 1** — Sensors + ML (collect data, predict carbon value) ✅ *in progress*
- **Module 2** — Web Dashboard (show data + credits) ⏳ *upcoming*

---

## Hardware Used

- ESP32 (microcontroller)
- DHT22 (temperature & humidity)
- Soil Moisture Sensor
- MQ135 (gas sensor)
- NPK/pH Sensor (soil nutrients)

---

## Files in This Project

| File | What It Is |
|---|---|
| `Project_Brief.pdf` | Problem statement, objectives, reference paper |
| `wiring_diagram.png` | How sensors connect to ESP32 |
| `carbon_credit_synthetic_dataset.csv` | Raw sample data |
| `cleaned_carbon_credit_dataset.csv` | Cleaned, ready-to-use data |
| `Module1_Data_Cleaning_EDA.ipynb` | Code for cleaning data + graphs |
| `eda_outputs/` | Graphs/charts from the data |

---

## Tools Used

Python, pandas, scikit-learn, Firebase, ESP32, React (for Module 2)

---

## Progress So Far

- ✅ Problem statement & objectives done
- ✅ Hardware wiring planned
- ✅ Sample dataset created
- ✅ Data cleaning & graphs done
- ⏳ ML model (next step)
- ⏳ Dashboard (Module 2)

---
