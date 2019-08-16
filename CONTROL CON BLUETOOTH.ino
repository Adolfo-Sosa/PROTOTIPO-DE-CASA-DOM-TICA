#include <SoftwareSerial.h>
SoftwareSerial tmserial(0,1);
int ledpin=13;
int data;
void setup()
{
  tmserial.begin(9600);
  tmserial.println("Bluetooth encendido... preciona 1  para encender, 0 para apagar..."); //lo que se va a imprimir una ves conectado
  tmserial.println();
  pinMode(ledpin,OUTPUT);
}
void loop()
{
  if(tmserial.available())
  {
    data=tmserial.read();
    if(data=='1')
    {
      digitalWrite(ledpin,1);
      tmserial.println("led d13 = encendido !");
      tmserial.println();
    }

    if(data=='0')
    {
      digitalWrite(ledpin,0);
      tmserial.println("led d13= apagado !");
      tmserial.println();
    }
  }
  delay(100);
}

