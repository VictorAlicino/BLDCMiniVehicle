#include <Arduino.h>
#include "utils.hpp"
#include "config.h"
#include "motors_control.hpp"

extern mcu_state_t mcu_status;
extern conn_state_t conn_status;

void status_led_init(){
    const char* TAG = "UTILS";
	pinMode(LED0, OUTPUT); // Status LED 1
	pinMode(LED1, OUTPUT); // Status LED 2
	ESP_LOGD(TAG, "Status LEDs activated");

    // Initializing LED Status task
	xTaskCreate(
		status_led_blink,	// Task Function
		"Status LED Task",	// Task Name
		10000,				// Task Stack Size
		NULL,				// Task Parameters
		1,					// Task Priority
		NULL				// Task Handler
	);
	ESP_LOGD(TAG, "Status LED Task Initialized");
}

void status_led_blink(void * param){
    while(true){
        switch(conn_status){
            case CONN_STATE_INIT:
            case CONN_STATE_READY:
                digitalWrite(LED0, HIGH);
                digitalWrite(LED1, HIGH);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                digitalWrite(LED1, LOW);
                digitalWrite(LED0, LOW);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                break;
            case CONN_STATE_CONNECTED:
                break;
            case CONN_STATE_DISCONNECTED:
                digitalWrite(LED0, HIGH);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                digitalWrite(LED1, LOW);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                break;
            case CONN_STATE_ERROR:
                break;
            default:
                break;
        }
    }
}

void safety_test(){
    const char* TAG = "SAFETY TEST";
    if(digitalRead(BOARD_PWR) == HIGH){
        ESP_LOGW(TAG, "Controller Board is already on, turning it off...");
        switch_board_power(OFF);
        while(digitalRead(BOARD_PWR) != LOW){
            switch_board_power(OFF);
            vTaskDelay(5000 / portTICK_PERIOD_MS);
        }
    }
}

void status_led_connected(){
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    digitalWrite(LED1, LOW);
    digitalWrite(LED0, LOW);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(LED1, LOW);
    digitalWrite(LED0, LOW);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(LED1, LOW);
    digitalWrite(LED0, LOW);
}