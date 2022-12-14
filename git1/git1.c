#include<Wire.h>
#include <Servo.h>;

#define servoPin1 D0
#define servoPin2 D1
#define servoPin3 D2

Servo servo1;
Servo servo2;
Servo servo3;

const int MPU = 0x68;//MPU6050 I2C주소
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int Button1 = 2;
int Button2 = 3;
void get6050();
void setup()
{
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);//MPU6050 을 동작 대기 모드로 변경
    Wire.endTransmission(true);
    Serial.begin(9600);
    servo.attach(7); //servo 서보모터를 7번 핀에 연결한다.
}
void loop()
{
    get6050();//센서값 갱신
 //받아온 센서값을 출력합니다.
    int t = AcY //자이로센서 y값을 t에 대입한다.
        while (1)
        {
            if (digitalRead(Button1) == HIGH && digitalRead(Button2) == HIGH && t < -10)
                //발 전체가 오르막길에 착지하는 시점
            {
                servo1.write(-t); //-t만큼 밑창의 서보모터를 회전시킨다.
                servo2.write(-asin(sqrt((tan(t) * 70 / l_1)))); //2,3번째 모터 가동
                servo3.write(-asin(sqrt((tan(t) * 70 / l_1))));
                if (digitalRead(Button1) == LOW && digitalRead(Button2) == LOW)
                    // 발 전체가 허공으로 뜨는 시점
                    servo1.write(t); //t만큼 서보모터를 회전시킨다. 원상태로 복구됨.}
                servo2.write(asin(sqrt((tan(t) * 70 / l_1)))); //2,3번째 모터 원위치
                servo3.write(asin(sqrt((tan(t) * 70 / l_1))));
            }

        }
    void get6050()
    {
        Wire.beginTransmission(MPU);//MPU6050 호출
        Wire.write(0x3B);//AcX 레지스터 위치 요청
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 14, true);//14byte의 데이터를 요청
        AcX = Wire.read() << 8 | Wire.read();//두개의 나뉘어진 바이트를 하나로 이어붙입니다.
        AcY = Wire.read() << 8 | Wire.read();
        AcZ = Wire.read() << 8 | Wire.read();
        Tmp = Wire.read() << 8 | Wire.read();
        GyX = Wire.read() << 8 | Wire.read();
        GyY = Wire.read() << 8 | Wire.read();
        GyZ = Wire.read() << 8 | Wire.read();
    }