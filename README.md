# Pong Game with PIC16F877A and MAX7219

This project implements a basic Pong game using a PIC16F877A microcontroller and a MAX7219 LED driver to display the game on an 8x8 LED matrix. The game features two players who control paddles to hit a ball back and forth.

## Project Overview

### Hardware Components

- **Microcontroller**: PIC16F877A
- **LED Driver**: MAX7219
- **LED Matrix**: 8x8 LED matrix
- **Buttons**: Four buttons for controlling the paddles (two for each player)
- **Oscillator**: 20MHz crystal oscillator

### Circuit Diagram

![Circuit Diagram](.\proteusFiles\proteusPinSchema.png)

The circuit diagram shows the connections between the PIC16F877A, the MAX7219, the buttons, and the LED matrix. The buttons are connected to PORTB of the PIC16F877A, while the MAX7219 is connected to PORTC.

### Pin Configuration

- **Player 1 Up**: RB0
- **Player 1 Down**: RB1
- **Player 2 Up**: RB2
- **Player 2 Down**: RB3

### Software Implementation

The software is written in C and compiled using MPLAB X IDE with the XC8 compiler. The main components of the software include:

- **Initialization**: Sets up the microcontroller and initializes the game state.
- **Button Reading**: Reads the state of the buttons to control the paddles.
- **Game Logic**: Updates the positions of the paddles and the ball, and checks for collisions and scores.
- **Display Update**: Updates the LED matrix to reflect the current game state.

## Getting Started

### Prerequisites

- MPLAB X IDE
- XC8 Compiler
- PICkit or other compatible programmer

### Installing

1. **Clone the Repository**:
    ```sh
    git clone https://github.com/icelal-kskn/PicPong.git
    cd PicPong/src
    ```

2. **Open the Project**:
    - Open MPLAB X IDE.
    - Navigate to `File -> Open Project`.
    - Select the `PicPong` project file.

3. **Build the Project**:
    - Click on the build icon or press `F11` to compile the project.

4. **Program the Microcontroller**:
    - Connect your PICkit (or other programmer) to the PIC16F877A.
    - Click on the "Make and Program Device" icon or press `Shift + F11`.

### Running the Game

1. **Power the Circuit**: Ensure the circuit is properly powered.
2. **Start Playing**: Use the buttons to control the paddles. Player 1 uses RB0 (up) and RB1 (down), and Player 2 uses RB2 (up) and RB3 (down).

### Code Explanation

- **Initialization**: 
    ```c
    void initGame() {
        ballX = 4;
        ballYState = Row4;
        MAX7219_write(8, No_Light);
        MAX7219_write(1, No_Light);
        MAX7219_write(7, p1State);
        MAX7219_write(2, p2State);
        MAX7219_write(ballX, ballYState);
        isScore = false;
    }
    ```

- **Button Handling**: 
    ```c
    int readButton0() {
        return Player1_up_pin;
    }
    
    int readButton1() {
        return Player1_down_pin;
    }
    
    int readButton2() {
        return Player2_up_pin;
    }
    
    int readButton3() {
        return Player2_down_pin;
    }
    ```

- **Game Update Loop**:
    ```c
    while (!isScore) {
        if (readButton0() == 1) {
            buttonGoUp(1);
        }
        if (readButton1() == 1) {
            buttonGoDown(1);
        }
        if (readButton2() == 1) {
            buttonGoUp(2);
        }
        if (readButton3() == 1) {
            buttonGoDown(2);
        }
        __delay_ms(5);
        updateBallPosition();
    }
    ```

## Project Contributiors

 - [İkram Celal KESKİN 200316059](https://github.com/icelal-kskn)
 - [Musa Sina ERTUĞRUL ?](https://github.com/?)
 - 

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to the developers of the MPLAB X IDE and XC8 compiler.
- Special thanks to the community for their support and resources.