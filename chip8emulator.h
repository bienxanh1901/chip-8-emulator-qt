#ifndef CHIP8EMULATOR_H
#define CHIP8EMULATOR_H

#include <qqml.h>
#include <QAbstractListModel>
#include <QStack>
#include <QTimer>
#include "constants.h"
#include "opcode.h"

class Chip8Emulator : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int keyPressed WRITE setCurrKeyPressed)
public:
    enum Roles {
        PixelRole = Qt::UserRole + 1,
    };
    Q_ENUM(Roles)

    explicit Chip8Emulator(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void loadProgram(QString &rom);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void resume();
    Q_INVOKABLE void restart();
    void setCurrKeyPressed(quint8 newCurrKeyPressed);

private:

    // init
    void init();
    void loadFont();

    // PC handler
    void setPC(quint16 addr);
    void nextOpcode();

    // Program running handler
    bool loadROM(QString &rom);
    quint16 fetch();
    Opcode decode(quint16 &bytes);
    void execute(Opcode &code);
    void clear();

    // Registors handler
    void clearRegs();
    void clearIdxReg();

    // Screen handler
    void clearDisplay();
    void draw(quint8 x0, quint8 y0, quint8 h);

    // Opcode handler
    void opcode8Handler(Opcode &code);
    void opcodeFHandler(Opcode &code);
    void regDump(quint8 x);
    void regLoad(quint8 x);
    void BCDStorage(quint8 val);

    // Timer handler
    void timerHandler();


    // Key handler
    quint8 waitKey();

private slots:
    void run();

private:
    void debug(Opcode &code);


private:
    // RAM with 4096 bytes
    QByteArray ram;
    // display 64x32 pixels
    quint8 display[WIDTH*HEIGHT] = {0};
    // Program counter (PC)
    quint16 pc = PROGRAM_START_ADDRESS;
    // 16-bit registor (I)
    quint16 idxReg = 0;
    // 16-bit stack
    QStack<quint16> stack;
    // 16 8-bit registors (V0 -> VF)
    quint8 varRegs[NUM_VAR_REGS] = {0};
    // key pressed
    quint8 currKey = 0xFF;
    // rom size
    quint16 romSize = 0;
    // timers
    QTimer CPUTimer;
    quint8 delayTimer = 0;
    quint8 soundTimer = 0;
    quint16 clockCounter = 0;
};

#endif // CHIP8EMULATOR_H
