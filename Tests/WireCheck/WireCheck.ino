/*
It is code for ESP32, we use UART2 (Serial2), for other MCU change it for yours
*/

#include "sbusTx.h"
#include "ltm.h"

uint8_t sbusPacket[SBUS_PACKET_LENGTH];
int rcChannels[SBUS_CHANNEL_NUMBER];
uint32_t sbusSendTime = 0;
uint8_t telemReadState = WAIT;
char telemFrameType;
uint8_t telemFrameLength;
uint8_t telemReceiverIndex;
uint8_t telemSerialBuffer[LONGEST_FRAME_LENGTH];

void setup()
{
    Serial.begin(115200);
    Serial.println("[INFO] Starting...");

    for (uint8_t i = 0; i < SBUS_CHANNEL_NUMBER; i++)
    {
        rcChannels[i] = 1055 + (i + 1) * 2;
    }
    Serial2.begin(100000, SERIAL_8E2);
    Serial1.begin(19200, SERIAL_8N1, 14, 12);
}

void loop()
{
    if (millis() - sbusSendTime >= SBUS_UPDATE_RATE)
    {
        rcChannels[0] += 1;
        if (rcChannels[0] > 2000)
            rcChannels[0] = 1200;
        createSbusPacket(sbusPacket, rcChannels, false, false);
        Serial2.write(sbusPacket, SBUS_PACKET_LENGTH);
        sbusSendTime = millis();
    }
    if (Serial1.available())
    {
        char recievedByte = Serial1.read();
        if (telemReadState == WAIT)
        {
            if (recievedByte == '$')
                telemReadState = HEADER_START1;
        }
        else if (telemReadState == HEADER_START1)
        {
            if (recievedByte == 'T')
                telemReadState = HEADER_START2;
            else
                telemReadState = WAIT;
        }
        else if (telemReadState == HEADER_START2)
        {
            telemFrameType = recievedByte;
            telemReadState = HEADER_MSGTYPE;
            telemReceiverIndex = 0;
            switch (recievedByte)
            {
            case 'G':
                telemFrameLength = G_FRAME_LENGTH;
                break;
            case 'A':
                telemFrameLength = G_FRAME_LENGTH;
                break;
            case 'S':
                telemFrameLength = G_FRAME_LENGTH;
                break;
            case 'O':
                telemFrameLength = G_FRAME_LENGTH;
                break;
            case 'N':
                telemFrameLength = G_FRAME_LENGTH;
                break;
            case 'X':
                telemFrameLength = G_FRAME_LENGTH;
                break;
            default:
                telemReadState = WAIT;
            }
        }
        else if (telemReadState == HEADER_MSGTYPE)
        {
            if (telemReceiverIndex == telemFrameLength - 4)
            {
                if (telemFrameType == 'S')
                {
                    uint16_t voltage = (int) telemSerialBuffer[0] + ((int) telemSerialBuffer[1] << 8);
                    uint8_t rssi = telemSerialBuffer[4];
                    uint8_t mode = telemSerialBuffer[6] >> 2;
                    Serial.print(voltage);
                    Serial.println(" mV");
                }


                telemReadState = WAIT;
                memset(telemSerialBuffer, 0, LONGEST_FRAME_LENGTH);
            }
            else
            {
                telemSerialBuffer[telemReceiverIndex++] = recievedByte;
            }
        }
    }
}