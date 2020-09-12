#include "IRremote.h"
#define PIN 2

// Подключение:
// https://robotclass.ru/tutorials/arduino-ir-remote-control/
//Датчик - VS1838B
//  левая нога - контрол, например: второй вывод
//  средняя нога - ground
//  правая нога - 5v
// 
// === MGTS ===
// Power: FDC23D
// Mute: FD629D
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


IRrecv irrecv(PIN); // указываем вывод, к которому подключен приемник

decode_results results;

void setup() {
  Serial.begin(9600); // выставляем скорость COM порта
  irrecv.enableIRIn(); // запускаем прием
}

void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    Serial.print("HEX of incoming code: ");
    Serial.println( results.value, HEX ); // печатаем данные
    irrecv.resume(); // принимаем следующую команду
    show_decoded_type();
  }
}

// Decode type
void show_decoded_type(){
//        Serial.println(results.value, HEX);
        Serial.print("Decoded type: ");
        switch (results.decode_type){
            case NEC: Serial.println("NEC"); break ;
            case SONY: Serial.println("SONY"); break ;
            case RC5: Serial.println("RC5"); break ;
            case RC6: Serial.println("RC6"); break ;
            case DISH: Serial.println("DISH"); break ;
            case SHARP: Serial.println("SHARP"); break ;
            case JVC: Serial.println("JVC"); break ;
            case SANYO: Serial.println("SANYO"); break ;
            case MITSUBISHI: Serial.println("MITSUBISHI"); break ;
            case SAMSUNG: Serial.println("SAMSUNG"); break ;
            case LG: Serial.println("LG"); break ;
            case WHYNTER: Serial.println("WHYNTER"); break ;
            case AIWA_RC_T501: Serial.println("AIWA_RC_T501"); break ;
            case PANASONIC: Serial.println("PANASONIC"); break ;
            case DENON: Serial.println("DENON"); break ;
          default:
            case UNKNOWN: Serial.println("UNKNOWN"); break ;
          }
        irrecv.resume();
 
}
