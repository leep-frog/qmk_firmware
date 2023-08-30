# groogerpad

![groogerpad](imgur.com image replace me!)

Running QMK with an Xbox controller!

* Keyboard Maintainer: [leep-frog](https://github.com/leep-frog)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make groogerpad:default

Flashing example for this keyboard:

    make groogerpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Circuit Board Setup Instructions

* Install arduino-fwuploader
* See full list of board options with `.\arduino-fwuploader.exe firmware list`
* Set the board by running `set BOARD=arduino:samd:nano_33_iot`
* Run the following command to flash the NINA board with the proper logic:
```
.\arduino-fwuploader.exe firmware flash -b arduino:samd:mkrwifi1010 -a COM8 -i ..\bluepad32-nina-v3.8.3.tar\bluepad32-nina-v3.8.3\bluepad32-nina-v3.8.3\bluepad32-nina-full-v3.8.3.bin
```
