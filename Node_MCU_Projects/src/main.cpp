#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/* ---------- WiFi ---------- */
const char* ssid     = "Airtel_nand_2308";
const char* password = "air51529";

/* ---------- MQTT ---------- */
const char* mqtt_server = "192.168.1.8";
const int   mqtt_port   = 1883;

/* ---------- MQTT Topics ---------- */
const char* sub_topic = "test/topic";
const char* pub_topic = "test/nodemcu/status";

/* ---------- Objects ---------- */
WiFiClient espClient;
PubSubClient client(espClient);

/* ---------- MQTT callback ---------- */
void mqttCallback(char* topic, byte* payload, unsigned int length) {
    String message;

    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    Serial.print("Received [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println(message);

    if (String(topic) == sub_topic) {
        if (message == "ON") {
            digitalWrite(LED_BUILTIN, LOW);   // LED ON
        } else if (message == "OFF") {
            digitalWrite(LED_BUILTIN, HIGH);  // LED OFF
        }
    }
}

/* ---------- MQTT reconnect ---------- */
void mqttReconnect() {
    while (!client.connected()) {
        Serial.print("Connecting to MQTT... ");

        String clientId = "NodeMCU-";
        clientId += String(ESP.getChipId());

        if (client.connect(clientId.c_str())) {
            Serial.println("clientId: " + clientId + " connected");
            client.subscribe(sub_topic);
        } else {
            Serial.print("failed, rc=");
            Serial.println(client.state());
            delay(2000);
        }
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // LED OFF

    /* WiFi connect */
    WiFi.begin(ssid, password);
    Serial.print("Connecting WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    /* MQTT setup */
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(mqttCallback);
}

void loop() {
    if (!client.connected()) {
        mqttReconnect();
    }

    client.loop();

    static unsigned long lastPublish = 0;
    if (millis() - lastPublish > 5000) {
        lastPublish = millis();
        client.publish(pub_topic, "NodeMCU is alive");
    }
}
