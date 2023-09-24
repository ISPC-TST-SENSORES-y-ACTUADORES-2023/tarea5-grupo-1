
/***************************************************
  Este es un ejemplo de pintura de pantalla táctil para 
  Adafruit ILI9341 captouch

 Realizado por Ulises Ale
 ****************************************************/

#include <TFT_eSPI.h>
#include <SPI.h>       // Esto se necesita para el display
#include <Wire.h>      
#include <Adafruit_FT6206.h>

// El FT6206 es usado para el Hardware I2C
Adafruit_FT6206 ctp = Adafruit_FT6206();

// La pantalla también utiliza hardware SPI, plus #9 & #10
#define TFT_CS 15
#define TFT_DC 2
#define TFT_MOSI 23
#define TFT_SCLK 18

TFT_eSPI tft = TFT_eSPI(); // Invocar una biblioteca personalizada con ancho y alto predeterminados

#define ILI9341_RED TFT_RED
#define ILI9341_YELLOW TFT_YELLOW
#define ILI9341_GREEN TFT_GREEN
#define ILI9341_CYAN TFT_CYAN
#define ILI9341_BLUE TFT_BLUE
#define ILI9341_MAGENTA TFT_MAGENTA


// Tamaño de los cuadros de selección de color y tamaño del pincel.
#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

void setup(void) {
  Serial.begin(115200);
  Serial.println(F("Pintura al tacto de la tapa!"));
  
  tft.begin();

  if (! ctp.begin(40)) {  // Pasar el coeficiente de 'sensibilidad'
    Serial.println("No se pudo iniciar el controlador de pantalla táctil FT6206");
    while (1);
  }

  Serial.println("Pantalla táctil capacitiva iniciada");
  
  tft.fillScreen(ILI9341_BLACK);
  
  // Hacer los cuadros de selección de color
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
  tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
  tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
  tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
  tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
 
  // Seleccione el color actual 'rojo'
  tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
  currentcolor = ILI9341_RED;
}

void loop() {
  // Espera un toque
  if (! ctp.touched()) {
    delay(10); // Acelera la simulación.
    return;
  }

  // Recuperar un punto  
  TS_Point p = ctp.getPoint();
  
 /*
  // Imprima datos sin procesar desde el controlador táctil de pantalla
  Serial.print("X = "); Serial.print(p.x);
  Serial.print("\tY = "); Serial.print(p.y);
  Serial.print(" -> ");
 */

  // Dale la vuelta para que coincida con la pantalla.
  p.x = map(p.x, 0, 240, 240, 0);
  p.y = map(p.y, 0, 320, 320, 0);

  // Imprima las coordenadas reasignadas (girada)
  Serial.print("("); Serial.print(p.x);
  Serial.print(", "); Serial.print(p.y);
  Serial.println(")");
  

  if (p.y < BOXSIZE) {
     oldcolor = currentcolor;

     if (p.x < BOXSIZE) { 
       currentcolor = ILI9341_RED; 
       tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*2) {
       currentcolor = ILI9341_YELLOW;
       tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*3) {
       currentcolor = ILI9341_GREEN;
       tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*4) {
       currentcolor = ILI9341_CYAN;
       tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*5) {
       currentcolor = ILI9341_BLUE;
       tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x <= BOXSIZE*6) {
       currentcolor = ILI9341_MAGENTA;
       tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     }

     if (oldcolor != currentcolor) {
        if (oldcolor == ILI9341_RED) 
          tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
        if (oldcolor == ILI9341_YELLOW) 
          tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
        if (oldcolor == ILI9341_GREEN) 
          tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
        if (oldcolor == ILI9341_CYAN) 
          tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
        if (oldcolor == ILI9341_BLUE) 
          tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
        if (oldcolor == ILI9341_MAGENTA) 
          tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
     }
  }
  if (((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < tft.height())) {
    tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
  }
}