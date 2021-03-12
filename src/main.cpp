// Display Library example for SPI e-paper panels from Dalian Good Display and
// boards from Waveshare. Requires HW SPI and Adafruit_GFX. Caution: the e-paper
// panels require 3.3V supply AND data lines!
//
// Display Library based on Demo Example from Good Display:
// http://www.e-paper-display.com/download_list/downloadcategoryid=34&isMode=false.html
//
// Author: Jean-Marc Zingg
//
// Version: see library.properties
//
// Library: https://github.com/ZinggJM/GxEPD2

// GxEPD2_U8G2_Fonts_Example : show use of U8G2_FOR_ADAFRUIT_GFX with GxEPD2
//
// Library: https://github.com/olikraus/U8g2_for_Adafruit_GFX
// see: https://github.com/olikraus/U8g2_for_Adafruit_GFX/blob/master/README.md
//
// NOTE: you need to SAVE the modified example to a saveable location for UTF-8
// characters to work
//       e.g. for Umlauts

// Supporting Arduino Forum Topics:
// Waveshare e-paper displays with SPI:
// http://forum.arduino.cc/index.php?topic=487007.0 Good Display ePaper for
// Arduino: https://forum.arduino.cc/index.php?topic=436411.0

// mapping suggestion from Waveshare SPI e-Paper to Wemos D1 mini
// BUSY -> D2, RST -> D4, DC -> D3, CS -> D8, CLK -> D5, DIN -> D7, GND ->
// GND, 3.3V -> 3.3V NOTE: connect 3.3k pull-down from D8 to GND if your board
// or shield has level converters NOTE for ESP8266: using SS (GPIO15) for CS may
// cause boot mode problems, use different pin in case, or 4k7 pull-down

// mapping suggestion from Waveshare SPI e-Paper to generic ESP8266
// BUSY -> GPIO4, RST -> GPIO2, DC -> GPIO0, CS -> GPIO15, CLK -> GPIO14, DIN ->
// GPIO13, GND -> GND, 3.3V -> 3.3V NOTE: connect 3.3k pull-down from GPIO15 to
// GND if your board or shield has level converters NOTE for ESP8266: using SS
// (GPIO15) for CS may cause boot mode problems, use different pin in case,
// or 3.3k pull-down

// mapping of Waveshare e-Paper ESP8266 Driver Board, new version (see
// GxEPD2_boards_added.h for old version) BUSY -> GPIO5, RST -> GPIO2, DC ->
// GPIO4, CS -> GPIO15, CLK -> GPIO14, DIN -> GPIO13, GND -> GND, 3.3V -> 3.3V
// NOTE for ESP8266: using SS (GPIO15) for CS may cause boot mode problems, add
// a 3.3k pull-down in case
//      the e-Paper ESP8266 Driver Board should have no boot mode issue, as it
//      doesn't use level converters

// mapping suggestion for ESP32, e.g. LOLIN32, see
// .../variants/.../pins_arduino.h for your board NOTE: there are variants with
// different pins for SPI ! CHECK SPI PINS OF YOUR BOARD BUSY -> 4, RST -> 16,
// DC -> 17, CS -> SS(5), CLK -> SCK(18), DIN -> MOSI(23), GND -> GND, 3.3V
// -> 3.3V

// mapping of Waveshare ESP32 Driver Board
// BUSY -> 25, RST -> 26, DC -> 27, CS-> 15, CLK -> 13, DIN -> 14
// NOTE: this board uses "unusual" SPI pins and requires re-mapping of HW SPI to
// these pins in SPIClass
//       see example GxEPD2_WS_ESP32_Driver.ino, it shows how this can be done
//       easily

// new mapping suggestion for STM32F1, e.g. STM32F103C8T6 "BluePill"
// BUSY -> A1, RST -> A2, DC -> A3, CS-> A4, CLK -> A5, DIN -> A7

// mapping suggestion for AVR, UNO, NANO etc.
// BUSY -> 7, RST -> 9, DC -> 8, CS-> 10, CLK -> 13, DIN -> 11

// mapping of Waveshare Universal e-Paper Raw Panel Driver Shield for Arduino /
// NUCLEO BUSY -> 7, RST -> 8, DC -> 9, CS-> 10, CLK -> 13, DIN -> 11

// mapping suggestion for Arduino MEGA
// BUSY -> 7, RST -> 9, DC -> 8, CS-> 53, CLK -> 52, DIN -> 51

// base class GxEPD2_GFX can be used to pass references or pointers to the
// display instance as parameter, uses ~1.2k more code enable or disable
// GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0
#include <GxEPD2_3C.h>
#include <GxEPD2_7C.h>
#include <GxEPD2_BW.h>
#include <U8g2_for_Adafruit_GFX.h>

#if defined(ESP8266)
// select one and adapt to your mapping, can use full buffer size (full HEIGHT)
// GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(/*CS=D8*/ SS,
// /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEP015OC1 no longer available
// GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT>
// display(GxEPD2_154_D67(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEH0154D67 GxEPD2_BW<GxEPD2_154_T8, GxEPD2_154_T8::HEIGHT>
// display(GxEPD2_154_T8(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEW0154T8 152x152 GxEPD2_BW<GxEPD2_154_M09, GxEPD2_154_M09::HEIGHT>
// display(GxEPD2_154_M09(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEW0154M09 200x200 GxEPD2_BW<GxEPD2_154_M10, GxEPD2_154_M10::HEIGHT>
// display(GxEPD2_154_M10(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEW0154M10 152x152 GxEPD2_BW<GxEPD2_213, GxEPD2_213::HEIGHT>
// display(GxEPD2_213(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
// // GDE0213B1, phased out GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT>
// display(GxEPD2_213_B72(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEH0213B72 GxEPD2_BW<GxEPD2_213_B73, GxEPD2_213_B73::HEIGHT>
// display(GxEPD2_213_B73(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEH0213B73 GxEPD2_BW<GxEPD2_213_flex, GxEPD2_213_flex::HEIGHT>
// display(GxEPD2_213_flex(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEW0213I5F GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT>
// display(GxEPD2_290(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
// GxEPD2_BW<GxEPD2_290_T5, GxEPD2_290_T5::HEIGHT>
// display(GxEPD2_290_T5(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEW029T5 GxEPD2_BW<GxEPD2_260, GxEPD2_260::HEIGHT>
// display(GxEPD2_260(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
// GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=D8*/ SS,
// /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); GxEPD2_BW<GxEPD2_371,
// GxEPD2_371::HEIGHT> display(GxEPD2_371(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/
// 2, /*BUSY=D2*/ 4)); GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT>
// display(GxEPD2_420(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
// can use only half buffer size
// GxEPD2_BW < GxEPD2_583, GxEPD2_583::HEIGHT / 2 > display(GxEPD2_583(/*CS=D8*/
// SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); GxEPD2_BW < GxEPD2_583_T8,
// GxEPD2_583_T8::HEIGHT / 2 > display(GxEPD2_583_T8(/*CS=D8*/ SS, /*DC=D3*/ 0,
// /*RST=D4*/ 2, /*BUSY=D2*/ 4)); GxEPD2_BW < GxEPD2_750, GxEPD2_750::HEIGHT / 2
// > display(GxEPD2_750(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
// GxEPD2_BW < GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT / 2 >
// display(GxEPD2_750_T7(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEW075T7 800x480
// 3-color e-papers
// GxEPD2_3C<GxEPD2_154c, GxEPD2_154c::HEIGHT> display(GxEPD2_154c(/*CS=D8*/ SS,
// /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEW0154Z04 no longer available
// GxEPD2_3C<GxEPD2_154_Z90c, GxEPD2_154_Z90c::HEIGHT>
// display(GxEPD2_154_Z90c(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEH0154Z90 GxEPD2_3C<GxEPD2_213c, GxEPD2_213c::HEIGHT>
// display(GxEPD2_213c(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
// GxEPD2_3C<GxEPD2_290c, GxEPD2_290c::HEIGHT> display(GxEPD2_290c(/*CS=D8*/ SS,
// /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); GxEPD2_3C<GxEPD2_270c,
// GxEPD2_270c::HEIGHT> display(GxEPD2_270c(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/
// 2, /*BUSY=D2*/ 4));
// can use only half buffer size
// GxEPD2_3C<GxEPD2_420c, GxEPD2_420c::HEIGHT / 2> display(GxEPD2_420c(/*CS=D8*/
// SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
// can use only quarter buffer size
// GxEPD2_3C < GxEPD2_583c, GxEPD2_583c::HEIGHT / 4 >
// display(GxEPD2_583c(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
// GxEPD2_3C<GxEPD2_750c, GxEPD2_750c::HEIGHT / 4> display(GxEPD2_750c(/*CS=D8*/
// SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); GxEPD2_3C < GxEPD2_750c_Z08,
// GxEPD2_750c_Z08::HEIGHT / 4 > display(GxEPD2_750c_Z08(/*CS=D8*/ SS, /*DC=D3*/
// 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEW075Z08 800x480 GxEPD2_3C <
// GxEPD2_750c_Z90, GxEPD2_750c_Z90::HEIGHT / 4 >
// display(GxEPD2_750c_Z90(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/
// 4)); // GDEH075Z90 880x528
// 7-color e-paper
// GxEPD2_3C < GxEPD2_565c, GxEPD2_565c::HEIGHT / 4 >
// display(GxEPD2_565c(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
// // Waveshare 5.65" 7-color (3C graphics) GxEPD2_7C < GxEPD2_565c,
// GxEPD2_565c::HEIGHT / 4 > display(GxEPD2_565c(/*CS=D8*/ SS, /*DC=D3*/ 0,
// /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // Waveshare 5.65" 7-color
// grey levels parallel IF e-papers on Waveshare e-Paper IT8951 Driver HAT
// HRDY -> 4, RST -> 2, CS -> SS(15), SCK -> SCK(14), MOSI -> MOSI(D7(13)), MISO
// -> MISO(D6(12)), GND -> GND, 5V -> 5V note: 5V supply needs to be exact and
// strong; 5V pin of USB powered Wemos D1 mini doesn't work!
// GxEPD2_BW<GxEPD2_it60, GxEPD2_it60::HEIGHT / 8> display(GxEPD2_it60(/*CS=5*/
// SS, /*DC=*/ 0, /*RST=*/ 2, /*BUSY=*/ 4)); GxEPD2_BW < GxEPD2_it60_1448x1072,
// GxEPD2_it60_1448x1072::HEIGHT / 8 > display(GxEPD2_it60_1448x1072(/*CS=5*/ SS,
// /*DC=*/ 0, /*RST=*/ 2, /*BUSY=*/ 4));

// ***** for mapping of Waveshare e-Paper ESP8266 Driver Board *****
// select one , can use full buffer size (full HEIGHT)
// GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(/*CS=15*/ SS,
// /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); // GDEP015OC1 no longer available
// GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT>
// display(GxEPD2_154_D67(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// // GDEH0154D67 GxEPD2_BW<GxEPD2_154_T8, GxEPD2_154_T8::HEIGHT>
// display(GxEPD2_154_T8(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// // GDEW0154T8 152x152 GxEPD2_BW<GxEPD2_154_M09, GxEPD2_154_M09::HEIGHT>
// display(GxEPD2_154_M09(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// // GDEW0154M09 200x200 GxEPD2_BW<GxEPD2_154_M10, GxEPD2_154_M10::HEIGHT>
// display(GxEPD2_154_M10(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// // GDEW0154M10 152x152 GxEPD2_BW<GxEPD2_213, GxEPD2_213::HEIGHT>
// display(GxEPD2_213(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); //
// GDE0213B1, phased out GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT>
// display(GxEPD2_213_B72(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// // GDEH0213B72 GxEPD2_BW<GxEPD2_213_B73, GxEPD2_213_B73::HEIGHT>
// display(GxEPD2_213_B73(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// // GDEH0213B73 GxEPD2_BW<GxEPD2_213_flex, GxEPD2_213_flex::HEIGHT>
// display(GxEPD2_213_flex(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// // GDEW0213I5F GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT>
// display(GxEPD2_290(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// GxEPD2_BW<GxEPD2_290_T5, GxEPD2_290_T5::HEIGHT>
// display(GxEPD2_290_T5(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// // GDEW029T5 GxEPD2_BW<GxEPD2_260, GxEPD2_260::HEIGHT>
// display(GxEPD2_260(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=15*/ SS,
// /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); GxEPD2_BW<GxEPD2_371,
// GxEPD2_371::HEIGHT> display(GxEPD2_371(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2,
// /*BUSY=5*/ 5)); GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT>
// display(GxEPD2_420(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// can use only half buffer size
// GxEPD2_BW < GxEPD2_583, GxEPD2_583::HEIGHT / 2 > display(GxEPD2_583(/*CS=15*/
// SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); GxEPD2_BW < GxEPD2_583_T8,
// GxEPD2_583_T8::HEIGHT / 2 > display(GxEPD2_583_T8(/*CS=15*/ SS, /*DC=4*/ 4,
// /*RST=2*/ 2, /*BUSY=5*/ 5)); GxEPD2_BW < GxEPD2_750, GxEPD2_750::HEIGHT / 2 >
// display(GxEPD2_750(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// GxEPD2_BW < GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT / 2 >
// display(GxEPD2_750_T7(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// // GDEW075T7 800x480
// 3-color e-papers
// GxEPD2_3C<GxEPD2_154c, GxEPD2_154c::HEIGHT> display(GxEPD2_154c(/*CS=15*/ SS,
// /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); // GDEW0154Z04 no longer available
// GxEPD2_3C<GxEPD2_154_Z90c, GxEPD2_154_Z90c::HEIGHT>
// display(GxEPD2_154_Z90c(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// // GDEH0154Z90 GxEPD2_3C<GxEPD2_213c, GxEPD2_213c::HEIGHT>
// display(GxEPD2_213c(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// GxEPD2_3C<GxEPD2_290c, GxEPD2_290c::HEIGHT> display(GxEPD2_290c(/*CS=15*/ SS,
// /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); GxEPD2_3C<GxEPD2_270c,
// GxEPD2_270c::HEIGHT> display(GxEPD2_270c(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/
// 2, /*BUSY=5*/ 5));
// can use only half buffer size
// GxEPD2_3C<GxEPD2_420c, GxEPD2_420c::HEIGHT / 2> display(GxEPD2_420c(/*CS=15*/
// SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
// can use only quarter buffer size
// GxEPD2_3C<GxEPD2_583c, GxEPD2_583c::HEIGHT / 4> display(GxEPD2_583c(/*CS=15*/
// SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); GxEPD2_3C<GxEPD2_750c,
// GxEPD2_750c::HEIGHT / 4> display(GxEPD2_750c(/*CS=15*/ SS, /*DC=4*/ 4,
// /*RST=2*/ 2, /*BUSY=5*/ 5)); GxEPD2_3C<GxEPD2_750c_Z08,
// GxEPD2_750c_Z08::HEIGHT / 4> display(GxEPD2_750c_Z08(/*CS=15*/ SS, /*DC=4*/ 4,
// /*RST=2*/ 2, /*BUSY=5*/ 5)); // GDEW075Z08 800x480 GxEPD2_3C<GxEPD2_750c_Z90,
// GxEPD2_750c_Z90::HEIGHT / 4> display(GxEPD2_750c_Z90(/*CS=15*/ SS, /*DC=4*/ 4,
// /*RST=2*/ 2, /*BUSY=5*/ 5)); // GDEH075Z90 880x528
// 7-color e-paper
// GxEPD2_7C < GxEPD2_565c, GxEPD2_565c::HEIGHT / 4 >
// display(GxEPD2_565c(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); //
// Waveshare 5.65" 7-color
#endif

#if defined(ESP32)
// select one and adapt to your mapping, can use full buffer size (full HEIGHT)
// GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(/*CS=5*/ SS,
// /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEP015OC1 no longer available
// GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT>
// display(GxEPD2_154_D67(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); //
// GDEH0154D67 GxEPD2_BW<GxEPD2_154_T8, GxEPD2_154_T8::HEIGHT>
// display(GxEPD2_154_T8(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); //
// GDEW0154T8 152x152 GxEPD2_BW<GxEPD2_154_M09, GxEPD2_154_M09::HEIGHT>
// display(GxEPD2_154_M09(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); //
// GDEW0154M09 200x200 GxEPD2_BW<GxEPD2_154_M10, GxEPD2_154_M10::HEIGHT>
// display(GxEPD2_154_M10(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); //
// GDEW0154M10 152x152 GxEPD2_BW<GxEPD2_213, GxEPD2_213::HEIGHT>
// display(GxEPD2_213(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); //
// GDE0213B1, phased out GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT>
// display(GxEPD2_213_B72(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); //
// GDEH0213B72 GxEPD2_BW<GxEPD2_213_B73, GxEPD2_213_B73::HEIGHT>
// display(GxEPD2_213_B73(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); //
// GDEH0213B73 GxEPD2_BW<GxEPD2_213_flex, GxEPD2_213_flex::HEIGHT>
// display(GxEPD2_213_flex(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
// // GDEW0213I5F GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT>
// display(GxEPD2_290(/*CS=5*/ 15, /*DC=*/27, /*RST=*/26, /*BUSY=*/25));
// GxEPD2_BW<GxEPD2_290_T5, GxEPD2_290_T5::HEIGHT>
// display(GxEPD2_290_T5(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); //
// GDEW029T5 GxEPD2_BW<GxEPD2_260, GxEPD2_260::HEIGHT>
// display(GxEPD2_260(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
// GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=5*/ SS,
// /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); GxEPD2_BW<GxEPD2_371,
// GxEPD2_371::HEIGHT> display(GxEPD2_371(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16,
// /*BUSY=*/ 4)); GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT>
// display(GxEPD2_420(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
// GxEPD2_BW<GxEPD2_583, GxEPD2_583::HEIGHT> display(GxEPD2_583(/*CS=5*/ 15,
// /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25));
GxEPD2_BW<GxEPD2_583_T8, GxEPD2_583_T8::HEIGHT> display(
    GxEPD2_583_T8(/*CS=5*/ 15, /*DC=*/27, /*RST=*/26, /*BUSY=*/25));
// GxEPD2_BW<GxEPD2_750, GxEPD2_750::HEIGHT> display(GxEPD2_750(/*CS=5*/ SS,
// /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); GxEPD2_BW<GxEPD2_750_T7,
// GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/
// 16, /*BUSY=*/ 4)); // GDEW075T7 800x480
// 3-color e-papers
// GxEPD2_3C<GxEPD2_154c, GxEPD2_154c::HEIGHT> display(GxEPD2_154c(/*CS=5*/ SS,
// /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW0154Z04 no longer available
// GxEPD2_3C<GxEPD2_154_Z90c, GxEPD2_154_Z90c::HEIGHT>
// display(GxEPD2_154_Z90c(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
// // GDEH0154Z90 GxEPD2_3C<GxEPD2_213c, GxEPD2_213c::HEIGHT>
// display(GxEPD2_213c(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
// GxEPD2_3C<GxEPD2_290c, GxEPD2_290c::HEIGHT> display(GxEPD2_290c(/*CS=5*/ SS,
// /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); GxEPD2_3C<GxEPD2_270c,
// GxEPD2_270c::HEIGHT> display(GxEPD2_270c(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16,
// /*BUSY=*/ 4)); GxEPD2_3C<GxEPD2_420c, GxEPD2_420c::HEIGHT>
// display(GxEPD2_420c(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
// GxEPD2_3C<GxEPD2_583c, GxEPD2_583c::HEIGHT> display(GxEPD2_583c(/*CS=5*/ SS,
// /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); GxEPD2_3C<GxEPD2_750c,
// GxEPD2_750c::HEIGHT> display(GxEPD2_750c(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16,
// /*BUSY=*/ 4)); GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT>
// display(GxEPD2_750c_Z08(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
// // GDEW075Z08 800x480 GxEPD2_3C<GxEPD2_750c_Z90, GxEPD2_750c_Z90::HEIGHT / 2>
// display(GxEPD2_750c_Z90(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
// // GDEH075Z90 880x528
// 7-color e-paper
// GxEPD2_3C < GxEPD2_565c, GxEPD2_565c::HEIGHT / 2 >
// display(GxEPD2_565c(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); //
// Waveshare 5.65" 7-color (3C graphics) GxEPD2_7C < GxEPD2_565c,
// GxEPD2_565c::HEIGHT / 2 > display(GxEPD2_565c(/*CS=5*/ SS, /*DC=*/ 17,
// /*RST=*/ 16, /*BUSY=*/ 4)); // Waveshare 5.65" 7-color

// grey levels parallel IF e-papers on Waveshare e-Paper IT8951 Driver HAT
// HRDY -> 4, RST -> 16, CS -> SS(5), SCK -> SCK(18), MOSI -> MOSI(23), MISO ->
// MISO(19), GND -> GND, 5V -> 5V note: 5V supply needs to be exact and strong;
// 5V over diode from USB (e.g. Wemos D1 mini) doesn't work!
// GxEPD2_BW<GxEPD2_it60, GxEPD2_it60::HEIGHT> display(GxEPD2_it60(/*CS=5*/ SS,
// /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); GxEPD2_BW < GxEPD2_it60_1448x1072,
// GxEPD2_it60_1448x1072::HEIGHT / 4 > display(GxEPD2_it60_1448x1072(/*CS=5*/ SS,
// /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

// Waveshare 12.48 b/w SPI display board and frame or Good Display 12.48 b/w
// panel GDEW1248T3 general constructor for use with all parameters, e.g. for
// Waveshare ESP32 driver board mounted on connection board
// GxEPD2_BW < GxEPD2_1248, GxEPD2_1248::HEIGHT / 4 >
// display(GxEPD2_1248(/*sck=*/ 13, /*miso=*/ 12, /*mosi=*/ 14, /*cs_m1=*/ 23,
// /*cs_s1=*/ 22, /*cs_m2=*/ 16, /*cs_s2=*/ 19,
//                             /*dc1=*/ 25, /*dc2=*/ 17, /*rst1=*/ 33, /*rst2=*/
//                             5, /*busy_m1=*/ 32, /*busy_s1=*/ 26, /*busy_m2=*/
//                             18, /*busy_s2=*/ 4));
#endif

// can't use package "STMF1 Boards (STM32Duino.com)" (Roger Clark) anymore with
// Adafruit_GFX, use "STM32 Boards (selected from submenu)" (STMicroelectronics)
#if defined(ARDUINO_ARCH_STM32)
#define MAX_DISPLAY_BUFFER_SIZE 15000ul  // ~15k is a good compromise
#define MAX_HEIGHT(EPD)                                        \
    (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) \
         ? EPD::HEIGHT                                         \
         : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
// select one and adapt to your mapping
// GxEPD2_BW<GxEPD2_154, MAX_HEIGHT(GxEPD2_154)> display(GxEPD2_154(/*CS=4*/ SS,
// /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); // GDEP015OC1 no longer available
// GxEPD2_BW<GxEPD2_154_D67, MAX_HEIGHT(GxEPD2_154_D67)>
// display(GxEPD2_154_D67(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEH0154D67 GxEPD2_BW<GxEPD2_154_T8, MAX_HEIGHT(GxEPD2_154_T8)>
// display(GxEPD2_154_T8(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEW0154T8 152x152 GxEPD2_BW<GxEPD2_154_M09, MAX_HEIGHT(GxEPD2_154_M09)>
// display(GxEPD2_154_M09(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEW0154M09 200x200 GxEPD2_BW<GxEPD2_154_M10, MAX_HEIGHT(GxEPD2_154_M10)>
// display(GxEPD2_154_M10(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEW0154M10 152x152 GxEPD2_BW<GxEPD2_213, MAX_HEIGHT(GxEPD2_213)>
// display(GxEPD2_213(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDE0213B1, phased out GxEPD2_BW<GxEPD2_213_B72, MAX_HEIGHT(GxEPD2_213_B72)>
// display(GxEPD2_213_B72(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEH0213B72 GxEPD2_BW<GxEPD2_213_B73, MAX_HEIGHT(GxEPD2_213_B73)>
// display(GxEPD2_213_B73(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEH0213B73 GxEPD2_BW<GxEPD2_213_flex, MAX_HEIGHT(GxEPD2_213_flex)>
// display(GxEPD2_213_flex(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEW0213I5F GxEPD2_BW<GxEPD2_290, MAX_HEIGHT(GxEPD2_290)>
// display(GxEPD2_290(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1));
// GxEPD2_BW<GxEPD2_290_T5, MAX_HEIGHT(GxEPD2_290_T5)>
// display(GxEPD2_290_T5(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEW029T5 GxEPD2_BW<GxEPD2_260, MAX_HEIGHT(GxEPD2_260)>
// display(GxEPD2_260(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1));
// GxEPD2_BW<GxEPD2_270, MAX_HEIGHT(GxEPD2_270)> display(GxEPD2_270(/*CS=4*/ SS,
// /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); GxEPD2_BW<GxEPD2_371,
// MAX_HEIGHT(GxEPD2_371)> display(GxEPD2_371(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2,
// /*BUSY=*/ 1)); GxEPD2_BW<GxEPD2_420, MAX_HEIGHT(GxEPD2_420)>
// display(GxEPD2_420(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1));
// GxEPD2_BW<GxEPD2_583, MAX_HEIGHT(GxEPD2_583)> display(GxEPD2_583(/*CS=4*/ SS,
// /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); GxEPD2_BW <GxEPD2_583_T8,
// MAX_HEIGHT(GxEPD2_583_T8)> display(GxEPD2_583_T8(/*CS=4*/ SS, /*DC=*/ 3,
// /*RST=*/ 2, /*BUSY=*/ 1)); GxEPD2_BW<GxEPD2_750, MAX_HEIGHT(GxEPD2_750)>
// display(GxEPD2_750(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1));
// GxEPD2_BW<GxEPD2_750_T7, MAX_HEIGHT(GxEPD2_750_T7)>
// display(GxEPD2_750_T7(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEW075T7 800x480
// 3-color e-papers
#define MAX_HEIGHT_3C(EPD)                                           \
    (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) \
         ? EPD::HEIGHT                                               \
         : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))
// GxEPD2_3C<GxEPD2_154c, MAX_HEIGHT_3C(GxEPD2_154c)>
// display(GxEPD2_154c(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEW0154Z04 no longer available GxEPD2_3C<GxEPD2_154_Z90c,
// MAX_HEIGHT_3C(GxEPD2_154_Z90c)> display(GxEPD2_154_Z90c(/*CS=4*/ SS, /*DC=*/
// 3, /*RST=*/ 2, /*BUSY=*/ 1)); // GDEH0154Z90 GxEPD2_3C<GxEPD2_213c,
// MAX_HEIGHT_3C(GxEPD2_213c)> display(GxEPD2_213c(/*CS=4*/ SS, /*DC=*/ 3,
// /*RST=*/ 2, /*BUSY=*/ 1)); GxEPD2_3C<GxEPD2_290c, MAX_HEIGHT_3C(GxEPD2_290c)>
// display(GxEPD2_290c(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1));
// GxEPD2_3C<GxEPD2_270c, MAX_HEIGHT_3C(GxEPD2_270c)>
// display(GxEPD2_270c(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1));
// GxEPD2_3C<GxEPD2_420c, MAX_HEIGHT_3C(GxEPD2_420c)>
// display(GxEPD2_420c(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1));
// GxEPD2_3C<GxEPD2_583c, MAX_HEIGHT_3C(GxEPD2_583c)>
// display(GxEPD2_583c(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1));
// GxEPD2_3C<GxEPD2_750c, MAX_HEIGHT_3C(GxEPD2_750c)>
// display(GxEPD2_750c(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1));
// GxEPD2_3C<GxEPD2_750c_Z08, MAX_HEIGHT_3C(GxEPD2_750c_Z08)>
// display(GxEPD2_750c_Z08(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEW075Z08 800x480 GxEPD2_3C<GxEPD2_750c_Z90, MAX_HEIGHT_3C(GxEPD2_750c_Z90)>
// display(GxEPD2_750c_Z90(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// GDEH075Z90 880x528
// 7-color e-paper
#define MAX_HEIGHT_7C(EPD)                                       \
    (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE) / (EPD::WIDTH / 2) \
         ? EPD::HEIGHT                                           \
         : (MAX_DISPLAY_BUFFER_SIZE) / (EPD::WIDTH / 2))  // 2 pixel per byte
// GxEPD2_7C<GxEPD2_565c, MAX_HEIGHT_7C(GxEPD2_565c)>
// display(GxEPD2_565c(/*CS=4*/ SS, /*DC=*/ 3, /*RST=*/ 2, /*BUSY=*/ 1)); //
// Waveshare 5.65" 7-color
#endif

#if defined(__AVR)
#if defined(ARDUINO_AVR_MEGA2560)
#define MAX_DISPLAY_BUFFER_SIZE 5000  // e.g. full height for 200x200
#else
#define MAX_DISPLAY_BUFFER_SIZE 800  //
#endif
#define MAX_HEIGHT(EPD)                                        \
    (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) \
         ? EPD::HEIGHT                                         \
         : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
// select one and adapt to your mapping
// GxEPD2_BW<GxEPD2_154, MAX_HEIGHT(GxEPD2_154)> display(GxEPD2_154(/*CS=10*/
// SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEP015OC1 no longer available
// GxEPD2_BW<GxEPD2_154_D67, MAX_HEIGHT(GxEPD2_154_D67)>
// display(GxEPD2_154_D67(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEH0154D67 GxEPD2_BW<GxEPD2_154_T8, MAX_HEIGHT(GxEPD2_154_T8)>
// display(GxEPD2_154_T8(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEW0154T8 152x152 GxEPD2_BW<GxEPD2_154_M09, MAX_HEIGHT(GxEPD2_154_M09)>
// display(GxEPD2_154_M09(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEW0154M09 200x200 GxEPD2_BW<GxEPD2_154_M10, MAX_HEIGHT(GxEPD2_154_M10)>
// display(GxEPD2_154_M10(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEW0154M10 152x152 GxEPD2_BW<GxEPD2_213, MAX_HEIGHT(GxEPD2_213)>
// display(GxEPD2_213(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDE0213B1, phased out GxEPD2_BW<GxEPD2_213_B72, MAX_HEIGHT(GxEPD2_213_B72)>
// display(GxEPD2_213_B72(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEH0213B72 GxEPD2_BW<GxEPD2_213_B73, MAX_HEIGHT(GxEPD2_213_B73)>
// display(GxEPD2_213_B73(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEH0213B73 GxEPD2_BW<GxEPD2_213_flex, MAX_HEIGHT(GxEPD2_213_flex)>
// display(GxEPD2_213_flex(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEW0213I5F GxEPD2_BW<GxEPD2_290, MAX_HEIGHT(GxEPD2_290)>
// display(GxEPD2_290(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
// GxEPD2_BW<GxEPD2_290_T5, MAX_HEIGHT(GxEPD2_290_T5)>
// display(GxEPD2_290_T5(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEW029T5 GxEPD2_BW<GxEPD2_260, MAX_HEIGHT(GxEPD2_260)>
// display(GxEPD2_260(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
// GxEPD2_BW<GxEPD2_270, MAX_HEIGHT(GxEPD2_270)> display(GxEPD2_270(/*CS=10*/
// SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); GxEPD2_BW<GxEPD2_371,
// MAX_HEIGHT(GxEPD2_371)> display(GxEPD2_371(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/
// 9, /*BUSY=*/ 7)); GxEPD2_BW<GxEPD2_420, MAX_HEIGHT(GxEPD2_420)>
// display(GxEPD2_420(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
// GxEPD2_BW<GxEPD2_583, MAX_HEIGHT(GxEPD2_583)> display(GxEPD2_583(/*CS=10*/
// SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); GxEPD2_BW <GxEPD2_583_T8,
// MAX_HEIGHT(GxEPD2_583_T8)> display(GxEPD2_583_T8(/*CS=10*/ SS, /*DC=*/ 8,
// /*RST=*/ 9, /*BUSY=*/ 7)); GxEPD2_BW<GxEPD2_750, MAX_HEIGHT(GxEPD2_750)>
// display(GxEPD2_750(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
// GxEPD2_BW<GxEPD2_750_T7, MAX_HEIGHT(GxEPD2_750_T7)>
// display(GxEPD2_750_T7(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEW075T7 800x480
// 3-color e-papers
#define MAX_HEIGHT_3C(EPD)                                           \
    (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) \
         ? EPD::HEIGHT                                               \
         : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))
// GxEPD2_3C<GxEPD2_154c, MAX_HEIGHT_3C(GxEPD2_154c)>
// display(GxEPD2_154c(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEW0154Z04 no longer available GxEPD2_3C<GxEPD2_154_Z90c,
// MAX_HEIGHT_3C(GxEPD2_154_Z90c)> display(GxEPD2_154_Z90c(/*CS=10*/ SS, /*DC=*/
// 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEH0154Z90 GxEPD2_3C<GxEPD2_213c,
// MAX_HEIGHT_3C(GxEPD2_213c)> display(GxEPD2_213c(/*CS=10*/ SS, /*DC=*/ 8,
// /*RST=*/ 9, /*BUSY=*/ 7)); GxEPD2_3C<GxEPD2_290c, MAX_HEIGHT_3C(GxEPD2_290c)>
// display(GxEPD2_290c(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
// GxEPD2_3C<GxEPD2_270c, MAX_HEIGHT_3C(GxEPD2_270c)>
// display(GxEPD2_270c(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
// GxEPD2_3C<GxEPD2_420c, MAX_HEIGHT_3C(GxEPD2_420c)>
// display(GxEPD2_420c(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
// GxEPD2_3C<GxEPD2_583c, MAX_HEIGHT_3C(GxEPD2_583c)>
// display(GxEPD2_583c(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
// GxEPD2_3C<GxEPD2_750c, MAX_HEIGHT_3C(GxEPD2_750c)>
// display(GxEPD2_750c(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
// GxEPD2_3C<GxEPD2_750c_Z08, MAX_HEIGHT_3C(GxEPD2_750c_Z08)>
// display(GxEPD2_750c_Z08(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEW075Z08 800x480 GxEPD2_3C<GxEPD2_750c_Z90, MAX_HEIGHT_3C(GxEPD2_750c_Z90)>
// display(GxEPD2_750c_Z90(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// GDEH075Z90 880x528
// 7-color e-paper
#define MAX_HEIGHT_7C(EPD)                                       \
    (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE) / (EPD::WIDTH / 2) \
         ? EPD::HEIGHT                                           \
         : (MAX_DISPLAY_BUFFER_SIZE) / (EPD::WIDTH / 2))  // 2 pixel per byte
// GxEPD2_7C<GxEPD2_565c, MAX_HEIGHT_7C(GxEPD2_565c)>
// display(GxEPD2_565c(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); //
// Waveshare 5.65" 7-color
#endif
#include <ArduinoJson.h>

#include "SmartConfigManager.h"
#include "config.h"
#include "esp_bt.h"
#include "esp_wifi.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/soc.h"
#include "soulapi.h"
#if defined(ESP32)
#include "SPIFFS.h"
#endif

#include <FS.h>
#define FileClass fs::File
#define EPD_CS SS

// 字体
#include "u8g2_font_pingfang.h"
#include "u8g2_mfxinran_92_number.h"

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
#include <ESPDateTime.h>

#include "ceep_english_word.h"

const char* WEEKDAY_CN[] = {"周日", "周一", "周二", "周三",
                            "周四", "周五", "周六"};
const char* WEEKDAY_EN[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                            "Thursday", "Friday", "Saturday"};
const char* MONTH_CN[] = {"一月", "二月", "三月", "四月", "五月", "六月",
                          "七月", "八月", "九月", "十月", "十一月", "十二月"};
const char* MONTH_EN[] = {"January", "February", "March", "April",
                          "May", "June", "July", "August",
                          "September", "October", "November", "December"};
const uint16_t SMARTCONFIG_QR_CODE_WIDTH = 120;
const uint16_t SMARTCONFIG_QR_CODE_HEIGHT = 120;

int16_t DISPLAY_WIDTH;
int16_t DISPLAY_HEIGHT;
u8_t pageIndex = 0;

// soul api
SoulAPI soulapi;

// api data
PsychologyDaily pd;
WordDaily wd;
Lunar lunar;

static const uint16_t input_buffer_pixels = 800;  // may affect performance

static const uint16_t max_row_width = 800;       // for up to 7.5" display 800x480
static const uint16_t max_palette_pixels = 256;  // for depth <= 8

uint8_t input_buffer[3 * input_buffer_pixels];  // up to depth 24
uint8_t output_row_mono_buffer[max_row_width /
                               8];                   // buffer for at least one row of b/w bits
uint8_t output_row_color_buffer[max_row_width / 8];  // buffer for at least one
                                                     // row of color bits
uint8_t mono_palette_buffer[max_palette_pixels /
                            8];  // palette buffer for depth <= 8 b/w
uint8_t color_palette_buffer[max_palette_pixels /
                             8];                  // palette buffer for depth <= 8 c/w
uint16_t rgb_palette_buffer[max_palette_pixels];  // palette buffer for depth <=
                                                  // 8 for buffered graphics,
                                                  // needed for 7-color display

// 根据
// https://randomnerdtutorials.com/esp32-deep-sleep-arduino-ide-wake-up-sources/
// 的评论中所描述，
// 在偶然的电源消耗问题造成的重启过程中，可能会导致数据丢失。所以他用了RTC_NOINIT_ATTR
// 代替了 RTC_DATA_ATTR
RTC_NOINIT_ATTR u8_t LASTPAGE = -1;
RTC_DATA_ATTR int bootCount = 0;

#define uS_TO_S_FACTOR \
    1000000                   /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 60 * 60 /* Time ESP32 will go to sleep (in seconds) */

// 唤醒原因
void print_wakeup_reason() {
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason) {
        case ESP_SLEEP_WAKEUP_EXT0:
            Serial.println("Wakeup caused by external signal using RTC_IO");
            break;
        case ESP_SLEEP_WAKEUP_EXT1:
            Serial.println("Wakeup caused by external signal using RTC_CNTL");
            break;
        case ESP_SLEEP_WAKEUP_TIMER:
            Serial.println("Wakeup caused by timer");
            break;
        case ESP_SLEEP_WAKEUP_TOUCHPAD:
            Serial.println("Wakeup caused by touchpad");
            break;
        case ESP_SLEEP_WAKEUP_ULP:
            Serial.println("Wakeup caused by ULP program");
            break;
        default:
            Serial.printf("Wakeup was not caused by deep sleep: %d\n",
                          wakeup_reason);
            break;
    }
}

uint16_t read16(fs::File& f) {
    // BMP data is stored little-endian, same as Arduino.
    uint16_t result;
    ((uint8_t*)&result)[0] = f.read();  // LSB
    ((uint8_t*)&result)[1] = f.read();  // MSB
    return result;
}

uint32_t read32(fs::File& f) {
    // BMP data is stored little-endian, same as Arduino.
    uint32_t result;
    ((uint8_t*)&result)[0] = f.read();  // LSB
    ((uint8_t*)&result)[1] = f.read();
    ((uint8_t*)&result)[2] = f.read();
    ((uint8_t*)&result)[3] = f.read();  // MSB
    return result;
}

void setupDateTime() {
    DateTime.setTimeZone(8);
    DateTime.begin(/* timeout param */);
    if (!DateTime.isTimeValid()) {
        Serial.println("Failed to get time from server.");
    }
}

void drawBitmapFromSpiffs_Buffered(const char* filename,
                                   int16_t x,
                                   int16_t y,
                                   bool with_color,
                                   bool partial_update,
                                   bool overwrite) {
    fs::File file;
    bool valid = false;  // valid format to be handled
    bool flip = true;    // bitmap is stored bottom-to-top
    bool has_multicolors = display.epd2.panel == GxEPD2::ACeP565;
    uint32_t startTime = millis();
    if ((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT))
        return;
    Serial.println();
    Serial.print("Loading image '");
    Serial.print(filename);
    Serial.println('\'');
#if defined(ESP32)
    file = SPIFFS.open(String("/") + filename, "r");
#else
    file = SPIFFS.open(filename, "r");
#endif
    if (!file) {
        Serial.print("File not found");
        return;
    }
    // Parse BMP header
    if (read16(file) == 0x4D42)  // BMP signature
    {
        uint32_t fileSize = read32(file);
        uint32_t creatorBytes = read32(file);
        uint32_t imageOffset = read32(file);  // Start of image data
        uint32_t headerSize = read32(file);
        uint32_t width = read32(file);
        uint32_t height = read32(file);
        uint16_t planes = read16(file);
        uint16_t depth = read16(file);  // bits per pixel
        uint32_t format = read32(file);
        if ((planes == 1) &&
            ((format == 0) ||
             (format == 3)))  // uncompressed is handled, 565 also
        {
            Serial.print("File size: ");
            Serial.println(fileSize);
            Serial.print("Image Offset: ");
            Serial.println(imageOffset);
            Serial.print("Header size: ");
            Serial.println(headerSize);
            Serial.print("Bit Depth: ");
            Serial.println(depth);
            Serial.print("Image size: ");
            Serial.print(width);
            Serial.print('x');
            Serial.println(height);
            // BMP rows are padded (if needed) to 4-byte boundary
            uint32_t rowSize = (width * depth / 8 + 3) & ~3;
            if (depth < 8)
                rowSize = ((width * depth + 8 - depth) / 8 + 3) & ~3;
            if (height < 0) {
                height = -height;
                flip = false;
            }
            uint16_t w = width;
            uint16_t h = height;
            if ((x + w - 1) >= DISPLAY_WIDTH)
                w = DISPLAY_WIDTH - x;
            if ((y + h - 1) >= DISPLAY_HEIGHT)
                h = DISPLAY_HEIGHT - y;
            // if (w <= max_row_width) // handle with direct drawing
            {
                valid = true;
                uint8_t bitmask = 0xFF;
                uint8_t bitshift = 8 - depth;
                uint16_t red, green, blue;
                bool whitish, colored;
                if (depth == 1)
                    with_color = false;
                if (depth <= 8) {
                    if (depth < 8)
                        bitmask >>= depth;
                    // file.seek(54); //palette is always @ 54
                    file.seek(imageOffset -
                              (4 << depth));  // 54 for regular, diff for
                                              // colorsimportant
                    for (uint16_t pn = 0; pn < (1 << depth); pn++) {
                        blue = file.read();
                        green = file.read();
                        red = file.read();
                        file.read();
                        whitish =
                            with_color
                                ? ((red > 0x80) && (green > 0x80) &&
                                   (blue > 0x80))
                                : ((red + green + blue) > 3 * 0x80);  // whitish
                        colored = (red > 0xF0) ||
                                  ((green > 0xF0) &&
                                   (blue > 0xF0));  // reddish or yellowish?
                        if (0 == pn % 8)
                            mono_palette_buffer[pn / 8] = 0;
                        mono_palette_buffer[pn / 8] |= whitish << pn % 8;
                        if (0 == pn % 8)
                            color_palette_buffer[pn / 8] = 0;
                        color_palette_buffer[pn / 8] |= colored << pn % 8;
                        rgb_palette_buffer[pn] = ((red & 0xF8) << 8) |
                                                 ((green & 0xFC) << 3) |
                                                 ((blue & 0xF8) >> 3);
                    }
                }
                if (partial_update)
                    display.setPartialWindow(x, y, w, h);
                else
                    display.setFullWindow();
                display.firstPage();
                do {
                    if (!overwrite)
                        display.fillScreen(GxEPD_WHITE);
                    uint32_t rowPosition =
                        flip ? imageOffset + (height - h) * rowSize
                             : imageOffset;
                    for (uint16_t row = 0; row < h;
                         row++, rowPosition += rowSize)  // for each line
                    {
                        uint32_t in_remain = rowSize;
                        uint32_t in_idx = 0;
                        uint32_t in_bytes = 0;
                        uint8_t in_byte = 0;  // for depth <= 8
                        uint8_t in_bits = 0;  // for depth <= 8
                        uint16_t color = GxEPD_WHITE;
                        file.seek(rowPosition);
                        for (uint16_t col = 0; col < w;
                             col++)  // for each pixel
                        {
                            // Time to read more pixel data?
                            if (in_idx >=
                                in_bytes)  // ok, exact match for 24bit also
                                           // (size IS multiple of 3)
                            {
                                in_bytes =
                                    file.read(input_buffer,
                                              in_remain > sizeof(input_buffer)
                                                  ? sizeof(input_buffer)
                                                  : in_remain);
                                in_remain -= in_bytes;
                                in_idx = 0;
                            }
                            switch (depth) {
                                case 24:
                                    blue = input_buffer[in_idx++];
                                    green = input_buffer[in_idx++];
                                    red = input_buffer[in_idx++];
                                    whitish =
                                        with_color
                                            ? ((red > 0x80) && (green > 0x80) &&
                                               (blue > 0x80))
                                            : ((red + green + blue) >
                                               3 * 0x80);  // whitish
                                    colored =
                                        (red > 0xF0) ||
                                        ((green > 0xF0) &&
                                         (blue >
                                          0xF0));  // reddish or yellowish?
                                    color = ((red & 0xF8) << 8) |
                                            ((green & 0xFC) << 3) |
                                            ((blue & 0xF8) >> 3);
                                    break;
                                case 16: {
                                    uint8_t lsb = input_buffer[in_idx++];
                                    uint8_t msb = input_buffer[in_idx++];
                                    if (format == 0)  // 555
                                    {
                                        blue = (lsb & 0x1F) << 3;
                                        green = ((msb & 0x03) << 6) |
                                                ((lsb & 0xE0) >> 2);
                                        red = (msb & 0x7C) << 1;
                                        color = ((red & 0xF8) << 8) |
                                                ((green & 0xFC) << 3) |
                                                ((blue & 0xF8) >> 3);
                                    } else  // 565
                                    {
                                        blue = (lsb & 0x1F) << 3;
                                        green = ((msb & 0x07) << 5) |
                                                ((lsb & 0xE0) >> 3);
                                        red = (msb & 0xF8);
                                        color = (msb << 8) | lsb;
                                    }
                                    whitish =
                                        with_color
                                            ? ((red > 0x80) && (green > 0x80) &&
                                               (blue > 0x80))
                                            : ((red + green + blue) >
                                               3 * 0x80);  // whitish
                                    colored =
                                        (red > 0xF0) ||
                                        ((green > 0xF0) &&
                                         (blue >
                                          0xF0));  // reddish or yellowish?
                                } break;
                                case 1:
                                case 4:
                                case 8: {
                                    if (0 == in_bits) {
                                        in_byte = input_buffer[in_idx++];
                                        in_bits = 8;
                                    }
                                    uint16_t pn =
                                        (in_byte >> bitshift) & bitmask;
                                    whitish = mono_palette_buffer[pn / 8] &
                                              (0x1 << pn % 8);
                                    colored = color_palette_buffer[pn / 8] &
                                              (0x1 << pn % 8);
                                    in_byte <<= depth;
                                    in_bits -= depth;
                                    color = rgb_palette_buffer[pn];
                                } break;
                            }
                            if (with_color && has_multicolors) {
                                // keep color
                            } else if (whitish) {
                                color = GxEPD_WHITE;
                            } else if (colored && with_color) {
                                color = GxEPD_COLORED;
                            } else {
                                color = GxEPD_BLACK;
                            }
                            uint16_t yrow = y + (flip ? h - row - 1 : row);
                            display.drawPixel(x + col, yrow, color);
                        }  // end pixel
                    }      // end line
                } while (display.nextPage());
                Serial.print("loaded in ");
                Serial.print(millis() - startTime);
                Serial.println(" ms");
            }
        }
    }
    file.close();
    if (!valid) {
        Serial.println("bitmap format not handled.");
    }
}

void DrawMultiLineString(string content,
                         uint16_t x,
                         uint16_t y,
                         uint16_t contentAreaWidthWithMargin,
                         uint16_t lineHeight) {
    string ch;
    vector<string> contentArray;
    for (size_t i = 0, len = 0; i != content.length(); i += len) {
        unsigned char byte = (unsigned)content[i];
        if (byte >= 0xFC)
            len = 6;
        else if (byte >= 0xF8)
            len = 5;
        else if (byte >= 0xF0)
            len = 4;
        else if (byte >= 0xE0)
            len = 3;
        else if (byte >= 0xC0)
            len = 2;
        else
            len = 1;
        ch = content.substr(i, len);
        contentArray.push_back(ch);
    }

    string outputContent;
    for (size_t j = 0; j < contentArray.size(); j++) {
        outputContent += contentArray[j];
        int16_t wTemp = u8g2Fonts.getUTF8Width(outputContent.c_str());
        if (wTemp >= contentAreaWidthWithMargin ||
            j == (contentArray.size() - 1)) {
            u8g2Fonts.drawUTF8(x, y, outputContent.c_str());
            y += lineHeight;
            outputContent = "";
        }
    }
}

void ShowWiFiSmartConfig() {
    display.clearScreen(GxEPD_WHITE);

    const uint16_t x = (DISPLAY_WIDTH - SMARTCONFIG_QR_CODE_WIDTH) / 2;
    const uint16_t y = (DISPLAY_HEIGHT - SMARTCONFIG_QR_CODE_HEIGHT) / 2;

    u8g2Fonts.setFont(u8g2_font_pingfang_regular_18pt);
    uint16_t tipsY = y + SMARTCONFIG_QR_CODE_HEIGHT + 40;

    display.firstPage();
    do {
        DrawMultiLineString(
            "请用微信扫描上方的二维码或使用 ESPTouch 配置网络。", 90, tipsY,
            300, 30);
    } while (display.nextPage());
    drawBitmapFromSpiffs_Buffered("smartconfig.bmp", x, y, false, true, false);
}

// enum PageContent : u8_t { CALENDAR = 0,
//                           WEATHER = 1 };

// 头部横线
void ShowHeaderLine() {
    // draw a line
    display.drawLine(28, 28, DISPLAY_WIDTH - 28, 28, 0);
}

// 头部日期
void ShowLunarAndDate() {
    // 日期
    u8g2Fonts.setFont(u8g2_font_pingfang_heavy_20pt);
    time_t t = DateTime.now();
    int16_t tWidth = u8g2Fonts.getUTF8Width(DateFormatter::format("%m.%d", t).c_str());
    u8g2Fonts.drawUTF8(28, 34 + 28, DateFormatter::format("%m.%d", t).c_str());

    // 星期
    u8g2Fonts.setFont(u8g2_font_pingfang_regular_9pt);

    u8g2Fonts.drawUTF8(32 + tWidth, 34 + 18,
                       WEEKDAY_CN[DateTime.getParts().getWeekDay()]);

    // 竖线
    display.drawLine(287, 34, 287, 64, 0);

    // 农历 1
    String lunarLine1 = "农历";
    lunarLine1.concat(" ");
    lunarLine1.concat(lunar.date);
    u8g2Fonts.setFont(u8g2_font_pingfang_regular_12pt);
    int16_t lunarLine1Width = u8g2Fonts.getUTF8Width(lunarLine1.c_str());
    u8g2Fonts.drawUTF8(DISPLAY_WIDTH - lunarLine1Width - 28, 34 + 10,
                       lunarLine1.c_str());

    // 农历 2
    String lunarLine2 = lunar.ganzhi_year;
    lunarLine2.concat(" ");
    lunarLine2.concat(lunar.ganzhi_month);
    lunarLine2.concat("月");
    lunarLine2.concat(" ");
    lunarLine2.concat(lunar.ganzhi_day);
    lunarLine2.concat("日");
    u8g2Fonts.setFont(u8g2_font_pingfang_regular_12pt);

    int16_t lunarLine2Width = u8g2Fonts.getUTF8Width(lunarLine2.c_str());
    u8g2Fonts.drawUTF8((DISPLAY_WIDTH - lunarLine2Width - 28),
                       36 + 28, lunarLine2.c_str());
}

// 外边框
void ShowBorder() {
    display.fillRect(28, 70, DISPLAY_WIDTH - 28 * 2, 548, 0);
    display.fillRect(28 + 2, 70 + 2, DISPLAY_WIDTH - 28 * 2 - 4, 548 - 4, 1);
}
// 判断是不是闰年
bool isLeap(int year) {
    return (!(year % 4) && (year % 100)) || !(year % 400);
    //(1) 被4整除且不被100整除 或
    //(2) 被400整除
}

// 当前时间(几号)
void ShowCurrentMonthDay() {
    int monthDay = DateTime.getParts().getMonthDay();
    String dateInCenter = String(monthDay);

    // 每月的几号
    u8g2Fonts.setFont(u8g2_mfxinran_92_number);
    int16_t dateWidth = u8g2Fonts.getUTF8Width(dateInCenter.c_str());
    u8g2Fonts.drawUTF8((DISPLAY_WIDTH - dateWidth) / 2, DISPLAY_HEIGHT / 3 + 42,
                       dateInCenter.c_str());
    // 月份
    // u8g2Fonts.setFont(u8g2_mfyuehei_14_gb2312);
    // int16_t monthWidth = u8g2Fonts.getUTF8Width(MONTH_CN[m]);
    // u8g2Fonts.drawUTF8((DISPLAY_WIDTH - monthWidth) / 2, 340, MONTH_CN[m]);
}

// 这个月剩余几天
void ShowLeftoverDay() {
    int monthDay = DateTime.getParts().getMonthDay();
    int m = DateTime.getParts().getMonth() + 1;

    u8g2Fonts.setFont(u8g2_font_pingfang_regular_12pt);
    int leftoverDay = 0;
    int currentYear = DateTime.getParts().getYear();
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
        leftoverDay = 31 - monthDay;
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        leftoverDay = 30 - monthDay;
    } else if (m == 2) {
        if (isLeap(currentYear)) {
            leftoverDay = 29 - monthDay;
        } else {
            leftoverDay = 28 - monthDay;
        }
    }
    Serial.printf("year:%s, month: %s, days: %s, leftover: %sdays\n",
                  String(currentYear), String(m), String(monthDay),
                  String(leftoverDay));
    String leftover = "这个月剩余 ";
    leftover.concat(String(leftoverDay));
    leftover.concat(" 天");
    int16_t leftoverWidth = u8g2Fonts.getUTF8Width(leftover.c_str());
    u8g2Fonts.drawUTF8((DISPLAY_WIDTH - leftoverWidth) / 2,
                       DISPLAY_HEIGHT / 3 + 42 + 28, leftover.c_str());
}

// 随机考研英语单词展示
void ShowRandomEnglishWord() {
    string word = wd.origin + " " + wd.translation;
    u8g2Fonts.setFont(u8g2_font_pingfang_regular_18pt);
    // todo: maybe just need one line
    int16_t wordWidth = u8g2Fonts.getUTF8Width(word.c_str());
    DrawMultiLineString(word, (DISPLAY_WIDTH - wordWidth) / 2, 332 + 42,
                        DISPLAY_WIDTH - 28 * 2, 36);
}

// 横线
void ShowHLine() {
    display.drawLine(58, 426, DISPLAY_WIDTH - 28 * 2, 426, 0);
}
void ShowHLine2() {
    display.drawLine(58, 590, DISPLAY_WIDTH - 28 * 2, 590, 0);
}
// 考研心理学知识点展示
void ShowPsychology() {
    u8g2Fonts.setFont(u8g2_font_pingfang_regular_12pt);

    string psy = pd.knowledge;

    int16_t psyWidth = u8g2Fonts.getUTF8Width(psy.c_str());
    //  todo: 居中显示
    DrawMultiLineString(psy, 60 + 12, 436 + 8, 300 + 12, 24);
}

// 心理学分类
void ShowPsychologyType() {
    u8g2Fonts.setFont(u8g2_font_pingfang_regular_12pt);
    String pd_classify = "《" + pd.classify + "》";
    u8g2Fonts.drawUTF8(56, 596 + 12, pd_classify.c_str());
}
// logo
void ShowLogo() {
    u8g2Fonts.setFont(u8g2_font_pingfang_heavy_14pt);
    String pt = "Soul";
    int16_t ptWidth = u8g2Fonts.getUTF8Width(pt.c_str());
    u8g2Fonts.drawUTF8(DISPLAY_WIDTH - ptWidth - 56, 590 + 12, pt.c_str());

    u8g2Fonts.setFont(u8g2_font_pingfang_regular_9pt);
    String gift = "a gift for lan";
    int16_t giftWidth = u8g2Fonts.getUTF8Width(gift.c_str());
    u8g2Fonts.drawUTF8(DISPLAY_WIDTH - giftWidth - 56, 604 + 12, gift.c_str());
}
// 最终展示界面
void ShowPage() {
    // 初始化

    // 获取当天心理学知识点
    pd = soulapi.GetPsychologyDaily();
    // 获取当天单词
    wd = soulapi.GetWordDaily();
    // 获取农历
    lunar = soulapi.GetLunar();

    display.setFullWindow();
    display.clearScreen(GxEPD_WHITE);
    display.setRotation(3);

    u8g2Fonts.setFontMode(1);                   // use u8g2 transparent mode (this is default)
    u8g2Fonts.setFontDirection(0);              // left to right (this is default)
    u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
    u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color

    // 暂时用不到图片
    // String iconFileSmall = "32/";
    // iconFileSmall.concat(cw.icon);
    // iconFileSmall.concat(".bmp");
    // String iconFileBig = "64/";
    // iconFileBig.concat(cw.icon);
    // iconFileBig.concat(".bmp");
    /**
     * @brief 先写文字
     *
     */
    display.firstPage();
    do {
        /**
         * @brief 头部都用一样的吧
         *
         */
        ShowBorder();
        ShowHeaderLine();

        ShowLunarAndDate();
        // 几号
        ShowCurrentMonthDay();
        // 剩余几天
        ShowLeftoverDay();
        // 考研英语单词
        ShowRandomEnglishWord();

        ShowHLine();
        // 心理学内容
        ShowPsychology();
        ShowHLine2();
        ShowHLine();
        // 哪本书的
        ShowPsychologyType();
        // logo
        ShowLogo();

    } while (display.nextPage());

    /**
     * @brief
     * 貌似没法让u8g2和平共处，所以只能先输出文字再输出需要显示的图片，导致整体刷新时间太长。
     *
     */
    // switch (pageContent)
    // {
    // case PageContent::CALENDAR:
    //   drawBitmapFromSpiffs_Buffered(iconFileSmall.c_str(), 48, DISPLAY_HEIGHT
    //   - 48, false, true, false); break;
    // case PageContent::WEATHER:
    //   drawBitmapFromSpiffs_Buffered(iconFileSmall.c_str(), 48, DISPLAY_HEIGHT
    //   - 48, false, true, false);
    //   drawBitmapFromSpiffs_Buffered(iconFileBig.c_str(), 88, 140, false,
    //   true, false); break;
    // }
}

// arduino 初始化
void setup() {
    // 🐞fix: Brownout detector was triggered
    // 关闭brownout detector
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    //Increment boot number and print it every reboot
    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
    // 输出唤醒原因
    print_wakeup_reason();

    String logo;
    logo.concat("   _____             _ \n");
    logo.concat("  / ____|           | |\n");
    logo.concat(" | (___   ___  _   _| |\n");
    logo.concat("  \\___ \\ / _ \\| | | | |\n");
    logo.concat("  ____) | (_) | |_| | |\n");
    logo.concat(" |_____/ \\___/ \\__,_|_|\n");
    Serial.println(logo);
    Serial.println("----A gift for lan");

    Serial.println("Soul setup:");

    // 定时唤醒
    // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    // 设置唤醒时间为 1hour
    // bugs：使用 TIME_TO_SLEEP * uS_TO_S_FACTOR 会不断重启，待解决
    esp_sleep_enable_timer_wakeup(3600000000);

    Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                   " Seconds");

    // SPI
    SPI.end();
    SPI.begin(13, 12, 14, 15);

    // Initialise SPIFFS
    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS initialisation failed!");
        while (1)
            yield();  // Stay here twiddling thumbs waiting
    }
    Serial.println("\r\nSPIFFS Initialisation done.");

    display.init();
    display.setRotation(3);
    DISPLAY_WIDTH = display.width();
    DISPLAY_HEIGHT = display.height();

    // 字体 display 初始化
    u8g2Fonts.begin(display);                   // connect u8g2 procedures to Adafruit GFX
    u8g2Fonts.setFontMode(1);                   // use u8g2 transparent mode (this is default)
    u8g2Fonts.setFontDirection(0);              // left to right (this is default)
    u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
    u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color

    // init wifi
    SmartConfigManager scm;
    scm.initWiFi(ShowWiFiSmartConfig);

    // soul api init config
    soulapi.Config(SOULAPI_TOKEN);

    // 获取 ip location
    // MyIP myIP(Language::CHINESE);
    // Serial.printf("IP: %s\n", myIP.IP.c_str());
    // Serial.printf("City: %s\n", myIP.City.c_str());

    // gi = qwAPI.GetGeoInfo(myIP.City, myIP.Province);
    // Serial.printf("从和风天气中取到匹配城市: %s\n", gi.name.c_str());

    setupDateTime();

    // 内容展示
    // ++LASTPAGE;
    // if (LASTPAGE > PageContent::WEATHER)
    //     LASTPAGE = PageContent::CALENDAR;

    ShowPage();

    Serial.println("-------  SETUP FINISHED  -----------");
    Serial.println("zzzzzZZZZZZZ~~ ~~ ~~");
    delay(1000);
    Serial.flush();

    /**
     * @brief 关掉蓝牙和WiFi,进入Deep sleep模式
     *
     */
    esp_bt_controller_disable();

    esp_wifi_stop();

    esp_deep_sleep_start();
}

void loop() {}
