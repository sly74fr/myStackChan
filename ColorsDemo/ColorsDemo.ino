#include <Arduino.h>
#include <M5Unified.h>

////////////////////////////////////////////////////////////////////////
typedef struct { 
  char* name;
  int value;
} Dictionary;

const Dictionary COLORS[] {
  // RED
    {"POWDERBLUE", 0xB0E0},
    {"DARKGOLDENROD", 0xB886},
    {"RED", 0xF800},
  // ORANGE
    {"LIGHTCORAL", 0xF080},
    {"SALMON", 0xFA80},
    {"SANDYBROWN", 0xF4A4},
  // YELLOW
    {"GOLD", 0xFEA0},
    {"YELLOW", 0xFFE0},
    {"LEMONCHIFFON", 0xFFAC},
    {"SEASHELL", 0xFFF5},
    {"GREENYELLOW", 0xB7E0},
  // GREEN
    {"LIGHTSLATEGRAY", 0x7788},
    {"GREEN", 0x07E0},
    {"SPRINGGREEN", 0x4682},
    {"SEAGREEN", 0x2E8B},
    {"MEDIUMAQUAMARINE", 0x66CD},
    {"DARKSLATEGRAY", 0x2F4F},
  // BLUE
    {"AQUAMARINE", 0x7FFA},
    {"DARKCYAN", 0x03EF},
    {"BLUE", 0x001F},
    {"DEEPSKYBLUE", 0x00BF},
    {"STEELBLUE", 0x00FF},
    {"MIDNIGHTBLUE", 0x1919},
    {"LIGHTSEAGREEN", 0x20B2},
    {"SLATEBLUE", 0x6A5A},
  // VIOLET
    {"VIOLET", 0x915C},
    {"LAWNGREEN", 0x7CFC},
    {"MAGENTA", 0xF81F},
    {"LIGHTCYAN", 0xE0FF},
    {"THISTLE", 0xD8BF},
    {"SIENNA", 0xA052},
  // SHADES
    {"WHITE", 0xFFFF},
    {"SNOW", 0xFFFA},
    {"BURLYWOOD", 0xDEB8},
    {"GREY", 0x8410},
    {"DARKGREY", 0x7BEF}
};
const int COLORS_SIZE = sizeof(COLORS) / sizeof(Dictionary);

////////////////////////////////////////////////////////////////////////
const int MAX_ROWS = 8;
int nbOfRows = 1;
int colorIndex = 0;

void DrawColors()
{
  static int x = 0;
  static int y = 0;
  const int margin = 3;
  const int h = (M5.Display.height() / nbOfRows) - margin;
  const int remaining = M5.Display.height() - (nbOfRows * (h + margin));
  const int w = (M5.Display.width());
  if (colorIndex == 0) {
    Serial.println("~~~ turnaround ~~~");
    Serial.print("nbOfRows = ");
    Serial.println(nbOfRows);
    Serial.print("margin = ");
    Serial.println(margin);
    Serial.print("h = ");
    Serial.println(h);
    Serial.print("remaining = ");
    Serial.println(remaining);
    Serial.println("~~~~~~~");
  }

  LGFX_Button button;
  button.initButtonUL(&M5.Display, x, y, w, h, TFT_BLACK, COLORS[colorIndex].value, TFT_BLACK, COLORS[colorIndex].name, 2, 2);
  Serial.print(y);
  Serial.print(": ");
  Serial.print(COLORS[colorIndex].name);
  Serial.print(" (");
  Serial.print(colorIndex + 1);
  Serial.print(" / ");
  Serial.print(COLORS_SIZE);
  Serial.println(").");
  button.drawButton();

  M5.delay(500);

  y += (h + margin);
  if ((M5.Display.height() - y) < (h + margin)) {
    y = 0;
    Serial.println("- cls -");
  }

  if (++colorIndex >= COLORS_SIZE) {
    colorIndex = 0;
    y = 0;
    M5.delay(3000);
    M5.Display.clearDisplay();
    ++nbOfRows;
    if (nbOfRows >= MAX_ROWS) {
      nbOfRows = 1;
    }
  }
}

void Show(char* str)
{
    M5.Display.print(str);
    Serial.print(str);
}

////////////////////////////////////////////////////////////////////////
void setup(void)
{
  M5.begin();
  int textSize = M5.Display.height() / 100;
  if (textSize == 0) { textSize = 1; }
  M5.Display.setTextSize(textSize);
  Serial.begin(115200);
  Serial.println("Booted.");

  Show("==========================\n");
  Show("Sketch: '"__FILE__"'.\n\n");

  Show("Screen:\n");
  Show("\t* height = ");
  M5.Display.print(M5.Display.height());
  Serial.print(M5.Display.height());
  Show("\n");
  Show("\t* width = ");
  M5.Display.print(M5.Display.width());
  Serial.print(M5.Display.width());
  Show("\n");
  Show("\t* textSize = ");
  M5.Display.print(textSize);
  Serial.print(textSize);
  Show("\n\n");

  Show("Build:\n");
  Show("\t* "__DATE__"\n");
  Show("\t* "__TIME__"\n");
  Show("\n");

  Show("Colors:");
  M5.Display.print(COLORS_SIZE);
  Serial.print(COLORS_SIZE);
  Show("\n");
  Show("==========================\n");

  M5.delay(3000);
  M5.Display.clearDisplay();
}

void loop(void)
{
  DrawColors();
}
