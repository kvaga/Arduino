#if defined(__AVR__)
#include "IRremote.h"
#elif defined(ESP8266)
#include "IRremoteESP8266.h"
#endif



#define PIN 2

#define CMD_PWR 100
#define CMD_MUTE 101
#define CMD_VOL_P 102
#define CMD_VOL_M 103
#define CMD_CH_P 104
#define CMD_CH_M 105
#define CMD_CH_0 106
#define CMD_CH_1 107
#define CMD_CH_2 108
#define CMD_CH_3 109
#define CMD_CH_4 110
#define CMD_CH_5 111
#define CMD_CH_6 112
#define CMD_CH_7 113
#define CMD_CH_8 114
#define CMD_CH_9 115

#define CMD_PWR_CODE 0xFDC23D
#define CMD_MUTE_CODE 0xFD629D
#define CMD_VOL_P_CODE 0xFD4AB5
#define CMD_VOL_M_CODE 0xFDCA35
#define CMD_CH_P_CODE 0xFDD22D
#define CMD_CH_M_CODE 0xFD32CD
#define CMD_CH_0_CODE 0xFD50AF
#define CMD_CH_1_CODE 0xFDD02F
#define CMD_CH_2_CODE 0xFD30CF
#define CMD_CH_3_CODE 0xFDB04F
#define CMD_CH_4_CODE 0xFD708F
#define CMD_CH_5_CODE 0xFDF00F
#define CMD_CH_6_CODE 0xFD807F
#define CMD_CH_7_CODE 0xFD8877
#define CMD_CH_8_CODE 0xFD48B7
#define CMD_CH_9_CODE 0xFDC837


// Подключение:
// https://habr.com/ru/post/391001/
// ИК светодиод
//  левая нога (длинная) - плюс, вторая (короткая) - минус
//  !ВАЖНО - подключение через сопровотивление 100ОМ
//  
//
// === MGTS ===
// Power: FDC23D
// Mute: FD629D  например
// Volume+: FD4AB5
// Volume-: FDCA35
// Channel+: FDD22D
// Channel-: FD32CD
// 1: FDD02F
// 2: FD30CF
// 3: FDB04F
// 4: FD708F
// 5: FDF00F
// 6: FD807F
// 7: FD8877
// 8: FD48B7
// 9: FDC837
// 0: FD50AF


IRsend irsend;             // пин передатчика для Duemilanove, Diecimila, LilyPad, Mini, Fio, Nano, Uno - (3), для Мега - (9), для ATmega32U4 - (10).


void setup() {
  Serial.begin(9600); // выставляем скорость COM порта
}

void loop() {
  int cmd = CMD_MUTE;
  switch (cmd) {
    case (CMD_PWR): {
        Serial.print("Sending CMD_PWR command: ");
        Serial.println(CMD_PWR_CODE);
        irsend.sendNEC(CMD_PWR_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
    case (CMD_MUTE): {
        Serial.print("Sending CMD_MUTE command: ");
        Serial.println(CMD_MUTE_CODE);
        irsend.sendNEC(CMD_MUTE_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_VOL_P): {
        Serial.print("Sending CMD_VOL_P command: ");
        Serial.println(CMD_VOL_P_CODE);
        irsend.sendNEC(CMD_VOL_P_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_VOL_M): {
        Serial.print("Sending CMD_VOL_M command: ");
        Serial.println(CMD_VOL_M_CODE);
        irsend.sendNEC(CMD_VOL_M_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_P): {
        Serial.print("Sending CMD_CH_P command: ");
        Serial.println(CMD_CH_P_CODE);
        irsend.sendNEC(CMD_CH_P_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_M): {
        Serial.print("Sending CMD_CH_M command: ");
        Serial.println(CMD_CH_M_CODE);
        irsend.sendNEC(CMD_CH_M_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_0): {
        Serial.print("Sending CMD_CH_0 command: ");
        Serial.println(CMD_CH_0_CODE);
        irsend.sendNEC(CMD_CH_0_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_1): {
        Serial.print("Sending CMD_CH_1 command: ");
        Serial.println(CMD_CH_1_CODE);
        irsend.sendNEC(CMD_CH_1_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_2): {
        Serial.print("Sending CMD_CH_2 command: ");
        Serial.println(CMD_CH_2_CODE);
        irsend.sendNEC(CMD_CH_2_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_3): {
        Serial.print("Sending CMD_CH_3 command: ");
        Serial.println(CMD_CH_3_CODE);
        irsend.sendNEC(CMD_CH_3_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_4): {
        Serial.print("Sending CMD_CH_4 command: ");
        Serial.println(CMD_CH_4_CODE);
        irsend.sendNEC(CMD_CH_4_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_5): {
        Serial.print("Sending CMD_CH_5 command: ");
        Serial.println(CMD_CH_5_CODE);
        irsend.sendNEC(CMD_CH_5_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_6): {
        Serial.print("Sending CMD_CH_6 command: ");
        Serial.println(CMD_CH_6_CODE);
        irsend.sendNEC(CMD_CH_6_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_7): {
        Serial.print("Sending CMD_CH_7 command: ");
        Serial.println(CMD_CH_7_CODE);
        irsend.sendNEC(CMD_CH_7_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_8): {
        Serial.print("Sending CMD_CH_8 command: ");
        Serial.println(CMD_CH_8_CODE);
        irsend.sendNEC(CMD_CH_8_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
      case (CMD_CH_9): {
        Serial.print("Sending CMD_CH_9 command: ");
        Serial.println(CMD_CH_9_CODE);
        irsend.sendNEC(CMD_CH_9_CODE, 32); // посылаем ик-сигнал для NEC
      } break;
  }
  delay(5000);
}
