#include <SoftwareSerial.h>
 
const byte llaveXOR = 0b00000100;
 
// RX, TX
SoftwareSerial enlace(10, 11);
 
void setup() {
  Serial.begin(9600);
  enlace.begin(9600);
 
  Serial.println("ARDUINO B - DESCIFRADO XOR");
  Serial.println("Esperando mensajes de Arduino A...");
}
 
void loop() {
  static String mensajeCifrado = "";
 
  while (enlace.available() > 0) {
    byte dato = enlace.read();
 
    if (dato == '\n') {
      String mensajeDescifrado = "";
 
      Serial.print("Mensaje cifrado recibido (bytes): ");
 
      for (unsigned int i = 0; i < mensajeCifrado.length(); i++) {
        byte cifrado = (byte)mensajeCifrado[i];
 
        // Mostrar los bytes cifrados
        Serial.print(cifrado);
        Serial.print(" ");
 
        // Recuperar el carácter original
        byte original = cifrado ^ llaveXOR;
        mensajeDescifrado += (char)original;
      }
 
      Serial.println();
      Serial.print("Mensaje descifrado: ");
      Serial.println(mensajeDescifrado);
      Serial.println("-------------------------");
 
      mensajeCifrado = "";
    } else {
      mensajeCifrado += (char)dato;
    }
  }
}
