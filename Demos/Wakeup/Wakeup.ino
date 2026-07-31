#include <M5Unified.h>
void setup(void) {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setTextColor(GREEN);
  M5.Display.setTextDatum(middle_center);
  M5.Display.setFont(&fonts::FreeSerifItalic18pt7b);
  M5.Display.setTextSize(1);
  M5.Display.drawString("Touch", M5.Display.width() / 2,
                        M5.Display.height() / 2 - 60);
  M5.Display.drawString("to sleep", M5.Display.width() / 2,
                        M5.Display.height() / 2 - 20);
  M5.Display.drawString("After 5s", M5.Display.width() / 2,
                        M5.Display.height() / 2 + 20);
  M5.Display.drawString("Wakeup", M5.Display.width() / 2,
                        M5.Display.height() / 2 + 60);
}
void loop(void) {
  M5.update();
  if (M5.Touch.getCount() && M5.Touch.getDetail(0).wasClicked()) {
    M5.Power.timerSleep(5);
    // M5.Power.timerSleep(const rtc_time_t& time);
    // M5.Power.timerSleep(const rtc_date_t& date, const rtc_time_t&
    // time);
    // M5.Power.powerOff(); shutdown
  }
}
