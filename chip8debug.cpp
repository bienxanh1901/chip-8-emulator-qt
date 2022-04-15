#include <QDebug>
#include "chip8emulator.h"


void Chip8Emulator::debug(Opcode &code)
{
    qDebug() << "Opcode =" << Qt::hex << code.data;
    qDebug() << "   |----Type=" << Qt::hex << code.type;
    qDebug() << "   |----N   =" << Qt::hex << code.n;
    qDebug() << "   |----NN  =" << Qt::hex << code.nn;
    qDebug() << "   |----NNN =" << Qt::hex << code.nnn;
    qDebug() << "   |----X   =" << Qt::hex << code.x;
    qDebug() << "   |----Y   =" << Qt::hex << code.y;

    qDebug() << "Variable Registors:";
    qDebug() << "   |----V0  =" << Qt::hex << this->varRegs[0];
    qDebug() << "   |----V1  =" << Qt::hex << this->varRegs[1];
    qDebug() << "   |----V2  =" << Qt::hex << this->varRegs[2];
    qDebug() << "   |----V3  =" << Qt::hex << this->varRegs[3];
    qDebug() << "   |----V4  =" << Qt::hex << this->varRegs[4];
    qDebug() << "   |----V5  =" << Qt::hex << this->varRegs[5];
    qDebug() << "   |----V6  =" << Qt::hex << this->varRegs[6];
    qDebug() << "   |----V7  =" << Qt::hex << this->varRegs[7];
    qDebug() << "   |----V8  =" << Qt::hex << this->varRegs[8];
    qDebug() << "   |----V9  =" << Qt::hex << this->varRegs[9];
    qDebug() << "   |----V10 =" << Qt::hex << this->varRegs[10];
    qDebug() << "   |----V11 =" << Qt::hex << this->varRegs[11];
    qDebug() << "   |----V12 =" << Qt::hex << this->varRegs[12];
    qDebug() << "   |----V13 =" << Qt::hex << this->varRegs[13];
    qDebug() << "   |----V14 =" << Qt::hex << this->varRegs[14];
    qDebug() << "   |----V15 =" << Qt::hex << this->varRegs[15];

    qDebug() << "Program Counter PC = " << Qt::hex << this->pc;
    qDebug() << "opcode start: " << Qt::hex << this->ram[this->pc];
    qDebug() << "Index Registor: I = " << Qt::hex << this->idxReg;
    qDebug() << "Delay Timer: DTm = " << Qt::hex << this->delayTimer;
    qDebug() << "Sound Timer: STm = " << Qt::hex << this->soundTimer;
    qDebug() << "================================================";

}
