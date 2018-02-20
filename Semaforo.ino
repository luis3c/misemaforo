/*
  Castañeda Mares Luis Gerardo
  Práctica: SEMAFORO.
  20 Febrero 2018
  Sistemas Programables
*/
// 1 == automovil --- 2 == peaton
const int verde1 = 8;
const int amarillo1 = 9;
const int rojo1 = 10;
const int verde2 = 11;
const int rojo2 = 12;
const int boton = 13;
 
// Tiempo mínimo en verde para el semaforo de automoviles
const int tiempo_minimo_verde_auto = 7000;
 

void iniciar_semaforo(void) { 
// Inicializar semáforo.
   // Encender el led verde para automóviles. Apaga los demás leds
   digitalWrite(verde1, HIGH);
   digitalWrite(rojo1, LOW);
   digitalWrite(amarillo1, LOW);
 
   // Enciende el led rojo para peatones. Apaga los demás leds
   digitalWrite(rojo2, HIGH);
   digitalWrite(verde2, LOW);
}
 
 
void semaforo_auto_rojo(void) { // Cambia el semáforo de automóviles a rojo
   
   // Apaga el led verde para coches
   digitalWrite(verde1,  LOW);
 
   // Enciende el led amarillo para coches y parpadea 3 veces
   for(int i=4; i>0; i--) {
      delay(500);
      digitalWrite(amarillo1, HIGH);
      delay(500);
      digitalWrite(amarillo1, LOW);
   }
 
   // Enciende el led rojo para coches
   digitalWrite(rojo1, HIGH);
}
 

// Espera a que se presione el pulsador
void pulsador_wait(void) {
   int presionado;
   long time;
   
   // Espera a que se presione el pulsador
   // Debe permanecer esperando un tiempo mínimo
   time = millis() + tiempo_minimo_verde_auto; 
   presionado = 0;
   while(1) {
      // Lee el estado del pulsador
      if (digitalRead(boton) == LOW)
         presionado = 1;
         
      // Si ha pasado el tiempo de verde para coches
      // y se ha presionado el pulsador, salir
      if ((millis() > time) && (presionado == 1))
         break;
   }
}
  
//
// Espera un tiempo que depende del potenciómetro
//
void delay_semaforo(void) {
   int tiempo_peatones;
   
   // Calcula el tiempo de espera.
   // 2 segundos más el tiempo que añada el potenciómetro
   tiempo_peatones = 2000 + 5 * analogRead(A0);
   
   // Envía por el puerto serie el tiempo de espera
   Serial.print("Tiempo peatones=");
   Serial.println(tiempo_peatones);
 
   // Espera
   delay(tiempo_peatones);
}
 
//   
// Cambia el semáforo de peatones a rojo
//
void cambio_semaforo_rojo(void) {
 
   // Parpadea el led verde 3 veces
   for(int i=3; i>0; i--) {
      digitalWrite(verde2, LOW);
      delay(500);
      digitalWrite(verde2, HIGH);
      delay(500);
   }
 
   // Enciende el led rojo para peatones y apaga el verde
   digitalWrite(verde2, LOW);
   digitalWrite(rojo2, HIGH);
}
  
void setup() {
   //  salidas de Arduino
   pinMode(verde1, OUTPUT);
   pinMode(amarillo1, OUTPUT);
   pinMode(rojo1, OUTPUT);
   pinMode(verde2, OUTPUT);
   pinMode(rojo2, OUTPUT);
 
   // entradas con resistencia de Pull-up
   pinMode(boton, INPUT_PULLUP);
   
   // Inicializa el puerto de comunicaciones
   Serial.begin(9600);
   Serial.println("Semaforo en marcha");
}
 
//
// Programa principal
//
void loop() {
   
   // Inicializar semáforo. Verde para automóviles
   iniciar_semaforo();
   
   // Esperar a que se presione el boton
   pulsador_wait();
   
   // Cambiar el semáforo de automóviles a rojo
   cambio_semaforo_rojo();
 
   // Esperar antes de permitir paso a peatones
   delay(1500);
 
   // Encender el led verde para peatones
   digitalWrite(rojo2, LOW);
   digitalWrite(verde2, HIGH);
 
   // Espera un tiempo que depende del potenciómetro
   delay_semaforo();
 
   // Cambia el semáforo de peatones a rojo
   semaforo_peatones_rojo();
 
   delay(2000);
 
}
