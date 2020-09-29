#include <M5Stack.h>
#include "utility/MPU6886.h"

float ax, ay, az;
float ball_x, ball_y, ball_vx, ball_vy;

MPU6886 IMU;

void setup() {
  // M5StackとI2Cの初期化
  M5.begin();
  Wire.begin();

  // MPU6886の初期化とキャリブレーション
  IMU.Init();
  
  M5.Lcd.setTextSize(2);
  ball_x = 160;
  ball_y = 120;
  ball_vx = 20;
  ball_vy = 15;
}


void loop() {
  const float ball_radius = 10.0; // ボールの半径
  const float restitution_coef = 0.7; // 画面端との反発係数
  const float gravity_coef = 8.0; // 重力の大きさ
  
  IMU.getAccelData(&ax, &ay, &az);
  // 表示更新
  M5.Lcd.clear();
/*
  M5.Lcd.setCursor(0,  0); M5.Lcd.print("MPU6886 acceleration");
  M5.Lcd.setCursor(0, 32); M5.Lcd.printf("X: %7.2f mG", 1000 * ax);
  M5.Lcd.setCursor(0, 64); M5.Lcd.printf("Y: %7.2f mG", 1000 * ay);    
  M5.Lcd.setCursor(0, 96); M5.Lcd.printf("Z: %7.2f mG", 1000 * az);
*/
  // ボールの位置更新
  ball_x += ball_vx;
  // 画面外に出てしまう場合は反射
  if (ball_x < ball_radius && ball_vx < 0) {
    ball_x = 2.0 * ball_radius - ball_x;
    ball_vx = -restitution_coef * ball_vx;
  }
  else if (ball_x > 320.0 - ball_radius && ball_vx > 0) {
    ball_x = (640.0 - 2.0 * ball_radius) - ball_x;
    ball_vx = -restitution_coef * ball_vx;
  }

  ball_y += ball_vy;
  if (ball_y < ball_radius && ball_vy < 0) {
    ball_y = 2.0 * ball_radius - ball_y;
    ball_vy = -restitution_coef * ball_vy;
  }
  else if (ball_y > 240.0 - ball_radius && ball_vy > 0) {
    ball_y = (480.0 - 2.0 * ball_radius) - ball_y;
    ball_vy = -restitution_coef * ball_vy;
  }

  ball_vx -= ax * gravity_coef;
  ball_vy += ay * gravity_coef;

  M5.Lcd.fillCircle(ball_x, ball_y, ball_radius, WHITE);
  delay(10);
}
