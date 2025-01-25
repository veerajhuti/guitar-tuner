#define MIC A0

int sig = 0;

void setup()
{
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void led() {
  sig = analogRead(MIC)*50;

  if (sig > 1000)  {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }

if (sig > 2000) {
  digitalWrite(3, HIGH);
} else {
  digitalWrite(3, LOW);
}

  if (sig > 3000) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
  }
  if (sig > 4000) {
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(5, LOW);
  }
  if (sig > 5000) {
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }
  if (sig > 6000) {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  if (sig > 7000) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }
}

void loop() {
  led();
}