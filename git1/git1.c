#include<Wire.h>
#include <Servo.h>;

#define servoPin1 D0
#define servoPin2 D1
#define servoPin3 D2

Servo servo1;
Servo servo2;
Servo servo3;

const int MPU = 0x68;//MPU6050 I2C�ּ�
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int Button1 = 2;
int Button2 = 3;
void get6050();
void setup()
{
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);//MPU6050 �� ���� ��� ���� ����
    Wire.endTransmission(true);
    Serial.begin(9600);
    servo.attach(7); //servo �������͸� 7�� �ɿ� �����Ѵ�.
}
void loop()
{
    get6050();//������ ����
 //�޾ƿ� �������� ����մϴ�.
    int t = AcY //���̷μ��� y���� t�� �����Ѵ�.
        while (1)
        {
            if (digitalRead(Button1) == HIGH && digitalRead(Button2) == HIGH && t < -10)
                //�� ��ü�� �������濡 �����ϴ� ����
            {
                servo1.write(-t); //-t��ŭ ��â�� �������͸� ȸ����Ų��.
                servo2.write(-asin(sqrt((tan(t) * 70 / l_1)))); //2,3��° ���� ����
                servo3.write(-asin(sqrt((tan(t) * 70 / l_1))));
                if (digitalRead(Button1) == LOW && digitalRead(Button2) == LOW)
                    // �� ��ü�� ������� �ߴ� ����
                    servo1.write(t); //t��ŭ �������͸� ȸ����Ų��. �����·� ������.}
                servo2.write(asin(sqrt((tan(t) * 70 / l_1)))); //2,3��° ���� ����ġ
                servo3.write(asin(sqrt((tan(t) * 70 / l_1))));
            }

        }
    void get6050()
    {
        Wire.beginTransmission(MPU);//MPU6050 ȣ��
        Wire.write(0x3B);//AcX �������� ��ġ ��û
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 14, true);//14byte�� �����͸� ��û
        AcX = Wire.read() << 8 | Wire.read();//�ΰ��� �������� ����Ʈ�� �ϳ��� �̾���Դϴ�.
        AcY = Wire.read() << 8 | Wire.read();
        AcZ = Wire.read() << 8 | Wire.read();
        Tmp = Wire.read() << 8 | Wire.read();
        GyX = Wire.read() << 8 | Wire.read();
        GyY = Wire.read() << 8 | Wire.read();
        GyZ = Wire.read() << 8 | Wire.read();
    }