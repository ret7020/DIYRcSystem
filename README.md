# DIYRcSystem - Diy Radio Control System

This is a an attempt to create full featured long range open-source control system for UAVs with ability to diy hardware (like, esp32, arudino and other modules from Aliexpress). 

Main modulation is LoRA, but I am planning to use multiple frequency bands for control at same time: 433 Mhz link, 868 Mhz link (or 915 in some countries) and 2.4 Ghz link (maybe). 

So, the reciever will have 2 or 3 independent transievers that can be configured "on-fly" (example: use 433 MHz as RX, 868 Mhz as Telemetry TX. If 433 Mhz will have too much noises it can switch to 868 MHz as RX, or even use 868Mhz and 433 Mhz links at same time to RX).

Reciever will be supported with Flight Controller (we have to use fligh controller for long-range :). It will use SBUS protocol to send RX channels to FC and Mavlink over UART to get telemetry from FC.

Maybe, I will post some notes/dev-logs/tutorials to my habr profile (ru).