//
// Created by Gajdos Gábor on 2019. 10. 31..
//
#include "stm32l4xx_hal.h"
#include "ws2812_lib.h"

extern TIM_HandleTypeDef htim2;

static uint8_t LED_BUFFER[LED_BUFFER_SIZE] = {0};


void ws2812_init() {
  HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_3, (uint32_t *)LED_BUFFER, LED_BUFFER_SIZE);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
  HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_3, (uint32_t *)LED_BUFFER, LED_BUFFER_SIZE);
}

void set_led_color(size_t led, rgb_t color) {
  size_t led_index = led % LED_NUMBER;

  for (size_t i = 0; i < 8; i++) {
      LED_BUFFER[RESET_SLOT + led_index * 24 + i] = ((color.g << i) & 0x80u) ? WS2812_1 : WS2812_0;
      LED_BUFFER[RESET_SLOT + led_index * 24 + i + 8] = ((color.r << i) & 0x80u) ? WS2812_1 : WS2812_0;
      LED_BUFFER[RESET_SLOT + led_index * 24 + i + 16] = ((color.b << i) & 0x80u) ? WS2812_1 : WS2812_0;
  }
}

void set_all_led_to(rgb_t color) {
  for (size_t i = 0; i < LED_NUMBER; i++)
    set_led_color(i, color);
}

void clear_buffer(void) {
  for(size_t i = 0; i < LED_BUFFER_SIZE; i++)
      LED_BUFFER[i] = 0;
}

rgb_t hsv2rgb(hsv_t hsv) {
    uint16_t index = hsv.h;
    uint8_t sat = hsv.s;
    uint8_t bright = hsv.v;

    uint16_t r_temp, g_temp, b_temp;
    uint8_t index_mod;
    uint8_t inverse_sat = (sat ^ 255u);

    index = index % 768;
    index_mod = index % 256;

    if (index < 256) {
        r_temp = index_mod ^ 255u;
        g_temp = index_mod;
        b_temp = 0;
    } else if (index < 512) {
        r_temp = 0;
        g_temp = index_mod ^ 255u;
        b_temp = index_mod;
    } else if ( index < 768) {
        r_temp = index_mod;
        g_temp = 0;
        b_temp = index_mod ^ 255u;
    } else {
        r_temp = 0;
        g_temp = 0;
        b_temp = 0;
    }

    r_temp = ((r_temp * sat) / 255) + inverse_sat;
    g_temp = ((g_temp * sat) / 255) + inverse_sat;
    b_temp = ((b_temp * sat) / 255) + inverse_sat;

    r_temp = (r_temp * bright) / 255;
    g_temp = (g_temp * bright) / 255;
    b_temp = (b_temp * bright) / 255;

    return (rgb_t){r_temp, g_temp, b_temp};
}
