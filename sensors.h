#include "AsyncTaskLib.h"

float temp;
float temperatura;  // Almacenamiento datos de temperatura.
float humedad;      // Almacenamiento de datos de humedad.
float valorft;
DHT dht(sensor, DHT11);  // Crea objeto sensor humedad y temperatura donde sensor es el pin de entrada y DHT11 el tipo de sensor.

void senconf() {
  dht.begin();//
  pinMode(ft, INPUT);
  pinMode(umbrallow, OUTPUT);
  pinMode(umbralhigh, OUTPUT);
  pinMode(ledTemp, OUTPUT);
  pinMode (buzzer,OUTPUT);
}

void hum_temp() {
  humedad = dht.readHumidity();
  String temp = String(temperatura, 1); //conversión de datos recibidos a cadena de caracteres para la vista del diseño en la terminal.
  String humidity = String(humedad, 0); //conversión de datos recibidos a cadena de caracteres para la vista del diseño en la terminal.
  
  Terminal.print("temperatura :" +temp+ "°C" );
  Serial.println ("temperatura");
  Serial.println (temperatura);
  Terminal.print( "humedad  : "+humidity+ "%" );
  Serial.println ("humedad");
  Serial.println(humedad);

// Umbrales de Temperatura.

  if (temperatura <= 20) {
    digitalWrite(umbrallow, HIGH);
  } else if (temperatura >=30) {
    digitalWrite(ledTemp,LOW);
    digitalWrite(umbralhigh, HIGH);
    digitalWrite(buzzer,HIGH);
    delay(1000);
    digitalWrite(buzzer,LOW);
  } else {
    Terminal.print("la temperatura funciona correctamente!");
    digitalWrite(ledTemp, HIGH); 
  } 
}
  
void sensor_luz() {
  String ldr = String(valorft, 0);
  Terminal.print("luz: " + ldr);
}
