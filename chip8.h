#ifndef CHIP8_H
#define CHIP8_H

#include "constants.h"
#include "opcode.h"
#include <QByteArray>
#include <QStack>
#include <QTimer>

class Chip8
{
public:
    Chip8();

private:
    void loadROM(QString &fileName);
    void loadFont();
    QByteArray readFile(QString &fileName);
    void setPC(quint16 newAddress);
    void nextOpcode();
    opcode_bytes_t fetch();
    Opcode decode(opcode_bytes_t &bytes);
    void execute(Opcode &opcode);
    void executeMathOp(Opcode &opcode);
    void clearDisplay();
    void clearRegistor();


private:
    // RAM with 4096 bytes
    QByteArray ram;
    // display 64x32 pixels
    bool screenPixels[HEIGHT][WIDTH] = {{false}};
    // Program counter (PC)
    quint16 pc;
    // 16-bit registor (I)
    quint16 memoryRegistor = 0;
    // 16-bit stack
    QStack<quint16> stack;
    // 16 8-bit registors (V0 -> VF)
    quint8 registors[NUM_REGS] = {0};
    // Delay timer
    QTimer delayTimer;
    QTimer soundTimer;
};

#endif // CHIP8_H
