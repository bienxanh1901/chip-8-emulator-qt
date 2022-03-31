#include <QFile>
#include "chip8model.h"
#include "constants.h"

Chip8Model::Chip8Model(QObject *parent)
    : QAbstractItemModel(parent),
    ram(RAM_AMOUNT, 0x00),
    pc(PROGRAM_START_ADDRESS),
    delayTimer(),
    soundTimer()
{
    this->init();
}

int Chip8Model::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    return WIDTH*HEIGHT;
}

QVariant Chip8Model::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);

    quint8 row = index.row()%WIDTH;
    quint8 col = index.row()/HEIGHT + 1;
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant(this->screenPixels[row][col]);
}

void Chip8Model::init()
{
    // Load font
    this->loadFont();

    // Init timer
    connect(this->delayTimer, &QTimer::timeout, this, &onDelayTimerExpried);
    connect(this->soundTimer, &QTimer::timeout, this, &onSoundTimerExpried);
}

void Chip8Model::loadFont()
{
    for (quint16 i = 0; i < FONT_LENGTH; i++)
    {
        this->ram[i + FONT_START_ADDRESS] = font[i];
    }
}

void Chip8Model::setPC(quint16 addr)
{
    this->pc = addr;
}

void Chip8Model::nextOpcode()
{
    this->pc+=2;
}

void clear()
{
    // Stop timers
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

void Chip8Model::run(QString &rom)
{

    // Clear
    this->clear();
    // Load rom
    this->loadROM(rom);

}

void Chip8Model::loadROM(QString &rom)
{
    QFile file(rom);
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        data = file.readAll();
        file.close();
    }

    this->ram.replace(PROGRAM_START_ADDRESS, data.size(), data);
}

quint16 Chip8Model::fetch()
{
    quint16 opcode =  this->ram.mid(this->pc, 2).toInt();
    this->nextOpcode();
    return opcode;
}

Opcode Chip8Model::decode(quint16 &bytes)
{
    return Opcode(bytes);
}

void Chip8Model::execute(Opcode &code)
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
        break;
    case I_SET_NNN: // ANNN
        break;
    case JUMP_B: // BNNN
        break;
    case VX_RAND:// CXNN
        break;
    case DRAW_SPRITE: // DXYN
        break;
    case KEY_OP: // EX9E, EXA1
        break;
    case F_OP: // FX{07, 0A, 15, 18, 1E, 29, 33, 55, 65}
        break;
    }
}

void Chip8Model::clearRegs()
{
    for (auto &reg : this->regs)
    {
        reg = 0x00;
    }
}

void Chip8Model::clearMemRegs()
{
    this->memRegs = 0x00;
}

void Chip8Model::clearDisplay()
{
    for (quint8 i = 0; i < HEIGHT; i++)
    {
        for (quint8 j = 0; j < WIDTH; j++)
        {
            this->screenPixels[i][j] = false;
        }
    }
}

void draw(quint8 x, quint8 y, quint8 n)
{
    // Ensure x is in range [0, 63]
    x&=(WIDTH - 1);
    // Ensure y is in range [0, 31]
    y&=(HEIGHT - 1);

    // Set VF to 0
    this->regs[NUM_REGS - 1] = 0;

    for (quint16 row = y; row < y + n && row < HEIGHT; row++)
    {
        quint8 ridx = x;
        quint8 pixels = this->ram.at(this->memReg + row);
        for (quint8 col = 0; col < 8 && (col + x < WIDTH); col++)
        {
            quint8 pixel = ((pixels >> (col + 1)) & 1);
            if (pixel)
            {
                if (pixel ^ this->screenPixels[col + x][row])
                {
                    // incase(1 ^ 0 = 1)
                    this->screenPixels[col + x][row] = true;
                } else
                {
                    // incase (1 ^ 1 = 0)
                    this->screenPixels[col + x][row] = false;
                    this->regs[NUM_REGS - 1];
                }
            }
        }
    }

}

void Chip8Model::executeMathOp(Opcode &code)
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

void executeFOpGroup(Opcode &code)
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

void regDump(quint8 x)
{
    quint16 start = this->memReg;
    for (quint8 i = 0; i < x; i++)
    {
        this->ram[start + i] = this->regs[i];
    }
}

void regLoad(quint8 x)
{
    quint16 start = this->memReg;
    for (quint8 i = 0; i < x; i++)
    {
         this->regs[i] = this->ram[start + i];
    }
}

void BCDStorage(quint8 val)
{
    for (int i = 2; i >= 0; i--)
    {
        this->ram[this->memReg + i] = val%10;
        val/=10;
    }
}

void setDelayTimerValue(quint8 val)
{
    this->delayTimer.stop();
    this->delayTimerValue = val;
    this->delayTimer.start(0.1666666666667);
}

void setSoundTimerValue(quint8 val)
{
    this->soundTimer.stop();
    this->soundTimerValue = val;
    this->soundTimer.start(0.1666666666667);

    // TODO enable beep
}

void onDelayTimerExpried()
{
    this->delayTimerValue--;
    if (this->delayTimerValue == 0)
    {
        this->delayTimer.stop();
    }
}

void onSoundTimerExpried()
{
    this->soundTimerValue--;
    if (this->soundTimerValue == 0)
    {
        this->soundTimerValue.stop();
        // TODO disable beep
    }
}


