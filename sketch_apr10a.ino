#include <Servo.h>
#include <SimpleWebSerial.h>

SimpleWebSerial WebSerial;
// ---------- Servo Setup ----------
Servo myservo;
#define servoPin 3
#define pushButtonPin 2

int angle = 80;
int angleStep = 10;
const int minAngle = 80;
const int maxAngle = 180;
const int type = 2;
int buttonPushed = 0;

// ---------- Ultrasonido + Buzzer ----------
#define trigPin 10
#define echoPin 9
int speakerPin = 7;
int numTones = 10;
int tones[] = {1500, 1000};

void setup() {
  Serial.begin(9600);

  // Servo
  myservo.attach(servoPin);
  pinMode(pushButtonPin, INPUT_PULLUP);
  Serial.println("Robojax Servo Button");
  myservo.write(angle);

  // Sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   WebSerial.on("led", toggleLed);
}


void toggleLed() {
  
   // digitalWrite(servoPin, HIGH);
    buttonPushed=1;
  
}

void loop() {
    WebSerial.check();

  // ----------- SENSOR ULTRASÓNICO + BUZZER -----------
  long duracion, distancia;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia = duracion / 2 / 29.1;
  Serial.println(String(distancia) + " cm.");

  if (distancia > 100) {
    noTone(speakerPin);
  }

  if (distancia < 100 && distancia > 10) {
    tone(speakerPin, tones[1]);
  } else if (distancia < 10) {
    tone(speakerPin, tones[0]);
  } else {
    noTone(speakerPin);
  }

  // ----------- SERVO MOTOR CON BOTÓN -----------
  if (digitalRead(pushButtonPin) == LOW) {
    buttonPushed = 1;
  }

  if (buttonPushed) {
    angle = angle + angleStep;

    if (angle >= maxAngle) {
      delay(7500); // espera 7.5 segundos al llegar a 180°
      angleStep = -angleStep;
      if (type == 1) {
        buttonPushed = 0;
      }
    }

    if (angle <= minAngle) {
      angleStep = -angleStep;
      if (type == 2) {
        buttonPushed = 0;
      }
    }

    myservo.write(angle);
    Serial.print("Moved to: ");
    Serial.print(angle);
    Serial.println(" degree");
    delay(100);
  }
}
