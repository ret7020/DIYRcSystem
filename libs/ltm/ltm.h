// Some source taken from this https://github.com/DzikuVx/ltm_telemetry_reader/

#ifndef LTM_H
#define LTM_H

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



#endif