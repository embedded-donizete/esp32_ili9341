#include <TFT_eSPI.h>

#define WIDTH 240
#define HEIGHT 320

TFT_eSPI tft = TFT_eSPI(WIDTH, HEIGHT);

void setup()
{
  // Use serial port
  Serial.begin(9600);
  tft.init();
  tft.setRotation(5);
}

void loop()
{
  static uint16_t x = 0, y = 0; // To store the touch coordinates

  // Pressed will be set true is there is a valid touch on the screen
  if (tft.getTouch(&x, &y))
  {
    tft.drawCircle(x, y, 2, 0x00);
  }
}
