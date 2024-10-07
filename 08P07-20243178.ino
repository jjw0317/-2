#define SND_VEL 346.0     // 음속  (unit: m/sec)
#define INTERVAL 25 //100      // 초음파 센서 측정 주기 (샘플링) (unit: msec)
#define PULSE_DURATION 10 // 초음파 송출 시간 (unit: usec)
#define _DIST_MIN 100.0   // 최소 거리 (unit: mm)
#define _DIST_MAX 300.0   // 최대 거리 (unit: mm)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // 최대 에코 대기시간
#define SCALE (0.001 * 0.5 * SND_VEL) // 시간을 거리로 변환하는 계수

unsigned long last_sampling_time;   //단위: msec

void setup() {
  //  GPIO pins 초기화
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  // 초음파 트리거
  pinMode(PIN_ECHO, INPUT);   //  초음파 에코
  digitalWrite(PIN_TRIG, LOW);  // 초음파 비활성화 
  
  // 시리얼 포트 초기화
  Serial.begin(57600);
}

void loop() {
  float distance;

  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO); // 거리측정
  int brightness = 0; // LED 밝기 초기화
  if ((distance == 0.0) || (distance > _DIST_MAX)) {
      distance = _DIST_MAX + 10.0;    // 더 높은 값으로 설정
      digitalWrite(PIN_LED, 0);       // LED 끄기
  } else if (distance < _DIST_MIN) {
      distance = _DIST_MIN - 10.0;    // 더 낮은값으로 설정
      digitalWrite(PIN_LED, 0);       // LED 끄기
  } else if ( distance> 100 && distance <200) {
   brightness = map(distance, _DIST_MIN, _DIST_MAX, 255, 0);   
  } else {    // In desired Range
    brightness = map(distance, _DIST_MIN, _DIST_MAX, 0, 255);
  } 
 
  analogWrite(PIN_LED, brightness);
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
  // 거리를 시리얼 포트에 출력
  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(",distance:");  Serial.print(distance);
  Serial.print(",Max:");       Serial.print(_DIST_MAX);
  Serial.println("");
  
  last_sampling_time += INTERVAL;
}

// USS 에서 거리측정. 반환값은 밀리미터 단위
float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // unit: mm
}