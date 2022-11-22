#include <DHT.h>
#include <DabbleESP32.h>
#include "pinout.h"
#include "sensors.h"
#include "validation.h"
#include "AsyncTaskLib.h"

unsigned long tiempo;
unsigned long tiempoc = 0;
AsyncTask asyncTask_luz(1000, []() {  valorft = analogRead(ft); });// tiempo asincronico del fotoreceptor.
AsyncTask asyncTask_temperatura(5000, []() {  temperatura = dht.readTemperature(); });// tiempo asicronico de la temperatura.

void setup() {
  
  Serial.begin(115200);
  Dabble.begin("Grupo 5"); //Nombre para establecer comunicacion entre esp32 y dispositivo movil mediante bluetooth.
  senconf(); //configuracion de los elementos utilizados(sensores, buzzer, led rgb).
  ledconf(); //configuracion  de los elementos utilizados para el sistema de seguridad.
  asyncTask_luz.Start();// comienza a correr el tiempo de registro de luz. 
  asyncTask_temperatura.Start();// comienza a corres el tiempo de registro de temperatura.
  
}

void loop() {

  if (intentos == 3) {

    bloqueo();
  }
  if (correcto == true) {

  hum_temp();
  sensor_luz();
  asyncTask_luz.Update(asyncTask_temperatura);// cuando acaba el tiempo de registro de luz, empieza el tiempo de la temperatura.
  asyncTask_temperatura.Update(asyncTask_luz);// cuando acaba el tiempo de registro de temperatura,empieza el de la luz.
  
  } else {
    tiempo = millis();
    if (tiempo - tiempoc >= 11050) {
      tiempoc = tiempo;
      Terminal.print("Ingrese contraseña:");
    }
    validacion();
  }
}
