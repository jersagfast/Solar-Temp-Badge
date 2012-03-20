/*
Solar Temperature Badge
Jeremy Saglimbeni - 2012 - http://thecustomgeek.com
For more information go to http://thecustomgeek.com/2012/02/18/solar-temperature-badge/
*/
int del = 2;
unsigned int i;
unsigned int j;
unsigned int bluev;
unsigned int redv;
unsigned int average[11];
unsigned int tot;
unsigned int ones;
unsigned int tens;
unsigned int hundreds;
int mode = 1;
void setup() {
 // Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  pinMode(13, INPUT);
  pinMode(14, INPUT);
  digitalWrite(14, HIGH);
  digitalWrite(13, HIGH);
  pinMode(17, OUTPUT);
  pinMode(18, INPUT);
  pinMode(19, OUTPUT);
  digitalWrite(17, LOW);
  digitalWrite(19, HIGH);
  delay(2000);
}

void loop() {
  if (mode == 1) {
  for (int k = 0; k <= 9; k++) {
    button();
    analogReference(INTERNAL);
    int reading = analogRead(18);
  //   Serial.println(reading);
    float voltage = reading * 1.05;
    voltage /= 1024.0;
    float temperatureC = (voltage - 0.5) * 100;
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 //    Serial.print(temperatureF); Serial.println(" degrees F");
    int i = (int) temperatureF; // float to int function!
    average[k] = i;
  }
  
  tot = (average[0] + average[1] + average[2] + average[3] + average[4] + average[5] + average[6] + average[7] + average[8] + average[9]);
  i = tot / 10;
  tot = 0;
  if ((i < 120) & (i > 32)) {
  bluev = map(i, 32, 120, 0, 255);
  redv = map(i, 32, 120, 255, 0);
  analogWrite(11, bluev);
  analogWrite(9, redv);
  }
  if (i >= 120) {
    digitalWrite(11, HIGH);
    pulsered(4);
  }
  if (i <= 32) {
    digitalWrite(9, HIGH);
    pulseblue(4);
  }
  button();
  ones = i % 10;
  tens = (i % 100) /10;
  hundreds = (i % 1000) /100;
/*
  Serial.print("temp value:");
  Serial.print(i);
  Serial.print("  hundreds:");
  Serial.print(hundreds);
  Serial.print("  tens:");
  Serial.print(tens);
  Serial.print("  ones:");
  Serial.println(ones);
  */
  } // end mode 0
  button();
  if (mode == 2) {
    for (int x = 255; x >= 0; x--) { // red up
    if (mode == 2) {
      analogWrite(9, x);
      delay(del);
      button();
    }
    }
    for (int x = 255; x >= 0; x--) { // blue up
    if (mode == 2) {
      analogWrite(11, x);
      delay(del);
      button();
    }
    }
    for (int x = 0; x <= 255; x++) { // red down
    if (mode == 2) {
      analogWrite(9, x);
      delay(del);
      button();
    }
    }
    for (int x = 255; x >= 0; x--) { // green up
    if (mode == 2) {
      analogWrite(10, x);
      delay(del);
      button();
    }
    }
    for (int x = 0; x <= 255; x++) { // blue down
    if (mode == 2) {
      analogWrite(11, x);
      delay(del);
      button();
    }
    }
    for (int x = 0; x <= 255; x++) { // green down
    if (mode == 2) {
      analogWrite(10, x);
      delay(del);
      button();
    }
    }
  }
  button();
  if (mode == 3) {
    showtempred();
  }
    button();
    if (mode == 3) {
    showtempgreen();
    }
    button();
    if (mode == 3) {
    showtempblue();
  }
      
      
    

}

void button() {
  if (mode == 1) {
  if (digitalRead(13) == LOW) {
    showtempgreen();
  }
  }
  if (mode == 2) {
  }
  if (digitalRead(14) == LOW) {
    mode++;
    for (int y = 0; y <= 5; y++) {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      delay(25);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      delay(25);

    }
    if (mode >= 4) {
      mode = 1;
    }
    delay(300);
    if (mode == 1) {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      delay(500);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      delay(500);
  }
  if (mode == 2) {
    for (int y = 0; y <= 1; y++) {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      delay(500);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      delay(500);
    }
  }
  if (mode == 3) {
    for (int y = 0; y <= 2; y++) {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      delay(500);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      delay(500);
    }
  }
  }
}

void pulsered(int ledx) {
  for (int x = 0; x <=ledx; x++) {
    digitalWrite(9, LOW);
    delay(250);
    button();
    digitalWrite(9, HIGH);
    delay(250);
    button();
  }
}

void pulsegreen(int ledx) {
  for (int x = 0; x <=ledx; x++) {
    digitalWrite(10, LOW);
    delay(250);
    button();
    digitalWrite(10, HIGH);
    delay(250);
    button();
  }
}

void pulseblue(int ledx) {
  for (int x = 0; x <=ledx; x++) {
    digitalWrite(11, LOW);
    delay(250);
    button();
    digitalWrite(11, HIGH);
    delay(250);
    button();
  }
}

void showtempred() {
  digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    delay(200);
    pulsered(hundreds - 1);
    delay(350);
    pulsered(tens - 1);
    delay(350);
    pulsered(ones - 1);
}

void showtempgreen() {
  digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    delay(200);
    pulsegreen(hundreds - 1);
    delay(350);
    pulsegreen(tens - 1);
    delay(350);
    pulsegreen(ones - 1);
}

void showtempblue() {
  digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    delay(200);
    pulseblue(hundreds - 1);
    delay(350);
    pulseblue(tens - 1);
    delay(350);
    pulseblue(ones - 1);
}
