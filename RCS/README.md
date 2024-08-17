# Protocol description

## Control protocol
You can set 2 precision levels: 8 bit and 10 bit, so each channel will have 8 bit or 10 bit.

In 8 bit precision joystick `0-255` will be mapped to `1000-2000`

In 10 bit precision joystick `0-1024` will be mapped to `1000-2000`

You can configure payload format for different platforms to optimize payload size and don't send redundant data

Example for 4 control channel plane (aileron, rudder, elevator, 1 motor throttle):
```
[
    CH_0: 8/10 bits: Servo/ESC throttle
    CH_1: 8/10 bits: Servo/ESC throttle
    CH_2: 8/10 bits: Servo/ESC throttle
    CH_3: 8/10 bits: Servo/ESC throttle
    PADDING
]
```
Except 8-10 bit servo control you can send muilti-selectors(4 or 16 states, you can make some states `dummy`) and switches (ON/OFF).

You can use up to 8 switches:

```
[
    SW_0: 1 bit: ON or OFF
    SW_1: 1 bit: ON or OFF
    SW_2: 1 bit: ON or OFF
    SW_3: 1 bit: ON or OFF
    SW_4: 1 bit: ON or OFF
    SW_5: 1 bit: ON or OFF
    SW_6: 1 bit: ON or OFF
    SW_7: 1 bit: ON or OFF
]
```

Multi-selectors can be used in following configurations

```
[
    MS_2_0: 2 bit selector (4 states)
    MS_2_1: 2 bit selector (4 states)
    MS_2_2: 2 bit selector (4 states)
    MS_2_3: 2 bit selector (4 states)
] -> 8 bit
```

Or this

```
[
    MS_4_0: 4 bit selector (16 states)
    MS_4_1: 4 bit selector (16 states)
] -> 8 bit
```

Per channel memory distribution **variant_0**:

```
[
    SERVO/ESC -> summary 5 byte (40 bit) up to 4 x 10 bit precision joysticks or 5 x 8 bit precision joysticks
    BINARY_SELECTORS -> summary 1 byte (8 bit)
    SWITCH -> summary 1 byte (8 bit) can combine 4 bit + 2 bit + 2 bit or just 4 x 2 bit
]
```

Total: 7 byte (56 bits)

```
Less data - more speed on same params (coding rate, band-width).
```


## Telemtry protocol