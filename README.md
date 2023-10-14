# `3 Smart Modes` Project README

---

## Table of Contents
1. [Project Information](#project-information)
2. [Code Explanation](#code-explanation)
    - [Mode Selector](#mode-selector)
    - [Calculator Functionality](#calculator-functionality)
    - [Stopwatch Functionality](#stopwatch-functionality)
    - [Timer Functionality](#timer-functionality)
3. [Video Link](#video-link)

---

## Project Information
- Project: `[3 Smart Modes]`
- Authors: `[Amal Amr]`, `[Malak Tarek]`, `[Mark Mohab]`, `[Youssef Sherif]`, `[Youssef Amir]`
- Video: [Link](https://drive.google.com/drive/folders/10zPuur7hFEGiXTilziT9V1bLNemreWvS?usp=sharing)

---

## Code Explanation

### Mode Selector
The `select_mode` function facilitates the mode selection (calculator, timer, or stopwatch) through an interface composed of a keypad and LCD display. On activating this function, the LCD prompts the user to "select mode." Following the keypad input:
- Pressing '+' initiates the calculator mode.
- Pressing '-' begins the timer mode.
- Pressing '/' starts the stopwatch mode.

To mitigate unintentional multi-mode triggering due to a single keypress, a 400-millisecond delay is incorporated. Before transitioning to a new mode, the existing stopwatch or timer modes are duly terminated.

### Calculator Functionality
The `calculator_start` function creates a basic calculator interface using the Arduino setup, a keypad, and an LCD. Upon initialization:
- The LCD showcases the "Calculator" prompt.
- Number inputs via the keypad get displayed on the LCD.
- On entering an operator (like '+', '-', '/', '*'), the first number is computed.
- Following this, the second number is input and displayed.
- Pressing '=' computes the result which is then displayed on the LCD.

### Stopwatch Functionality
A series of functions defines the stopwatch capabilities, namely:
- `stopwatch_pause` halts the stopwatch timer, and displays "PAUSED."
- `stopwatch_resume` restarts the timer, erasing the "PAUSED" indication.
- `stopwatch_reset_handler` & `stopwatch_reset` reset the stopwatch.

In essence, `stopwatch_start` initializes the stopwatch, and with each timer expiry, `stopwatch_handler` is summoned. The `stopwatch_counter` updates the display with the current time, and for every 60 seconds, the minute counter increases.

### Timer Functionality
The timer allows users to set a specific duration, visually represented on the LCD:
- `timer_start` captures the timer duration via the keypad and showcases it on the LCD.
- `timer_enable` configures the timer and activates it.
- On each timer expiry, `timer_handler` gets activated and calls `timer_counter` to refresh the timer count on the LCD.

Functions like `timer_end` and `stopwatch_end` are designed to respectively terminate and reset timers and stopwatches.
