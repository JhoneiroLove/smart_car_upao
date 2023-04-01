#include <Ultrasonic.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

int Trigger=13; //PIN usado para trigger
int Echo=11; //PIN usado para echo
int t,d; //variables para valores del sensor
int m1a = 3;             //Motor 1, pin 4 del arduino va al pin 15 del L293B.
int m1b = 4;             //Motor 1, pin 3 del arduino va al pin 10 del L293B.
int m2a = 5;             //Motor 2, pin 6 DEL arduino va al pin 2 del L293B.
int m2b = 6;             //Motor 2, pin 5 del arduino va al pin 7 del L293B.
int led1 = 8;            //LED delanteros, pin 8 del arduino va al protoboard.
int led2 = 10;           //LED trasero, pin 10 del arduino va al protoboard.
int zumbador = 12;       //Bocina, pin 12 del arduino va al protoboard.
char val;
LiquidCrystal_I2C lcd(0x27,16,2); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2).

void setup() 
{  
 pinMode(Trigger,OUTPUT); //Declaramos a trigger de tipo Salida (emisor)
pinMode(Echo,INPUT); //Declaramos a echo de tipo Entrada (receptor)
digitalWrite(Trigger,LOW); //Inicializamos el sensor en cero (apagado)
pinMode(m1a, OUTPUT);  // Digital pin 4 set as output Pin
pinMode(m1b, OUTPUT);  // Digital pin 3 set as output Pin
pinMode(m2a, OUTPUT);  // Digital pin 6 set as output Pin
pinMode(m2b, OUTPUT);  // Digital pin 5 set as output Pin
pinMode(led1, OUTPUT); // Digital pin 8 set as output Pin
pinMode(led2, OUTPUT); // Digital pin 10 set ad output pin
pinMode(zumbador, OUTPUT); // Digital pin 12 set ad output pin0
 lcd.init();
 lcd.backlight();
Serial.begin(9600);
 lcd.setCursor(0, 0);
  lcd.print("SMART CAR UPAO");
  lcd.setCursor(2, 1);
  lcd.print("Jhoel Bryan ");
}

void loop()
{
  // medición del sensor ultrasonido
  delay(100);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH);
  d = 0.01715 * t;

  // encendido del zumbador
  if (d < 20)
  {
    digitalWrite(zumbador, HIGH);
  }
  else
  {
    digitalWrite(zumbador, LOW);
  }

  // encendido de los LED
  if (val == 'F')
  {
    digitalWrite(led1, HIGH);
  }
  else if (val == 'B')
  {
    digitalWrite(led2, HIGH);
  }
  else
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }

  while (Serial.available() > 0)
  {
    val = Serial.read();
    Serial.println(val);
  }

  if( val == 'F')                   // Hacia adelante
    {
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, HIGH);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, HIGH);
      digitalWrite(led1,HIGH);
      digitalWrite(led1,HIGH);  
    }
  else if(val == 'B')              // Hacia atras
    {
      digitalWrite(m1a, HIGH);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, HIGH);
      digitalWrite(m2b, LOW); 
      digitalWrite(led2,HIGH);
      digitalWrite(led2,HIGH);
    }
  
    else if(val == 'L')             // Izquierda 
    {
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
    }
    else if(val == 'R')              //Derecha
    {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
    }
      else if(val == 'S')               //Stop - Pare, Auto detenido
    {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW); 
    digitalWrite(led1,LOW);
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led2,LOW);
    }   
     }   
