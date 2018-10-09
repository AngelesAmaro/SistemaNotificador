Alumno: Maria de los Angeles Espinoza Amaro

Instituto Tecnológico de León

Materia: Sistemas Programables

Profesor: Carlos Rafael Levy Rojas

León, Guanajuato 27 de Septiembre de 2018

      
      *Requisito indispensable:* Reducir el consumo de energía al mínimo. Mientras la alarma no esté sonando el arduino deberá consumir la mínima cantidad de energía. Cuando la puerta se cierre esta deberá de dejar de sonar y regresar al estado de bajo consumo energético.

**Entorno**
Para el desarrollo de esta práctica se utiizo el sistema operativo Elementary OS.0.4.14 y se complemento con Windows 10 Essentials, con apoyo de IDE ARDUINO, Fritzing 0.9.1 para la simulación del circuito.


**Materiales usados**
_Arduino UNO -Cable USB -Placa de prototipado o protoboard -10 cabless -2 Leds (Rojo,Azul) -2 Resistencias de 220Ω y 10KΩ -Reed Switch -Buzzer

**Descripcion**
Se presenta el siguiente codigo:


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
**Se implemento el uso de LCD 16x2 para mostrar un mensaje en cuanto suene la alarma "mensaje de atención"

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

