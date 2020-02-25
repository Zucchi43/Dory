#include "_config.h"
#include "motors.h"
#include "Sensores.h"
#include <VL53L0X.h>
#include <stdlib.h>


//IRrecv irrecv(PIN_IR_DIGITAL);
//decode_results controle;
void setup()
{
	Serial.begin(9600);
	Serial.println("Setup Start...  ");
	pinMode(PIN_BUTTON,INPUT);
	Serial.println("Button ON  ");
	pinMode(PIN_REDLED,OUTPUT);
	Serial.println("Leds ON  ");
	Motors::init();
	Serial.println("Motors ON  ");
	Sensores::init();
	Serial.println("Sensors ON  ");
	Serial.println("Setup Finished...  ");
}	

void pisca_led(int frequencia,int piscagens){
	while(millis()%(piscagens*frequencia*2)!=0)
	{
		if((millis()/frequencia)%2 == 0){
		digitalWrite(PIN_REDLED,1);
	}
		else
	digitalWrite(PIN_REDLED,0);
	}
	digitalWrite(PIN_REDLED,0);
}

/*void Basico(int Power){
	long Valores[3];
	int Threshold = 300;
	while(digitalRead(PIN_BUTTON) != HIGH)
	{
		digitalWrite(PIN_REDLED,1);
	}
	digitalWrite(PIN_REDLED,0);
	delay(4900);
	while(digitalRead(PIN_BUTTON) != HIGH){
			Valores[0] = Sensores::get_valor(Sensores::sensor);
			Valores[1] = Sensores::get_valor(Sensores::sensor2);
			Valores[2] = Sensores::get_valor(Sensores::sensor3);
			//TODOS OS SENSORES
			if(Valores[0] <= Threshold && Valores[1] <= Threshold && Valores[2] <= Threshold){
				Motors::driveTank(Power,Power);
			}
			//NENHUM DOS SENSORES
			else if(Valores[0] > Threshold && Valores[1] > Threshold && Valores[2] > Threshold){
				Motors::driveTank(15,-15);
			}
			//APENAS SENSOR ESQUERDA
			else if(Valores[0] <= Threshold && Valores[1] > Threshold && Valores[2] > Threshold){
				Motors::driveTank(Power*0.6,-Power*0.6);
			}
			//APENAS SENSOR DIREITA
			else if(Valores[0] > Threshold && Valores[1] > Threshold && Valores[2] <= Threshold){
				Motors::driveTank(-Power*0.6,Power*0.6);
			}
			//APENAS SENSOR DO MEIO E ESQUERDA
			else if(Valores[0] <= Threshold && Valores[1] <= Threshold && Valores[2] > Threshold){
				Motors::driveTank(Power*0.2,Power);
			}
			//APENAS SENSOR DO MEIO E DIREITA
			else if(Valores[0] > Threshold && Valores[1] <= Threshold && Valores[2] <= Threshold){
				Motors::driveTank(Power,Power*0.2);
			}
	}

		Motors::stop();
		delay(2000);
		return;
}
void RandomWalk(){
	while(digitalRead(PIN_BUTTON) != HIGH){
	if(digitalRead(PIN_REFL_FRENTE) == 0){
		Motors::driveTankforMillis(75,75,10);
	}
	else{
		Motors::driveTankforMillis(-75,-75,10);
				delay(100);
				Motors::driveTankforMillis(75,-75,10);
				delay(rand() % 100 + 101);
	}
}


}
*/
void Defesa(int Power){
	int Threshold = 200;
	//int visto = -1; //0->ESQUERDA ;1->Centro; 2-> DIREITA
	int Sensor_esquerda = Sensores::get_valor(Sensores::sensor2);
	int Sensor_direita = Sensores::get_valor(Sensores::sensor1);
	int tempo = millis();
	Serial.println("Aguardando...");
	while(digitalRead(PIN_BUTTON) != LOW)
	{
		digitalWrite(PIN_REDLED,1);
	}
	digitalWrite(PIN_REDLED,0);
	delay(5000);
	Serial.println("Vai!");
	while(1){
		//ATUALIZA OS VALORES DOS SENSORES A CADA 60ms
		if (millis() - tempo >= 50){
			 Sensor_esquerda = Sensores::get_valor(Sensores::sensor2);
			 Sensor_direita = Sensores::get_valor(Sensores::sensor1);
			
			Serial.print("Sensor_esquerda:: ");
			Serial.println(Sensor_esquerda);
			//Serial.print("Sensor_meio:: ");
			//Serial.println(Sensor_meio);
			Serial.print("Sensor_direita:: ");
			Serial.println(Sensor_direita);
			
			tempo = millis();
		}
			//CHECA LINHA BRANCA
      /*
			if (digitalRead(PIN_REFL_FRENTE) == 0){
				Motors::driveTankforMillis(-Power,-Power,10);
				delay(100);
				Motors::driveTankforMillis(Power,-Power,10);
				delay(200);
			}
			else if(digitalRead(PIN_REFL_BUMBUM) == 0){
				Motors::driveTankforMillis(Power,Power,10);
			}
			else{
     */

			//ALGO A FRENTE
			if(Sensor_direita <= Threshold && Sensor_esquerda <= Threshold){//CENTRO
				//Motors::driveTankforMillis(Power,0.8*Power,1);
				//visto = 1;
				Motors::driveTank(Power,Power);
			}
			//ALGO A DIREITA
			else if(Sensor_direita <= Threshold ){//DIREITA
				//visto = 2;
				Motors::driveTank(Power,-Power);
			}
			//ALGO A ESQUERDA
			else if(Sensor_esquerda <= Threshold  ){//ESQUERDA
				//visto = 0;
				Motors::driveTank(-Power,Power);
			}
			else {//ESQUERDA
				//visto = 0;
				Motors::driveTank(-Power,Power);
			}
			//Serial.print("visto:  ");
			//Serial.println(visto);

}
		Motors::stop();
		delay(1000);
		return;
}
void Topeira(int Power){
	Motors::stop();
	while(digitalRead(PIN_BUTTON) != LOW)
	{
		digitalWrite(PIN_REDLED,1);
	}
	Motors::driveTank(Power,Power);
	delay(1000);
	/*Motors::driveTank(-Power,Power);
	delay(1000);
	Motors::driveTank(Power,-Power);
	delay(1000);
	Motors::driveTank(-Power,-Power);*/
	delay(1000);
	Motors::stop();
	delay(20);
	return;

}
void Teste_Sensores(){
	int Sensor_esquerda = Sensores::get_valor(Sensores::sensor2);
	int Sensor_direita = Sensores::get_valor(Sensores::sensor1);
	while(digitalRead(PIN_BUTTON) != LOW)
	{
		digitalWrite(PIN_REDLED,1);
		Sensor_esquerda = Sensores::get_valor(Sensores::sensor2);
		Sensor_direita = Sensores::get_valor(Sensores::sensor1);
		Serial.print("Sensor_esquerda:: ");
		Serial.println(Sensor_esquerda);
			//Serial.print("Sensor_meio:: ");
			//Serial.println(Sensor_meio);
		Serial.print("Sensor_direita:: ");
		Serial.println(Sensor_direita);
		delay(200);
	}
	delay(1000);
	return;
}
void loop() {
	Serial.println(digitalRead(PIN_BUTTON));
if(digitalRead(PIN_BUTTON) == LOW){
	Serial.println("Começando...");
	pisca_led(200,10);
	digitalWrite(PIN_REDLED,HIGH);
	delay(500);
	//Topeira(50);
	//Teste_Sensores();
	Defesa(50);
			}
/* 
if (irrecv.decode(&controle)) {
    irrecv.resume(); // Receive the next value
  }
switch(controle.value){
		case Number_1:
		pisca_led(200,5);
			while(controle.value == Number_1){
				if(digitalRead(PIN_BUTTON) == HIGH){
					pisca_led(100,10);
					Basico(75);
			}
				else if(irrecv.decode(&controle)){
					break;						
			}
		}
			break;


		case Number_2:
			pisca_led(500,5);
			while(controle.value == Number_1){
				if(digitalRead(PIN_BUTTON) == HIGH){
					pisca_led(100,10);
					Basico(50);
			}
				else if(irrecv.decode(&controle)){
					break;						
			}
		}
			break;

		case Number_3:
			while(controle.value == Number_3){
				if(digitalRead(PIN_BUTTON) == HIGH){
					pisca_led(200,5);
			}
				else if(irrecv.decode(&controle)){
					break;						
			}
		}


		case ENTER:
			while(controle.value ==  ENTER){
				if(digitalRead(PIN_BUTTON) == HIGH){
					pisca_led(1000,3);
			}
				else if(irrecv.decode(&controle)){
					break;						
			}
		}



		case OFF:
			while(controle.value == OFF){
				if(digitalRead(PIN_BUTTON) == HIGH){
					pisca_led(100,10);
			}
				else if(irrecv.decode(&controle)){
					break;						
			}
		}
	}*/
}
