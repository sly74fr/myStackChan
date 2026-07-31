#include "M5Unified.h"

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setRotation(1);
  M5.Display.setTextColor(GREEN);
  M5.Display.setTextDatum(middle_center);
  M5.Display.setTextFont(&fonts::Orbitron_Light_24);
  M5.Display.setTextSize(1);
  M5.Display.drawString("Speaker Test", M5.Display.width() / 2,
                        M5.Display.height() / 2);
}

void loop() {
  M5.Speaker.tone(10000, 100);
  delay(1000);
  M5.Speaker.tone(4000, 20);
  delay(1000);
}
