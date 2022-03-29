#ifndef OPCODE_H
#define OPCODE_H

#include <QtGlobal>


typedef struct {
    quint8 first;
    quint8 second;          // NN: The second byte (third and fourth nibbles). An 8-bit immediate number.
} opcode_bytes_t;

typedef struct {
    quint8 type:4;          // First nibble: Instruction type (0 -> F)
    union {
        quint16 nnn:12;     // NNN: The second, third and fourth nibbles. A 12-bit immediate memory address.
        struct {
            quint8 x:4;     // X: The second nibble. Used to look up one of the 16 registers (VX) from V0 through VF.
            quint8 y:4;     // Y: The third nibble. Also used to look up one of the 16 registers (VY) from V0 through VF.
            quint8 n:4;     // N: The fourth nibble. A 4-bit number.
        } xyn;
    } data;

} opcode_nibbles_t;

typedef union {
    opcode_bytes_t bytes;
    opcode_nibbles_t nibbles;
} opcode_t;

class Opcode
{
public:
    Opcode(opcode_bytes_t &bytes);

    quint8 type();
    quint8 VX();
    quint8 VY();
    quint8 N();
    quint8 NN();
    quint16 NNN();

private:
    opcode_t data;
};

#endif // OPCODE_H
