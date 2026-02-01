# NodeMCU MQTT Flow

```mermaid
flowchart TD
    Start --> WiFiConnect
    WiFiConnect --> MQTTConnect
    MQTTConnect --> Subscribe
    Subscribe --> Loop
    Loop -->|Message arrives| Callback
    Callback --> Loop
