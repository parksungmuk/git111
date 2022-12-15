#define SW1 2
#define SW2 1

#include <Stepper.h>

// 2048:한바퀴(360도), 1024:반바퀴(180도)...
const int stepsPerRevolution = 2048; 
// 모터 드라이브에 연결된 핀 IN4, IN2, IN3, IN1
Stepper myStepper(stepsPerRevolution,11,9,10,8);  
Stepper myStepper2(stepsPerRevolution,7,5,3,4);         

#include<Wire.h>

const int MPU_ADDR = 0x68;    // I2C통신을 위한 MPU6050의 주소
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;   // 가속도(Acceleration)와 자이로(Gyro)
double angleAcX, angleAcY, angleAcZ;
double angleGyX, angleGyY, angleGyZ;

const double RADIAN_TO_DEGREE = 180 / 3.14159;  
const double DEG_PER_SEC = 32767 / 250;    // 1초에 회전하는 각도
// GyX, GyY, GyZ 값의 범위 : -32768 ~ +32767 (16비트 정수범위)


unsigned long now = 0;   // 현재 시간 저장용 변수
unsigned long past = 0;  // 이전 시간 저장용 변수
double dt = 0;           // 한 사이클 동안 걸린 시간 변수 

double averAcX, averAcY, averAcZ;
double averGyX, averGyY, averGyZ;

void setup() {
  initSensor();
  Serial.begin(115200);
  caliSensor();   //  초기 센서 캘리브레이션 함수 호출
  past = millis(); // past에 현재 시간 저장  
  myStepper.setSpeed(14); 
  myStepper2.setSpeed(14);

  pinMode(SW, INPUT);
}

void loop() {
  getData(); 
  getDT();
  angleGyX += ((GyX - averGyX) / DEG_PER_SEC) * dt;
  angleGyY += ((GyY - averGyY) / DEG_PER_SEC) * dt;
  angleGyZ += ((GyZ - averGyZ) / DEG_PER_SEC) * dt;
  
  Serial.print("Angle Gyro X:");
  Serial.print(angleGyX);
  Serial.print("\t\t Angle Gyro y:");
  Serial.print(angleGyY);  
  Serial.print("\t\t Angle Gyro Z:");
  Serial.println(angleGyZ);  
  delay(20);

  int sw = digitalRead(SW1);
 int sw2 = digitalRead(SW2);


//put a랑 b는 각각 1과 4; n층: n+4(n-1) = 5n-4
//경사 높이: h
//h=5n-4에서 n=(h+4)/5
//원주율: 15
//바퀴 회전수: k
//15*k=5n-4
//k=(5n-4)/15

//AcX: 자이로센서가 측정한 오르막길 각도
//h: 오르막길이 기울어진 거리
//n: 막대1이 움직여야하는 거리
//k: 서보모터1 바퀴 회전 수

h=0; k=0;//아직 잰 기울기가 없으므로 0으로 초기화
while(1){

//서보모터를 몇 바퀴(k) 돌려야하는가
if(h!=0) //이미 잰 기울기가 존재한다면
{
tan(h/30)=AcX;이므로
h=tan^(-1)(AcX)*30
n=(h+4)/5;
k=(5n-4)/15;}

//서보모터1 회전; // k바퀴 down
for(i=0; i<k; i)
myStepper.step(stepsPerRevolution);

//서보모터 2 회전; // forward
myStepper2.step(stepsPerRevolution);

if (sw1==HIGH && sw==HIGH)
{
h=angleGyX; // 기울기를 자이로센서에서 측정한 값으로 업데이트
}

if (sw==LOW && sw1==LOW)


//서보모터2 회전; // backward
for(i=0; i<k; i)
myStepper.step(-stepsPerRevolution);

//서보모터1 회전; // -k바퀴 up
myStepper2.step(-stepsPerRevolution);
}



}



void initSensor() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);   // I2C 통신용 어드레스(주소)
  Wire.write(0x6B);    // MPU6050과 통신을 시작하기 위해서는 0x6B번지에    
  Wire.write(0);
  Wire.endTransmission(true);
}

void getData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);   // AcX 레지스터 위치(주소)를 지칭합니다
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);  // AcX 주소 이후의 14byte의 데이터를 요청
  AcX = Wire.read() << 8 | Wire.read(); //두 개의 나뉘어진 바이트를 하나로 이어 붙여서 각 변수에 저장
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
}

// loop 한 사이클동안 걸리는 시간을 알기위한 함수
void getDT() {
  now = millis();   
  dt = (now - past) / 1000.0;  
  past = now;
}

// 센서의 초기값을 10회 정도 평균값으로 구하여 저장하는 함수
void caliSensor() {
  double sumAcX = 0 , sumAcY = 0, sumAcZ = 0;
  double sumGyX = 0 , sumGyY = 0, sumGyZ = 0;
  getData();
  for (int i=0;i<10;i++) {
    getData();
    sumAcX+=AcX;  sumAcY+=AcY;  sumAcZ+=AcZ;
    sumGyX+=GyX;  sumGyY+=GyY;  sumGyZ+=GyZ;
    delay(50);
  }
  averAcX=sumAcX/10;  averAcY=sumAcY/10;  averAcZ=sumAcY/10;
  averGyX=sumGyX/10;  averGyY=sumGyY/10;  averGyZ=sumGyZ/10;
}
