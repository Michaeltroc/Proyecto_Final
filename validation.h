int timec = 1000;
String terminaldata = "";
bool dataflag = 0;  // // Retorna un valor de cero o uno en la comparacion de String para validacion de contraseña.
bool correcto = false;
byte intentos = 0;  //  para sumar los intentos de contraseña erroneas.

void validacion() {

  Dabble.processInput();             //esta función se utiliza para actualizar los datos obtenidos del teléfono inteligente.
  while (Terminal.available() != 0)  // esta función indica si hay nuevos datos presentes en la cola del terminal o no. Devuelve 0 si no hay datos y 1 si hay datos presentes.
  {
    terminaldata = Terminal.readString();  //Recoge los datos y los transform a una cadena de caracteres.
    dataflag = 1; //Si desde la terminal del dispositivo movil se enviara un dato, la bandera de datos pasara a 1 de lo contrario  0.

    if (dataflag == 1) {
      Serial.println(terminaldata);

      if (terminaldata == clave) { //Comparacion de cadena de carateres con la clave prefifinida.

        Serial.print(clave);
        Terminal.print("contraseña correcta ");
        correcto = true;
        digitalWrite(ledgreen, HIGH);
        delay(1000);
        digitalWrite(ledgreen, LOW);

      } else {
        Terminal.print("contraseña incorrecta");
        digitalWrite(ledyellow, HIGH);
        delay(1000);
        digitalWrite(ledyellow, LOW);

        if (intentos < 2) {
          Terminal.print("Ingrese contraseña:");
        }
        String vacio = terminaldata;
        terminaldata = "";
        intentos++;
      }
    }
  }
}

void bloqueo() {
  Terminal.print("sist. bloqueado");
  delay(2000);
  digitalWrite(ledred, HIGH);
  delay(1000);
  digitalWrite(ledred, LOW);
  Terminal.print("sist.desbloqueado");
  delay(500);
  intentos = 0;
}

//Configuracion de leds para el sistema de seguridad.
void ledconf() {
  pinMode(ledgreen, OUTPUT);
  pinMode(ledyellow, OUTPUT);
  pinMode(ledred, OUTPUT);
}
