
/***************************************************
  Este es un ejemplo de pintura de pantalla táctil para 
  Adafruit ILI9341 captouch

 Realizado por Ulises Ale
 ****************************************************/
// La pantalla también utiliza hardware SPI, plus #9 & #10
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <Adafruit_FT6206.h>

#define TFT_CS 15
#define TFT_DC 2
#define TS_CS 4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_FT6206 ts;

void setup(void) {
  Serial.begin(115200);
  if (!ts.begin(TS_CS)) {
    Serial.println("No se pudo iniciar el controlador de pantalla táctil");
    while (1);
  }

  tft.begin();

  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  tft.println("Toca la pantalla!");
}

void loop() {
  // Comprueba si se ha tocado la pantalla
  if (ts.touched()) {
    // Recopila datos del toque
    TS_Point p = ts.getPoint();

    // Muestra las coordenadas del toque en la pantalla
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0, 0);
    tft.print("X = "); tft.println(p.x);
    tft.print("Y = "); tft.println(p.y);
  }
}
