#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtGlobal>
#include <QByteArray>

// Memory definition
#define RAM_AMOUNT 0x1000
#define FONT_LENGTH 0x050
#define FONT_START_ADDRESS 0x050
#define PROGRAM_START_ADDRESS 0x200
#define PROGRAM_MAX_SIZE 0xE00

// Screen definition
#define WIDTH 32
#define HEIGHT 64

// Registor
#define NUM_REGS 16


// Opcode instruction type definition
/*
NNN: address
NN: 8-bit constant
N: 4-bit constant
X and Y: 4-bit register identifier
PC : Program Counter
I : 16bit register (For memory address) (Similar to void pointer);
VN: One of the 16 available variables. N may be 0 to F (hexadecimal);
*/

/*
0NNN - Call machine code routine at address NNN
00E0 - Clear display
00EE - Return from a subroutine
1NNN - Jump to address NNN
2NNN - Calls subroutine at NNN.
3XNN - Skips the next instruction if VX equals NN
4XNN - Skips the next instruction if VX does not equal NN.
5XY0 - Skips the next instruction if VX equals VY.
6XNN - Sets VX to NN.
7XNN - Adds NN to VX. (Carry flag is not changed);
8XY0 - Sets VX to the value of VY.
8XY1 - Sets VX to VX or VY. (Bitwise OR operation).
8XY2 - Sets VX to VX and VY. (Bitwise AND operation).
8XY3 - Sets VX to VX xor VY. (Bitwise XOR operation).
8XY4 - Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there is not.
8XY5 - VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there is not.
8XY6 - Stores the least significant bit of VX in VF and then shifts VX to the right by 1.
8XY7 - Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there is not.
8XYE - Stores the most significant bit of VX in VF and then shifts VX to the left by 1.
9XY0 - Skips the next instruction if VX does not equal VY. (Usually the next instruction is a jump to skip a code block);
ANNN - Sets I to the address NNN.
BNNN - Jumps to the address NNN plus V0.
CXNN - Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
DXYN - Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels.
EX9E - Skips the next instruction if the key stored in VX is pressed.
EXA1 - Skips the next instruction if the key stored in VX is not pressed.
FX07 - Sets VX to the value of the delay timer.
FX0A - A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event);
FX15 - Sets the delay timer to VX.
FX18 - Sets the sound timer to VX.
FX1E - Adds VX to I. VF is not affected.
FX29 - Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
FX33 - Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.);
FX55 - Stores from V0 to VX (including VX) in memory, starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
FX65 - Fills from V0 to VX (including VX) with values from memory, starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
*/


enum InstructionTypes {
    ZERO_OP = 0x00,
    JUMP_1 = 0x01,
    CALL_SUB = 0x02,
    VX_EQ_NN = 0x03,
    VX_NE_NN = 0x04,
    VX_EQ_VY = 0x05,
    VX_SET_NN = 0x06,
    VX_ADD_NN = 0x07,
    VXY_MATH  = 0x08,
    VX_NE_VY = 0x09,
    I_SET_NNN = 0x0A,
    JUMP_B = 0x0B,
    VX_RAND = 0x0C,
    DRAW_SPRITE = 0x0D,
    KEY_OP = 0x0E,
    F_OP = 0x0F
};


enum MathOpcode {
    VXY_SET = 0x00,
    VXY_OR = 0x01,
    VXY_AND = 0x02,
    VXY_XOR = 0x03,
    VXY_ADD = 0x04,
    VXY_SUB = 0x05,
    VXY_LSB = 0x06,
    VXY_MINUS = 0x07,
    VXY_MSB = 0x0E
};

enum KeyOpcode {
    KEY_PRESSED = 0x9E,
    KEY_NOT_PRESSED = 0xA1
};

enum FOpcode {
    SET_DELAY_TIMER = 0x07,
    VX_WAIT_KEY_PRESSED = 0x0A,
    VX_SET_BY_DELAY_TIMER = 0x15,
    VX_SET_BY_SOUND_TIMER = 0x18,
    I_ADD_VX = 0x1E,
    I_SET_BY_SPRITE_ADDR = 0x29,
    I_STORE_BCD = 0x33,
    REG_DUMP = 0x55,
    REG_LOAD = 0x65
};

const quint8 font[FONT_LENGTH] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


#endif // CONSTANTS_H
