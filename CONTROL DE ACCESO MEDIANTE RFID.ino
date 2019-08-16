#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); ///Creamos el objeto para el RC522

const int reele=0;
const int led1=1;
const int led2=2;

void setup() {
  Serial.begin(9600); //Iniciamos La comunicacion serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Control de acceso:");
  pinMode(reele,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
}

byte ActualUID[4]; //almacenará el código del Tag leído
byte Usuario1[4]= {0x74, 0x70, 0x28, 0x6F} ; //código del usuario 1
void loop() {
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
      //Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print(F("Card UID:"));
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                          ActualUID[i]=mfrc522.uid.uidByte[i];
                          digitalWrite(reele,LOW);
                    digitalWrite(led1,LOW);
                    digitalWrite(led2,LOW);         
                  } 
                  Serial.print("     ");                 
                  //comparamos los UID para determinar si es uno de nuestros usuarios  
                  if(compareArray(ActualUID,Usuario1)){
                    Serial.println("Acceso concedido...");
                    digitalWrite(reele,HIGH);
                    digitalWrite(led1,HIGH);
                    digitalWrite(led2,LOW);
                    delay(1000);
                    digitalWrite(reele,LOW);
                    digitalWrite(led1,LOW);
                    digitalWrite(led2,LOW);
                    ;
                  }
                  else{
                    Serial.println("Acceso denegado...");
                    digitalWrite(reele,LOW);
                    digitalWrite(led1,LOW);
                    digitalWrite(led2,HIGH);
                    delay(1000); 
                    digitalWrite(reele,LOW);
                    digitalWrite(led1,LOW);
                    digitalWrite(led2,LOW);
                  }
                  
                  // Terminamos la lectura de la tarjeta tarjeta  actual
                  mfrc522.PICC_HaltA();
          
            }
      
  }
  
}

//Función para comparar dos vectores
 boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}
