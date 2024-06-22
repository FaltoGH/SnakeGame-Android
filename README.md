# SnakeGame-Android

## Introduction
This is mobile system programming with a smart tablet device board.

It uses custom hardware on the right-hand side of the board (FPGA board)

To reduce development time, we forked [SnakeGame-Android](https://github.com/YangDai2003/SnakeGame-Android) and did work on it.

We focused hardware control part than software.

We used JNI to call C/C++ function to control fpga devices.

[Demo YouTube clip](https://youtube.com/watch?v=HBxpRqMa0Ok)

## Features

### LED
The snake's length is synchronized with the number of led turned on.

Since snake's default length is 3, the number of led turned on is determined on `length - 3`.

![led](images/led.png)

### 7-segment
7-segment LEDs display current score.

![segment](images/segment.png)

### Dip switch
The number of dip switch on is synchronized with the number of barrier blocks. (But when you enter setting page, it is automatically set to two of multiple. That's why the number of barrier blocks 4 mismatches the number of dip switch on 5 in the picture. Anyway, it's not a big deal.)


![dipsw](images/dipsw.png)

### Keypad
The keypad is the main controller of snake. The other keys is not recognized by device driver(-), or its behavior is undefined(x).


![keypad](images/keypad.png)

### Full Color LED
- It becomes red whenever the snake eats red food.

- It becomes yellow whenever the snake eats yellow food.

![fled](images/fled.png)

### Dot Matrix
It displays the user's high score if all following conditions are true:
- Previous highscore is less than current score. That is, the user recorded new high score.
- Game over.

![dotmatrix](images/dotmatrix.png)
