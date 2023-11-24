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
    Q_PROPERTY(Stages stage READ getStage NOTIFY stageChanged)
public:
    enum Roles {
        PixelRole = Qt::UserRole + 1,
    };

    enum Stages {
        RunningStage,
        PauseStage
    };

    Q_ENUM(Roles)
    Q_ENUM(Stages)

    explicit Chip8Emulator(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void startProgram(QString rom);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void resume();
    Q_INVOKABLE void restart();
    void setCurrKeyPressed(quint8 newCurrKeyPressed);
    Stages getStage();
signals:
    void stageChanged();
private:

    // init
    void init();
    void loadFont();
    void setStage(Stages st);

    // PC handler
    void setPC(quint16 addr);
    void nextOpcode();

    // Program running handler
    void loadROM();
    bool readROM(QString &rom);
    void clearROM();
    quint16 fetch();
    Opcode decode(quint16 &bytes);
    void execute(Opcode & code);
    void clear();
    void clearRegs();
    void clearIdxReg();

    // Screen handler
    void clearDisplay();
    void draw(quint8 x0, quint8 y0, quint8 h);

    // Opcode handler
    void OpcodeHandler(Opcode &code);
    void opcode0Handler(Opcode &code);
    void opcode1Handler(Opcode &code);
    void opcode2Handler(Opcode &code);
    void opcode3Handler(Opcode &code);
    void opcode4Handler(Opcode &code);
    void opcode5Handler(Opcode &code);
    void opcode6Handler(Opcode &code);
    void opcode7Handler(Opcode &code);
    void opcode8Handler(Opcode &code);
    void opcode9Handler(Opcode &code);
    void opcodeAHandler(Opcode &code);
    void opcodeBHandler(Opcode &code);
    void opcodeCHandler(Opcode &code);
    void opcodeDHandler(Opcode &code);
    void opcodeEHandler(Opcode &code);
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
    // timers
    QTimer CPUTimer;
    quint8 delayTM = 0;
    quint8 soundTM = 0;
    quint16 clockCounter = 0;

    // status
    Stages stage = RunningStage;

    std::unique_ptr<QByteArray> rom;
};

#endif // CHIP8EMULATOR_H
