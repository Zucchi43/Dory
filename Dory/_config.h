#include <Arduino.h>
//Motor A LADO ESQUERDO
#define PWMA 9 //Speed control
#define AIN1 7	 //Direction
#define AIN2 8//Direction

//Motor B LADO DIREITO
#define PWMB 3 //Speed control
#define BIN1 5 //Direction
#define BIN2 4 //Direction

#define STBY 6 //Stand-by

// Motors config (H-Bridge)
#define MOTOR_ABS_MAX          255

//all the rest
//Sensores IR


#define Xshut_1 A0 //Direita
#define Xshut_2 A1 //Esquerda

#define SCL A5
#define SDA A4

#define PIN_BUTTON 2

#define PIN_REDLED 13

/*
#define Number_1 3772784863
#define Number_2 3772817503
#define Number_3 3772801183
#define ENTER 3772782313
#define OFF 3772793023
*/