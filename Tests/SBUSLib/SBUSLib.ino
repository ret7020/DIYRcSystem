#include "sbusTx.h"

SbusTX sbus(Serial2);

void setup(){
    Serial.begin(115200);
    sbus.set(0, 1000);
    sbus.set(1, 1550);
    sbus.set(2, 1400);
    sbus.set(4, 1800);
}
void loop(){
    sbus.refresh();
}