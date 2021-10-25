int trigPins[] = {13, 14, 26, 33, 5};
int echoPins[] = {12, 27, 25, 32, 18};
int distance[] = {0, 0, 0, 0, 0};
int counts[] = {0, 0, 0, 0, 0};
bool occupied[] = {false, false, false, false, false};

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
int distanceCm;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  for (int i = 0; i < 5; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }
}

void loop() {

  for (int i = 0; i < 5; i++) {
    // Clears the trigPin
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPins[i], HIGH);

    // Calculate the distance
    distance[i] = round(duration * SOUND_SPEED/2);

    if (occupied[i]) { // se a vaga i está ocupada
      if (distance[i] > 30) { // se nao identificou carro
        if (counts[i] > 5) { // se ja esta a 5 ciclos sem identificar carro
          Serial.println((String)"Vaga: "+ i +" foi liberada");
          occupied[i] = false;
          counts[i] = 0;
        }
        else {
          counts[i]++;
        }
      }
      else {
        if (counts[i] > 0) {
          counts[i] = 0;
        }
      }
    }
    if (!occupied[i]) { // se a vaga i está desocupada
      if (distance[i] < 30) { // se identificou carro
        if (counts[i] > 5) { // se ja esta a 5 ciclos identificando carro
          Serial.println((String)"Vaga: "+ i +" foi ocupada");
          occupied[i] = true;
          counts[i] = 0;
        }
        else {
          counts[i]++;
        }
      }
      else {
        if (counts[i] > 0) {
          counts[i] = 0;
        }
      }
    }

    for (int i = 0; i < 5; i++) {
      Serial.print(distance[i]);
      if (i < 4) {
        Serial.print(" - ");
      }
      else {
        Serial.println(" ")
      }
    }
    for (int i = 0; i < 5; i++) {
      Serial.print(counts[i]);
      if (i < 4) {
        Serial.print(" - ");
      }
      else {
        Serial.println(" ")
      }
    }
    for (int i = 0; i < 5; i++) {
      Serial.print(occupied[i]);
      if (i < 4) {
        Serial.print(" - ");
      }
      else {
        Serial.println(" ")
      }
    }
    Serial.println(" ")

    // if (i < 4) {
    //   Serial.print(min(float(distanceCm), float(30)));
    //   Serial.print(" ");
    // }
    // else {
    //   Serial.println(min(float(distanceCm), float(30)));
    // }
  } 
  delay(500);
}
