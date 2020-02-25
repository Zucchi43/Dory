#include <VL53L0X.h>
#include "Sensores.h"
#include "_config.h"
#include <Wire.h>
VL53L0X Sensores::sensor1;
VL53L0X Sensores::sensor2;

void Sensores::init(){
  Wire.begin();
  pinMode(Xshut_1, OUTPUT);
  pinMode(Xshut_2, OUTPUT);

  digitalWrite(Xshut_1, LOW);
  digitalWrite(Xshut_2, LOW);

  delay(10);
  //Wire.begin();
  //SENSOR (DIREITA)
  pinMode(Xshut_1, INPUT);
  delay(50);
  Sensores::sensor1.init(true);
  delay(20);
  Sensores::sensor1.setAddress((uint8_t)0x22);
  //SENSOR 3(ESQUERDA)
  pinMode(Xshut_2, INPUT);
  delay(50);
  Sensores::sensor2.init(true);
  delay(20);
  Sensores::sensor2.setAddress((uint8_t)0x2A);

  Sensores::sensor1.setTimeout(100);
  Sensores::sensor2.setTimeout(100);

//Sensores::sensor.setMeasurementTimingBudget(20000);
//Sensores::sensor2.setMeasurementTimingBudget(20000);
//Sensores::sensor3.setMeasurementTimingBudget(20000);
}
int Sensores::get_valor(VL53L0X sensor){
  return sensor.readRangeSingleMillimeters();
}
/*
void Sensores::Serial()
{
  Serial.println("__________________________________________________________________");
  Serial.println("");
  Serial.println("=================================");
  Serial.println ("I2C scanner. Scanning ...");
  //FWD OR SENSOR
  if (sensor.timeoutOccurred())
  {
    Serial.println("_________________________________");
    Serial.print("Distance FWD (READING): ");
    Serial.println(" TIMEOUT");
    Serial.println("_________________________________");
    Serial.println("");
  }
  else
  {
    
    Serial.print("Distance SENSOR 0 (mm): ");
    Serial.println(Sensores::init(sensor));
  }

  //FLT OR SENSOR2
  if (sensor2.timeoutOccurred())
  {
    Serial.print("Distance SENSOR 1 (READING): ");
    Serial.println(" TIMEOUT");
    Serial.println("_________________________________");
    Serial.println("");
  }
  else
  {
    Serial.print("Distance SENSOR 1 (mm): ");
    Serial.println(Sensores::init(sensor2));
  }
  
  //FRT OR SENSOR3
  if (sensor3.timeoutOccurred())
  {
    Serial.println("_________________________________");
    Serial.print("Distance SENSOR 2 (READING): ");
    Serial.println(" TIMEOUT");
    Serial.println("_________________________________");
    Serial.println("");
  }
  else
  {
    Serial.print("Distance SENSOR 2 (mm): ");
    Serial.println(Sensores::init(sensor3));
  }
  
  delay(1000);//can change to a lower time like 100
}*/