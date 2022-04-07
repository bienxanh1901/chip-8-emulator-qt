#include <QFile>
#include <QRandomGenerator>
#include <QCoreApplication>
#include <QDebug>
#include "chip8emulator.h"
#include "common.h"


Chip8Emulator::Chip8Emulator(QObject *parent)
    : QAbstractListModel(parent),
      ram(RAM_AMOUNT, 0x00),
      CPUTimer()
{
    this->init();
}

int Chip8Emulator::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return WIDTH*HEIGHT;
}

QVariant Chip8Emulator::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch (role) {
    case Roles::PixelRole:
        return this->display[index.row()];
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Chip8Emulator::roleNames() const
{
    return {{Roles::PixelRole, "status"}};
}

void Chip8Emulator::pause()
{
    this->CPUTimer.stop();
    // TODO disable beep
}

void Chip8Emulator::resume()
{
    this->CPUTimer.start();
    // TODO enable beep

}

void Chip8Emulator::restart()
{
    this->clear();
    this->CPUTimer.start();
}

void Chip8Emulator::init()
{
    // Load font
    this->loadFont();
    // running timer
    this->CPUTimer.setInterval(RUNNING_SPEED);
    connect(&this->CPUTimer, &QTimer::timeout, this, &Chip8Emulator::run);
}

void Chip8Emulator::loadFont()
{
    for (quint16 i = 0; i < FONT_LENGTH; i++)
    {
        this->ram[i + FONT_START_ADDRESS] = font[i];
    }
}

void Chip8Emulator::setPC(quint16 addr)
{
    this->pc = addr;
}

void Chip8Emulator::nextOpcode()
{
    this->pc+= 2;
}

void Chip8Emulator::clear()
{
    this->pause();
    this->clearRegs();
    this->clearIdxReg();
    this->clearDisplay(); // clear current Display
    this->setPC(PROGRAM_START_ADDRESS); // Set PC to start address
    this->delayTimer = 0;
    this->soundTimer = 0;
    this->clockCounter = 0;
}

void Chip8Emulator::run()
{
    // handle timer
    this->clockCounter++;
    // run step by step
    quint16 bytes = this->fetch();
    Opcode opcode = this->decode(bytes);
    this->execute(opcode);
    // handle timer
    this->timerHandler();
}

void Chip8Emulator::setCurrKeyPressed(quint8 newCurrKeyPressed)
{
    currKey = newCurrKeyPressed;
}

void Chip8Emulator::loadProgram(QString &rom)
{
    QString path(fileUrlToPath(rom));
    this->clear();
    if (this->loadROM(path))
    {
        this->CPUTimer.start();
    }
}

bool Chip8Emulator::loadROM(QString &rom)
{

    QByteArray data;
    if (readFile(rom, data))
    {
        // clear RAM
        this->ram.replace(PROGRAM_START_ADDRESS, this->romSize, QByteArray(this->romSize, 0x00));
        // load ROM to RAM
        this->romSize = data.size();
        this->ram.replace(PROGRAM_START_ADDRESS, this->romSize, data);
        return true;
    } else {
        // TODO handle error
        qDebug() << "Load ROM Failed";
        return false;
    }
}

quint16 Chip8Emulator::fetch()
{
    QByteArray bytes = this->ram.mid(this->pc, 2);
    QDataStream dataStream(bytes);
    quint16 opcode;
    dataStream >> opcode;
    this->nextOpcode();
    return opcode;
}

Opcode Chip8Emulator::decode(quint16 &bytes)
{
    return Opcode(bytes);
}

void Chip8Emulator::execute(Opcode &code)
{
    switch (code.type) {
    case ZERO_OP: // 00EE - 00E0 - 0NNN
        if (code.nn == 0xEE)
        {
            this->setPC(this->stack.pop());
            qDebug() << "Jump to " << this->pc;
        }
        else if (code.nn == 0xE0)
        {
            this->clearDisplay();
            qDebug() << "Clear Display";
        }
        else
        {
            // Not implemented
        }
        break;
    case JUMP_1: // 1NNN
        this->setPC(code.nnn);
        qDebug() << "Set PC = " << code.nnn;
        break;
    case CALL_SUB: // 2NNN
        this->stack.push(this->pc);
        this->setPC(code.nnn);
        qDebug() << "Call subroutine at " << code.nnn;
        break;
    case VX_EQ_NN: // 3XNN
        if (this->varRegs[code.x] == code.nn)
        {
            this->nextOpcode();
            qDebug() << "Skip next Opcode 3XNN " << "V[" << code.x << "] ==" << code.nn;
        }
        break;
    case VX_NE_NN: // 4XNN
        if (this->varRegs[code.x] != code.nn)
        {
            this->nextOpcode();
            qDebug() << "Skip next Opcode 4XNN " << "V[" << code.x << "] !=" << code.nn;
        }
        break;
    case VX_EQ_VY: // 5XY0
        if (this->varRegs[code.x] == this->varRegs[code.y])
        {
            this->nextOpcode();
            qDebug() << "Skip next Opcode 5XNN " << "V[" << code.x << "] !=" << "V[" << code.y << "]";
        }
        break;
    case VX_SET_NN: // 6XNN.
        this->varRegs[code.x] = code.nn;
        qDebug() << "Set V[" << code.x << "] = " << code.nn;
        break;
    case VX_ADD_NN: // 7XNN
        this->varRegs[code.x]+= code.nn;
        qDebug() << "V[" << code.x << "] += " << code.nn;
        break;
    case VXY_MATH: // 8XY{0, 1, 2, 3, 4, 5, 6, 7, E}
        this->opcode8Handler(code);
        break;
    case VX_NE_VY: // 9XY0
        if (this->varRegs[code.x] != this->varRegs[code.y])
        {
            this->nextOpcode();
            qDebug() << "Skip next Opcode 9XY0";
        }
        break;
    case I_SET_NNN: // ANNN
        this->idxReg = code.nnn;
        qDebug() << "I = " << code.nnn;
        break;
    case JUMP_B: // BNNN
        this->setPC(code.nnn + this->varRegs[0]);
        qDebug() << "PC = " << this->pc;
        break;
    case VX_RAND:// CXNN
        this->varRegs[code.x] = (QRandomGenerator::global()->generate()%255) & code.nn;
        qDebug() << "V[" << code.x << "] += " << this->varRegs[code.x];
        break;
    case DRAW_SPRITE: // DXYN
        this->draw(this->varRegs[code.x], this->varRegs[code.y], code.n);
        qDebug() << " Draws (x, y, h) = (" << this->varRegs[code.x] << ", " << this->varRegs[code.y] << ", " << code.n << ")";
        break;
    case E_OP: // EX9E, EXA1
        if (code.nn == 0x9E)
        {
            if (this->varRegs[code.x] == this->currKey)
            {
                this->nextOpcode();
                qDebug() << "Skip next Opcode EX9E";
            }
        } else if (code.nn == 0xA1)
        {
            if (this->varRegs[code.x] != this->currKey)
            {
                this->nextOpcode();
                qDebug() << "Skip next Opcode EXA1";
            }
        }
        break;
    case F_OP: // FX{07, 0A, 15, 18, 1E, 29, 33, 55, 65}
        this->opcodeFHandler(code);
        break;
    }
}

void Chip8Emulator::clearRegs()
{
    for (auto &reg : this->varRegs)
    {
        reg = 0x00;
    }
}

void Chip8Emulator::clearIdxReg()
{
    this->idxReg = 0x00;
}

void Chip8Emulator::clearDisplay()
{
    for (quint8 &i : this->display)
    {
        i = 0;
    }

    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, 0), QVector<int>() << PixelRole);
}

void Chip8Emulator::draw(quint8 x0, quint8 y0, quint8 h)
{
    // Ensure x is in range [0, 63]
    x0&=(WIDTH - 1);
    // Ensure y is in range [0, 31]
    y0&=(HEIGHT - 1);

    // Set VF to 0
    this->varRegs[0x0F] = 0;
    quint16 spriteIdx = this->idxReg;

    for (quint16 y = 0; y < h; y++, spriteIdx++)
    {
        quint8 sprite = this->ram.at(spriteIdx);
        quint16 idx = (y + y0)*WIDTH + x0;

        for (quint8 col = 0; col < 8; col++, idx++)
        {
            quint8 pixel = ((sprite >> (7 - col)) & 1);

            if (pixel)
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

void Chip8Emulator::opcode8Handler(Opcode &code)
{
    quint8 &VX = this->varRegs[code.x];
    quint8 &VY = this->varRegs[code.y];
    quint8 &VF = this->varRegs[0x0F];

    switch (code.n) {
    case VXY_SET: // 8XY0
        VX = VY;
        qDebug() << "Set V[" << code.x << "] = " << "V[" << code.y << "]";
        break;
    case VXY_OR: // 8XY1
        VX|= VY;
        qDebug() << "Set V[" << code.x << "] |= " << "V[" << code.y << "]";
        break;
    case VXY_AND: // 8XY2
        qDebug() << "Set V[" << code.x << "] &= " << "V[" << code.y << "]";
        VX&= VY;
        break;
    case VXY_XOR: // 8XY3
        qDebug() << "Set V[" << code.x << "] ^= " << "V[" << code.y << "]";
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
        qDebug() << "Set V[" << code.x << "] += " << "V[" << code.y << "] 8XY4";
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
        qDebug() << "Set V[" << code.x << "] -= " << "V[" << code.y << "] 8XY5";
        break;
    case VXY_LSB: // 8XY6
        VF = VX & 1;
        VX>>= 1;
        qDebug() << "V[" << code.x << "] >> 1";
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
        qDebug() << "Set V[" << code.x << "] = " << "V[" << code.y << "] - V[" << code.x << "] 8XY5";
        break;
    case VXY_MSB: // 8XYE
        VF = VX >> 7;
        VX<<= 1;
        qDebug() << "V[" << code.x << "] << 1";
        break;
    }
}

void Chip8Emulator::opcodeFHandler(Opcode &code)
{
    quint8 &VX = this->varRegs[code.x];

    switch (code.nn) {
    case GET_DELAY_TIMER: // FX07
        VX = this->delayTimer;
        qDebug() << "V[" << code.x << "] = delayTimerval = " << VX;
        break;
    case VX_WAIT_KEY_PRESSED: // FX0A
        qDebug() << "Keypress waiting ";
        VX = this->waitKey();
        break;
    case SET_DELAY_TIMER: // FX15
        this->delayTimer = VX;
        qDebug() << "Set Delay timer = " << this->delayTimer;
        break;
    case SET_SOUND_TIMER: // FX18
        this->soundTimer = VX;
        //TODO enable sound
        qDebug() << "Set Sound timer" << this->soundTimer;
        break;
    case I_ADD_VX: // FX1E
        this->idxReg+= VX;
        qDebug() << "I = " << this->idxReg;
        break;
    case I_SET_BY_SPRITE_ADDR: // FX29
        this->idxReg = VX*5 + FONT_START_ADDRESS;
        qDebug() << "FX29 I = " << this->idxReg;
        break;
    case I_STORE_BCD:// FX33
        this->BCDStorage(VX);
        qDebug() << "BCD Storage";
        break;
    case REG_DUMP: // FX55
        this->regDump(code.x);
        qDebug() << "RegDump";
        break;
    case REG_LOAD: // FX65
        this->regLoad(code.x);
        qDebug() << "RegLoad";
        break;
    }
}

void Chip8Emulator::regDump(quint8 x)
{
    quint16 start = this->idxReg;
    for (quint8 i = 0; i <= x; i++)
    {
        this->ram[start + i] = this->varRegs[i];
    }
}

void Chip8Emulator::regLoad(quint8 x)
{
    quint16 start = this->idxReg;
    for (quint8 i = 0; i <= x; i++)
    {
         this->varRegs[i] = this->ram[start + i];
    }
}

void Chip8Emulator::BCDStorage(quint8 val)
{
    for (int i = 2; i >= 0; i--)
    {
        this->ram[this->idxReg + i] = val%10;
        val/=10;
    }
}

void Chip8Emulator::timerHandler()
{
    if(this->clockCounter%CLOCK_TICK == 0)
    {
        if (this->delayTimer > 0) this->delayTimer--;
        if (this->soundTimer > 0)
        {
            this->soundTimer--;
        } else
        {
            // TODO disable beep
        }
    }
}

quint8 Chip8Emulator::waitKey()
{
    quint8 key = 0xff;
    while (true) {
        QCoreApplication::processEvents();
        key = this->currKey;
        if (key != 0xff)
        {
            return key;
        }
    }
}
