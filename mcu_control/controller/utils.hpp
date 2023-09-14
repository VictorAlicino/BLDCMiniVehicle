#pragma once

#define WIFI_SSID "Canoa"
#define LED0 5
#define LED1 18
#define PWR 15

/**
 * @brief Microcontroller state
 * 
 * This enum is used to watch board state across multiple functions.
 */
typedef enum mcu_state {
    MCU_STATE_INIT,
    MCU_STATE_READY,
    MCU_STATE_OK,
    MCU_STATE_ERROR
} mcu_state_t;

/**
 * @brief Wi-Fi Connection state
 * 
 * This enum is used to watch connection state, and monitor possible disconnections.
 */
typedef enum conn_state {
    CONN_STATE_INIT,
    CONN_STATE_READY,
    CONN_STATE_CONNECTED,
    CONN_STATE_DISCONNECTED,
    CONN_STATE_ERROR
} conn_state_t;

void status_led_blink(void * param);