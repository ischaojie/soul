#ifndef _U8G2_WQY_H
#define _U8G2_WQY_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef U8G2_USE_LARGE_FONTS
#define U8G2_USE_LARGE_FONTS
#endif

#ifndef U8X8_FONT_SECTION

#ifdef __GNUC__
#  define U8X8_SECTION(name) __attribute__ ((section (name)))
#else
#  define U8X8_SECTION(name)
#endif

#if defined(__GNUC__) && defined(__AVR__)
#  define U8X8_FONT_SECTION(name) U8X8_SECTION(".progmem." name)
#endif

#if defined(ESP8266)
#  define U8X8_FONT_SECTION(name) __attribute__((section(".text." name)))
#endif

#ifndef U8X8_FONT_SECTION
#  define U8X8_FONT_SECTION(name) 
#endif

#endif

#ifndef U8G2_FONT_SECTION
#define U8G2_FONT_SECTION(name) U8X8_FONT_SECTION(name) 
#endif
extern const uint8_t u8g2_font_dqhtjw3_9pt[] U8G2_FONT_SECTION(u8g2_font_dqhtjw3_9pt);
extern const uint8_t u8g2_font_dqhtjw3_12pt[] U8G2_FONT_SECTION(u8g2_font_dqhtjw3_12pt);
extern const uint8_t u8g2_font_dqhtjw3_14pt[] U8G2_FONT_SECTION(u8g2_font_dqhtjw3_14pt);
extern const uint8_t u8g2_font_dqhtjw3_16pt[] U8G2_FONT_SECTION(u8g2_font_dqhtjw3_16pt);
extern const uint8_t u8g2_font_dqhtjw3_18pt[] U8G2_FONT_SECTION(u8g2_font_dqhtjw3_18pt);
extern const uint8_t u8g2_font_dqhtjw6_20pt[] U8G2_FONT_SECTION(u8g2_font_dqhtjw6_20pt);
extern const uint8_t u8g2_font_dqhtjw6_90pt[] U8G2_FONT_SECTION(u8g2_font_dqhtjw6_90pt);
"#ifdef __cplusplus
}
#endif

#endif"