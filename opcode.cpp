#include "opcode.h"


Opcode::Opcode(opcode_bytes_t & bytes)
{
    this->data.bytes = bytes;
}

quint8 Opcode::type()
{
    return this->data.nibbles.type;
}

quint8 Opcode::VX()
{
    return this->data.nibbles.data.xyn.x;
}

quint8 Opcode::VY()
{
    return this->data.nibbles.data.xyn.y;
}

quint8 Opcode::N()
{
    return this->data.nibbles.data.xyn.n;
}

quint8 Opcode::NN()
{
    return this->data.bytes.second;
}

quint16 Opcode::NNN()
{
    return this->data.nibbles.data.nnn;
}
