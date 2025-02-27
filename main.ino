#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "Charonn";
const char* password = "10101100esiW";

// Sensor pins
#define DHT_PIN 32
#define MQ135_PIN 34
#define MQ9_PIN 33
#define MQ7_PIN 35

// DHT sensor setup
#define DHT_TYPE DHT11
DHT dht_sensor(DHT_PIN, DHT_TYPE);

// Create WebServer object on port 80
WebServer server(80);

// JSON document for sensor data
StaticJsonDocument<512> sensorDoc;
char jsonBuffer[512];

// تابع برای محاسبه MQ135
float calculateMQ135PPM(float raw_value) {
    float voltage = raw_value * (5.0 / 4095.0);
    return 100 * pow(1.75 * (voltage / 5.0), 3);
}

// تابع برای محاسبه سایر سنسورها
float calculatePPM(float raw_value, float clean_air_factor) {
    float voltage = (raw_value / 4095.0) * 3.3;
    float rs = ((3.3 * 10.0) / voltage) - 10.0;
    float ratio = rs / clean_air_factor;
    return 200.0 * pow(ratio, -2.0);
}

void handleRoot() {
    File file = SPIFFS.open("/index.html", "r");
    if (file) {
        server.streamFile(file, "text/html");
        file.close();
    } else {
        server.send(404, "text/plain", "File not found");
    }  
}

void handleCSS() { 
    File file = SPIFFS.open("/styles.css", "r");
    if (file) {
        server.streamFile(file, "text/css");
        file.close();
    }
}

void handleJS() {
    File file = SPIFFS.open("/script.js", "r");
    if (file) {
        server.streamFile(file, "text/javascript");
        file.close();
    }
}

void handleSensorData() {
    // Read sensor values
    float temperature = dht_sensor.readTemperature();
    float humidity = dht_sensor.readHumidity();
    
    float mq7_raw = analogRead(MQ7_PIN);
    float mq9_raw = analogRead(MQ9_PIN);
    float mq135_raw = analogRead(MQ135_PIN);
    
    // Create JSON document
    sensorDoc.clear();
    sensorDoc["temperature"] = isnan(temperature) ? 0 : temperature;
    sensorDoc["humidity"] = isnan(humidity) ? 0 : humidity;
    
    sensorDoc["mq7"]["co"] = calculatePPM(mq7_raw, 10.0);
    sensorDoc["mq9"]["lpg"] = calculatePPM(mq9_raw, 5.0);
    sensorDoc["mq135"]["co2"] = calculateMQ135PPM(mq135_raw);
    
    // Calculate air quality
    float co2_value = sensorDoc["mq135"]["co2"];
    const char* airQuality;
    if (co2_value < 100) airQuality = "Good 😊";
    else if (co2_value < 250) airQuality = "Fair 😐";
    else if (co2_value < 500) airQuality = "Poor 😷";
    else airQuality = "Very Poor 🤢";
    
    sensorDoc["airQuality"] = airQuality;
    
    // Serialize JSON
    serializeJson(sensorDoc, jsonBuffer);
    
    // Send response
    server.send(200, "application/json", jsonBuffer);
}

void setup() {
    Serial.begin(115200);
    
    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("An error occurred while mounting SPIFFS");
        return;
    }
    
    // Initialize sensors
    dht_sensor.begin();
    
    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println(WiFi.localIP());
    
    // Set up web server routes
    server.on("/", HTTP_GET, handleRoot);
    server.on("/styles.css", HTTP_GET, handleCSS);
    server.on("/script.js", HTTP_GET, handleJS);
    server.on("/sensor-data", HTTP_GET, handleSensorData);
    
    // CORS Headers
    server.enableCORS(true);
    
    // Start server
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
    delay(2); // Allow the CPU to switch to other tasks
}
