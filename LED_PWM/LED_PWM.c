/****************************************/
/*
 * LED_PWM.c
 *
 * PWM manual por software en pin D0 (PD0) usando Timer2 en modo CTC.
 * - Frecuencia: 1953 Hz (no visible flicker)
 * - Resoluci�n: 128 niveles de brillo
 *
 * Autor: Willy Ulises Cuellar
 * Fecha: 10/04/2025
 */
/****************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "LED_PWM.h"

// Variables internas para el PWM
static volatile uint8_t led_counter = 0;     // Contador de ticks
static volatile uint8_t led_threshold = 0;   // Umbral de apagado

// Inicializar Timer2 y pin PD0
void ledPWM_init(void) {
    DDRD |= (1 << PD0);  // PD0 como salida

    // Configurar Timer2 en modo CTC (WGM21=1)
    TCCR2A = (1 << WGM21);

    // Prescaler = 64 ? Tick cada 4 �s (16MHz / 64 = 250 kHz)
    TCCR2B = (1 << CS22);  // CS22=1, CS21=0, CS20=0

    // TOP = 127 ? Per�odo = 128 ticks (128 * 4 �s = 512 �s)
    OCR2A = LED_PWM_PERIOD - 1;

    // Habilitar interrupci�n por comparaci�n A
    TIMSK2 = (1 << OCIE2A);
}

// Actualizar el umbral de apagado (0-127)
void ledPWM_setThreshold(uint8_t value) {
    if (value >= LED_PWM_PERIOD) {
        value = LED_PWM_PERIOD - 1;  // Limitar valor m�ximo
    }
    led_threshold = value;  // Actualizar umbral (seguro en 8 bits)
}

// ISR del Timer2 (ejecutada cada 512 �s)
ISR(TIMER2_COMPA_vect) {
    led_counter++;
    if (led_counter >= LED_PWM_PERIOD) {
        led_counter = 0;          // Reiniciar ciclo
        PORTD |= (1 << PD0);      // Encender LED al inicio
    }
    if (led_counter == led_threshold) {
        PORTD &= ~(1 << PD0);     // Apagar LED al alcanzar el umbral
    }
}
/****************************************/