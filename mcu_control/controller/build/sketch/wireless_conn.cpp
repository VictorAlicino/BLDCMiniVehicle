#line 1 "C:\\Users\\victo\\Documents\\GitRepos\\BLDCMiniVehicle\\mcu_control\\controller\\wireless_conn.cpp"
#include <Arduino.h>
#include <WebServer.h>
#include "wireless_conn.hpp"

WebServer server(80);

#define WIFI_SSID "Canoa"

void wifi_start(){
    const char* TAG = "WIFI";
    WiFi.mode(WIFI_AP); // Access Point Mode
    WiFi.softAP(WIFI_SSID); // Access Point Name
    ESP_LOGD(TAG, "Access Point Started");

    IPAddress IP = WiFi.softAPIP(); // Access Point IP Address
    ESP_LOGI(TAG, "Access Point IP Address: %s", IP.toString().c_str());
}

void web_server_start(){
    const char* TAG = "WEB_SERVER";
    server.on("/", [](){
        if( server.hasArg("State") ){
            Serial.println(server.arg("State"));
        }
        server.send ( 200, "text/html", "" );
        delay(1);
    });

    server.onNotFound([](){
        if( server.hasArg("State") ){
            Serial.println(server.arg("State"));
        }
        server.send ( 200, "text/html", "" );
        delay(1);
    });

}