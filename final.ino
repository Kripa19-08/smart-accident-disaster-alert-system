// ===== PIN DEFINITIONS =====
int trigLeft = 2;
int echoLeft = 3;

int trigRight = 9;
int echoRight = 10;

int leftLED = 6;
int rightLED = 5;

int buzzer = 7;
int waterSensor = A0;

// ===== ULTRASONIC FUNCTION =====
long readUltrasonic(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout

  if (duration == 0) {
    return 999; // no valid reading
  }

  long distance = duration * 0.034 / 2;
  return distance;
}

void setup() {

  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);

  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);

  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);  // ensure buzzer off at start

  Serial.begin(9600);
}

void loop() {

  // ===== READ ULTRASONICS =====
  long distanceLeft = readUltrasonic(trigLeft, echoLeft);
  delay(50);  // prevent cross-interference
  long distanceRight = readUltrasonic(trigRight, echoRight);

  // ===== VEHICLE LOGIC WITH HYSTERESIS =====

  // LEFT SENSOR controls RIGHT LED
 if (distanceLeft > 2 && distanceLeft < 10) {
    digitalWrite(rightLED, HIGH);
  } 
  else if (distanceLeft > 35) {
    digitalWrite(rightLED, LOW);
  }

  // RIGHT SENSOR controls LEFT LED
  if (distanceRight > 2 && distanceRight < 10) {
    digitalWrite(leftLED, HIGH);
  } 
  else if (distanceRight > 35) {
    digitalWrite(leftLED, LOW);
  }

  // ===== WATER SENSOR =====
  int waterValue = analogRead(waterSensor);

  // Adjust threshold if needed after testing
  if (waterValue > 600) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(80);  // overall system stability
}