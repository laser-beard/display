// DS18B20 Read to Display of Nokia 3410

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire bus(A6);

DallasTemperature sensors(&bus);

#include "U8glib.h" 
U8GLIB_PCF8812 u8g(7, 6, 4, 5, 3);   // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8

float temperature;
char temperatureString[6] = "-";

void draw(void) {
// graphic commands to redraw the complete screen should be placed here
u8g.setFont(u8g_font_unifont);
u8g.drawStr( 0, 22, "In room:");
u8g.setFont(u8g_font_fub25);
// u8g.setFont(u8g_font_osr);
u8g.drawStr( 0, 54, temperatureString);
u8g.drawStr( 100, 54, "C");
}

void setup() {
// Start the sensors
u8g.setRot180();

sensors.begin();
}

void loop() {
// picture loop
u8g.firstPage();
do {
draw();
} while( u8g.nextPage() );

// Update the sensor readings
sensors.requestTemperatures();

// Read Temperature
temperature = sensors.getTempCByIndex(0);
dtostrf(temperature, 2, 1, temperatureString);

// Delay for 1 seconds between readings
delay(1000);
}
