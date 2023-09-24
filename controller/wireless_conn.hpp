#pragma once

#include <Arduino.h>

void wifi_start();

void web_server_start();

void wifi_events_watchdog(WiFiEvent_t event);