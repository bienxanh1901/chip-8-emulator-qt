#include <QFile>
#include <QRandomGenerator>
#include <QDebug>
#include "emulator.h"

Emulator::Emulator(QObject *parent)
    : QObject{parent},
      ram(RAM_AMOUNT, 0x00),
      screenPixels(WIDTH*HEIGHT, 0),
      pc(PROGRAM_START_ADDRESS),
      delayTimer(),
      soundTimer(),
      runningTimer(),
      displayTimer()
{
    this->init();
}


void Emulator::stop()
{
    this->runningTimer.stop();
    this->delayTimer.stop();
    this->soundTimer.stop();
    this->delayTimerValue = 0;
    this->soundTimerValue = 0;

}

QVariantList Emulator::pixels()
{
    QVariantList data;
    for (int &i : this->screenPixels)
    {
        data << i;
    }
    return data;
}


void Emulator::init()
{
    // Load font
    this->loadFont();

    // Init timer
    this->delayTimer.setInterval(COUNTDOWN_PERIOD);
    this->delayTimer.setTimerType(Qt::PreciseTimer);
    this->soundTimer.setInterval(COUNTDOWN_PERIOD);
    this->soundTimer.setTimerType(Qt::PreciseTimer);
    connect(&this->delayTimer, &QTimer::timeout, this, &Emulator::onDelayTimerExpried);
    connect(&this->soundTimer, &QTimer::timeout, this, &Emulator::onSoundTimerExpried);

    // running timer
    this->runningTimer.setSingleShot(true);
    this->runningTimer.setInterval(0);
    connect(&this->runningTimer, &QTimer::timeout, this, &Emulator::run);

    // display update timer
    this->displayTimer.setInterval(COUNTDOWN_PERIOD);
    connect(&this->displayTimer, &QTimer::timeout, this, &Emulator::onDisplayTimerExpired);
    this->displayTimer.start();
}

void Emulator::loadFont()
{
    for (quint16 i = 0; i < FONT_LENGTH; i++)
    {
        this->ram[i + FONT_START_ADDRESS] = font[i];
    }
}

void Emulator::setPC(quint16 addr)
{
    this->pc = addr;
}

void Emulator::nextOpcode()
{
    this->pc+=2;
}

void Emulator::clear()
{
    // Stop timers
    this->runningTimer.stop();
    this->delayTimer.stop();
    this->soundTimer.stop();
    this->delayTimerValue = 0;
    this->soundTimerValue = 0;
    // clear current Display
    this->clearDisplay();

    // Set PC to start address
    this->setPC(PROGRAM_START_ADDRESS);

    // clear RAM
    this->ram.replace(PROGRAM_START_ADDRESS, PROGRAM_MAX_SIZE, QByteArray(PROGRAM_MAX_SIZE, 0x00));
}

void Emulator::run()
{
    // run the program
    quint16 bytes;
    Opcode opcode;
    while (this->pc < this->romSize + PROGRAM_START_ADDRESS)
    {
        bytes = this->fetch();
        if (!bytes) break;
        opcode = this->decode(bytes);
        this->execute(opcode);
    }
}

void Emulator::romChanged(QString &rom)
{
    qDebug() << "ROM changed!";
    // Clear
    this->clear();
    // Load rom
    this->loadROM(rom);
    // run
    this->runningTimer.start();
    qDebug() << "running";

}

void Emulator::loadROM(QString &rom)
{
    QFile file(rom);
    QByteArray data;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        data = file.readAll();
        file.close();
    }
    else
    {
        qDebug() << "error read file!";
    }

    this->romSize = data.size();
    this->ram.replace(PROGRAM_START_ADDRESS, romSize, data);
}

quint16 Emulator::fetch()
{
    QByteArray bytes = this->ram.mid(this->pc, 2);
    QDataStream dataStream(bytes);
    quint16 opcode;
    dataStream >> opcode;
    this->nextOpcode();
    return opcode;
}

Opcode Emulator::decode(quint16 &bytes)
{
    return Opcode(bytes);
}

void Emulator::execute(Opcode &code)
{
    switch (code.type) {
    case ZERO_OP: // 00EE - 00E0 - 0NNN
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
        break;
    case JUMP_1: // 1NNN
        this->setPC(code.nnn);
        break;
    case CALL_SUB: // 2NNN
        this->stack.push(code.nnn);
        break;
    case VX_EQ_NN: // 3XNN
        if (this->regs[code.x] == code.nn)
        {
            this->nextOpcode();
        }
        break;
    case VX_NE_NN: // 4XNN
        if (this->regs[code.x] != code.nn)
        {
            this->nextOpcode();
        }
        break;
    case VX_EQ_VY: // 5XY0
        if (this->regs[code.x] == this->regs[code.y])
        {
            this->nextOpcode();
        }
        break;
    case VX_SET_NN: // 6XNN.
        this->regs[code.x] = code.nn;
        break;
    case VX_ADD_NN: // 7XNN
        this->regs[code.x] += code.nn;
        break;
    case VXY_MATH: // 8XY{0, 1, 2, 3, 4, 5, 6, 7, E}
        this->executeMathOp(code);
        break;
    case VX_NE_VY: // 9XY0
        if (this->regs[code.x] != this->regs[code.y])
        {
            this->nextOpcode();
        }
        break;
    case I_SET_NNN: // ANNN
        this->memReg = code.nnn;
        break;
    case JUMP_B: // BNNN
        this->setPC(this->memReg + this->regs[code.x]);
        break;
    case VX_RAND:// CXNN
        this->regs[code.x] = QRandomGenerator::global()->generate() & code.nn;
        break;
    case DRAW_SPRITE: // DXYN
        this->draw(this->regs[code.x], this->regs[code.y], code.n);
        break;
    case E_OP: // EX9E, EXA1
        break;
    case F_OP: // FX{07, 0A, 15, 18, 1E, 29, 33, 55, 65}
        this->executeFOpGroup(code);
        break;
    }
}

void Emulator::clearRegs()
{
    for (auto &reg : this->regs)
    {
        reg = 0x00;
    }
}

void Emulator::clearMemReg()
{
    this->memReg = 0x00;
}

void Emulator::clearDisplay()
{
    for (int &i : this->screenPixels)
    {
        i = 0;
    }
}

void Emulator::draw(quint8 x, quint8 y, quint8 n)
{
    // Ensure x is in range [0, 63]
    x&=(WIDTH - 1);
    // Ensure y is in range [0, 31]
    y&=(HEIGHT - 1);

    // Set VF to 0
    this->regs[NUM_REGS - 1] = 0;

    for (quint16 row = 0; row < n && (row + y < HEIGHT); row++)
    {
        quint8 pixels = this->ram.at(this->memReg + row);
        for (quint8 col = 0; col < 8 && (col + x < WIDTH); col++)
        {
            quint16 pixelIdx = (row + y)*WIDTH + (col + x);
            quint8 pixel = ((pixels >> (7 - col)) & 1);
            if (pixel)
            {
                if (pixel ^ this->screenPixels[pixelIdx])
                {
                    // incase(1 ^ 0 = 1)
                    this->screenPixels[pixelIdx] = 1;
                } else
                {
                    // incase (1 ^ 1 = 0)
                    this->screenPixels[pixelIdx] = 0;
                    this->regs[NUM_REGS - 1] = 1;
                }
            }
        }
    }

}

void Emulator::executeMathOp(Opcode &code)
{
    quint8 &VX = this->regs[code.x];
    quint8 &VY = this->regs[code.y];
    quint8 &VF = this->regs[NUM_REGS - 1];

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
        if (VX + VY > 255)
        {
            VF = 0x01;
        }
        VX+= VY;
        break;
    case VXY_SUB: // 8XY5
        if (VX >= VY)
        {
            VF = 0x01;
        }
        VX-= VY;
        break;
    case VXY_LSB: // 8XY6
        VX>>= 1;
        VF = VX & 1;
        break;
    case VXY_MINUS: // 8XY7
        if (VY >= VX)
        {
            VF = 0x01;
        }
        VX = VY - VX;
        break;
    case VXY_MSB: // 8XYE
        VF = VX >> 7;
        VX<<= 1;
        break;
    }
}

void Emulator::executeFOpGroup(Opcode &code)
{
    quint8 &VX = this->regs[code.x];

    switch (code.n) {
    case SET_DELAY_TIMER: // FX07
        this->setDelayTimerValue(VX);
        break;
    case VX_WAIT_KEY_PRESSED: // FX0A
        this->keyPressedWaiting(VX);
        break;
    case VX_SET_BY_DELAY_TIMER: // FX15
        VX = this->delayTimerValue;
        break;
    case VX_SET_BY_SOUND_TIMER: // FX18
        VX = this->soundTimerValue;
        break;
    case I_ADD_VX: // FX1E
        this->memReg+= VX;
        break;
    case I_SET_BY_SPRITE_ADDR: // FX29
        this->memReg = this->ram.indexOf(VX, FONT_START_ADDRESS);
        break;
    case I_STORE_BCD:// FX33
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

void Emulator::regDump(quint8 x)
{
    quint16 start = this->memReg;
    for (quint8 i = 0; i < x; i++)
    {
        this->ram[start + i] = this->regs[i];
    }
}

void Emulator::regLoad(quint8 x)
{
    quint16 start = this->memReg;
    for (quint8 i = 0; i < x; i++)
    {
         this->regs[i] = this->ram[start + i];
    }
}

void Emulator::BCDStorage(quint8 val)
{
    for (int i = 2; i >= 0; i--)
    {
        this->ram[this->memReg + i] = val%10;
        val/=10;
    }
}

void Emulator::setDelayTimerValue(quint8 val)
{
    this->delayTimer.stop();
    this->delayTimerValue = val;
    this->delayTimer.start();
}

void Emulator::setSoundTimerValue(quint8 val)
{
    this->soundTimer.stop();
    this->soundTimerValue = val;
    this->soundTimer.start();

    // TODO enable beep
}

void Emulator::onDelayTimerExpried()
{
    this->delayTimerValue--;
    if (this->delayTimerValue == 0)
    {
        this->delayTimer.stop();
    }
}

void Emulator::onSoundTimerExpried()
{
    this->soundTimerValue--;
    if (this->soundTimerValue == 0)
    {
        this->soundTimer.stop();
        // TODO disable beep
    }
}

void Emulator::onDisplayTimerExpired()
{
    emit pixelsChanged();
}

void Emulator::keyPressedWaiting(quint8 val)
{

}
