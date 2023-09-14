#include <Arduino.h>
#include <Webserver.h>
#include <WiFi.h> 
#include "wireless_conn.hpp"
#include "utils.hpp"

extern WebServer *server;

void wifi_start(){
    const char* TAG = "WIFI";
    WiFi.mode(WIFI_AP); // Access Point Mode
    WiFi.softAP(
        WIFI_SSID,      // Access Point Name
        NULL,           // Access Point Password
        1,              // Channel
        0,              // Broadcast SSID (0 = Yes, 1 = No)
        1               // Max Connections
        );
    ESP_LOGD(TAG, "Access Point Started");

    IPAddress IP = WiFi.softAPIP(); // Access Point IP Address
    ESP_LOGI(TAG, "Access Point IP Address: %s", IP.toString().c_str());
}

void web_server_start(){
    const char* TAG = "WEB_SERVER";

    server = new WebServer(80);

    server->on("/", [](){
        if( server->hasArg("State") ){
            Serial.println(server->arg("State"));
        }
        server->send ( 200, "text/html", "" );
        delay(1);
    });

    server->onNotFound([](){
        if( server->hasArg("State") ){
            Serial.println(server->arg("State"));
        }
        server->send ( 200, "text/html", "" );
        delay(1);
    });

    server->begin();
    ESP_LOGI(TAG, "Web Server Started");
}