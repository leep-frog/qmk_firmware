## PAS Macropad

This is compiled with [QMK](https://github.com/qmk/qmk_firmware). See that link
for more info (clicking around the
[docs](https://github.com/qmk/qmk_firmware/tree/master/docs)
folder is a great place to start).

### Base Layer

```
                  |  USB  |
                  | Input |
/--------------------------------------------|
|              |              |              |
|   CR Desc    |    CR ID     |   Mystery    |
|    Macro     |              |   Button!    |
|--------------------------------------------|
|              |              |              |
|     Copy     |    Paste     |  Light Mode  |
|              |              |              |
|--------------------------------------------|
|              |              |              |
|   URL Copy   |  URL Paste   |  Link Layer  |
|              |              |   (Hold)     |
|--------------------------------------------/

```

### Link Layer

```
                  |  USB  |
                  | Input |
/--------------------------------------------|
|  Bootloader  |              |              |
|     Mode     |    Conduit   |    KC_NO     |
|    (Reset)   |              |              |
|--------------------------------------------|
|              |              |              |
|     CRUX     |     Quip     |    KC_NO     |
|              |              |              |
|--------------------------------------------|
|              |              |              |
|    Chime     |   Meetings   | (Held down)  |
|              |              |              |
|--------------------------------------------/

```

### Key Descriptions

* **CR Desc Macro:** This key starts a macro that automatically moves the cursor and fills in the CR description template used by our team! Follow the below instructions to use:
  * Move your cursor to the middle of the first bracket answer:
    `[<cursor here>] This change is a single, isolated change`
  * Press the `CR Desc Macro` button
  * Press tbe top-left button for `y`
  * Press tbe top-middle button for `n`
  * Press tbe top-right button for `n/a`
  * Press any other button to end the macro (the macro will automatically end after the last question is completed)
  * Your cursor will automatically move to the next question entry! `[|]`
* **CR ID:** When on a CR page, this button will highlight and copy the CR ID from the URL bar.
* **Mystery Button:** Press to find out (this button just writes some text `:)`)
* **Copy:** Ctrl+c
* **Paste:** Ctrl+v
* **URL Copy:** Copies the URL of the web page you are currently on.
* **URL Paste:** Opens a new browser tab with whatever data is in your clipboard (i.e. if `www.amazon.com` has been copied, then pressing this button will open a new browser tab to `www.amazon.com`).
* **Light Mode:** Press to toggle through different [QMK RGB matrix light modes](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgb_matrix.md#rgb-matrix-effects-idrgb-matrix-effects)
* **Link Layer:** Hold this key to go to the `Link Layer`
* **Bootloader Mode (Reset):** Puts the macropad into [bootloading mode](https://github.com/qmk/qmk_firmware/blob/master/docs/newbs_flashing.md) (for re-flashing). If unintentionally pressed, just unplug and plug back in.
* **Conduit:** Opens Conduit in a new browser tab.
* **CRUX:** Opens CRUX in a new browser tab.
* **Quip:** Opens Quip in a new browser tab.
* **Chime:** Opens Chime in a new browser tab.
* **Meetings:** Opens Meetings in a new browser tab.
