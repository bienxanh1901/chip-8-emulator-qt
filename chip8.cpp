#include "chip8.h"
#include <QFile>

Chip8::Chip8():
    ram(RAM_AMOUNT, 0x00),
    pc(PROGRAM_START_ADDRESS)
{
    this->loadFont();

}

/**
 * @brief Chip8::loadROM
 * @param fileName path to chip8 program (instruction file)
 * @details Load a chip8 program to RAM.
 */
void Chip8::loadROM(QString &fileName)
{
    QByteArray newProgram = this->readFile(fileName);

    // clear Display
    this->clearDisplay();

    // Set PC to start address
    this->setPC(PROGRAM_START_ADDRESS);

    // Clear old program from RAM
    this->ram.replace(PROGRAM_START_ADDRESS, PROGRAM_MAX_SIZE, QByteArray(PROGRAM_MAX_SIZE, 0x00));

    // Load new program to RAM
    this->ram.replace(PROGRAM_START_ADDRESS, newProgram.size(), newProgram);
}

/**
 * @brief Chip8::loadFont
 * @details Load the font to RAM
 */
void Chip8::loadFont()
{
    for (quint16 i = 0; i < FONT_LENGTH; i++)
    {
        this->ram[i + FONT_START_ADDRESS] = font[i];
    }
}

/**
 * @brief Chip8::readFile
 * @param fileName: path to file
 * @return Bytes data of file
 * @details Read all bytes from a file
 */
QByteArray Chip8::readFile(QString &fileName)
{
    QFile file(fileName);
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        data = file.readAll();
        file.close();
    }

    return data;
}

/**
 * @brief Chip8::setPC
 * @param newAddress: New Memory (RAM) address
 * @details Set Program counter (PC) to new memory address
 */
void Chip8::setPC(quint16 newAddress)
{
    this->pc = newAddress;
}

/**
 * @brief Chip8::nextOpcode
 * @details Increase Program Counter (PC) by 2 to goto next opcode
 */
void Chip8::nextOpcode()
{
    this->pc+=2;
}

/**
 * @brief Chip8::fetch
 * @details Move Program Counter (PC) to next Opcode
 * @return 2 bytes Opcode
 */
opcode_bytes_t Chip8::fetch()
{
    // fetch opcode
    opcode_bytes_t bytes;
    bytes.first = this->ram[this->pc];
    bytes.second = this->ram[this->pc];

    // Then goto next opcode for next round
    this->nextOpcode();

    return bytes;
}

/**
 * @brief Chip8::decode
 * @param bytes: 2 bytes Opcode
 * @return Decoded Opcode
 * @details Decode Opcode to get type, data, ...
 */
Opcode Chip8::decode(opcode_bytes_t &bytes)
{
    Opcode opcode(bytes);
    return opcode;
}

/**
 * @brief Chip8::execute
 * @param opcode: Decoded opcode to be executed
 * @details Execute an opcode
 */
void Chip8::execute(Opcode &opcode)
{
    switch (opcode.type()) {
    case ZERO_OP:
        // 0NNN, 00E0, 00EE
        if (opcode.NN() == 0xE0)            // 00E0 - Clear display
        {
            this->clearDisplay();
        } else if (opcode.NN() == 0xEE)     // 00EE - Return from a subroutine
        {
            this->setPC(this->stack.pop());
        } else                              // 0NNN - Call machine code routine at address NNN
        {
            // Not be implemented
        }
        break;
    case JUMP_1:
        // 1NNN - Jump to address NNN
        this->setPC(opcode.NNN());
        break;
    case CALL_SUB:
        // 2NNN - Calls subroutine at NNN.
        this->stack.push(opcode.NNN());
        break;
    case VX_EQ_NN:
        // 3XNN - Skips the next instruction if VX equals NN
        if (this->registors[opcode.VX()] == opcode.NN())
        {
            this->nextOpcode();
        }
        break;
    case VX_NE_NN:
        // 4XNN - Skips the next instruction if VX does not equal NN.
        if (this->registors[opcode.VX()] != opcode.NN())
        {
            this->nextOpcode();
        }
        break;
    case VX_EQ_VY:
        // 5XY0 - Skips the next instruction if VX equals VY.
        if (this->registors[opcode.VX()] == this->registors[opcode.VY()])
        {
            this->nextOpcode();
        }
        break;
    case VX_SET_NN:
        // 6XNN - VX = NN.
        this->registors[opcode.VX()] = opcode.NN();
        break;
    case VX_ADD_NN:
        // 7XNN - VX+= NN (Carry flag is not changed);
        this->registors[opcode.VX()] += opcode.NN();
        break;
    case VXY_MATH:
        // 8XY{0, 1, 2, 3, 4, 5, 6, 7, E}
        this->executeMathOp(opcode);
        break;
    case VX_NE_VY:      // 9XY0 - Skips the next instruction if VX does not equal VY.
        break;
    case I_SET_NNN:     // ANNN - I = NNN
        break;
    case JUMP_B:        // BNNN - Jumps to the address NNN plus V0.
        break;
    case VX_RAND:       // CXNN - VX = RAND() & NN
        break;
    case DRAW_SPRITE:   // DXYN - Draws a sprite at coordinate (VX, VY)
        break;
    case KEY_OP:        // EX9E, EXA1
        break;
    case F_OP:          // FX{07, 0A, 15, 18, 1E, 29, 33, 55, 65}
        break;
    }
}

void Chip8::executeMathOp(Opcode &opcode)
{
    quint8 &VX = this->registors[opcode.VX()];
    quint8 &VY = this->registors[opcode.VX()];
    quint8 &VF = this->registors[NUM_REGS - 1];

    switch (opcode.N()) {
    case VXY_SET:
        // 8XY0 - Sets VX to the value of VY.
        VX = VY;
        break;
    case VXY_OR:
        // 8XY1 - Sets VX to VX or VY. (Bitwise OR operation).
        VX|= VY;
        break;
    case VXY_AND:
        // 8XY2 - Sets VX to VX and VY. (Bitwise AND operation).
        VX&= VY;
        break;
    case VXY_XOR:
        // 8XY3 - Sets VX to VX xor VY. (Bitwise XOR operation).
        VX^= VY;
        break;
    case VXY_ADD:
        // 8XY4 - Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there is not.
        if (VX + VY > 255)
        {
            VF = 0x01;
        }
        VX+= VY;
        break;
    case VXY_SUB:
        // 8XY5 - VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there is not.
        if (VX >= VY)
        {
            VF = 0x01;
        }
        VX-= VY;
        break;
    case VXY_LSB:
        // 8XY6 - Stores the least significant bit of VX in VF and then shifts VX to the right by 1.
        VX>>= 1;
        VF = VX & 1;
        break;
    case VXY_MINUS:
        // 8XY7 - Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there is not.
        if (VY >= VX)
        {
            VF = 0x01;
        }
        VX = VY - VX;
        break;
    case VXY_MSB:
        // 8XYE - Stores the most significant bit of VX in VF and then shifts VX to the left by 1.
        VX<<= 1;
        VF = VX & 1; // @TODO
        break;
        break;
    }
}

/**
 * @brief Chip8::clearDisplay
 * @details Clear screen
 */
void Chip8::clearDisplay()
{
    for (quint8 i = 0; i < HEIGHT; i++)
    {
        for (quint8 j = 0; j < WIDTH; j++)
        {
            this->screenPixels[i][j] = false;
        }
    }
}

void Chip8::clearRegistor()
{
    for (auto &reg : this->registors)
    {
        reg = 0x00;
    }
}
