#include "sbusTx.h"
#include "ltm.h"

SbusTX sbus(Serial2);
LTMRX ltm(Serial1); // GPIO14 as RX

uint32_t lastTelemPrint = 0;

void setup(){
    Serial.begin(115200);
}

void loop(){
    sbus.refresh();
    ltm.read();
    if (millis() - lastTelemPrint >= 500){ // 2 Hz
        // builtin printf is esp32 feature
        printf("---\nVoltage: %u mV\n\nRoll: %u\nPitch: %u\nYaw:%u\n", ltm.last.voltage, ltm.last.roll, ltm.last.pitch, ltm.last.yaw); 
        lastTelemPrint = millis();
    }
}