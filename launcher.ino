#include <TFT_eSPI.h>  // Include the graphics library
TFT_eSPI tft = TFT_eSPI(); // Create object "tft"

struct Button {
  String name;
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  void (*function)(); // Pointer to function to be called when button is pressed
};

#define BUTTON_SPACING 12

void mode1Function() { /* Your code for Mode 1 goes here */}
void mode2Function() { /* Your code for Mode 2 goes here */}
void mode3Function() { /* Your code for Mode 2 goes here */}
void mode4Function() { /* Your code for Mode 2 goes here */}
// Define more mode functions as needed

Button buttons[] = {
  {"Release\nHounds", 0, 0, 0, 0, mode1Function},
  {"Mode 2", 0, 0, 0, 0, mode2Function},
  {"Mode\n3", 0, 0, 0, 0, mode3Function},
  {"Go\nHome", 0, 0, 0, 0, mode4Function},
  {"Settings", 0, 0, 0, 0, mode4Function},
  {"Mode 9", 0, 0, 0, 0, mode4Function},
  {"Mode 44", 0, 0, 0, 0, mode4Function},
  {"Jiminy", 0, 0, 0, 0, mode4Function},
  {"Games", 0, 0, 0, 0, mode4Function},
  {"Produc\ntivity", 0, 0, 0, 0, mode4Function},
  {"Lights\nOff", 0, 0, 0, 0, mode4Function},
  {"Get\nReal", 0, 0, 0, 0, mode4Function},
  // Add other modes here as needed
};

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  arrangeButtons();
}

void arrangeButtons() {
  int buttonSpacing = BUTTON_SPACING; // Define spacing between buttons
  int numButtons = sizeof(buttons) / sizeof(buttons[0]);
  int numRows = (numButtons <= 4) ? 2 : ((numButtons <= 9) ? 3 : 4);
  int numColumns = (numButtons + numRows - 1) / numRows;

  int buttonWidth = (tft.width() - (numColumns + 1) * buttonSpacing) / numColumns;
  int buttonHeight = (tft.height() - (numRows + 1) * buttonSpacing) / numRows;

  int idx = 0;
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numColumns; ++col) {
      if (idx < numButtons) {
        buttons[idx].x = col * (buttonWidth + buttonSpacing) + buttonSpacing;
        buttons[idx].y = row * (buttonHeight + buttonSpacing) + buttonSpacing;
        buttons[idx].width = buttonWidth;
        buttons[idx].height = buttonHeight;
        drawButton(buttons[idx]);
        ++idx;
      }
    }
  }
}

void drawButton(const Button &button) {
  tft.setTextFont(1); // Adjust the font if needed
  tft.setTextSize(2);
  tft.fillRect(button.x, button.y, button.width, button.height, TFT_BLUE);
  tft.drawRect(button.x, button.y, button.width, button.height, TFT_WHITE); // Draw border
  
  tft.setTextColor(TFT_WHITE, TFT_BLUE); // set text color to white and background color to blue

  int charWidth = 12;
  int lineHeight = 16; // Adjust this value to set the spacing between lines
  String line1 = "";
  String line2 = "";

  // Split the button name into two lines at '\n'
  int newlinePos = button.name.indexOf('\n');
  if(newlinePos != -1) {
    line1 = button.name.substring(0, newlinePos);
    line2 = button.name.substring(newlinePos + 1);
  } else {
    line1 = button.name;
  }

  // Calculate the positions and draw the lines
  int yCenter = button.y + button.height / 2;
  int xCenter = button.x + button.width / 2;

  if(line2 != "") {
    tft.setCursor(xCenter - (line1.length() * charWidth / 2), yCenter - lineHeight);
    tft.print(line1);

    tft.setCursor(xCenter - (line2.length() * charWidth / 2), yCenter + lineHeight - charWidth);
    tft.print(line2);
  } else {
    tft.setCursor(xCenter - (line1.length() * charWidth / 2), yCenter - charWidth / 2);
    tft.print(line1);
  }
}

void loop() {
  uint16_t t_x, t_y;
  if (tft.getTouch(&t_x, &t_y)) {
    for (const auto &button : buttons) {
      if (t_x >= button.x && t_x <= button.x + button.width && t_y >= button.y && t_y <= button.y + button.height) {
        button.function();
        delay(300);
        break;
      }
    }
  }
}
