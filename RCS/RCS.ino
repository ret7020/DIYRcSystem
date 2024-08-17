/*
It is code for ESP32 MCU
*/

#include "sbusTx.h"


uint8_t sbusPacket[SBUS_PACKET_LENGTH];
int rcChannels[SBUS_CHANNEL_NUMBER];
uint32_t sbusSendTime = 0;

void setup(){
    Serial.begin(115200);
    Serial.println("[INFO] Starting...");

    for (uint8_t i = 0; i < SBUS_CHANNEL_NUMBER; i++) {
        rcChannels[i] = 1500; // Default middle stick positions
    }
    Serial2.begin(100000, SERIAL_8E2);
}

void loop(){
    if (millis() - sbusSendTime >= SBUS_UPDATE_RATE){
        rcChannels[0] += 1;
        if (rcChannels[0] > 2000) rcChannels[0] = 1200;
        createSbusPacket(sbusPacket, rcChannels, false, false);
        Serial2.write(sbusPacket, SBUS_PACKET_LENGTH);
        sbusSendTime = millis();
    }

}