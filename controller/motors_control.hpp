#pragma once

void switch_board_power();

void _i2c_callback();

void control_2_board(float _speed, float _steer, float _limit);

void motor_forward();

void motor_backward();

void motor_left();

void motor_right();

void motor_forward_right();

void motor_forward_left();

void motor_backward_right();

void motor_backward_left();

void motor_stop();

void motor_speed(float speed);

void EMERGENCY_SHUTDOWN();
