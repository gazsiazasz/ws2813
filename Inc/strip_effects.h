//
// Created by Gajdos Gábor on 2019. 10. 29..
//

#ifndef WS2813_STRIP_EFFECTS_H
#define WS2813_STRIP_EFFECTS_H

#include "main.h"

#define HEARTBEAT_STEPS 16

void stripEffect_CircularRing(uint32_t interval, rgb_t color);
void stripEffect_HeartBeat(uint32_t interval, rgb_t color);
void stripEffect_ColorWheel(uint32_t interval);
void stripEffect_AllColors(uint32_t interval);
void stripEffect_PatternMove(uint32_t interval, uint32_t parts, rgb_t color);
void stripEffect_FullEmpty(uint32_t interval, rgb_t color);
void stripEffect_FromTo(uint32_t interval, uint32_t steps, uint8_t r_A, uint8_t g_A, uint8_t b_A, uint8_t r_B, uint8_t g_B, uint8_t b_B);
void stripEffect_AlternateColors(uint32_t interval, uint32_t steps, uint8_t r_A, uint8_t g_A, uint8_t b_A, uint8_t r_B, uint8_t g_B, uint8_t b_B);
void stripEffect_Rainbow(uint32_t interval);

#endif // WS2813_STRIP_EFFECTS_H
