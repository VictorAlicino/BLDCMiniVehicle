#include <Arduino.h>
#include <Wire.h>

#include "motors_control.hpp"
#include "config.h"

const char* MOTORS_TAG = "MOTORS";

// Valor padrão de direção 0 do robô.
#define STD_X 130
// Valor padrão de velocidade 0 do robô.
#define STD_Y 123

// Variável utilizada para manipular qual será o x enviado para o robô. Significa a direção enviada.
int x;
// Variável utilizada para manipular qual será o u enviado para o robô. Significa a velocidade enviada.
int y;

// Variável 'virtual' que controla a velocidade do robô
int Speed;
// Variável 'virtual' que controla a direção do robô
int Steer;
// Variável 'virtual' que controla o limite do robô
int Limit;
// Variável que controla o acionamento do relé
int power;

uint8_t vector[6] = {218, 130, 0, 1, 0, 1};

/** Função que responde às chamadas da placa do hover board, utilizando o
 protocolo I2C.
 Utiliza a variável global vector para enviar os valores. */
void _i2c_callback(){
    int i;
    vector[0] = x;
    vector[1] = y;
    for(i = 0; i < 6; i++){
        Wire.write(vector,6);
    }
}

void switch_board_power(){
    digitalWrite(PWR, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(PWR, LOW);
}

/** Função que define as variáveis x e y que serão enviadas para a placa do hover board. \n
  Verifica e corrige os valores recebidos como parâmetros para os adequar às regras de funcionamento
  placa do hover board. */
void control_2_board(float _speed, float _steer, float _limit){
	float  coefficient_speed, coefficient_steer;  
	coefficient_speed = (_speed/100) * abs(_limit);
	coefficient_steer = (_steer/100) * abs(_limit);
	y = STD_Y +  coefficient_speed;
	if(y < 35) y = 35; if(y > 230) y = 230; 
	x = STD_X +  coefficient_steer;
	if(x < 35) x = 35; if(x > 230) x = 230;
}

float POWER_LIMIT = 50.0; // Power Limit for motors [0.0 - 100.0] (MUST BE FLOAT!)

void motor_forward(){
    control_2_board(100, 0, POWER_LIMIT);
	ESP_LOGD(MOTORS_TAG, "Motor Forward");
}

void motor_backward(){
    control_2_board(-100, 0, POWER_LIMIT);
	ESP_LOGD(MOTORS_TAG, "Motor Backward");
}

void motor_left(){
    control_2_board(0, -100, POWER_LIMIT);
	ESP_LOGD(MOTORS_TAG, "Motor Left");
}

void motor_right(){
    control_2_board(0, 100, POWER_LIMIT);
	ESP_LOGD(MOTORS_TAG, "Motor Right");
}

void motor_forward_right(){
    control_2_board(0, 50, POWER_LIMIT);
	ESP_LOGD(MOTORS_TAG, "Motor Forward Right");
}

void motor_forward_left(){
    control_2_board(0, -50, POWER_LIMIT);
	ESP_LOGD(MOTORS_TAG, "Motor Forward Left");
}

void motor_backward_right(){
	ESP_LOGD(MOTORS_TAG, "Unable to perfomr backward right");
}

void motor_backward_left(){
    ESP_LOGD(MOTORS_TAG, "Unable to perfomr backward left");
}

void motor_stop(){
    control_2_board(0,0,0);
	//ESP_LOGD(MOTORS_TAG, "Motor Stop");
}

void motor_speed(float speed){
    POWER_LIMIT = speed;
	ESP_LOGD(MOTORS_TAG, "Motor Speed: %f", speed);
}

void EMERGENCY_SHUTDOWN(){
	control_2_board(0,0,0);
	ESP_LOGE(MOTORS_TAG, "EMERGENCY SHUTDOWN");

	while(digitalRead(BOARD_PWR) != LOW){
		switch_board_power(); 
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	ESP_LOGE(MOTORS_TAG, "Restarting...");
	ESP.restart();
}