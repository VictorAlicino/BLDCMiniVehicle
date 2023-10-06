#include <Arduino.h>
#include <Wire.h>
#include <WebServer.h>
#include "wireless_conn.hpp"
#include "motors_control.hpp"
#include "utils.hpp"
#include "config.h"

mcu_state_t mcu_status = MCU_STATE_INIT;	// MCU Status (see utils.hpp)
conn_state_t conn_status = CONN_STATE_INIT;	// Connection Status (see utils.hpp)
WebServer *server;
String command; // In order to not instantiate a new String object every loop, we declare it here (save us some time)

void setup(){
	const char* TAG = "SETUP";
	ESP_LOGD(TAG, "Using ARDUINO IDE");
	ESP_LOGI(TAG, "BLDC 'Canoa' Controller");

	// Initializing Pins Direction
	ESP_LOGD(TAG, "Setting GPIOs direction");

	pinMode(BUILTIN_LED, OUTPUT); // Built-in LED
	ESP_LOGD(TAG, "Built-in LED activated");

	pinMode(PWR, OUTPUT); // Controller Board On/Off Relay
	ESP_LOGD(TAG, "Controller Board Relay armed");
	safety_test(); // Testing if the motor is already on for some reason, and turns it off if it is

	pinMode(BOARD_PWR, INPUT_PULLDOWN); 
	// Check the optocoupler attached to board power in order to know if the board is on or off
	ESP_LOGD(TAG, "Board Power Optocoupler activated");

	status_led_init(); // Initializing Status LED

	// Intializing onboard WiFi
	wifi_start();
	WiFi.onEvent(wifi_events_watchdog);

	// Intializing WebServer
	web_server_start();

	// Waiting for controller to connect
	ESP_LOGD(TAG, "Waiting for Client connection");
	do{
		
	}while(WiFi.softAPgetStationNum() != 1);

	// Waiting for controller to send "PON" (Power On) command
	do{
		server->handleClient();
	}while(server->arg("State") != "PON");
	switch_board_power(ON);

	// Activating Controller Board
	do{
		// This shouldn't take long, 
	}while(digitalRead(BOARD_PWR) != HIGH); // Waiting for Controller Board to turn on
	// Initializing I²C Bus
	// I²C Configuration -> Slave Addr = 0x52 / SDA = 21 / SCL = 22 / Clock = 100kHz
	Wire.begin(0x52, 21, 22, 100000);
	Wire.onRequest(_i2c_callback); // I²C Callback Function for send data to Controller Board
	ESP_LOGD(TAG, "I2C Bus Initialized");
	control_2_board(0, 0, 0);

	ESP_LOGI(TAG, "Setup Complete");
}

void loop(){
	server->handleClient();

	command = server->arg("State");
	if (command == "F")		{motor_forward();}			// Forward
	else if (command == "B") {motor_backward();}		// Backward
	else if (command == "L") {motor_left();}			// Left
	else if (command == "R") {motor_right();}			// Right
	else if (command == "I") {motor_forward_right();}	// Forward Right
	else if (command == "G") {motor_forward_left();}	// Forward Left
	else if (command == "J") {motor_backward_right();}	// Backward Right
	else if (command == "H") {motor_backward_left();}	// Backward Left
	else if (command == "0") {motor_speed(0);}
	else if (command == "1") {motor_speed(10);}
	else if (command == "2") {motor_speed(20);}
	else if (command == "3") {motor_speed(30);}
	else if (command == "4") {motor_speed(40);}
	else if (command == "5") {motor_speed(50);}
	else if (command == "6") {motor_speed(60);}
	else if (command == "7") {motor_speed(70);}
	else if (command == "8") {motor_speed(80);}
	else if (command == "9") {motor_speed(100);}
	else if (command == "S") {motor_stop();}
	else if (command == "POFF") {switch_board_power(OFF);} // Vai saber né
	else if (command == "wait") { /* Do nothing */ }
	else {control_2_board(0, 0, 0);}
	vTaskDelay(100 / portTICK_PERIOD_MS);

	if(conn_status == CONN_STATE_DISCONNECTED){ 
		ESP_LOGD("LOOP", "Client disconnected"); 
		EMERGENCY_SHUTDOWN();
	}
	if(digitalRead(BOARD_PWR) == LOW){ 
		ESP_LOGD("LOOP", "Board offline"); 
		EMERGENCY_SHUTDOWN();
	}
}