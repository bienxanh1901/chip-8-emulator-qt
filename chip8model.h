#ifndef CHIP8MODEL_H
#define CHIP8MODEL_H

#include <QAbstractItemModel>
#include <QStack>
#include <QTimer>
#include "constants.h"
#include "opcode.h"


class Chip8Model : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit Chip8Model(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:

    // init
    void init();
    void loadFont();

    // PC handler
    void setPC(quint16 addr);
    void nextOpcode();

    // Program running handler
    void clear();
    void run(QString &rom);
    void loadROM(QString &rom);
    quint16 fetch();
    Opcode decode(quint16 &bytes);
    void execute(Opcode &code);

    // Registors handler
    void clearRegs();
    void clearMemRegs();

    // Screen handler
    void clearDisplay();
    void draw();

    // Opcode handler
    void executeMathOp(Opcode &code);
    void executeFOpGroup(Opcode &code);
    void regDump(quint8 x);
    void regLoad(quint8 x);
    void BCDStorage(quint8 val);

    // Timer handler
    void setDelayTimerValue(quint8 val);
    void setSoundTimerValue(quint8 val);
    void onDelayTimerExpried();
    void onSoundTimerExpried();

    // Key handler

private:
    // RAM with 4096 bytes
    QByteArray ram;
    // display 64x32 pixels
    bool screenPixels[WIDTH][HEIGHT] = {{false}};
    // Program counter (PC)
    quint16 pc;
    // 16-bit registor (I)
    quint16 memRegs = 0;
    // 16-bit stack
    QStack<quint16> stack;
    // 16 8-bit registors (V0 -> VF)
    quint8 regs[NUM_REGS] = {0};
    // Delay timer
    QTimer delayTimer;
    QTimer soundTimer;
    quint8 delayTimerValue = 0;
    quint8 SoundTimerValue = 0;

    // key pressed
    quint8 currKeyPressed = 0x00;
};

#endif // CHIP8MODEL_H
