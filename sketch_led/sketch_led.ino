
void setup() {
  /* シリアル通信設定 (デバッグ用) */
  Serial.begin(9600);
}

void loop() {
  static int cnt = 0;
  static int hue = 0;
  int r, g, b;
  
  /* cntのインクリメントでビジーウェイト */
  if (cnt++ > 10000) {
    /* 色相を正方向に回す */
    hue++;
    if (hue > 360) {
      hue -= 360;
    }
    cnt = 0;

    /* HSV→RGB変換の要領で、色相からRGB値を求める
     * if構文の並びの関係か、hueの値が増加するにつれて
     * 色相の変化が遅くなっている気がする
     */
    if (hue <= 60) {
      r = 255;
      g = hue * 255 / 60;
      b = 0;
    }
    else if (hue <= 120) {
      r = (120 - hue) * 255 / 60;
      g = 255;
      b = 0;
    }
    else if (hue <= 180) {
      r = 0;
      g = 255;
      b = (hue - 120) * 255 / 60;
    }
    else if (hue <= 240) {
      r = 0;
      g = (240 - hue) * 255 / 60;
      b = 255;
    }
    else if (hue <= 300) {
      r = (hue - 240) * 255 / 60;
      g = 0;
      b = 255;
    }
    else {
      r = 255;
      g = 0;
      b = (360 - hue) * 255 / 60;
    }

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
}
