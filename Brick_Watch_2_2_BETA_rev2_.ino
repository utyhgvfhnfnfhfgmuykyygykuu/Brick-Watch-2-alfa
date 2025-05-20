
//████//███//███/████/█//█////█///█/████/███/████/█//█////████///████//██/████//███/███/████/██//
//█//██/█//█//█//█//█/█/█/////█///█/█//█//█//█//█/█//█////█//█///█//█/██//█//██/█////█//█//█//██/
//████//████//█//█////██//////█/█/█/████//█//█////████//////██/////██/█///████//███//█//████///█/
//█//██/█/█///█//█//█/█/█//////█/█//█//█//█//█//█/█//█////██/////██///██//█//██/█////█//█//█//██/
//████//█/█//███/████/█//█/////█/█//█//█//█//████/█//█////████/█/████//██/████//███//█//█//█/██//

//THE DEVELOPER OF THE PROGRAM:NIKITA POPOV(14 years)
//(30.05.2024)-(05.02.2025)
int d = 1000; //ВРЕМЯ ДЛЯ РАСЧЕТА ВРЕМЕНИ В МС
#include <Wire.h>
#include <buildTime.h>
#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
int h = BUILD_HOUR; //ЧАСЫ
int m = BUILD_MIN;  //МИНУТЫ
int p = BUILD_SEC;  //СЕКУНДЫ
int s = p;
int l = 0;
int S = s + 10; //СЕКУНДЫ + ЗАГРУЗКА СКЕТЧА
int DAI = BUILD_DAY; //ДЕНЬ
int MES = BUILD_MONTH; //МЕСЯЦ
int GOD = BUILD_YEAR; //ГОД
int o = 0; //ЗНАЧЕНИЕ КНОПКИ
int k = 0; //СЧЕТ ДЛЯ ПЕРЕКЛЮЧЕНИЯ ВРЕМЕНИ
int i = 0; //ПЕРЕМЕННАЯ ДЛЯ СНА(ЛИПОВОГО ПРОСТО ВЫКЛЮЧЕНИЕ ДИСПЛЭЯ)
void setup() {
  /////////////////////////////////////////////////////////////-(ЧАСТЬ ДЛЯ РАБОТЫ ДИСПЛЭЯ)
  Wire.begin();
  oled.clear(); //ОЧИСТКА ДИСПЛЭЯ
  oled.init(); //ИНИТ ДИСПЛЭЯ
  Serial.begin(9600);
  Wire.setClock(800000L);
  oled.setScale(1); //РАЗМЕР
  oled.home(); //КУРСОР В ПОЗИЦИЮ 0
  delay(400); //ЗАДЕРЖКА 400МС
  oled.print("Brick Watch 2.2(BETA)"); //ЗАСТАВКА
  delay(3400); //ЗАДЕРЖКА 3400М/С
  oled.setScale(1); //РАЗМЕР
  oled.clear(); //ОЧИСТКА ДИСПЛЭЯ
  pinMode(4, INPUT); //КНОПКА
  pinMode(7, INPUT); //ПЕРЕКЛЮЧЕНИЕ ДИСПЛЭЯ
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  /////////////////////////////////////////////////////////////-(ЧАСТЬ ДЛЯ РАСЧЕТА ВРЕМЕНИ)
  o = digitalRead(4); //КНОПКА
  S = S + 1; //ОТЧЕТ
  if (S >= 60) {              
  S = 0;                    
  m = m + 1;
  oled.clear();
  }
  if (m >= 60) {
  m = 0;
  h = h + 1;
  
  oled.clear();
  }
  if (h >= 24)
  {
   h = 0;
   m = 0;
   S = 0;
   DAI = DAI + 1;
   
   oled.clear();
  }
  if (DAI >= 31)
  {
   MES = MES + 1;
  }
  if (MES >= 12)
  {
   MES = 0;
   GOD = GOD + 1;
   oled.home();
   oled.print("С НОВЫМ ГОДОМ!");
   oled.clear();
   }
  /////////////////////////////////////////////////////////////-(РАСЧЕТ ДЕЙСТВИЙ КНОПКИ)
  if (o == 1){
    k = k + 5;
  }
    if (k == 25){
    i = i + 1;
  }
    if (k > 25){
    i = 0;
    k = 0;
  }
    if (k == 10){
    S = S + 10;
    if (S >= 60){
      S = 0;
      m = m + 1;
      oled.clear();
    }
  }
  /////////////////////////////////////////////////////////////-(ВВЫВОД ДАННЫХ)
  if (i < 1){
    oled.home();
    oled.print ("Brick Watch 2.0(BETA)"); //ЗАСТАВКА
    oled.setScale(1);
    oled.setCursor(0, 4); //ПОЛОЖЕНИЕ КУРСОРА
    oled.print("ВРЕМЯ");
    oled.print("(");
    oled.print(h); //ЧАСЫ
    oled.print(":");
    oled.print(m); //МИНУТЫ
    oled.print(":");
    oled.print(S); //СЕКУНДЫ
    oled.print(")");
    oled.setCursor(0, 2); //ПОЛОЖЕНИЕ КУРСОРА
    oled.print("ЧИСЛО");
    oled.print("(");
    oled.print(DAI); //ДЕНЬ
    oled.print(".");
    oled.print(MES); //МЕСЯЦ
    oled.print(".");
    oled.print(GOD); //ГОД
    oled.print(")");
    oled.setCursor(0, 3); //ПОЛОЖЕНИЕ КУРСОРА
  }
  if (i == 1){
    oled.clear();
    oled.print("Goodbye!");
    delay(1000);
    oled.clear();
    l = l + 1;
    if (l == 1){
      uint32_t tmr;
      tmr = millis();
      while (millis() - tmr < 5000) ball();
      l = l - 1;
    }
  }
  /////////////////////////////////////////////////////////////-(ОБНУЛЕНИЕ ЗНАЧЕНИЯ КНОПКИ)
   digitalWrite(LED_BUILTIN, LOW);
   delay(d); //ЗАДЕРЖКА ДЛЯ РАСЧЕТА ВРЕМЕНИ В МС
   o = 0;
  /////////////////////////////////////////////////////////////
}
void ball() {
  oled.clear();
  static int x, y;
  static int velX = 5, velY = 8;
  x += velX;
  y += velY;
  if (x >= (128 - 1) * 10 || x < 0) velX = -velX;
  if (y >= (64 - 1) * 10 || y < 0) velY = -velY;

  oled.dot(x / 10, y / 10, 1);
  oled.dot(x / 10 + 1, y / 10 + 1, 1);
  oled.dot(x / 10 + 1, y / 10, 1);
  oled.dot(x / 10, y / 10 + 1, 1);
  oled.update();
  delay(1);
}