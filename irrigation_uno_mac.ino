#include<string.h>
#define motor 5
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(motor, OUTPUT);
  digitalWrite(motor, LOW);

}
void loop() {
  // put your main code here, to run repeatedly:
  char buffer[20]="";
  int val;
  if(Serial.available()>0){
    char data = Serial.read();
    Serial.readBytesUntil('\n',buffer, 20);
    Serial.println(data);
    val = int(data);
    Serial.println(val);
    if (val == 49 ){
      digitalWrite(motor, HIGH);
      delay(15000) ;
      digitalWrite(motor, LOW);
      delay(5000) ;
    }
    }
  }
