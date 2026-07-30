#include <Arduino.h>
#include <M5Unified.h>

////////////////////////////////////////////////////////////////////////
typedef struct { 
  String label;
  int color;
} Button;
const unsigned int MAX_ROWS = 7;
Button ROWS[MAX_ROWS];
unsigned int nbOfRows = 0;

unsigned int FetchRows()
{
  int rowIndex = 0;
  while (1) {
    const long value = Serial.parseInt();
    if (value == 0) {
      break;
    }

    ROWS[rowIndex].label = String(value) + " min.";

    if (value <= 5) {
      ROWS[rowIndex].color = TFT_RED;
    } else if (value <= 15) {
      ROWS[rowIndex].color = TFT_YELLOW;
    } else {
      ROWS[rowIndex].color = TFT_GREEN;
    }
    ++rowIndex;
  }
  return rowIndex;
}

void DrawRows()
{
  const int w = (M5.Display.width());
  const int margin = 3;
  int x = 0;
  int y = 0;
  int h = 0;

  for (int rowIndex = 0; rowIndex < nbOfRows; ++rowIndex) {
    if (rowIndex == 0) {
      h = (M5.Display.height() / nbOfRows) - margin;
      M5.Display.clearDisplay();
    }

    LGFX_Button button;
    button.initButtonUL(&M5.Display, x, y, w, h, TFT_BLACK, ROWS[rowIndex].color, TFT_BLACK, ROWS[rowIndex].label.c_str(), 4, 4);
    button.drawButton();

    y += (h + margin);
  }
  nbOfRows = 0;
}

////////////////////////////////////////////////////////////////////////
void Show(char* str)
{
    M5.Display.print(str);
    Serial.print(str);
}

////////////////////////////////////////////////////////////////////////
void setup(void)
{
  M5.begin();
  int textsize = M5.Display.height() / 100;
  if (textsize == 0) { textsize = 1; }
  M5.Display.setTextSize(textsize);
  Serial.begin(115200);
  Serial.println("Booted.");

  Show("==========================\n");
  Show("Sketch:\n");
  Show(__FILE__);
  Show("\n\n");

  Show("Build:\n");
  Show("\t* "__DATE__"\n");
  Show("\t* "__TIME__"\n");
  Show("==========================\n");
}

void loop(void)
{
  nbOfRows = FetchRows();

  // @TODO: show warning screen if no update since XXX sec/min

  DrawRows();
}
