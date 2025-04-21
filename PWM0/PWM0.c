/****************************************/
/*
 * PWM0.c
 *
 * Author: Willy Ulises Cuellar
 * Description: Implementación de la librería para controlar Servo2 mediante Timer0 en OC0A (PD6).
 *              Se utiliza Fast PWM, modo 3 (WGM01=1, WGM00=1, WGM02=0) con TOP fijo a 0xFF.
 *              Con prescaler = 1024, cada tick dura 64 µs, generando un período de 256 × 64 µs ? 16.384 ms (~61 Hz).
 *              Se mapea un pulso de 0.6 ms (?9 ticks) a 2.4 ms (?38 ticks).
 */
/****************************************/

#include "PWM0.h"

void initPWM0(void)
{
    // Configurar PD6 (OC0A) como salida para la señal PWM
    DDRD |= (1 << PD6);
    
    // Configurar Timer0 en Fast PWM, modo 3: WGM01=1 y WGM00=1 (TOP = 0xFF)
    TCCR0A = (1 << WGM01) | (1 << WGM00);
    
    // Configurar salida OC0A en modo no invertido
    TCCR0A |= (1 << COM0A1);
    
    // Iniciar Timer0 con prescaler = 1024:
    // Para Timer0, prescaler 1024 se consigue con CS02=1, CS01=0, CS00=1.
    TCCR0B = (1 << CS02) | (1 << CS00);
    
    // Valor inicial para OCR0A (posición central, ~1.5 ms):
    // Con tick = 64 µs, 1.5 ms/64 µs ? 23 ticks.
    OCR0A = 23;
}

void setPWM0_OCR(uint8_t ticks)
{
    OCR0A = ticks;
}
