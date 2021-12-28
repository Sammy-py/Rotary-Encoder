#define CLK 6  //2
#define DT 5  //3
#define SW 4
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); //0x3F //0X27
int sayici = 0;
int SimdikiDurumCLK;
int SonDurumCLK;
unsigned long SonButonBasim = 0;
void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);
  SonDurumCLK = digitalRead(CLK);
  lcd.init();
  lcd.backlight();
}
void loop() {
  SimdikiDurumCLK = digitalRead(CLK);
  if (SimdikiDurumCLK != SonDurumCLK  && SimdikiDurumCLK == 1) {
    if (digitalRead(DT) != SimdikiDurumCLK) {
      sayici --;
    } else {
      sayici ++;
    }
    Serial.print("Sayı: ");
    Serial.println(sayici);
  }
  SonDurumCLK = SimdikiDurumCLK;
  int butonDurum = digitalRead(SW);
  if (butonDurum == LOW) {
    if (millis() - SonButonBasim > 50) {
      Serial.println("Buton Görevi");
      lcd.setCursor(0, 1);
      lcd.print("Buton Gorevi");
      delay(1000);
    }
    SonButonBasim = millis();
  }
  delay(10);
  lcd.setCursor(0, 0);
  lcd.print("Sayi:");
  lcd.setCursor(5, 0);
  if (sayici <= 9)
  {
    lcd.print("0");
  }
  lcd.print(sayici, DEC);
  lcd.setCursor(0, 1);
  lcd.print("             ");

}
