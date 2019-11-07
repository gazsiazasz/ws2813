//
// Created by Gajdos Gábor on 2019. 10. 29..
//

#include "strip_effects.h"
#include "ws2812_lib.h"

/* this array holds the RGB values to represent
 * a color wheel using 256 steps on each emitter
 * 256^3 = 16777216 colors
 * It was taken from http://eliaselectronics.com/
 */
rgb_t all_colors[766] = {
    {255, 0, 0},   {254, 1, 0},   {253, 2, 0},   {252, 3, 0},   {251, 4, 0},   {250, 5, 0},   {249, 6, 0},
    {248, 7, 0},   {247, 8, 0},   {246, 9, 0},   {245, 10, 0},  {244, 11, 0},  {243, 12, 0},  {242, 13, 0},
    {241, 14, 0},  {240, 15, 0},  {239, 16, 0},  {238, 17, 0},  {237, 18, 0},  {236, 19, 0},  {235, 20, 0},
    {234, 21, 0},  {233, 22, 0},  {232, 23, 0},  {231, 24, 0},  {230, 25, 0},  {229, 26, 0},  {228, 27, 0},
    {227, 28, 0},  {226, 29, 0},  {225, 30, 0},  {224, 31, 0},  {223, 32, 0},  {222, 33, 0},  {221, 34, 0},
    {220, 35, 0},  {219, 36, 0},  {218, 37, 0},  {217, 38, 0},  {216, 39, 0},  {215, 40, 0},  {214, 41, 0},
    {213, 42, 0},  {212, 43, 0},  {211, 44, 0},  {210, 45, 0},  {209, 46, 0},  {208, 47, 0},  {207, 48, 0},
    {206, 49, 0},  {205, 50, 0},  {204, 51, 0},  {203, 52, 0},  {202, 53, 0},  {201, 54, 0},  {200, 55, 0},
    {199, 56, 0},  {198, 57, 0},  {197, 58, 0},  {196, 59, 0},  {195, 60, 0},  {194, 61, 0},  {193, 62, 0},
    {192, 63, 0},  {191, 64, 0},  {190, 65, 0},  {189, 66, 0},  {188, 67, 0},  {187, 68, 0},  {186, 69, 0},
    {185, 70, 0},  {184, 71, 0},  {183, 72, 0},  {182, 73, 0},  {181, 74, 0},  {180, 75, 0},  {179, 76, 0},
    {178, 77, 0},  {177, 78, 0},  {176, 79, 0},  {175, 80, 0},  {174, 81, 0},  {173, 82, 0},  {172, 83, 0},
    {171, 84, 0},  {170, 85, 0},  {169, 86, 0},  {168, 87, 0},  {167, 88, 0},  {166, 89, 0},  {165, 90, 0},
    {164, 91, 0},  {163, 92, 0},  {162, 93, 0},  {161, 94, 0},  {160, 95, 0},  {159, 96, 0},  {158, 97, 0},
    {157, 98, 0},  {156, 99, 0},  {155, 100, 0}, {154, 101, 0}, {153, 102, 0}, {152, 103, 0}, {151, 104, 0},
    {150, 105, 0}, {149, 106, 0}, {148, 107, 0}, {147, 108, 0}, {146, 109, 0}, {145, 110, 0}, {144, 111, 0},
    {143, 112, 0}, {142, 113, 0}, {141, 114, 0}, {140, 115, 0}, {139, 116, 0}, {138, 117, 0}, {137, 118, 0},
    {136, 119, 0}, {135, 120, 0}, {134, 121, 0}, {133, 122, 0}, {132, 123, 0}, {131, 124, 0}, {130, 125, 0},
    {129, 126, 0}, {128, 127, 0}, {127, 128, 0}, {126, 129, 0}, {125, 130, 0}, {124, 131, 0}, {123, 132, 0},
    {122, 133, 0}, {121, 134, 0}, {120, 135, 0}, {119, 136, 0}, {118, 137, 0}, {117, 138, 0}, {116, 139, 0},
    {115, 140, 0}, {114, 141, 0}, {113, 142, 0}, {112, 143, 0}, {111, 144, 0}, {110, 145, 0}, {109, 146, 0},
    {108, 147, 0}, {107, 148, 0}, {106, 149, 0}, {105, 150, 0}, {104, 151, 0}, {103, 152, 0}, {102, 153, 0},
    {101, 154, 0}, {100, 155, 0}, {99, 156, 0},  {98, 157, 0},  {97, 158, 0},  {96, 159, 0},  {95, 160, 0},
    {94, 161, 0},  {93, 162, 0},  {92, 163, 0},  {91, 164, 0},  {90, 165, 0},  {89, 166, 0},  {88, 167, 0},
    {87, 168, 0},  {86, 169, 0},  {85, 170, 0},  {84, 171, 0},  {83, 172, 0},  {82, 173, 0},  {81, 174, 0},
    {80, 175, 0},  {79, 176, 0},  {78, 177, 0},  {77, 178, 0},  {76, 179, 0},  {75, 180, 0},  {74, 181, 0},
    {73, 182, 0},  {72, 183, 0},  {71, 184, 0},  {70, 185, 0},  {69, 186, 0},  {68, 187, 0},  {67, 188, 0},
    {66, 189, 0},  {65, 190, 0},  {64, 191, 0},  {63, 192, 0},  {62, 193, 0},  {61, 194, 0},  {60, 195, 0},
    {59, 196, 0},  {58, 197, 0},  {57, 198, 0},  {56, 199, 0},  {55, 200, 0},  {54, 201, 0},  {53, 202, 0},
    {52, 203, 0},  {51, 204, 0},  {50, 205, 0},  {49, 206, 0},  {48, 207, 0},  {47, 208, 0},  {46, 209, 0},
    {45, 210, 0},  {44, 211, 0},  {43, 212, 0},  {42, 213, 0},  {41, 214, 0},  {40, 215, 0},  {39, 216, 0},
    {38, 217, 0},  {37, 218, 0},  {36, 219, 0},  {35, 220, 0},  {34, 221, 0},  {33, 222, 0},  {32, 223, 0},
    {31, 224, 0},  {30, 225, 0},  {29, 226, 0},  {28, 227, 0},  {27, 228, 0},  {26, 229, 0},  {25, 230, 0},
    {24, 231, 0},  {23, 232, 0},  {22, 233, 0},  {21, 234, 0},  {20, 235, 0},  {19, 236, 0},  {18, 237, 0},
    {17, 238, 0},  {16, 239, 0},  {15, 240, 0},  {14, 241, 0},  {13, 242, 0},  {12, 243, 0},  {11, 244, 0},
    {10, 245, 0},  {9, 246, 0},   {8, 247, 0},   {7, 248, 0},   {6, 249, 0},   {5, 250, 0},   {4, 251, 0},
    {3, 252, 0},   {2, 253, 0},   {1, 254, 0},   {0, 255, 0},   {0, 254, 1},   {0, 253, 2},   {0, 252, 3},
    {0, 251, 4},   {0, 250, 5},   {0, 249, 6},   {0, 248, 7},   {0, 247, 8},   {0, 246, 9},   {0, 245, 10},
    {0, 244, 11},  {0, 243, 12},  {0, 242, 13},  {0, 241, 14},  {0, 240, 15},  {0, 239, 16},  {0, 238, 17},
    {0, 237, 18},  {0, 236, 19},  {0, 235, 20},  {0, 234, 21},  {0, 233, 22},  {0, 232, 23},  {0, 231, 24},
    {0, 230, 25},  {0, 229, 26},  {0, 228, 27},  {0, 227, 28},  {0, 226, 29},  {0, 225, 30},  {0, 224, 31},
    {0, 223, 32},  {0, 222, 33},  {0, 221, 34},  {0, 220, 35},  {0, 219, 36},  {0, 218, 37},  {0, 217, 38},
    {0, 216, 39},  {0, 215, 40},  {0, 214, 41},  {0, 213, 42},  {0, 212, 43},  {0, 211, 44},  {0, 210, 45},
    {0, 209, 46},  {0, 208, 47},  {0, 207, 48},  {0, 206, 49},  {0, 205, 50},  {0, 204, 51},  {0, 203, 52},
    {0, 202, 53},  {0, 201, 54},  {0, 200, 55},  {0, 199, 56},  {0, 198, 57},  {0, 197, 58},  {0, 196, 59},
    {0, 195, 60},  {0, 194, 61},  {0, 193, 62},  {0, 192, 63},  {0, 191, 64},  {0, 190, 65},  {0, 189, 66},
    {0, 188, 67},  {0, 187, 68},  {0, 186, 69},  {0, 185, 70},  {0, 184, 71},  {0, 183, 72},  {0, 182, 73},
    {0, 181, 74},  {0, 180, 75},  {0, 179, 76},  {0, 178, 77},  {0, 177, 78},  {0, 176, 79},  {0, 175, 80},
    {0, 174, 81},  {0, 173, 82},  {0, 172, 83},  {0, 171, 84},  {0, 170, 85},  {0, 169, 86},  {0, 168, 87},
    {0, 167, 88},  {0, 166, 89},  {0, 165, 90},  {0, 164, 91},  {0, 163, 92},  {0, 162, 93},  {0, 161, 94},
    {0, 160, 95},  {0, 159, 96},  {0, 158, 97},  {0, 157, 98},  {0, 156, 99},  {0, 155, 100}, {0, 154, 101},
    {0, 153, 102}, {0, 152, 103}, {0, 151, 104}, {0, 150, 105}, {0, 149, 106}, {0, 148, 107}, {0, 147, 108},
    {0, 146, 109}, {0, 145, 110}, {0, 144, 111}, {0, 143, 112}, {0, 142, 113}, {0, 141, 114}, {0, 140, 115},
    {0, 139, 116}, {0, 138, 117}, {0, 137, 118}, {0, 136, 119}, {0, 135, 120}, {0, 134, 121}, {0, 133, 122},
    {0, 132, 123}, {0, 131, 124}, {0, 130, 125}, {0, 129, 126}, {0, 128, 127}, {0, 127, 128}, {0, 126, 129},
    {0, 125, 130}, {0, 124, 131}, {0, 123, 132}, {0, 122, 133}, {0, 121, 134}, {0, 120, 135}, {0, 119, 136},
    {0, 118, 137}, {0, 117, 138}, {0, 116, 139}, {0, 115, 140}, {0, 114, 141}, {0, 113, 142}, {0, 112, 143},
    {0, 111, 144}, {0, 110, 145}, {0, 109, 146}, {0, 108, 147}, {0, 107, 148}, {0, 106, 149}, {0, 105, 150},
    {0, 104, 151}, {0, 103, 152}, {0, 102, 153}, {0, 101, 154}, {0, 100, 155}, {0, 99, 156},  {0, 98, 157},
    {0, 97, 158},  {0, 96, 159},  {0, 95, 160},  {0, 94, 161},  {0, 93, 162},  {0, 92, 163},  {0, 91, 164},
    {0, 90, 165},  {0, 89, 166},  {0, 88, 167},  {0, 87, 168},  {0, 86, 169},  {0, 85, 170},  {0, 84, 171},
    {0, 83, 172},  {0, 82, 173},  {0, 81, 174},  {0, 80, 175},  {0, 79, 176},  {0, 78, 177},  {0, 77, 178},
    {0, 76, 179},  {0, 75, 180},  {0, 74, 181},  {0, 73, 182},  {0, 72, 183},  {0, 71, 184},  {0, 70, 185},
    {0, 69, 186},  {0, 68, 187},  {0, 67, 188},  {0, 66, 189},  {0, 65, 190},  {0, 64, 191},  {0, 63, 192},
    {0, 62, 193},  {0, 61, 194},  {0, 60, 195},  {0, 59, 196},  {0, 58, 197},  {0, 57, 198},  {0, 56, 199},
    {0, 55, 200},  {0, 54, 201},  {0, 53, 202},  {0, 52, 203},  {0, 51, 204},  {0, 50, 205},  {0, 49, 206},
    {0, 48, 207},  {0, 47, 208},  {0, 46, 209},  {0, 45, 210},  {0, 44, 211},  {0, 43, 212},  {0, 42, 213},
    {0, 41, 214},  {0, 40, 215},  {0, 39, 216},  {0, 38, 217},  {0, 37, 218},  {0, 36, 219},  {0, 35, 220},
    {0, 34, 221},  {0, 33, 222},  {0, 32, 223},  {0, 31, 224},  {0, 30, 225},  {0, 29, 226},  {0, 28, 227},
    {0, 27, 228},  {0, 26, 229},  {0, 25, 230},  {0, 24, 231},  {0, 23, 232},  {0, 22, 233},  {0, 21, 234},
    {0, 20, 235},  {0, 19, 236},  {0, 18, 237},  {0, 17, 238},  {0, 16, 239},  {0, 15, 240},  {0, 14, 241},
    {0, 13, 242},  {0, 12, 243},  {0, 11, 244},  {0, 10, 245},  {0, 9, 246},   {0, 8, 247},   {0, 7, 248},
    {0, 6, 249},   {0, 5, 250},   {0, 4, 251},   {0, 3, 252},   {0, 2, 253},   {0, 1, 254},   {0, 0, 255},
    {1, 0, 254},   {2, 0, 253},   {3, 0, 252},   {4, 0, 251},   {5, 0, 250},   {6, 0, 249},   {7, 0, 248},
    {8, 0, 247},   {9, 0, 246},   {10, 0, 245},  {11, 0, 244},  {12, 0, 243},  {13, 0, 242},  {14, 0, 241},
    {15, 0, 240},  {16, 0, 239},  {17, 0, 238},  {18, 0, 237},  {19, 0, 236},  {20, 0, 235},  {21, 0, 234},
    {22, 0, 233},  {23, 0, 232},  {24, 0, 231},  {25, 0, 230},  {26, 0, 229},  {27, 0, 228},  {28, 0, 227},
    {29, 0, 226},  {30, 0, 225},  {31, 0, 224},  {32, 0, 223},  {33, 0, 222},  {34, 0, 221},  {35, 0, 220},
    {36, 0, 219},  {37, 0, 218},  {38, 0, 217},  {39, 0, 216},  {40, 0, 215},  {41, 0, 214},  {42, 0, 213},
    {43, 0, 212},  {44, 0, 211},  {45, 0, 210},  {46, 0, 209},  {47, 0, 208},  {48, 0, 207},  {49, 0, 206},
    {50, 0, 205},  {51, 0, 204},  {52, 0, 203},  {53, 0, 202},  {54, 0, 201},  {55, 0, 200},  {56, 0, 199},
    {57, 0, 198},  {58, 0, 197},  {59, 0, 196},  {60, 0, 195},  {61, 0, 194},  {62, 0, 193},  {63, 0, 192},
    {64, 0, 191},  {65, 0, 190},  {66, 0, 189},  {67, 0, 188},  {68, 0, 187},  {69, 0, 186},  {70, 0, 185},
    {71, 0, 184},  {72, 0, 183},  {73, 0, 182},  {74, 0, 181},  {75, 0, 180},  {76, 0, 179},  {77, 0, 178},
    {78, 0, 177},  {79, 0, 176},  {80, 0, 175},  {81, 0, 174},  {82, 0, 173},  {83, 0, 172},  {84, 0, 171},
    {85, 0, 170},  {86, 0, 169},  {87, 0, 168},  {88, 0, 167},  {89, 0, 166},  {90, 0, 165},  {91, 0, 164},
    {92, 0, 163},  {93, 0, 162},  {94, 0, 161},  {95, 0, 160},  {96, 0, 159},  {97, 0, 158},  {98, 0, 157},
    {99, 0, 156},  {100, 0, 155}, {101, 0, 154}, {102, 0, 153}, {103, 0, 152}, {104, 0, 151}, {105, 0, 150},
    {106, 0, 149}, {107, 0, 148}, {108, 0, 147}, {109, 0, 146}, {110, 0, 145}, {111, 0, 144}, {112, 0, 143},
    {113, 0, 142}, {114, 0, 141}, {115, 0, 140}, {116, 0, 139}, {117, 0, 138}, {118, 0, 137}, {119, 0, 136},
    {120, 0, 135}, {121, 0, 134}, {122, 0, 133}, {123, 0, 132}, {124, 0, 131}, {125, 0, 130}, {126, 0, 129},
    {127, 0, 128}, {128, 0, 127}, {129, 0, 126}, {130, 0, 125}, {131, 0, 124}, {132, 0, 123}, {133, 0, 122},
    {134, 0, 121}, {135, 0, 120}, {136, 0, 119}, {137, 0, 118}, {138, 0, 117}, {139, 0, 116}, {140, 0, 115},
    {141, 0, 114}, {142, 0, 113}, {143, 0, 112}, {144, 0, 111}, {145, 0, 110}, {146, 0, 109}, {147, 0, 108},
    {148, 0, 107}, {149, 0, 106}, {150, 0, 105}, {151, 0, 104}, {152, 0, 103}, {153, 0, 102}, {154, 0, 101},
    {155, 0, 100}, {156, 0, 99},  {157, 0, 98},  {158, 0, 97},  {159, 0, 96},  {160, 0, 95},  {161, 0, 94},
    {162, 0, 93},  {163, 0, 92},  {164, 0, 91},  {165, 0, 90},  {166, 0, 89},  {167, 0, 88},  {168, 0, 87},
    {169, 0, 86},  {170, 0, 85},  {171, 0, 84},  {172, 0, 83},  {173, 0, 82},  {174, 0, 81},  {175, 0, 80},
    {176, 0, 79},  {177, 0, 78},  {178, 0, 77},  {179, 0, 76},  {180, 0, 75},  {181, 0, 74},  {182, 0, 73},
    {183, 0, 72},  {184, 0, 71},  {185, 0, 70},  {186, 0, 69},  {187, 0, 68},  {188, 0, 67},  {189, 0, 66},
    {190, 0, 65},  {191, 0, 64},  {192, 0, 63},  {193, 0, 62},  {194, 0, 61},  {195, 0, 60},  {196, 0, 59},
    {197, 0, 58},  {198, 0, 57},  {199, 0, 56},  {200, 0, 55},  {201, 0, 54},  {202, 0, 53},  {203, 0, 52},
    {204, 0, 51},  {205, 0, 50},  {206, 0, 49},  {207, 0, 48},  {208, 0, 47},  {209, 0, 46},  {210, 0, 45},
    {211, 0, 44},  {212, 0, 43},  {213, 0, 42},  {214, 0, 41},  {215, 0, 40},  {216, 0, 39},  {217, 0, 38},
    {218, 0, 37},  {219, 0, 36},  {220, 0, 35},  {221, 0, 34},  {222, 0, 33},  {223, 0, 32},  {224, 0, 31},
    {225, 0, 30},  {226, 0, 29},  {227, 0, 28},  {228, 0, 27},  {229, 0, 26},  {230, 0, 25},  {231, 0, 24},
    {232, 0, 23},  {233, 0, 22},  {234, 0, 21},  {235, 0, 20},  {236, 0, 19},  {237, 0, 18},  {238, 0, 17},
    {239, 0, 16},  {240, 0, 15},  {241, 0, 14},  {242, 0, 13},  {243, 0, 12},  {244, 0, 11},  {245, 0, 10},
    {246, 0, 9},   {247, 0, 8},   {248, 0, 7},   {249, 0, 6},   {250, 0, 5},   {251, 0, 4},   {252, 0, 3},
    {253, 0, 2},   {254, 0, 1},   {255, 0, 0},
};

void stripEffect_AllColors(uint32_t interval) {
    uint32_t index = 0;
    uint32_t led;

    while (1) {
        for (led = 0; led < LED_NUMBER; led++)
            set_led_color(led, all_colors[index + led]);

        index++;

        if (index >= 766)
            index = 0;

        HAL_Delay(interval);
    }
}

void stripEffect_ColorWheel(uint32_t interval) {
    uint32_t index = 0;
    uint32_t led;
    size_t color_i;

    while (1) {
        for (led = 0; led < LED_NUMBER; led++) {
            color_i = (index + led * (766 / LED_NUMBER)) % 766;
            set_led_color(led, all_colors[color_i]);
        }
        index += (766 / LED_NUMBER);
        index %= 766;
        HAL_Delay(interval);
    }
}

void stripEffect_CircularRing(uint32_t interval, rgb_t color) {
    size_t led = 0;

    while (1) {
        set_all_led_to((rgb_t){0, 0, 0});
        set_led_color(led, color);
        led++;

        if (led >= LED_NUMBER)
            led = 0;

        HAL_Delay(interval);
    }
}

// the interval should be in the 300-1000 range for best visual effect
void stripEffect_HeartBeat(uint32_t interval, rgb_t color) {
    uint8_t r_inc, g_inc, b_inc;
    uint8_t r_max, g_max, b_max;

    r_inc = color.r / HEARTBEAT_STEPS;
    g_inc = color.g / HEARTBEAT_STEPS;
    b_inc = color.b / HEARTBEAT_STEPS;

    r_max = r_inc * (HEARTBEAT_STEPS - 1);
    g_max = g_inc * (HEARTBEAT_STEPS - 1);
    b_max = b_inc * (HEARTBEAT_STEPS - 1);

    size_t i;

    set_all_led_to((rgb_t){0, 0, 0});

    while (1) {
        // first stroke
        for (i = 0; i < HEARTBEAT_STEPS; i++) {
            set_all_led_to((rgb_t){i * r_inc, i * g_inc, i * b_inc});
            HAL_Delay(interval / 50);
        }
        for (i = 0; i < HEARTBEAT_STEPS; i++) {
            set_all_led_to((rgb_t){r_max - i * r_inc, g_max - i * g_inc, b_max - i * b_inc});
            HAL_Delay(interval / 45);
        }
        // second stroke
        for (i = 0; i < HEARTBEAT_STEPS; i++) {
            set_all_led_to((rgb_t){i * r_inc, i * g_inc, i * b_inc});
            HAL_Delay(interval / 40);
        }
        for (i = 0; i < HEARTBEAT_STEPS; i++) {
            set_all_led_to((rgb_t){r_max - i * r_inc, g_max - i * g_inc, b_max - i * b_inc});
            HAL_Delay(interval / 35);
        }
        // relax..
        HAL_Delay(interval);
    }
}

void stripEffect_PatternMove(uint32_t interval, uint32_t parts, rgb_t color) {
    uint32_t index = 0;
    uint32_t step;
    uint32_t i;

    step = LED_NUMBER / parts;

    while (1) {
        set_all_led_to((rgb_t){0, 0, 0});
        for (i = 0; i < parts; i++)
            set_led_color(index + i * step, color);
        index++;

        if (index >= LED_NUMBER)
            index = 0;

        HAL_Delay(interval);
    }
}

void stripEffect_FullEmpty(uint32_t interval, rgb_t color) {
    size_t led = 0;

    set_all_led_to((rgb_t){0, 0, 0});

    while (1) {
        for (led = 0; led < LED_NUMBER; led++) {
            set_led_color(led, color);
            HAL_Delay(interval);
        }

        for (led = 0; led < LED_NUMBER; led++) {
            set_led_color(led, (rgb_t){0, 0, 0});
            HAL_Delay(interval);
        }
    }
}

void stripEffect_FromTo(uint32_t interval, uint32_t steps, uint8_t r_A, uint8_t g_A, uint8_t b_A, uint8_t r_B,
                        uint8_t g_B, uint8_t b_B) {
    uint32_t i;
    int16_t r_delta, g_delta, b_delta;

    r_delta = ((int32_t)r_B - (int32_t)r_A) / (int32_t)steps;
    g_delta = ((int32_t)g_B - (int32_t)g_A) / (int32_t)steps;
    b_delta = ((int32_t)b_B - (int32_t)b_A) / (int32_t)steps;

    for (i = 0; i < steps; i++) {
        set_all_led_to((rgb_t){r_A + i * r_delta, g_A + i * g_delta, b_A + i * b_delta});
        HAL_Delay(interval / steps);
    }
}

void stripEffect_AlternateColors(uint32_t interval, uint32_t steps, uint8_t r_A, uint8_t g_A, uint8_t b_A, uint8_t r_B,
                                 uint8_t g_B, uint8_t b_B) {
    uint32_t i;
    int32_t r_delta, g_delta, b_delta;

    r_delta = ((int32_t)r_B - (int32_t)r_A) / (int32_t)steps;
    g_delta = ((int32_t)g_B - (int32_t)g_A) / (int32_t)steps;
    b_delta = ((int32_t)b_B - (int32_t)b_A) / (int32_t)steps;

    while (1) {
        for (i = 0; i < steps; i++) {
            set_all_led_to((rgb_t){r_A + i * r_delta, g_A + i * g_delta, b_A + i * b_delta});
            HAL_Delay(interval / steps);
        }
        for (i = steps - 1; i > 0; i--) {
            set_all_led_to((rgb_t){r_A + i * r_delta, g_A + i * g_delta, b_A + i * b_delta});
            HAL_Delay(interval / steps);
        }
    }
}

void stripEffect_Rainbow(uint32_t interval) {
    size_t index = 0, led;
    while (1) {
        for (led = 0; led < LED_NUMBER; led++) {
            // uint16_t hue = (766 / (LED_NUMBER / 24)) * (led / 24 + index);
            uint16_t hue = (766 / 30) * (led % 30 + index);
            set_led_color(led, hsv2rgb((hsv_t) {hue, 255, 100}));
        }

        index++;

        if (index >= 766)
            index = 0;

        HAL_Delay(interval);
    }
}
