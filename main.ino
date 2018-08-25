int LEDA = 36;
unsigned long syncA;

struct Point {
  double x;
  double y;
};

double MAX_POSITIVE_VOLTAGE = 5.0;
double MAX_NEGATIVE_VOLTAGE = -5.0;

Point startA = {0.0, 0.0};
Point aPoint1 = {0.75, -2.3};
Point aPoint2 = {0.0, 3.0};
Point stopA = {1.0, 3.0};

void setup() {
  pinMode(LEDA, OUTPUT);
  syncA = millis();
}

double linearBezier(Point start, Point stop, double x) {
  return  ((1 - x) * start.y) + (stop.y * x);
}

double quadBezier(Point start, Point b1, Point stop, double x) {
  return (pow((1 - x), 2) * start.y) + (2 * (1 - x) * x * b1.y) + (pow(x, 2) * stop.y);
}

double cubicBezier(double starty, double p1y, double p2y, double stopy, double x) {
  return (pow((1 - x), 3) * starty) + (3 * pow((1 - x), 2) * x * p1y) + (3 * (1 - x) * pow(x, 2) * p2y) + (pow(x, 3) * stopy);
}

double res;
double x;
double t;
Point p1;
Point p2;
double d = 500.0;

void loop() {
  unsigned long current = millis();
  t = (current-syncA)/d;
  if(t < 1.0) {
    //double x = scaleTime(startA, aPoint1, aPoint2, stopA, 100, current-syncA);
    //res = cubicBezier(startA, aPoint1, aPoint2, stopA, x);
    p1 = aPoint1;
    p2 = aPoint2;
    if(aPoint1.x > aPoint2.x) {
      p1 = aPoint2;
      p2 = aPoint1;
    }
    
    x = cubicBezier(startA.x, p1.x, p2.x, stopA.x, t);
    res = cubicBezier(startA.y, p1.y, p2.y, stopA.y, x);
    Serial.print(-100.0);
    Serial.print(" ");
    Serial.print(100.0);
    Serial.print(" ");
    Serial.println((res/MAX_POSITIVE_VOLTAGE)*100.0);
  } else {
    syncA = millis();
    res = startA.y;
    startA.y = random(-500, 500) / 100.0;
    stopA.y = random(-500, 500) / 100.0;
    aPoint1.x = random(0, 100) / 100.0;
    aPoint1.y = random(-500, 500) / 100.0;
    aPoint2.x = random(0, 100) / 100.0;
    aPoint2.y = random(-500, 500) / 100.0;
    d = random(0, 100) * 10.0;
  }
}

