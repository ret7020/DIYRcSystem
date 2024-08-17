// Some source taken from this https://github.com/DzikuVx/ltm_telemetry_reader/

#ifndef LTM_H
#define LTM_H

#include "Arduino.h"

enum ltmStates
{
    WAIT,
    HEADER_START1,
    HEADER_START2,
    HEADER_MSGTYPE,
    HEADER_DATA
};

#define LONGEST_FRAME_LENGTH 18
#define G_FRAME_LENGTH 18
#define A_FRAME_LENGTH 10
#define S_FRAMEL_ENGTH 11
#define O_FRAMEL_ENGTH 18
#define N_FRAMEL_ENGTH 10
#define X_FRAMEL_ENGTH 10
#define LTM_BAUD 19200

const char *flightModes[] = {
    "Manual",
    "Rate",
    "Angle",
    "Horizon",
    "Acro",
    "Stabilized1",
    "Stabilized2",
    "Stabilized3",
    "Altitude Hold",
    "GPS Hold",
    "Waypoints",
    "Head free",
    "Circle",
    "RTH",
    "Follow me",
    "Land",
    "Fly by wire A",
    "Fly by wire B",
    "Cruise",
    "Unknown"};


typedef struct telemetryPacket_s {
    // A_FRAME
    int pitch;
    int roll;
    int yaw;

    // S_FRAME
    uint16_t voltage; // mV
    uint8_t rssi;
    uint8_t flightMode;

} telemetryPacket_t;


class LTMRX
{
private:
    HardwareSerial *fcSerial;
    uint8_t telemReadState = WAIT;
    char telemFrameType;
    uint8_t telemFrameLength;
    uint8_t telemReceiverIndex;
    uint8_t telemSerialBuffer[LONGEST_FRAME_LENGTH];

public:
    telemetryPacket_t last;

    LTMRX(HardwareSerial &fcSer)
    {
        this->fcSerial = &fcSer;
        init();
    }

    void init()
    {
        fcSerial->begin(LTM_BAUD, SERIAL_8N1, 14, 12);
    }

    int parseInt(uint8_t offset){
        return (int) telemSerialBuffer[offset] + ((int) telemSerialBuffer[offset + 1] << 8);
    }

    void read()
    {
        // Call this in loop (as fast as can)
        if (fcSerial->available())
        {
            char recievedByte = fcSerial->read();
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
                        last.voltage = parseInt(0);
                        last.rssi = telemSerialBuffer[4];
                        last.flightMode = telemSerialBuffer[6] >> 2;
                    }

                    if (telemFrameType == 'A'){
                        last.pitch = parseInt(0) ;
                        last.roll = parseInt(2);
                        last.yaw = parseInt(4);
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
};

#endif
