#include <Wire.h>

#include "motors_control.hpp"

/** Função que responde às chamadas da placa do hover board, utilizando o
 protocolo I2C.
 Utiliza a variável global vector para enviar os valores. */
void _i2c_callback(){
    const char* TAG = "I2C";
    ESP_LOGD(TAG, "I2C Callback Called");
    Wire.write("Hello World");
    int i;
    vector[0] = x;
    vector[1] = y;
    for(i = 0; i < 6; i++){
        Wire.write(vector,6);
    }
}

void board_power_state(){
    digitalWrite(15, HIGH);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    digitalWrite(15, LOW);
}

/** Função que define as variáveis x e y que serão enviadas para a placa do hover board. \n
  Verifica e corrige os valores recebidos como parâmetros para os adequar às regras de funcionamento
  placa do hover board. */
void control(float _speed, float _steer, float _limit, bool sw_power){
  float  coefficient_speed, coefficient_steer;  
  coefficient_speed = (_speed/100) * abs(_limit);
  coefficient_steer = (_steer/100) * abs(_limit);
  y = STD_Y +  coefficient_speed;
  if(y < 35) y = 35; if(y > 230) y = 230; 
  x = STD_X +  coefficient_steer;
  if(x < 35) x = 35; if(x > 230) x = 230;
  if(sw_power) board_power_state(); // If power switch is true, switch the relay
}