String line         = "";
bool stringComplete = false;

void setup() {
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);

}

void loop() {
  if (stringComplete){
    if (line.equals("on\n")){
      digitalWrite(7,HIGH);
    }
    else if (line.equals("off\n")){
      digitalWrite(7,LOW);
    }
    stringComplete = false;
    line = "";
  }
  while(Serial.available()){
    char inChar = (char)Serial.read();
    Serial.print(inChar);
    line += inChar;
    if (inChar == '\n'){
      stringComplete = true;
      Serial.print(line);
    }
  }
}
