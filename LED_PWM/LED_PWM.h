/****************************************/
/*
 * LED_PWM.h
 *
 * Librería para control de LED con PWM por software en pin D0 (PD0),
 * usando el Timer2 en modo CTC.
 *
 * Proporciona:
 *  - Inicialización del módulo
 *  - Configuración del umbral de apagado (duty cycle)
 *
 * Autor: Willy Ulises Cuellar
 * Fecha: 10/04/2025
 */
/****************************************/

#ifndef LED_PWM_H_
#define LED_PWM_H_

#include <avr/io.h>

// Parámetros del PWM:
// - Período = 128 ticks ? Frecuencia = 1953 Hz (16MHz / 64 / 128)
// - Resolución: 128 niveles de brillo (0 = siempre encendido)
#define LED_PWM_PERIOD 128

// Prototipos de funciones
void ledPWM_init(void);
void ledPWM_setThreshold(uint8_t value);

#endif /* LED_PWM_H_ */
/****************************************/