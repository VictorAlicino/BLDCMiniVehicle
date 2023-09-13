#line 1 "C:\\Users\\victo\\Documents\\GitRepos\\BLDCMiniVehicle\\mcu_control\\controller\\controller.ino"
#include <Arduino.h>
#include <Wire.h>
#include "wireless_conn.hpp"

#line 5 "C:\\Users\\victo\\Documents\\GitRepos\\BLDCMiniVehicle\\mcu_control\\controller\\controller.ino"
void _i2c_callback();
#line 9 "C:\\Users\\victo\\Documents\\GitRepos\\BLDCMiniVehicle\\mcu_control\\controller\\controller.ino"
void setup();
#line 35 "C:\\Users\\victo\\Documents\\GitRepos\\BLDCMiniVehicle\\mcu_control\\controller\\controller.ino"
void loop();
#line 5 "C:\\Users\\victo\\Documents\\GitRepos\\BLDCMiniVehicle\\mcu_control\\controller\\controller.ino"
void _i2c_callback(){

}

void setup(){
	const char* TAG = "SETUP";
	ESP_LOGD(TAG, "Using ARDUINO IDE");
	ESP_LOGI(TAG, "BLDC 'Canoa' Controller");

	// Initializing Pins Direction
	ESP_LOGD(TAG, "Setting GPIOs direction");
	pinMode(2, OUTPUT); // Built-in LED
	ESP_LOGD(TAG, "IO2 set as OUTPUT");
	pinMode(15, OUTPUT); // Controller Board On/Off Relay
	ESP_LOGD(TAG, "IO15 set as OUTPUT");

	// Intializing onboard WiFi
	wifi_start();

	// Intializing WebServer
	web_server_start();

	// Initializing I²C Bus
	// I²C Configuration -> Slave Addr = 0x52 / SDA = 21 / SCL = 22 / Clock = 100kHz
	Wire.begin(0x52, 21, 22, 100000);
	Wire.onRequest(_i2c_callback);
	ESP_LOGD(TAG, "I2C Bus Initialized");
	ESP_LOGI(TAG, "Setup Complete");
}

void loop(){
	
}
