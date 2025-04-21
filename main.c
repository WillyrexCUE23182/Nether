/****************************************/
/*
 * main.c
 *
 * Created: 06/04/2025
 * Author : Willy Ulises Cuellar
 * Description:
 *   - Control de tres señales PWM:
 *       - Servo1: Potenciómetro en A6 ? PWM en Timer1 (OC1A - PB1)
 *       - Servo2: Potenciómetro en A7 ? PWM en Timer0 (OC0A - PD6)
 *       - LED:    Potenciómetro en A0 ? PWM manual en D0 (via Timer2 en CTC)
 *   - PWM del LED implementado con ISR interna (no expone variables globales)
 */
/****************************************/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Librerías para control de PWM
#include "PWM1/PWM1.h"         // Servo1 (Timer1 - OC1A)
#include "PWM0/PWM0.h"         // Servo2 (Timer0 - OC0A)
#include "LED_PWM/LED_PWM.h"   // LED (Timer2 - PWM manual)

// Prototipos de funciones
uint8_t readADC(uint8_t channel);
void setup(void);

int main(void) {
    uint8_t adc_servo1, adc_servo2, adc_led;
    uint16_t pulso_servo1;
    uint8_t pulso_servo2, led_thresh;

    setup();  // Configura periféricos

    while(1) {
        // Leer valores ADC (8 bits)
        adc_servo1 = readADC(6);   // A6 ? Servo1 (0-255)
        adc_servo2 = readADC(7);   // A7 ? Servo2 (0-255)
        adc_led    = readADC(0);   // A0 ? LED (0-255)

        // Mapeo para Servo1: 0-255 ? 1200-4800 ticks (Timer1, 16-bit)
        // Rango: 0.6ms (1200 ticks) a 2.4ms (4800 ticks)
        pulso_servo1 = 1200 + ((uint32_t)adc_servo1 * 3600) / 255;
        setPWM1_OCR(pulso_servo1);

        // Mapeo para Servo2: 0-255 ? 9-38 ticks (Timer0, 8-bit)
        // Rango: 0.6ms (9 ticks) a 2.4ms (38 ticks) @ 64 µs/tick
        pulso_servo2 = 9 + ((uint32_t)adc_servo2 * 29) / 255;
        setPWM0_OCR(pulso_servo2);

        // Mapeo para LED: 0-255 ? 0-127 (Timer2, 128 niveles)
        led_thresh = ((uint16_t)adc_led * LED_PWM_PERIOD) / 255;
        ledPWM_setThreshold(led_thresh);

        _delay_ms(10);  // Retardo para estabilizar lecturas ADC
    }
}

// Configuración inicial de periféricos
void setup(void) {
    cli();  // Deshabilitar interrupciones globales

    // Configuración ADC:
    // - Referencia AVCC (5V), ajuste a la izquierda (8 bits)
    // - Prescaler = 8 ? Frecuencia ADC = 16MHz / 8 = 2MHz
    ADMUX = (1 << REFS0) | (1 << ADLAR);
    ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);

    // Inicializar módulos PWM
    initPWM1(PWM1_TOP);  // Timer1 para Servo1 (ICR1 como TOP)
    initPWM0();          // Timer0 para Servo2 (Fast PWM)
    ledPWM_init();       // Timer2 para LED (Modo CTC + ISR)

    sei();  // Habilitar interrupciones globales
}

// Lectura ADC de 8 bits (canal 0-7)
uint8_t readADC(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);  // Seleccionar canal
    _delay_us(10);                // Esperar estabilización
    ADCSRA |= (1 << ADSC);        // Iniciar conversión
    while (ADCSRA & (1 << ADSC)); // Esperar fin de conversión (~13 ciclos)
    return ADCH;                  // Devolver resultado de 8 bits
}
/****************************************/