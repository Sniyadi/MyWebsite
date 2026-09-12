int led1 = 4;
int led2 = 5;
int led3 = 6;
int led4 = 7;
int led5 = 8;
int led6 = 9;
int led7 = 10;
int led8 = 11;
int led9 = 12;
int led10 = 13;

int pirsens1 = 2;
int pirsens2 = 3;

int sensorState1 = 0;
int sensorState2 = 0;

void setup()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);  
}

void loop()
{
  sensorState1 = digitalRead(pirsens1);
  sensorState2 = digitalRead(pirsens2);
  if(sensorState1 == HIGH && sensorState2 == LOW){
    delay(500);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(6, HIGH);
    delay(100);
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(8, HIGH);
    delay(100);
    digitalWrite(9, HIGH);
    delay(100);
    digitalWrite(10, HIGH);
    delay(100);
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(13, HIGH);
    delay(120000);
    digitalWrite(4, LOW);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
    digitalWrite(6, LOW);
    delay(100);
    digitalWrite(7, LOW);
    delay(100);
    digitalWrite(8, LOW);
    delay(100);
    digitalWrite(9, LOW);
    delay(100);
    digitalWrite(10, LOW);
    delay(100);
    digitalWrite(11, LOW);
    delay(100);
    digitalWrite(12, LOW);
    delay(100);
    digitalWrite(13, LOW);
    delay(1000);
    
    sensorState1 = digitalRead(pirsens1);
    sensorState2 = digitalRead(pirsens2);
    }
  else if(sensorState2 == HIGH && sensorState1 == LOW){
    delay(500);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(10, HIGH);
    delay(100);
    digitalWrite(9, HIGH);
    delay(100);
    digitalWrite(8, HIGH);
    delay(100);
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(6, HIGH);
    delay(100);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(4, HIGH);
    delay(120000);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(12, LOW);
    delay(100);
    digitalWrite(11, LOW);
    delay(100);
    digitalWrite(10, LOW);
    delay(100);
    digitalWrite(9, LOW);
    delay(100);
    digitalWrite(8, LOW);
    delay(100);
    digitalWrite(7, LOW);
    delay(100);
    digitalWrite(6, LOW);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
    digitalWrite(4, LOW);
    sensorState1 = digitalRead(pirsens1);
    sensorState2 = digitalRead(pirsens2);
    }
  else if(sensorState1 == HIGH && sensorState2 == HIGH){
    delay(500);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(6, HIGH);
    delay(100);
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(8, HIGH);
    delay(100);
    digitalWrite(9, HIGH);
    delay(100);
    digitalWrite(10, HIGH);
    delay(100);
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(13, HIGH);
    delay(120000);
    digitalWrite(4, LOW);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
    digitalWrite(6, LOW);
    delay(100);
    digitalWrite(7, LOW);
    delay(100);
    digitalWrite(8, LOW);
    delay(100);
    digitalWrite(9, LOW);
    delay(100);
    digitalWrite(10, LOW);
    delay(100);
    digitalWrite(11, LOW);
    delay(100);
    digitalWrite(12, LOW);
    delay(100);
    digitalWrite(13, LOW);
    sensorState1 = digitalRead(pirsens1);
    sensorState2 = digitalRead(pirsens2);
    }
  
  else if(sensorState1 == LOW && sensorState2 == LOW){
    delay(500);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
    digitalWrite(6, LOW);
    delay(100);
    digitalWrite(7, LOW);
    delay(100);
    digitalWrite(8, LOW);
    delay(100);
    digitalWrite(9, LOW);
    delay(100);
    digitalWrite(10, LOW);
    delay(100);
    digitalWrite(11, LOW);
    delay(100);
    digitalWrite(12, LOW);
    delay(100);
    digitalWrite(13, LOW);
    sensorState1 = digitalRead(pirsens1);
    sensorState2 = digitalRead(pirsens2);
  } 
}
