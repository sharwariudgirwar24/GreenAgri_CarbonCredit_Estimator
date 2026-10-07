"""
===========================================================================
 Module 1 - Fetch Sensor Data, Predict Carbon Credit, Push Result Back
 Project : GreenAgri Carbon Credit Estimator
 Purpose : Uses the Firebase connection from firebase_init.py to pull live
           sensor readings, run them through the trained ML model, and
           write the predicted carbon credit score back to Firebase.
===========================================================================
"""

from firebase_connection import db   # reuses the connection set up in firebase_init.py
import pandas as pd
import joblib
from datetime import datetime

# ---------------------------------------------------------------------
# STEP 1: Fetch Raw Sensor Data
# ---------------------------------------------------------------------
LOCATION = "Farm_A"
ref = db.reference(f"sensor_readings/{LOCATION}")
raw_data = ref.get()

if raw_data is None:
    raise ValueError("No data found at this path. Confirm ESP32 has pushed readings.")

# ---------------------------------------------------------------------
# STEP 2: Detect Structure -- single flat reading vs multiple push() entries
# ---------------------------------------------------------------------
first_value = next(iter(raw_data.values()))
is_multi_reading = isinstance(first_value, dict)

if is_multi_reading:
    print(f"Detected MULTIPLE readings ({len(raw_data)} entries) -- using push() structure.")
    entries = raw_data.items()
else:
    print("Detected a SINGLE flat reading -- current code is overwriting each time (set()).")
    entries = [("latest", raw_data)]

# ---------------------------------------------------------------------
# STEP 3: Convert Firebase Dict -> Pandas DataFrame
# ---------------------------------------------------------------------
records = []
for push_id, entry in entries:
    records.append({
        "Record_ID": push_id,
        "Location": LOCATION,
        "Temperature_C": entry.get("temperature"),
        "Humidity_%": entry.get("humidity"),
        "Soil_Moisture_%": entry.get("soil_moisture"),
        "Soil_Raw_ADC": entry.get("soil_raw"),
        "Gas_Sensor_ppm": entry.get("air_quality"),
    })

df = pd.DataFrame(records)
df["Date"] = datetime.now()

# ---------------------------------------------------------------------
# STEP 4: Fill Columns the Model Needs but Hardware Isn't Sending Yet
# ---------------------------------------------------------------------
df["Soil_pH"] = 6.5                     # placeholder until a pH sensor is added
df["Energy_Consumption_kWh"] = 100.0    # placeholder until an energy meter is added
df["Farming_Practice"] = "No-Till"      # placeholder -- replace with actual farm metadata
df["Crop_Type"] = "Wheat"               # placeholder -- replace with actual farm metadata

print("\nLive sensor data as DataFrame:")
print(df)

# ---------------------------------------------------------------------
# STEP 5: Load Trained Model and Predict
# ---------------------------------------------------------------------
model = joblib.load("carbon_credit_model.pkl")

feature_cols = ["Soil_Moisture_%", "Temperature_C", "Humidity_%", "Soil_pH",
                 "Gas_Sensor_ppm", "Energy_Consumption_kWh", "Farming_Practice", "Crop_Type"]

predictions = model.predict(df[feature_cols])
df["Predicted_Carbon_Credit_Score"] = predictions

print("\nPredictions:")
print(df[["Record_ID", "Predicted_Carbon_Credit_Score"]])

# ---------------------------------------------------------------------
# STEP 6: Write Predictions Back to Firebase
# ---------------------------------------------------------------------
pred_ref = db.reference(f"predictions/{LOCATION}")

for _, row in df.iterrows():
    pred_ref.push({
        "temperature": row["Temperature_C"],
        "humidity": row["Humidity_%"],
        "soil_moisture": row["Soil_Moisture_%"],
        "gas_ppm": row["Gas_Sensor_ppm"],
        "predicted_carbon_credit_score": row["Predicted_Carbon_Credit_Score"],
        "timestamp": datetime.now().isoformat(),
    })

print(f"\nPushed {len(df)} prediction(s) to Firebase under: predictions/{LOCATION}")

# ---------------------------------------------------------------------
# STEP 7: Save Locally Too (optional, useful for your report)
# ---------------------------------------------------------------------
df.to_csv("live_sensor_data_with_predictions.csv", index=False)
print("Also saved locally as: live_sensor_data_with_predictions.csv")