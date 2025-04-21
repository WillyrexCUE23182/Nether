/****************************************/
/*
 * PWM1.c
 *
 * Author: Willy Ulises Cuellar
 * Description: Implementación de la librería para controlar Servo1 mediante Timer1 en OC1A (PB1).
 *              Configura Timer1 en Fast PWM (modo 14) con TOP en ICR1.
 *              Con prescaler = 8 (cada tick = 0.5 µs) y ICR1 = 40000, se obtiene un período de 20 ms.
 *              Se mapea un pulso de 0.6 ms (1200 ticks) a 2.4 ms (4800 ticks).
 */
/****************************************/

#include "PWM1.h"

void initPWM1(uint16_t top)
{
    // Configurar PB1 (OC1A) como salida para la señal PWM
    DDRB |= (1 << PB1);
    
    // Configurar Timer1 en Fast PWM, modo 14 (WGM13:WGM10 = 1110), con TOP en ICR1
    TCCR1A = (1 << COM1A1);  // Salida no invertida en OC1A
    TCCR1B = (1 << WGM13) | (1 << WGM12);
    TCCR1A |= (1 << WGM11);
    
    // Establecer TOP para obtener un período de 20 ms (ICR1 = 40000 ticks)
    ICR1 = top;
    
    // Valor inicial: posición central (1.5 ms ? 3000 ticks)
    OCR1A = 3000;
    
    // Iniciar Timer1 con prescaler = 8 (CS11 = 1)
    TCCR1B |= (1 << CS11);
}

void setPWM1_OCR(uint16_t ticks)
{
    OCR1A = ticks;
}
