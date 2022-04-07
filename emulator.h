#ifndef EMULATOR_H
#define EMULATOR_H

#include <QObject>
#include <qqml.h>
#include <QStack>
#include <QTimer>
#include "constants.h"
#include "opcode.h"

class Emulator : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QVariantList pixels READ pixels NOTIFY pixelsChanged)

public:
    explicit Emulator(QObject *parent = nullptr);

    Q_INVOKABLE void romChanged(QString &rom);
    Q_INVOKABLE void stop();

    QVariantList pixels();

signals:
    void pixelsChanged();

private:

    // init
    void init();
    void loadFont();

    // PC handler
    void setPC(quint16 addr);
    void nextOpcode();

    // Program running handler
    void clear();
    void loadROM(QString &rom);
    quint16 fetch();
    Opcode decode(quint16 &bytes);
    void execute(Opcode &code);

    // Registors handler
    void clearRegs();
    void clearMemReg();

    // Screen handler
    void clearDisplay();
    void draw(quint8 x, quint8 y, quint8 n);

    // Opcode handler
    void executeMathOp(Opcode &code);
    void executeFOpGroup(Opcode &code);
    void regDump(quint8 x);
    void regLoad(quint8 x);
    void BCDStorage(quint8 val);

    // Timer handler
    void setDelayTimerValue(quint8 val);
    void setSoundTimerValue(quint8 val);


    // Key handler
    void keyPressedWaiting(quint8 val);

private slots:
    void onDelayTimerExpried();
    void onSoundTimerExpried();
    void onDisplayTimerExpired();
    void run();

    private:
        // RAM with 4096 bytes
        QByteArray ram;
        // display 64x32 pixels
        QVector<int> screenPixels;
        // Program counter (PC)
        quint16 pc;
        // 16-bit registor (I)
        quint16 memReg = 0;
        // 16-bit stack
        QStack<quint16> stack;
        // 16 8-bit registors (V0 -> VF)
        quint8 regs[NUM_REGS] = {0};

        // key pressed
        quint8 currKeyPressed = 0x00;

        // rom size
        quint16 romSize;

        // timers
        quint8 delayTimerValue = 0;
        quint8 soundTimerValue = 0;
        QTimer delayTimer;
        QTimer soundTimer;
        QTimer runningTimer;
        QTimer displayTimer;

};

#endif // EMULATOR_H
