#include <Arduino.h>
#include <Wire.h>
#include <WebServer.h>
#include "wireless_conn.hpp"
#include "motors_control.hpp"
#include "utils.hpp"

mcu_state_t mcu_status;		// MCU Status (see utils.hpp)
conn_state_t conn_status;	// Connection Status (see utils.hpp)
WebServer *server;

float POWER_LIMIT = 50.0; // Power Limit for motors [0.0 - 100.0] (MUST BE FLOAT!)
String command;

void setup(){
	const char* TAG = "SETUP";
	ESP_LOGD(TAG, "Using ARDUINO IDE");
	ESP_LOGI(TAG, "BLDC 'Canoa' Controller");

	// Initializing Pins Direction
	ESP_LOGD(TAG, "Setting GPIOs direction");
	pinMode(2, OUTPUT); // Built-in LED
	ESP_LOGD(TAG, "Built-in LED activated");
	pinMode(LED0, OUTPUT); // Status LED 1
	pinMode(LED1, OUTPUT); // Status LED 2
	ESP_LOGD(TAG, "Status LEDs activated");
	pinMode(PWR, OUTPUT); // Controller Board On/Off Relay
	ESP_LOGD(TAG, "Controller Board Relay armed");

	// Initializing LED Status task
	/*
	xTaskCreate(
		status_led_blink,	// Task Function
		"Status LED Task",	// Task Name
		10000,				// Task Stack Size
		NULL,				// Task Parameters
		1,					// Task Priority
		NULL				// Task Handler
	);*/

	
	// Intializing onboard WiFi
	wifi_start();

	// Intializing WebServer
	web_server_start();

	// Initializing I²C Bus
	// I²C Configuration -> Slave Addr = 0x52 / SDA = 21 / SCL = 22 / Clock = 100kHz
	Wire.begin(0x52, 21, 22, 100000);
	Wire.onRequest(_i2c_callback); // I²C Callback Function for send data to Controller Board
	ESP_LOGD(TAG, "I2C Bus Initialized");
	ESP_LOGI(TAG, "Setup Complete");
}

void loop(){
	control_2_board(0,0,0);
    server->handleClient();
    
	command = server->arg("State");
    if (command == "F") 	 {control_2_board(100, 0, POWER_LIMIT); ESP_LOGD("LOOP", "FOWARD");}// Forward
    else if (command == "B") {control_2_board(-100, 0, POWER_LIMIT); ESP_LOGD("LOOP", "BACKWARD");}// Backward
    else if (command == "L") {control_2_board(0, -100, POWER_LIMIT); ESP_LOGD("LOOP", "LEFT");} // Left
    else if (command == "R") {control_2_board(0, 100, POWER_LIMIT); ESP_LOGD("LOOP", "RIGHT");} // Right
    else if (command == "I") {control_2_board(0, 50, POWER_LIMIT); ESP_LOGD("LOOP", "FORWARD RIGHT");} // Forward Right
    else if (command == "G") {control_2_board(0, -50, POWER_LIMIT); ESP_LOGD("LOOP", "FORWARD LEFT");} // Forward Left
    else if (command == "J") {ESP_LOGD("LOOP", "Unable to perform Backward Right");} // Backward Right
    else if (command == "H") {ESP_LOGD("LOOP", "Unable to perform Backward Left");} // Backward Left
    else if (command == "0") {POWER_LIMIT = 0.0; ESP_LOGD("LOOP", "SPEED = 0");}
    else if (command == "1") {POWER_LIMIT = 10.0; ESP_LOGD("LOOP", "SPEED = 10");}
    else if (command == "2") {POWER_LIMIT = 20.0; ESP_LOGD("LOOP", "SPEED = 20");}
    else if (command == "3") {POWER_LIMIT = 30.0; ESP_LOGD("LOOP", "SPEED = 30");}
    else if (command == "4") {POWER_LIMIT = 40.0; ESP_LOGD("LOOP", "SPEED = 40");}
    else if (command == "5") {POWER_LIMIT = 50.0; ESP_LOGD("LOOP", "SPEED = 50");}
    else if (command == "6") {POWER_LIMIT = 60.0; ESP_LOGD("LOOP", "SPEED = 60");}
    else if (command == "7") {POWER_LIMIT = 70.0; ESP_LOGD("LOOP", "SPEED = 70");}
    else if (command == "8") {POWER_LIMIT = 80.0; ESP_LOGD("LOOP", "SPEED = 80");}
    else if (command == "9") {POWER_LIMIT = 100.0; ESP_LOGD("LOOP", "SPEED = 100");}
    else if (command == "S") {control_2_board(0,0,0); ESP_LOGD("LOOP", "STOP");}
	else {control_2_board(0,0,0); ESP_LOGD("LOOP", "STOP");}
}