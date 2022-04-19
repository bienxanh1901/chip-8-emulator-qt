#include <QCoreApplication>
#include <QRandomGenerator>
#include "chip8emulator.h"


/**
 * @brief Chip8Emulator::execute
 * @param code Current Opcode
 * @details Execute an opcode
 */
void Chip8Emulator::OpcodeHandler(Opcode &code)
{
    switch (code.type) {
    case 0x00: // 00EE - 00E0 - 0NNN
        this->opcode0Handler(code);
        break;
    case 0x01: // 1NNN
        this->opcode1Handler(code);
        break;
    case 0x02: // 2NNN
        this->opcode2Handler(code);
        break;
    case 0x03: // 3XNN
        this->opcode3Handler(code);
        break;
    case 0x04: // 4XNN
        this->opcode4Handler(code);
        break;
    case 0x05: // 5XY0
        this->opcode5Handler(code);
        break;
    case 0x06: // 6XNN.
        this->opcode6Handler(code);
        break;
    case 0x07: // 7XNN
        this->opcode7Handler(code);
        break;
    case 0x08: // 8XY{0, 1, 2, 3, 4, 5, 6, 7, E}
        this->opcode8Handler(code);
        break;
    case 0x09: // 9XY0
        this->opcode9Handler(code);
        break;
    case 0x0A: // ANNN
        this->opcodeAHandler(code);
        break;
    case 0x0B: // BNNN
        this->opcodeBHandler(code);
        break;
    case 0x0C:// CXNN
        this->opcodeCHandler(code);
        break;
    case 0x0D: // DXYN
        this->opcodeDHandler(code);
        break;
    case 0x0E: // EX9E, EXA1
        this->opcodeEHandler(code);
        break;
    case 0x0F: // FX{07, 0A, 15, 18, 1E, 29, 33, 55, 65}
        this->opcodeFHandler(code);
        break;
    }
}

/**
 * @brief Chip8Emulator::opcode0Handler
 * @param code
 * @details Handle 3 opcodes: 0NNN, 00E0, 00EE
 *   - 0NNN - Call machine code routine at address NNN
 *   - 00E0 - Clear display
 *   - 00EE - Return from a subroutine
 */
void Chip8Emulator::opcode0Handler(Opcode &code)
{
    if (code.nn == 0xEE)
    {
        this->setPC(this->stack.pop());
    }
    else if (code.nn == 0xE0)
    {
        this->clearDisplay();
    }
    else
    {
        // Not be implemented
    }
}

/**
 * @brief Chip8Emulator::opcode1Handler
 * @param code
 * @details Handle opcode 1NNN - Jump to address NNN.
 */
void Chip8Emulator::opcode1Handler(Opcode &code)
{
    this->setPC(code.nnn);
}

/**
 * @brief Chip8Emulator::opcode2Handler
 * @param code
 * @details Handle opcode 2NNN - Calls subroutine at NNN.
 */
void Chip8Emulator::opcode2Handler(Opcode &code)
{
    this->stack.push(this->pc);
    this->setPC(code.nnn);
}

/**
 * @brief Chip8Emulator::opcode3Handler
 * @param code
 * @details Handle opcode 3XNN - Skips the next instruction if VX equals NN.
 */
void Chip8Emulator::opcode3Handler(Opcode &code)
{
    if (this->varRegs[code.x] == code.nn)
    {
        this->nextOpcode();
    }
}

/**
 * @brief Chip8Emulator::opcode4Handler
 * @param code
 * @details Handle opcode 4XNN - Skips the next instruction if VX does not equal NN.
 */
void Chip8Emulator::opcode4Handler(Opcode &code)
{
    if (this->varRegs[code.x] != code.nn)
    {
        this->nextOpcode();
    }
}

/**
 * @brief Chip8Emulator::opcode5Handler
 * @param code
 * @details Handle opcode 5XY0 - Skips the next instruction if VX equals VY.
 */
void Chip8Emulator::opcode5Handler(Opcode &code)
{
    if (this->varRegs[code.x] == this->varRegs[code.y])
    {
        this->nextOpcode();
    }
}

/**
 * @brief Chip8Emulator::opcode6Handler
 * @param code
 * @details Handle opcode 6XNN - Sets VX to NN.
 */
void Chip8Emulator::opcode6Handler(Opcode &code)
{
    this->varRegs[code.x] = code.nn;
}

/**
 * @brief Chip8Emulator::opcode7Handler
 * @param code
 * @details Handle opcode 7XNN - Adds NN to VX. (Carry flag is not changed).
 */
void Chip8Emulator::opcode7Handler(Opcode &code)
{
    this->varRegs[code.x]+= code.nn;
}

/**
 * @brief Chip8Emulator::opcode8Handler
 * @param code
 * @details Handle 9 opcodes:
 *  - 8XY0 - Sets VX to the value of VY.
 *  - 8XY1 - Sets VX to VX or VY. (Bitwise OR operation).
 *  - 8XY2 - Sets VX to VX and VY. (Bitwise AND operation).
 *  - 8XY3 - Sets VX to VX xor VY. (Bitwise XOR operation).
 *  - 8XY4 - Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there is not.
 *  - 8XY5 - VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there is not.
 *  - 8XY6 - Stores the least significant bit of VX in VF and then shifts VX to the right by 1.
 *  - 8XY7 - Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there is not.
 *  - 8XYE - Stores the most significant bit of VX in VF and then shifts VX to the left by 1.
 */
void Chip8Emulator::opcode8Handler(Opcode &code)
{
    quint8 &VX = this->varRegs[code.x];
    quint8 &VY = this->varRegs[code.y];
    quint8 &VF = this->varRegs[0x0F];

    switch (code.n) {
    case VXY_SET: // 8XY0
        VX = VY;
        break;
    case VXY_OR: // 8XY1
        VX|= VY;
        break;
    case VXY_AND: // 8XY2
        VX&= VY;
        break;
    case VXY_XOR: // 8XY3
        VX^= VY;
        break;
    case VXY_ADD: // 8XY4
    {
        quint8 tmp = VX + VY;
        if (VX > tmp)
        {
            VF = 0x01;  // carry
        } else
        {
            VF = 0x00;
        }
        VX = tmp;
    }
        break;
    case VXY_SUB: // 8XY5
        if (VX >= VY)
        {
            VF = 0x01;
        } else
        {
            VF = 0x00; // borrow
        }

        VX-= VY;
        break;
    case VXY_LSB: // 8XY6
        VF = VX & 1;
        VX>>= 1;
        break;
    case VXY_MINUS: // 8XY7
        if (VY >= VX)
        {
            VF = 0x01;
        } else
        {
            VF = 0x00; // borrow
        }
        VX = VY - VX;
        break;
    case VXY_MSB: // 8XYE
        VF = VX >> 7;
        VX<<= 1;
        break;
    }
}

/**
 * @brief Chip8Emulator::opcode9Handler
 * @param code
 * @details Handle opcode 9XY0 - Skips the next instruction if VX does not equal VY
 */
void Chip8Emulator::opcode9Handler(Opcode &code)
{
    if (this->varRegs[code.x] != this->varRegs[code.y])
    {
        this->nextOpcode();
    }
}

/**
 * @brief Chip8Emulator::opcodeAHandler
 * @param code
 * @details Handle opcode ANNN - Sets I to the address NNN.
 */
void Chip8Emulator::opcodeAHandler(Opcode &code)
{
    this->idxReg = code.nnn;
}

/**
 * @brief Chip8Emulator::opcodeBHandler
 * @param code
 * @details Handle opcode BNNN - Jumps to the address NNN plus V0.
 */
void Chip8Emulator::opcodeBHandler(Opcode &code)
{
    this->setPC(code.nnn + this->varRegs[0]);
}

/**
 * @brief Chip8Emulator::opcodeCHandler
 * @param code
 * @details Handle opcode CXNN - Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
 */
void Chip8Emulator::opcodeCHandler(Opcode &code)
{
    this->varRegs[code.x] = (QRandomGenerator::global()->generate()%255) & code.nn;
}

/**
 * @brief Chip8Emulator::opcodeDHandler
 * @param code
 * @details Handle opcode DXYN - Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels.
 */
void Chip8Emulator::opcodeDHandler(Opcode &code)
{
    this->draw(this->varRegs[code.x], this->varRegs[code.y], code.n);
}

/**
 * @brief Chip8Emulator::opcodeEHandler
 * @param code
 * @details Handle 2 opcodes:
 *  - EX9E - Skips the next instruction if the key stored in VX is pressed.
 *  - EXA1 - Skips the next instruction if the key stored in VX is not pressed.
 */
void Chip8Emulator::opcodeEHandler(Opcode &code)
{
    if (code.nn == 0x9E)
    {
        if (this->varRegs[code.x] == this->currKey)
        {
            this->nextOpcode();
        }
    } else if (code.nn == 0xA1)
    {
        if (this->varRegs[code.x] != this->currKey)
        {
            this->nextOpcode();
        }
    }
}

/**
 * @brief Chip8Emulator::opcodeFHandler
 * @param code
 * @details Handle 9 opcodes
 *  - FX07 - Sets VX to the value of the delay timer.
 *   - FX0A - A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event);
 *   - FX15 - Sets the delay timer to VX.
 *   - FX18 - Sets the sound timer to VX.
 *   - FX1E - Adds VX to I. VF is not affected.
 *   - FX29 - Sets I to the location of the sprite for the character in VX.
 *            Characters 0-F (in hexadecimal) are represented by a 4x5 font.
 *   - FX33 - Stores the binary-coded decimal representation of VX.
 *   - FX55 - Stores from V0 to VX (including VX) in memory, starting at address I.
 *   - FX65 - Fills from V0 to VX (including VX) with values from memory, starting at address I.
 */
void Chip8Emulator::opcodeFHandler(Opcode &code)
{
    quint8 &VX = this->varRegs[code.x];

    switch (code.nn) {
    case GET_DELAY_TM: // FX07
        VX = this->delayTM;
        break;
    case WAIT_KEY: // FX0A
        VX = this->waitKey();
        break;
    case SET_DELAY_TM: // FX15
        this->delayTM = VX;
        break;
    case SET_SOUND_TM: // FX18
        this->soundTM = VX;
        //TODO enable sound
        break;
    case I_ADD_VX: // FX1E
        this->idxReg+= VX;
        break;
    case I_SET_SPRITE_ADDR: // FX29
        this->idxReg = VX*5 + FONT_START_ADDRESS;
        break;
    case BCD_STORE:// FX33
        this->BCDStorage(VX);
        break;
    case REG_DUMP: // FX55
        this->regDump(code.x);
        break;
    case REG_LOAD: // FX65
        this->regLoad(code.x);
        break;
    }
}

/**
 * @brief Chip8Emulator::waitKey
 * @return key pressed
 * @details Wait for a key pressed (block all operations)
 */
quint8 Chip8Emulator::waitKey()
{
    quint8 key = 0xff;
    while (true) {
        QCoreApplication::processEvents();
        if (this->currKey != 0xff)
        {
            key = this->currKey;
            this->currKey = 0xff;
            return key;
        }
    }
}

/**
 * @brief Chip8Emulator::clearDisplay
 * @details Clear screen display
 */
void Chip8Emulator::clearDisplay()
{
    for (quint8 &i : this->display)
    {
        i = 0;
    }

    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, 0), QVector<int>() << PixelRole);
}

/**
 * @brief Chip8Emulator::draw
 * @param x0 Start X
 * @param y0 Start Y
 * @param h  height
 * @details Draw sprites to screen
 */
void Chip8Emulator::draw(quint8 x0, quint8 y0, quint8 h)
{
    // Set VF to 0
    this->varRegs[0x0F] = 0;
    quint16 spriteIdx = this->idxReg;

    for (quint16 y = 0; y < h; y++, spriteIdx++)
    {
        quint8 sprite = this->ram.at(spriteIdx);
        quint16 idx = 0;

        for (quint8 x = 0; x < 8; x++)
        {

            idx = (y + y0)%HEIGHT*WIDTH + (x + x0)%WIDTH;

            if (((sprite >> (7 - x)) & 1) != 0)
            {
                if (!this->varRegs[0x0F] && this->display[idx])
                {
                    this->varRegs[0x0F] = 1;
                }

                this->display[idx] ^= 1;
            }
        }
    }

    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, 0), QVector<int>() << PixelRole);
}

/**
 * @brief Chip8Emulator::regDump
 * @param x number Registers
 * @details store value of registor from V0 to Vx into RAM
 */
void Chip8Emulator::regDump(quint8 x)
{
    quint16 start = this->idxReg;
    for (quint8 i = 0; i <= x; i++)
    {
        this->ram[start + i] = this->varRegs[i];
    }
}

/**
 * @brief Chip8Emulator::regLoad
 * @param x number Registers
 * @details load value of registors (V0 to Vx) from RAM
 */
void Chip8Emulator::regLoad(quint8 x)
{
    quint16 start = this->idxReg;
    for (quint8 i = 0; i <= x; i++)
    {
         this->varRegs[i] = this->ram[start + i];
    }
}

/**
 * @brief Chip8Emulator::BCDStorage
 * @param val
 * @details calculate BCD and store to RAM
 */
void Chip8Emulator::BCDStorage(quint8 val)
{
    for (int i = 2; i >= 0; i--)
    {
        this->ram[this->idxReg + i] = val%10;
        val/=10;
    }
}

/**
 * @brief Chip8Emulator::timerHandler
 * @details Handle timers (60Hz)
 */
void Chip8Emulator::timerHandler()
{
    if(this->clockCounter%TIMER_PERIOD == 0)
    {
        // delay timer
        if (this->delayTM > 0) {
            this->delayTM--;
        }

        // sound timer
        if (this->soundTM > 0)
        {
            this->soundTM--;
        } else
        {
            // TODO disable beep
        }
    }
}
