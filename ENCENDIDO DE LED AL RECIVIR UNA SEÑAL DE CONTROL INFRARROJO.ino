#include <IRremote.h>

int RECV_PIN = 8; 
IRrecv irrecv(RECV_PIN); 
decode_results results; 

void setup() {  
irrecv.enableIRIn(); 
pinMode(9, OUTPUT);
}

boolean on = LOW;

void loop() { 
if (irrecv.decode(&results)) { 
  on = !on;
  digitalWrite(9, on? HIGH : LOW);
irrecv.resume(); 
delay(300); 
} 
}
