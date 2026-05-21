/*
 * File:   main.c
 * Author: Samuel Marroquín Isaza
 *
 * Created on 19 de mayo de 2026, 16:09
 */


#include <xc.h>
#include "PWM.h"
void main(void) {
    PWM_Init();
    TRISB=0b1111111;
    while(1){
        if((RB1==0)&&(RB0==0)){
            PWM_Set(25);
        }else if((RB1==0)&&(RB0==1)){
            PWM_Set(50);
        }else if((RB1==1)&&(RB0==0)){
            PWM_Set(75);
        }else if((RB1==1)&&(RB0==1)){
            PWM_Set(100);
        }else{
            PWM_Set(0);
        }
    }
    
}
