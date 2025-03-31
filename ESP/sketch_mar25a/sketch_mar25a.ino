#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "iAM-RnD";   // Change this
const char* password = "1234567890";  // Change this

// MQTT Broker settings (Use a public broker like test.mosquitto.org or HiveMQ)
const char* mqtt_server = "10.129.2.43";  // Public MQTT broker
const int mqtt_port = 1883;  // MQTT port (default for unencrypted connection)
const char* mqtt_topic = "esp32/test";  // Topic name
const char* mqtt_user = "admin";  // Change this
const char* mqtt_pass = "admin123";  // Change this

WiFiClient espClient;
PubSubClient client(espClient);

// Function to connect to WiFi
void setup_wifi() {
    delay(10);
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
}

// Function to reconnect to MQTT broker if disconnected
void reconnect() {
    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");
        if (client.connect("ESP32_Client",mqtt_user, mqtt_pass)) {
            Serial.println("Connected!");
            client.subscribe(mqtt_topic);  // Subscribe to the topic
        } else {
            Serial.print("Failed, retrying in 5s...");
            delay(5000);
        }
    }
}

// Callback function when a message is received
void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message received on topic: ");
    Serial.println(topic);

    Serial.print("Message: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
    }
    Serial.println();
}

// Setup function
void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

// Loop function
void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Publish a message every 5 seconds
    static unsigned long lastMsg = 0;
    if (millis() - lastMsg > 5000) {
        lastMsg = millis();
        const char* msg = "Hello from ESP32!";
        Serial.print("Publishing message: ");
        Serial.println(msg);
        client.publish(mqtt_topic, msg);
    }
}
