#ifndef OPCODE_H
#define OPCODE_H

#include <QtGlobal>

class Opcode
{
public:
    Opcode(quint16 &bytes);

    quint16 data;
    quint8 type;
    quint8 x;
    quint8 y;
    quint8 n;
    quint8 nn;
    quint8 nnn;
};

#endif // OPCODE_H
