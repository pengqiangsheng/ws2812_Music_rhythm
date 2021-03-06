# ws2812_Music_rhythm

> ws2812灯带音乐律动项目

## 介绍

本项目采用 声音识别模块 + esp8266/32 + ws2812B灯带组成，配合音乐播放将会律动灯带呈现美轮美奂的视觉盛宴。

## 使用方法

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