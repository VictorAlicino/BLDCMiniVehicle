#include <Arduino.h>
#include "utils.hpp"

extern mcu_state_t mcu_status;
extern conn_state_t conn_status;

void status_led_blink(void * param){
    switch(mcu_status){
        case MCU_STATE_INIT:
            digitalWrite(LED0, HIGH);
            digitalWrite(LED1, HIGH);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            digitalWrite(LED0, LOW);
            digitalWrite(LED1, LOW);
            break;
        case MCU_STATE_READY:
            break;
        case MCU_STATE_OK:
            break;
        case MCU_STATE_ERROR:
            break;
        default:
            break;
    }

    switch(conn_status){
        case CONN_STATE_INIT:
            break;
        case CONN_STATE_READY:
            digitalWrite(LED0, HIGH);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            digitalWrite(LED1, LOW);
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