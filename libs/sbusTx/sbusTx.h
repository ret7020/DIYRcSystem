#ifndef sbusTX_H

#define sbusTX_H

#include "Arduino.h"

// Config
#define RC_CHANNEL_MIN 990
#define RC_CHANNEL_MAX 2010
#define SBUS_MIN_OFFSET 173
#define SBUS_MID_OFFSET 992
#define SBUS_MAX_OFFSET 1811
#define SBUS_CHANNEL_NUMBER 16
#define SBUS_PACKET_LENGTH 25
#define SBUS_FRAME_HEADER 0x0f
#define SBUS_FRAME_FOOTER 0x00
#define SBUS_FRAME_FOOTER_V2 0x04
#define SBUS_STATE_FAILSAFE 0x08
#define SBUS_STATE_SIGNALLOSS 0x04
#define SBUS_UPDATE_RATE 15 // ms
#define SBUS_BAUD 100000
#define SBUS_CHANNELS_DEFAULT 1500

class SbusTX
{
private:
    uint32_t lastRefreshTime = 0;
    HardwareSerial *fcSerial;
    HardwareSerial *debugSerial;
    uint8_t packet[SBUS_PACKET_LENGTH];
    int channels[SBUS_CHANNEL_NUMBER];

public:
    bool isSignalLoss = false;
    bool isFailsafe = false;

    SbusTX(HardwareSerial &fcSer)
    {
        this->fcSerial = &fcSer;
        init();
    }

    void init()
    {
        fcSerial->begin(SBUS_BAUD, SERIAL_8E2);
        // Defaults 1500 to all channels
        for (uint8_t i = 0; i < SBUS_CHANNEL_NUMBER; i++)
            channels[i] = SBUS_CHANNELS_DEFAULT;
    }

    void set(uint16_t channel, int value)
    {
        channels[channel] = value;
    }

    void createPacket(uint8_t packet[], int allChannels[])
    {
        static int output[SBUS_CHANNEL_NUMBER] = {0};
        for (uint8_t i = 0; i < SBUS_CHANNEL_NUMBER; i++)
        {
            output[i] = map(allChannels[i], RC_CHANNEL_MIN, RC_CHANNEL_MAX, SBUS_MIN_OFFSET, SBUS_MAX_OFFSET);
        }

        uint8_t stateByte = 0x00;
        if (isSignalLoss)
        {
            stateByte |= SBUS_STATE_SIGNALLOSS;
        }
        if (isFailsafe)
        {
            stateByte |= SBUS_STATE_FAILSAFE;
        }
        packet[0] = SBUS_FRAME_HEADER; // Header

        packet[1] = (uint8_t)(output[0] & 0x07FF);
        packet[2] = (uint8_t)((output[0] & 0x07FF) >> 8 | (output[1] & 0x07FF) << 3);
        packet[3] = (uint8_t)((output[1] & 0x07FF) >> 5 | (output[2] & 0x07FF) << 6);
        packet[4] = (uint8_t)((output[2] & 0x07FF) >> 2);
        packet[5] = (uint8_t)((output[2] & 0x07FF) >> 10 | (output[3] & 0x07FF) << 1);
        packet[6] = (uint8_t)((output[3] & 0x07FF) >> 7 | (output[4] & 0x07FF) << 4);
        packet[7] = (uint8_t)((output[4] & 0x07FF) >> 4 | (output[5] & 0x07FF) << 7);
        packet[8] = (uint8_t)((output[5] & 0x07FF) >> 1);
        packet[9] = (uint8_t)((output[5] & 0x07FF) >> 9 | (output[6] & 0x07FF) << 2);
        packet[10] = (uint8_t)((output[6] & 0x07FF) >> 6 | (output[7] & 0x07FF) << 5);
        packet[11] = (uint8_t)((output[7] & 0x07FF) >> 3);
        packet[12] = (uint8_t)((output[8] & 0x07FF));
        packet[13] = (uint8_t)((output[8] & 0x07FF) >> 8 | (output[9] & 0x07FF) << 3);
        packet[14] = (uint8_t)((output[9] & 0x07FF) >> 5 | (output[10] & 0x07FF) << 6);
        packet[15] = (uint8_t)((output[10] & 0x07FF) >> 2);
        packet[16] = (uint8_t)((output[10] & 0x07FF) >> 10 | (output[11] & 0x07FF) << 1);
        packet[17] = (uint8_t)((output[11] & 0x07FF) >> 7 | (output[12] & 0x07FF) << 4);
        packet[18] = (uint8_t)((output[12] & 0x07FF) >> 4 | (output[13] & 0x07FF) << 7);
        packet[19] = (uint8_t)((output[13] & 0x07FF) >> 1);
        packet[20] = (uint8_t)((output[13] & 0x07FF) >> 9 | (output[14] & 0x07FF) << 2);
        packet[21] = (uint8_t)((output[14] & 0x07FF) >> 6 | (output[15] & 0x07FF) << 5);
        packet[22] = (uint8_t)((output[15] & 0x07FF) >> 3);

        packet[23] = stateByte;         // Flags byte
        packet[24] = SBUS_FRAME_FOOTER; // Footer
    }

    void refresh()
    {
        // Call this in main loop (you can't execute it in IRQ via hardware timer without tuning esp32 watchdog)
        if (millis() - lastRefreshTime >= SBUS_UPDATE_RATE){
            createPacket(packet, channels);
            fcSerial->write(packet, SBUS_PACKET_LENGTH);
            lastRefreshTime = millis();

        }
        
    }
};

#endif