# snake

![snake](imgur.com image replace me!)

*A 40% keyboard with RGB lighting support*

* Keyboard Maintainer: [Sergei Krivtcov](https://github.com/1000eyed)
* Hardware Supported: STM32F072 microcontroller with 43 WS2812 LEDs
* Hardware Availability: Custom keyboard design

## Features

* 40% layout with multiple bottom row options
* 43 WS2812 RGB LEDs for underglow lighting
* RGB lighting effects controllable via VIAL
* RGB layers for modifier key status indication
* Encoder support for volume and RGB control
* VIAL-compatible for easy keymap editing

Make example for this keyboard (after setting up your build environment):

    make snake:default

Flashing example for this keyboard:

    make snake:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## RGB Lighting

The keyboard features 43 WS2812 RGB LEDs that can be controlled via VIAL or key combinations:

### Available Effects
* Static colors
* Breathing
* Rainbow mood
* Rainbow swirl
* Snake
* Knight rider
* Christmas
* Twinkle
* RGB test
* And more...

### RGB Controls
* **Encoder**: Rotate to change RGB mode (CCW) and RGB speed (CW)
* **VIAL**: Use the VIAL GUI to control all RGB settings
* **Key combinations**: Use RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD

### RGB Layers
The keyboard includes RGB layers that show the status of modifier keys:
* Shift (Green)
* Ctrl (Green) 
* Alt (Green)
* GUI/Win (Green)
* NUM layer (Cyan)
* FUN layer (Red)
* NAV layer (Purple)

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
