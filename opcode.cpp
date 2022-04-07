#include "opcode.h"


Opcode::Opcode()
{

}

Opcode::Opcode(quint16 & data):
    data(data)
{
    this->type = data >> 0x0C;
    this->x = (data >> 0x08) & 0x0F;
    this->y = (data >> 0x04) & 0x0F;
    this->n = data & 0x0F;
    this->nn = data & 0xFF;
    this->nnn = data & 0xFFF;
}


