# LED Matrix Scrolling Text Display with FastLED

This project controls an LED matrix using an FPGA and Arduino to display scrolling text with customizable colors. The code is written to display a message on a 5x5 LED matrix using the FastLED library. Each letter is represented by a 5x5 dot matrix pattern, and the text scrolls across the display.

## Features

- **Scrolling Text**: Displays a scrolling message across the LED matrix.
- **Customizable Colors**: Randomized color transitions are available, or a fixed color can be set.
- **Brightness and Speed Control**: Adjust the brightness of the LEDs and speed of scrolling.
- **Pattern Definition**: Letters are defined in a 5x5 binary array for easy customization.

## Requirements

- **Hardware**:
  - Arduino (or compatible microcontroller)
  - WS2812 or compatible LED strip with at least 25 LEDs

- **Libraries**:
  - [FastLED](https://github.com/FastLED/FastLED): Install via Arduino Library Manager or download from GitHub.

## Code Overview

- **LED Matrix Setup**: The matrix is set up as a 5x5 grid of WS2812 LEDs.
- **Scrolling Message**: The `loop` function continuously scrolls the specified message across the LED matrix.
- **Color Change Function**: Dynamically changes the color of each letter. When `RANDOMCOLOR` is set to true, colors transition smoothly across RGB values.

## Configuration

### Variables

- **`RANDOMCOLOR`**: Set to `true` for random color transitions, or `false` to use a fixed color (`COLOR`).
- **`COLOR`**: Fixed color used when `RANDOMCOLOR` is false.
- **`Brightness`**: Sets the brightness level of the LEDs (range 0-255).
- **`speed`**: Controls the scrolling speed. A higher number results in slower scrolling.
- **`space`**: Determines spacing between letters:
  - `6` for extra space,
  - `5` for letters close together,
  - `4` for slight overlap.

### Message Customization

Set your custom message in the `message[]` variable in the code:

```cpp
char message[] = "Test Message";
```

### Pattern Definition

Each letter pattern is defined in a 5x5 binary format within the letters array. Modify this array to customize the characters displayed.

### Usage
**Setup:**

1. Install the FastLED library in your Arduino environment.
2. Connect your WS2812 LEDs to the defined LED_PIN.

**Upload:**

3. Open the code in the Arduino IDE.
4. Select your board and upload the code.

### Display:

The LEDs should start scrolling the text message across the 5x5 matrix with your chosen settings.

**Functions**

- setup(): Initializes the LED strip and brightness settings.
- loop(): Main loop for scrolling text display.
- getPeice(): Retrieves the current segment of the message for display.
- fullMessage(): Converts the full message into binary representation.\
- colorChange(): Randomly transitions colors for each frame.
- displayLetter(byte pattern[5]): Displays a letter pattern on the LED matrix.
- getByte(): Controls the bitwise shift for scrolling the message.
