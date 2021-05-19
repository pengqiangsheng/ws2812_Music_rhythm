/**
 * 名称：音乐律动灯带
 * 作者：pengqiangsheng
 * 时间：5/19/2021
 * 材料：声音识别模块 + esp8266/32 + ws2812B灯带
 * 使用方法：将以上模块正确连接通电，烧写代码至esp8266/32
 * 注意事项：ws2812灯带需要单独供电，一颗灯珠0.3w，30颗就是9w（5v 2A电源），60颗18w（5v 4A电源）
 * 可能会发现的意外：arduino IDE报错：1.找不到GPIO13.../ 2.找不到A0... / 3.一切正常灯不律动
 * 原因及解决办法：1.esp8266板子选择 General esp8266 module
 *                2.esp32 选择 esp32 Dev module，修改A0为36
 *                3.确保ws2812的信号端接GPIO13，确保声音模块正常工作且信号端接A0
 * 
 * 更多内容：https://github.com/pengqiangsheng/ws2812_Music_rhythm  (点个star，祝您生活愉快！)
 * 
 */
#include "FastLED.h"

#define LED_DT 13                            // 控制引脚                                          
#define COLOR_ORDER GRB                      // 以GRB排列               
#define LED_TYPE WS2812                      // 灯条类型              
#define NUM_LEDS 28                          // 灯珠数量
#define FIXED_LEDS 4                         // 中间固定显示的灯珠数量

// 定义A0引脚
#ifndef A0
#define A0 6
#endif

struct CRGB leds[NUM_LEDS];
int8_t maxBright = 128;
int8_t leftStart, leftEnd, rightStart, rightEnd;

CHSV musicHSVcolor(80,255,200);  

void initWs2812() {
  leftStart = 0;
  leftEnd = (NUM_LEDS - FIXED_LEDS) / 2 - 1;
  rightStart = leftEnd + FIXED_LEDS + 1;
  rightEnd = NUM_LEDS - 1;

  for(int i=leftEnd + 1; i<rightStart; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
}

int8_t getActiveLedNum() {
  int8_t voiceLevel = 1024 / (leftEnd + 1);
  int8_t value = analogRead(A0) / voiceLevel;
  return value;
}

void showWithMusic(int8_t activeLedNum) {
  musicHSVcolor.h += 10;
  
  for(int i=rightEnd, j = 0; i>=activeLedNum + rightStart; i--, j++) {
    leds[i] = CRGB(0, 0, 0);
    leds[j] = CRGB(0, 0, 0);
    FastLED.show();
    delay(6);
  }

  for(int i=rightStart, j = 0; i<rightStart + activeLedNum; i++, j++) {
    leds[i] = musicHSVcolor;
    leds[i - (j * 2 + FIXED_LEDS + 1)] = musicHSVcolor;
    FastLED.show();
    delay(6);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("");
  delay(500);

  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER >(leds, NUM_LEDS);
  LEDS.setBrightness(maxBright);
  initWs2812();
}

void loop() {
  int8_t value = getActiveLedNum();
  Serial.println(value);
  showWithMusic(value);
  delay(24); 
}
