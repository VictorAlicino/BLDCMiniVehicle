#pragma once

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

void _i2c_callback();

void control(float _speed, float _steer, float _limit, bool sw_power);