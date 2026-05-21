/*
 * File:   PWM.c
 * Author: Usuario
 *
 * Created on 19 de mayo de 2026, 16:24
 */


#include <xc.h>


void PWM_Init(void)
{
    /* 1. Pin RC1/CCP2 como salida */
    TRISCbits.TRISC1 = 0;

    /* 2. Periodo del PWM: PR2 = (Fosc / (4 · Fpwm · Prescaler)) - 1
          Con Fpwm = 19531 Hz, Prescaler = 1 y Fosc = 20 MHz ? PR2 = 255 */
    PR2 = 0xFF;

    /* 3. CCP2CON: modo PWM (bits CCP2M3:CCP2M0 = 1100) */
    CCP2CON = 0x0C;

    /* 4. Duty-cycle inicial = 0 % */
    CCPR2L      = 0x00;
    CCP2CONbits.CCP2X = 0;
    CCP2CONbits.CCP2Y = 0;

    /* 5. TMR2: prescaler 1:1, postscaler 1:1, TMR2 ON
          T2CON bits: TOUTPS3:TOUTPS0=0000, TMR2ON=1, T2CKPS1:T2CKPS0=00 */
    T2CON = 0x04;   // TMR2ON=1, prescaler 1:1
    TMR2  = 0x00;
}


void PWM_Set(int porcentaje)
{
    uint16_t duty;

    /* Limitar rango de seguridad */
    if (porcentaje > 100) porcentaje = 100;
    if (porcentaje < 0)   porcentaje = 0;

    /* Valor de 10 bits proporcional al porcentaje (0 a 1023) */
    duty = (uint16_t)(((uint32_t)porcentaje * 1023U) / 100U);

    /* Cargar los 8 bits más significativos en CCPR2L */
    CCPR2L = (uint8_t)(duty >> 2);

    /* Cargar de forma segura los 2 bits menos significativos en el PIC16F877A */
    CCP2CONbits.CCP2X = (duty & 0x02) >> 1; // Bit 1 de 'duty' va a CCP2X (Bit 5)
    CCP2CONbits.CCP2Y = (duty & 0x01);      // Bit 0 de 'duty' va a CCP2Y (Bit 4)


}