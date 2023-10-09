# Drive Link: 

https://drive.google.com/drive/folders/10zPuur7hFEGiXTilziT9V1bLNemreWvS?usp=sharing

# Called Explanation

The first part of the code is a function that allows the user to select between three modes (calculator, timer, and stopwatch) using a keypad and an LCD screen. The function is called select_mode, and it uses a switch statement to determine which mode to select based on the key that is pressed on the keypad.

The function first clears the display and prints the message "select mode" on the first line of the LCD screen. Then, it enters a loop that reads a key from the keypad using the KEYPAD_getPressedKey2 function and waits for 400 milliseconds to avoid double pressing.

If the key pressed is '+', the function calls the calculator_start function to start the calculator mode. If the key pressed is '-', the function calls the timer_start function to start the timer mode. If the key pressed is '/', the function calls the stopwatch_start function to start the stopwatch mode.

The function also has code to end the stopwatch and timer modes before starting the new mode, using the stopwatch_end and timer_end functions. Finally, the function disables the cursor on the LCD screen using the LCD_Cmd function with the cursorOff parameter.

The next function implements a simple calculator using an Arduino, a keypad, and an LCD screen. The function is called calculator_start, and it allows the user to enter two numbers and an operator, and then displays the result of the calculation on the LCD screen.

The function starts by clearing the LCD screen, initializing some variables, and printing the message "Calculator" on the first line of the LCD screen. It then enters a loop to read numbers from the keypad and store them in an array called numbers. The numbers are displayed on the second line of the LCD screen as they are entered.

If the user enters an operator (e.g., '+', '-', '/', or '*') on the keypad, the function saves the operator in a variable called process and calculates the value of the first number using the numbers in the numbers array.

The function then enters a second loop to read numbers from the keypad and store them in a second array called numbers2. When the user presses the '=' key on the keypad, the function calculates the value of the second number using the numbers in the numbers2 array.

Finally, the function uses a switch statement to determine the result of the calculation based on the operator that was entered, and displays the result on the second line of the LCD screen. The function also has code to disable the cursor on the LCD screen using the LCD_Cmd function with the cursorOff parameter.

The next function is a set of functions related to a stopwatch implemented using an Arduino and an LCD screen.

The stopwatch_pause function disables the timer using the TimerDisable function from the TivaWare library and prints the message "PAUSED" on the first line of the LCD screen at column 9.

The stopwatch_resume function enables the timer using the TimerEnable function from the TivaWare library and clears the message "PAUSED" from the LCD screen by overwriting it with spaces.

The stopwatch_reset_handler function calls the stopwatch_reset function and clears the stopwatch display on the LCD screen by writing the value 0 to all the relevant digits.

The stopwatch_reset function resets the stopwatch by setting the values of two variables, z and y, to 0. These variables are likely used to store the minutes and seconds of the stopwatch, and are passed to the function as pointers (int* z and int* y).

The next part is a function that allows the user to set a timer using an Arduino and an LCD screen. The function is called timer_start, and it reads the minutes and seconds of the timer from a keypad and displays them on the LCD screen.

The function starts by clearing the LCD screen and printing the message "Enter time" on the first line. It then moves the cursor to column 2 on the second line and writes a colon (':') using the LCD_Write_Char function. The function then moves the cursor to column 0 on the second line and reads the first digit of the minutes from the keypad using the KEYPAD_getPressedKey function. It displays the digit on the LCD screen using the LCD_intgerToString function and waits for 400 milliseconds using the delay_ms function.

The function repeats this process for the second digit of the minutes, and then for the first and second digits of the seconds. Once all the digits have been read and displayed, the function calculates the total number of minutes and seconds entered by the user and stores them in two variables using pointers (pointer_sec and pointer_min). The function also sets a variable called timer_status to 1 to indicate that the timer is running.

The next part is a set of functions related to a timer implemented using an Arduino and an LCD screen.

The timer_enable function configures and enables a timer using the TivaWare library. It calls the TimerConfigure function to set the timer to periodic up-count mode, the TimerLoadSet function to set the timer's load value, and the TimerIntRegister function to register the timer interrupt handler function. It also enables the timer interrupt using the TimerIntEnable function and enables the timer using the TimerEnable function.

The timer_handler function is the timer interrupt handler function that is called when the timer reaches its load value. It clears the timer interrupt flag using the TIMER0_ICR_R register and calls the timer_counter function to update the timer's count. It also clears the LCD screen using the LCD_Cmd function with the clear_display parameter and disables the cursor on the LCD screen using the LCD_Cmd function with the cursorOff parameter.

The timer_counter function appears to be responsible for updating the timer's count and displaying it on the LCD screen. It likely takes two pointers as arguments (pointer_sec and pointer_min) to access the timer's minutes and seconds’ count.

I hope this helps clarify the purpose and functionality of these timer-related functions. Let me know if you have any questions.

Next function is the timer_counter function, which appears to be responsible for updating the timer's count and displaying it on the LCD screen. The function takes two integer arguments, y and z, which are likely used to store the timer's minutes and second’s count.

The function starts by moving the cursor to column 2 on the first line of the LCD screen and writing a colon (':') using the LCD_Write_Char function.

It then checks if the value of z is equal to 0. If it is, the function checks if the value of y is greater than 0. If it is, the function displays the current count on the LCD screen using the LCD_intgerToString function and the LCD_moveCursor function. It then decrements the value of y by 1. If the value of y is equal to 0, the function clears the LCD screen, prints the message "Done" on the first line, and disables the timer.

If the value of z is not equal to 0, the function displays the current count on the LCD screen in a similar way, but also checks if the value of y is less than 0. If it is, the function decrements the value of z by 1 and sets the value of y to 59.

The next function implements a stopwatch functionality in your code. The stopwatch_start() function initializes the timer and registers an interrupt handler function stopwatch_handler() which is called every time the timer "times out". The stopwatch_counter() function is called inside the stopwatch_handler() function and updates the display with the current stopwatch time, which is stored in two variables y and z (presumably representing seconds and minutes). The stopwatch_counter() function increments the seconds variable y and if it reaches 60, it resets y to 0 and increments the minutes variable z. It also updates the display with the current time by writing the appropriate digits to the LCD display.

It's worth noting that this code snippet is only a part of the stopwatch implementation, and other functions such as stopwatch_pause(), stopwatch_resume(), stopwatch_reset(), etc. might also be present in the full code.

These final functions appear to be used to stop and reset a timer and a stopwatch, respectively. The timer_end function unregisters, disables, and clears the interrupt for timer0, and it also clears the display and resets the values of timer_status, pointer_min, and pointer_sec to 0. The stopwatch_end function does the same for timer1 and also resets the values of pointer_stopwatch_min and pointer_stopwatch_sec to 0.
