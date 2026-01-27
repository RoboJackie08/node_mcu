#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "wifi_mgr.h"

/* ===== USER CONFIG ===== */
#define WIFI_SSID     "Airtel_nand_2308"
#define WIFI_PASS     "air51529"

/* ===== INTERNAL CONFIG ===== */
#define WIFI_CONNECT_TIMEOUT_MS 10000
#define WIFI_RETRY_INTERVAL_MS  5000

static unsigned long last_retry = 0;
static bool wifi_connected = false;

/* ===== Wi-Fi EVENT HANDLERS ===== */
static WiFiEventHandler gotIpHandler;
static WiFiEventHandler disconnectHandler;

static void onGotIP(const WiFiEventStationModeGotIP& event)
{
    wifi_connected = true;
    Serial.println("[WiFi] Connected");
    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.localIP());
}

static void onDisconnected(const WiFiEventStationModeDisconnected& event)
{
    wifi_connected = false;
    Serial.println("[WiFi] Disconnected");
}

/* ===== PUBLIC API ===== */
void wifi_init(void)
{
    Serial.println("[WiFi] Init");

    WiFi.mode(WIFI_AP_STA);

    /* Fallback AP (always available) */
    WiFi.softAP("ESP_SETUP", "12345678");
    Serial.print("[WiFi] AP IP: ");
    Serial.println(WiFi.softAPIP());

    /* Register events */
    gotIpHandler = WiFi.onStationModeGotIP(onGotIP);
    disconnectHandler = WiFi.onStationModeDisconnected(onDisconnected);

    /* Start STA connection */
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED &&
           millis() - start < WIFI_CONNECT_TIMEOUT_MS)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
}

void wifi_loop(void)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        unsigned long now = millis();
        if (now - last_retry > WIFI_RETRY_INTERVAL_MS)
        {
            last_retry = now;
            Serial.println("[WiFi] Reconnecting...");
            WiFi.disconnect();
            WiFi.begin(WIFI_SSID, WIFI_PASS);
        }
    }
}

bool wifi_is_connected(void)
{
    return wifi_connected;
}

int wifi_get_rssi(void)
{
    if (wifi_connected)
        return WiFi.RSSI();
    return -100;
}
