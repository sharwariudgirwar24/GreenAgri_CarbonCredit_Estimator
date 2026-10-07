#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include "DHT.h"

/*
  GreenAgri Carbon Credit Estimator
  Step 2 - ESP32 + Firebase Realtime Database (FIXED VERSION)

  Sensors:
    DHT22        -> GPIO4
    Soil Sensor  -> GPIO34
    MQ-135       -> GPIO35

  Data is sent to Firebase every 15 seconds.
*/


// --------------------------------------------------
// WIFI
// --------------------------------------------------

#define WIFI_SSID "vivo 1920"
#define WIFI_PASSWORD "12345678"

// --------------------------------------------------
// FIREBASE
// --------------------------------------------------

#define API_KEY "AIzaSyCOfkObRrIyn3Vbt3MTuCkNgtSQGoFSZb8"

#define DATABASE_URL "https://greenagri-aff32-default-rtdb.asia-southeast1.firebasedatabase.app/"

// --------------------------------------------------
// SENSOR PINS
// --------------------------------------------------

#define DHTPIN 4
#define DHTTYPE DHT22

#define SOIL_PIN 34
#define MQ135_PIN 35

DHT dht(DHTPIN, DHTTYPE);

// --------------------------------------------------
// FIREBASE OBJECTS
// --------------------------------------------------

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// --------------------------------------------------
// TIMER
// --------------------------------------------------

unsigned long lastSendTime = 0;

const unsigned long sendInterval = 15000;   // 15 seconds


void setup() {

  Serial.begin(115200);
  delay(1000);

  dht.begin();

  Serial.println();
  Serial.println("=====================================");
  Serial.println(" GreenAgri Carbon Credit Estimator");
  Serial.println(" ESP32 + Firebase");
  Serial.println("=====================================");


  // ------------------------------------------------
  // CONNECT TO WIFI
  // ------------------------------------------------

  Serial.print("Connecting to WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


  // ------------------------------------------------
  // FIREBASE CONFIGURATION
  // ------------------------------------------------

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;


  // ------------------------------------------------
  // ANONYMOUS FIREBASE LOGIN
  // ------------------------------------------------

  Serial.println("Signing in to Firebase...");

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase sign-up success!");
  }
  else {
    Serial.print("Firebase sign-up failed: ");
    Serial.println(config.signer.signupError.message.c_str());
  }


  // ------------------------------------------------
  // START FIREBASE
  // ------------------------------------------------

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("Firebase initialized.");
  Serial.println();

}


// ==================================================
// LOOP
// ==================================================

void loop() {

  // ------------------------------------------------
  // READ SENSORS
  // ------------------------------------------------

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int soilRaw = analogRead(SOIL_PIN);
  int soilPercent = map(soilRaw, 4095, 1200, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  int mq135Raw = analogRead(MQ135_PIN);


  // ------------------------------------------------
  // PRINT SENSOR DATA
  // ------------------------------------------------

  Serial.println("-------------------------------------");

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT22: failed to read");
  }
  else {
    Serial.print("Temperature   : ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity      : ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.print("Soil moisture : ");
  Serial.print(soilPercent);
  Serial.print(" %  (raw: ");
  Serial.print(soilRaw);
  Serial.println(")");

  Serial.print("Air quality   : ");
  Serial.println(mq135Raw);


  // ------------------------------------------------
  // SEND TO FIREBASE EVERY 15 SECONDS
  // FIXED: all values combined into ONE JSON object,
  // pushed ONCE, instead of 5 separate pushes
  // ------------------------------------------------

  if (Firebase.ready() &&
      (millis() - lastSendTime >= sendInterval ||
       lastSendTime == 0)) {

    lastSendTime = millis();

    Serial.println();
    Serial.println("Sending data to Firebase...");

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Skipping push: DHT22 read failed this cycle.");
    }
    else {

      FirebaseJson json;
      json.set("temperature", temperature);
      json.set("humidity", humidity);
      json.set("soil_moisture", soilPercent);
      json.set("soil_raw", soilRaw);
      json.set("air_quality", mq135Raw);
      json.set("timestamp", (int)(millis() / 1000));

      String path = "/sensor_readings/Farm_A";

      if (Firebase.RTDB.pushJSON(&fbdo, path.c_str(), &json)) {
        Serial.println("Data pushed to Firebase successfully!");
      }
      else {
        Serial.print("Push failed: ");
        Serial.println(fbdo.errorReason());
      }

    }

  }

  delay(2000);

}