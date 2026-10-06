# GreenAgri — Carbon Credit Estimation System

An IoT + Machine Learning based prototype that estimates how much carbon a farm or industry is saving or emitting, and shows it as an easy-to-read "carbon credit" score.

---

## What This Project Does

1. **Sensors** collect real-world data (soil moisture, temperature, gas levels, etc.)
2. **ESP32** sends this data to the cloud
3. An **ML model** uses this data to predict carbon emitted/saved
4. A **dashboard** (coming in Module 2) shows this as a carbon credit score

```
Sensors → ESP32 → Cloud → ML Model → Carbon Credit Score → Dashboard
```

---

## Why This Project

Checking carbon credits today needs manual audits or expensive satellite/scientific models, which small farmers can't easily access. This project builds a **low-cost, automated** alternative using basic sensors and ML.

---

## Project Modules

- **Module 1** — Sensors + Data + ML (collect data, clean it, predict carbon value) ✅ *in progress*
- **Module 2** — Web Dashboard (show data + credits) ⏳ *upcoming*

---

## Folder Structure

```
GreenAgri_CarbonCredit_Estimator/
├── data/
│   ├── raw/
│   │   ├── carbon_credit_synthetic_dataset.csv      # Original sample data
│   │   └── carbon_credit_synthetic_dataset.xlsx
│   └── processed/
|       ├── cleaned_carbon_credit_dataset.csv        # Cleaned, ready-to-use data 
├── notebook/
│   ├── eda_outputs/                                 # Graphs generated from the data
│   │   ├── 01_correlation_heatmap.png
│   │   ├── 02_carbon_credit_distribution.png
│   │   ├── 03_emission_by_practice.png
│   │   ├── 04_credit_by_crop.png
│   │   ├── 05_soilmoisture_vs_emission.png
│   │   └── 06_emission_category_count.png
│   └── Module1_Data_Cleaning_EDA.ipynb              # Code for cleaning data + making graphs
└── README.md
```

---

## Hardware Used (for Sensor Data Collection)

- ESP32 (microcontroller)
- DHT22 (temperature & humidity)
- Soil Moisture Sensor
- MQ135 (gas sensor)

---

## Tools Used

Python, pandas, scikit-learn, Matplotlib/Seaborn, Firebase, ESP32, React (for Module 2)

---

## Progress So Far

- ✅ Problem statement & objectives done
- ✅ Hardware wiring planned
- ✅ Sample dataset created (raw)
- ✅ Data cleaned + graphs generated
- ✅ Project pushed to GitHub
- ⏳ ML model (next step)
- ⏳ Dashboard (Module 2)

---

## Repository

[github.com/sharwariudgirwar24/GreenAgri_CarbonCredit_Estimator](https://github.com/sharwariudgirwar24/GreenAgri_CarbonCredit_Estimator)

---

## Reference Paper

Gokul et al. (2026). *Carbon credit mechanisms for sustainable agriculture and opportunities in North East India.* Discover Sustainability.

This project builds a working prototype for an idea the paper only discusses in theory — making carbon credit tracking simple and affordable using IoT + ML.
