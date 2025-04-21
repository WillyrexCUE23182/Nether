/****************************************/
/*
 * PWM0.h
 *
 * Author: Willy Ulises Cuellar
 * Description: Librería para controlar Servo2 mediante Timer0 en OC0A (PD6).
 *              Se utiliza Fast PWM (modo 3, TOP = 0xFF) para generar un período de aproximadamente 16.384 ms (~61 Hz).
 *              Con prescaler = 1024, cada tick equivale a 64 µs.
 *              Se mapea un pulso de 0.6 ms (~9 ticks) a 2.4 ms (~38 ticks).
 */
/****************************************/

#ifndef PWM0_H
#define PWM0_H

#include <avr/io.h>

// Inicializa Timer0 en Fast PWM para generar PWM en OC0A (PD6)
void initPWM0(void);

// Actualiza el duty cycle para el servo conectado a OC0A (PD6)
// Se espera un valor aproximadamente entre 9 y 38.
void setPWM0_OCR(uint8_t ticks);

#endif
