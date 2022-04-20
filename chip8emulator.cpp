#include <QFile>
#include <QCoreApplication>
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

/**
 * @brief Chip8Emulator::pause
 * @details Pause the program
 */
void Chip8Emulator::pause()
{
    this->setStage(PauseStage);
    this->CPUTimer.stop();
    // TODO disable beep
}

/**
 * @brief Chip8Emulator::resume
 * @details Resume the program
 */
void Chip8Emulator::resume()
{
    this->setStage(RunningStage);
    this->CPUTimer.start();
    // TODO enable beep
}

/**
 * @brief Chip8Emulator::restart
 * @details Restart the program
 */
void Chip8Emulator::restart()
{
    this->pause();
    this->clear();
    this->clearROM();
    this->loadROM();
    this->resume();
}

/**
 * @brief Chip8Emulator::init
 * @details Init the emulator
 */
void Chip8Emulator::init()
{
    this->loadFont();
    this->CPUTimer.setInterval(CLOCK_TICK);
    connect(&this->CPUTimer, &QTimer::timeout, this, &Chip8Emulator::run);
}

/**
 * @brief Chip8Emulator::loadFont
 * @details Load font to RAM
 */
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
    this->clearRegs();
    this->clearIdxReg();
    this->clearDisplay(); // clear current Display
    this->setPC(PROGRAM_START_ADDRESS); // Set PC to start address
    this->delayTM = 0;
    this->soundTM = 0;
    this->clockCounter = 0;
}

void Chip8Emulator::run()
{
    this->clockCounter++;
    quint16 bytes = this->fetch();
    Opcode opcode = this->decode(bytes);
    this->execute(opcode);
}

void Chip8Emulator::setCurrKeyPressed(quint8 newCurrKeyPressed)
{
    currKey = newCurrKeyPressed;
}

Chip8Emulator::Stages Chip8Emulator::getStage()
{
    return this->stage;
}

void Chip8Emulator::setStage(Stages st)
{
    this->stage = st;
    emit stageChanged();
}

/**
 * @brief Chip8Emulator::startProgram
 * @param rom path to ROM
 * @details start a program with specific ROM
 */
void Chip8Emulator::startProgram(QString &rom)
{
    this->pause();
    this->clear();
    if (this->readROM(rom))
    {
        this->clearROM();
        this->loadROM();
        this->resume();
    }
}

/**
 * @brief Chip8Emulator::loadROM
 * @details Load a ROM into RAM
 */
void Chip8Emulator::loadROM()
{
    this->ram.replace(PROGRAM_START_ADDRESS, this->rom->size(), *this->rom);
}

bool Chip8Emulator::readROM(QString &rom)
{
    this->rom.reset(new QByteArray());
    if (readFile(rom, this->rom.get()))
        return true;
    return false;

}

void Chip8Emulator::clearROM()
{
    this->ram.replace(PROGRAM_START_ADDRESS, this->rom->size(), QByteArray(this->rom->size(), 0x00));
}

/**
 * @brief Chip8Emulator::fetch
 * @return 16 bits data
 * @details Get current opcode data from RAM
 */
quint16 Chip8Emulator::fetch()
{
    QByteArray bytes = this->ram.mid(this->pc, 2);
    QDataStream dataStream(bytes);
    quint16 opcode;
    dataStream >> opcode;
    this->nextOpcode();
    return opcode;
}

/**
 * @brief Chip8Emulator::decode
 * @param bytes 16 bits data
 * @return Opcode
 * @details Convert data into Opcode
 */
Opcode Chip8Emulator::decode(quint16 &bytes)
{
    return Opcode(bytes);
}

void Chip8Emulator::execute(Opcode &code)
{
    this->OpcodeHandler(code);
    this->timerHandler();
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


