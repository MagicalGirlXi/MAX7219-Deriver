#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 my5110 = Adafruit_PCD8544(9, 10, 8);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  my5110.begin();
}

void showString(char *str, uint8_t length)
{
  const byte charWidth = 6;
  for (int i = 0;i < length; i++)
  {
    byte x = (i * charWidth) % 84;
    byte y = (i * charWidth) / 84 * 9;
    my5110.drawChar(x,y,str[i],1,1,1,1);
    
  }
}
char testStr[100] = "Current Speed is : 00.00";
float speed = 0.0;
void loop() {
  // put your main code here, to run repeatedly:
  my5110.display();
  delay(100);
  my5110.writeFillRect(0,0,84,48,0);
  speed+=1.0;
  dtostrf(speed,2, 2, testStr+19);
  Serial.println(testStr);
  showString(testStr, strlen(testStr));
}
