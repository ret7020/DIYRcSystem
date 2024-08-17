# DIYRcSystem - Diy Radio Control System

This is a an attempt to create full featured long range open-source control system for UAVs with ability to diy hardware (like, esp32, arudino and other modules from Aliexpress). 

Main modulation is LoRA, but I am planning to use multiple frequency bands for control at same time: 433 Mhz link, 868 Mhz link (or 915 in some countries) and 2.4 Ghz link (maybe). 

So, the reciever will have 2 or 3 independent transievers that can be configured "on-fly" (example: use 433 MHz as RX, 868 Mhz as Telemetry TX. If 433 Mhz will have too much noises it can switch to 868 MHz as RX, or even use 868Mhz and 433 Mhz links at same time to RX).

But I'm planning to use not only LoRA. In future I want to control UAV via NVIS antenna on Short Wave (2 - 5 Mhz in day time summer) with Si5351 chip and FSK (or other modulation), but this is comlicated task in part of creating "working" antenna.

Reciever will be supported with Flight Controller (we have to use fligh controller for long-range :). It will use SBUS protocol to send RX channels to FC and LTM/Mavlink over UART to get telemetry from FC.

Maybe, I will post some notes/dev-logs/tutorials to my habr profile (ru).


```bash
ln -s ~/Progs/DIYRcController/libs/sbusTx Arduino/libraries/sbusTx
```

## Hardware
For developmnet I use `esp32 node mcu` and `MatekF405 Wing V2` with `INAV 7.1.2` installed on it.