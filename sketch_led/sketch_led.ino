
void hue2rgb(int hue, int* r, int* g, int* b);

void setup() {
  /* シリアル通信設定 (デバッグ用) */
  Serial.begin(9600);
}

void loop() {
  static int hue = 0;
  int r, g, b;
  
  /* 100msごとに更新 */
  delay(100);
  
  /* 色相を正方向に回す */
  hue++;
  if (hue > 360) {
    hue -= 360;
  }

    /* HSV→RGB変換の要領で、色相からRGB値を求める
     * if構文の並びの関係か、hueの値が増加するにつれて
     * 色相の変化が遅くなっている気がする
     */
  hue2rgb(hue, &r, &g, &b);
  
/*
  デバッグ用
  Serial.print(r);
  Serial.print(",");
  Serial.print(g);
  Serial.print(",");
  Serial.println(b);
*/
  /* PWM出力 */
  analogWrite(3, (255 - r));
  analogWrite(5, (255 - g));
  analogWrite(6, (255 - b));  

}

void hue2rgb(int hue, int* r, int* g, int* b)
{
  switch(hue / 60) {
  case 0:
    *r = 255;
    *g = hue * 255 / 60;
    *b = 0;
    return;
  case 1:
    *r = (120 - hue) * 255 / 60;
    *g = 255;
    *b = 0;
    return;
  case 2:
    *r = 0;
    *g = 255;
    *b = (hue - 120) * 255 / 60;
    return;
  case 3:
    *r = 0;
    *g = (240 - hue) * 255 / 60;
    *b = 255;
    return;
  case 4:
    *r = (hue - 240) * 255 / 60;
    *g = 0;
    *b = 255;
    return;
  case 5:
  default:
    *r = 255;
    *g = 0;
    *b = (360 - hue) * 255 / 60;
    return;
  }
}
