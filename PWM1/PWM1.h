/****************************************/
/*
 * PWM1.h
 *
 * Author: Willy Ulises Cuellar
 * Description: Librería para controlar Servo1 mediante Timer1 en OC1A (PB1).
 *              Se utiliza Fast PWM (modo 14, TOP en ICR1) para generar un período de 20 ms (50 Hz).
 *              Con prescaler = 8, cada tick equivale a 0.5 µs, permitiendo mapear 0.6 ms a 2.4 ms (1200 a 4800 ticks).
 */
/****************************************/

#ifndef PWM1_H
#define PWM1_H

#include <avr/io.h>

// TOP para 50 Hz en Timer1: 20 ms / 0.5 µs = 40000 ticks.
#define PWM1_TOP 40000

// Inicializa Timer1 en modo Fast PWM con TOP en ICR1 y salida en OC1A (PB1)
void initPWM1(uint16_t top);

// Actualiza el duty cycle para el servo conectado a OC1A (PB1)
void setPWM1_OCR(uint16_t ticks);

#endif
