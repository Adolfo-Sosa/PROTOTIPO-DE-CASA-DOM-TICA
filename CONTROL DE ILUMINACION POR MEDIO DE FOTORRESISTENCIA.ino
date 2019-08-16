#define pinrele 11
boolean rele=false;
int ldr;
void setup()
{
  Serial.begin(9600);
  pinMode(pinrele,OUTPUT);
}

void loop()
{
  ldr=analogRead(0);
  if(ldr>=800)rele=true;
  else if(ldr<=600)rele=false;
  digitalWrite(pinrele,rele);
  digitalWrite(13,rele);
  Serial.print(ldr);
  delay;
}

