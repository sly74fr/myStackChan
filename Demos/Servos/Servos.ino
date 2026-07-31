#include <M5StackChan.h>

int state = 1;
const int MAX_STATE = 8;

void setup() {
  /* Init StackChan */
  M5StackChan.begin();
  M5StackChan.Motion.goHome();

  /* Setup display */
  M5StackChan.Display().setTextSize(2);
  M5StackChan.Display().setTextScroll(true);
  M5StackChan.Display().setTextColor(TFT_ORANGE);
  M5StackChan.Display().printf("> Touch the top to start\n");
  M5StackChan.Display().setTextColor(TFT_GREEN);

  // Set to false if high-frequency updates are needed
  // M5StackChan.Motion.setAutoAngleSyncEnabled(false);
}

void loop() {
  M5StackChan.update();
  if (M5StackChan.TouchSensor.wasPressed()) {
    switch (state) {
      /* Angle unit: 10 = 1 degrees, Speed range: 0~1000 */
      /* Range X: -1280 ~ 1280 (-128° ~ 128°), Range Y: 0 ~ 900 (0° ~ 90°) */
      case 1:
        /* Move X servo to 0°, Y servo to 45° */
        M5StackChan.Motion.move(0, 450);
        M5StackChan.Display().printf("> Turn Y to 45\n");
        break;
      case 2:
        /* Move X servo to 90° */
        M5StackChan.Motion.moveX(900, 500);
        M5StackChan.Display().printf("> Turn Left\n");
        break;
      case 3:
        /* Move X servo to -90° */
        M5StackChan.Motion.moveX(-900, 500);
        M5StackChan.Display().printf("> Turn Right\n");
        break;
      case 4:
        /* Move Y servo to 90° */
        M5StackChan.Motion.moveY(900, 300);
        M5StackChan.Display().printf("> Look Up\n");
        break;
      case 5:
        /* Move Y servo to 0° */
        M5StackChan.Motion.moveY(0, 300);
        M5StackChan.Display().printf("> Look Down\n");
        break;
      /* Only X axis supports continuous 360° rotation. Y axis does not. */
      /* Velocity range: -1000 ~ 1000 (Negative: CW, Positive: CCW) */
      case 6:
        /* Rotate clockwise */
        M5StackChan.Motion.rotateX(-800);
        M5StackChan.Display().printf("> Rotate clockwise\n");
        delay(2000);
        M5StackChan.Motion.stop();
        break;
      case 7:
        /* Rotate counter-clockwise */
        M5StackChan.Motion.rotateX(800);
        M5StackChan.Display().printf("> Rotate counter-clockwise\n");
        delay(2000);
        M5StackChan.Motion.stop();
        break;
      default:
        M5StackChan.Motion.goHome();
        M5StackChan.Display().printf("> Go home\n");
        break;
    }

    state++;
    if (state > MAX_STATE) {
      state = 1;
      M5StackChan.Display().setTextColor(TFT_ORANGE);
      M5StackChan.Display().printf("> Touch the top to start\n");
      M5StackChan.Display().setTextColor(TFT_GREEN);
    }
  }
  delay(10);
}
