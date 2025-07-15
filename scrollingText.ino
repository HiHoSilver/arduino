#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "animation.h"

ArduinoLEDMatrix matrix;
String receivedText = "  Waiting for input...";
String currentDisplayedText = "";
unsigned long lastScrollTime = 0;
const unsigned long scrollInterval = 1000;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  pinMode(13,OUTPUT);
  matrix.begin();
}

void loop() {
  // Play the animation
  matrix.loadSequence(frames);
  matrix.play(true); // Blocking mode: waits until animation finishes

  delay(3850); // ⏳ Add extra time after animation ends (adjust as needed)

  // Handle incoming Serial input
  if (Serial.available()) {
    String newMessage = Serial.readStringUntil('\n');
    if (newMessage.length() > 0) {
      receivedText = newMessage;
    }
  }

  // Scroll the text if interval has passed
  if (millis() - lastScrollTime >= scrollInterval) {
    digitalWrite(13, HIGH);
    matrix.beginDraw();
    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(50);
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(receivedText);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();
    digitalWrite(13, LOW);
    delay(100);

    lastScrollTime = millis();
  }
}
