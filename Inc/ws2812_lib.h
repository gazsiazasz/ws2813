//
// Created by Gajdos Gábor on 2019. 10. 31..
//

#ifndef NEOPIXEL_WS2812_LIB_H
#define NEOPIXEL_WS2812_LIB_H

#include "stm32l4xx_hal.h"

#define WS2812_FREQ         800000        // it is fixed: WS2812 require 800kHz
#define TIMER_CLOCK_FREQ    80000000      // can be modified - multiples of 0.8MHz are suggested
#define TIMER_PERIOD        ((TIMER_CLOCK_FREQ / WS2812_FREQ) - 1)
#define LED_NUMBER          240            // how many LEDs the MCU should control?
#define LED_DATA_SIZE       (LED_NUMBER * 24)
#define RESET_SLOT          170
#define LED_BUFFER_SIZE     (RESET_SLOT + LED_DATA_SIZE)
#define WS2812_0            (TIMER_PERIOD / 3)       // WS2812's zero high time is long about one third of the period
#define WS2812_1            ((TIMER_PERIOD / 3) * 2) // WS2812's one high time is long about two thirds of the period
#define WS2812_RESET        0

typedef struct rgb {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_t;

typedef struct hsv {
    uint16_t h;
    uint8_t s;
    uint8_t v;
} hsv_t;

void ws2812_init();
void set_led_color(size_t led, rgb_t color);
void set_all_led_to(rgb_t color);

rgb_t hsv2rgb(hsv_t hsv);

#endif // NEOPIXEL_WS2812_LIB_H
