/****************************************/
/*
 * LED_PWM.h
 *
 * Librer�a para control de LED con PWM por software en pin D0 (PD0),
 * usando el Timer2 en modo CTC.
 *
 * Proporciona:
 *  - Inicializaci�n del m�dulo
 *  - Configuraci�n del umbral de apagado (duty cycle)
 *
 * Autor: Willy Ulises Cuellar
 * Fecha: 10/04/2025
 */
/****************************************/

#ifndef LED_PWM_H_
#define LED_PWM_H_

#include <avr/io.h>

// Par�metros del PWM:
// - Per�odo = 128 ticks ? Frecuencia = 1953 Hz (16MHz / 64 / 128)
// - Resoluci�n: 128 niveles de brillo (0 = siempre encendido)
#define LED_PWM_PERIOD 128

// Prototipos de funciones
void ledPWM_init(void);
void ledPWM_setThreshold(uint8_t value);

#endif /* LED_PWM_H_ */
/****************************************/