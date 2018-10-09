//Alarma para el acceso a una puerta 
//Espinioza Amaro Maria de los Angeles
//Sistemas Programables

#include <avr/sleep.h>
#include <LiquidCrystal.h>

//LCD(rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define ledAzul 2
#define reed 3
#define buzzer 10

//FRECUENCIAS
const int tono1 = 990;
const int tono2 = 1050;

//EDO DEL REED SWITCH
volatile int value = HIGH;

void setup() {
  //INPUT // OUTPUT
  pinMode(reed, INPUT_PULLUP);
  pinMode(ledVerde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  
  //Modo de bajo consumo.
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  //Se crea una interrupcion que reaccione al cambiar de LOW a HIGH
  attachInterrupt(digitalPinToInterrupt(reed), interrupcion, RISING); 
  Serial.begin(9600);
}

void loop() {
  //Obtener el estado del reed switch
  value = digitalRead(reed);
 //si es LOW quiere decir que el iman esta cerca y HIGH al alejar el iman
  if (value == LOW) {
    sleep_disable();
    digitalWrite(ledVerde, HIGH);
    //Mostrar mensaje en display lcd 16x2
    lcd.display();
    lcd.home();
    lcd.print("WARNING");
    lcd.setCursor (0,1);
    lcd.print("      get in     ");
  
   //ALAMA CON BUZZER
   tone(buzzer, tono1);
   delay(200);
   tone(buzzer, tono2);

  } else {
     digitalWrite(ledVerde,LOW);//Apaga el led con la alarma
     noTone(buzzer);
     // Turn off the display:
     lcd.noDisplay();
     sleep_enable();//inicializamos el modo bajo consumo
     sleep_mode();//ponemos el modo bajo consumo.
  }
 
  delay(200);

}

void interrupcion() {
  value = !value;
}


