// DS18B20 Read to Display of Nokia 3410

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire bus(A2);

DallasTemperature sensors(&bus);

#include "U8glib.h" 
U8GLIB_PCF8812 u8g(7, 6, 4, 5, 3);   // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8

float temperatureH;
float temperatureS;
char temperatureStringH[6] = "-";
char temperatureStringS[6] = "-";


void draw(void) {
// graphic commands to redraw the complete screen should be placed here
u8g.setFont(u8g_font_unifont_0_8);
u8g.drawStr( 0, 10, "Outdoor:");
//u8g.setFont(u8g_font_fub25);
u8g.setFont(u8g_font_8x13B);
u8g.drawStr( 0, 27, temperatureStringH);
u8g.drawStr( 43, 27, "\260C");
u8g.setFont(u8g_font_unifont_0_8);
u8g.drawStr( 0, 43, "Indoor:");
u8g.setFont(u8g_font_8x13B);
u8g.drawStr( 0, 58, temperatureStringS);
u8g.drawStr( 43, 58, "\260C");
}

void setup() {
// Start the sensors

// Rotate the screen
// u8g.setRot180();

sensors.begin();
}

void loop() {
// picture loop
u8g.firstPage();
do {
draw();
} while( u8g.nextPage() );

// Read Temperature
sensors.requestTemperatures();

temperatureH = sensors.getTempCByIndex(0);
dtostrf(temperatureH, 2, 2, temperatureStringH);
temperatureS = sensors.getTempCByIndex(1);
dtostrf(temperatureS, 2, 2, temperatureStringS);

// Delay for 1 seconds between readings
delay(1000);
}
