#ifndef __ENUM_DISCRIPTIONS__
#define __ENUM_DISCRIPTIONS__

typedef enum
{
    PUSH_REG = 11,
    PUSH_NUM = 12,

    POP_REG  = 21,

    MOV_REG_REG = 31,
    MOV_REG_NUM = 32,

    ADD = 41,

    SUB = 51,

    IN_REG = 61,

    OUT_REG = 71,
    OUT_NUM = 72,

    CMP_NUM_REG = 81,
    CMP_NUM_NUM = 82,
    CMP_REG_REG = 83,
    CMP_REG_NUM = 84,

    DEC_REG = 91,
    DEC_NUM = 92,

    JMP = 101,
    JMZ = 102,
    JNE = 103,
    JLE = 104,

    AX = 111,
    BX = 112,
    CX = 113,
    DX = 114
}Commands;

#endif
