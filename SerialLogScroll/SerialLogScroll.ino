
#include <M5GFX.h>
M5GFX display;
M5Canvas canvas(&display);

void setup(void) {
  display.begin();

  if (display.isEPD()) {
    display.setEpdMode(epd_mode_t::epd_fastest);
    display.invertDisplay(true);
    display.clear(TFT_BLACK);
  }
  if (display.width() < display.height()) {
    display.setRotation(display.getRotation() ^ 1);
  }

  canvas.setColorDepth(8);
  canvas.createSprite(display.width(), display.height());
  canvas.setTextSize((float)canvas.width() / 160);
  canvas.setTextScroll(true);

  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.setTimeout(3000);

  canvas.setTextColor(TFT_GREEN);
  canvas.printf("READY !\r\n\r\n");
  canvas.pushSprite(0, 0);
}

void loop(void) {
  static int count = 1;

  String rx = Serial.readStringUntil('\n');
  if (rx.length() > 0) {
    canvas.setTextColor(TFT_GREEN);
    canvas.printf("%03d>", count);
    canvas.setTextColor(TFT_WHITE);
    canvas.printf(" %s\n", rx.c_str());
    canvas.pushSprite(0, 0);
    ++count;
  }
}
