#ifndef ____TOKEN____
#define ____TOKEN____

#include<string>
#include<map>
using namespace std;


typedef enum
{
    OP ,  //operator
    NUM, //number
    REG, //register
    PUN, //punctuation
    LAB,  //label
    MATH_OP //mathematical operator
} Type;


/*typedef enum
{
    PUSH,
    POP,
    MOV,
    ADD,
    SUB,
    IN,
    OUT,
    CMP,
    DEC,
    JMP,
    JNE,
    JNZ,
    JLE,
    AX,
    BX,
    CX,
    DX,
    PLUS,
    MINUS,
    MUL,
    DIV,
    OPEN_BR,
    CLOSE_BR,
    $,
    EQUALLY
} Value;
*/
static map <string,Type> map_tokens = {
{"push", OP},
{"pop", OP},
{"mov", OP},
{"add", OP},
{"sub", OP},
{"in",  OP},
{"out", OP},
{"cmp", OP},
{"dec", OP},
{"jmp", OP},
{"jnz", OP},
{"jne", OP},
{"jle", OP},
{"ax", REG},
{"bx", REG},
{"cx", REG},
{"dx", REG},
{"+" ,MATH_OP},
{"-" ,MATH_OP},
{"*" ,MATH_OP},
{"/" ,MATH_OP},
{"(" , PUN},
{")" , PUN},
{"=" ,  OP}
};

class token
{
    public:
        Type type;
        string value;
        size_t line;
    public:
        token(string _value, Type _type, size_t _line);
        token();
        ~token();
        token(const token& token);

        token operator= (const token& token);
};

/*static map <string,token> map_tokens = {{"push",token (OP, PUSH)},
                                   {"pop", token (OP, POP)},
                                   {"mov", token (OP, MOV)},
                                   {"add", token (OP, ADD)},
                                   {"sub", token (OP, SUB)},
                                   {"in",  token (OP, IN )},
                                   {"out", token (OP, OUT)},
                                   {"cmp", token (OP, CMP)},
                                   {"dec", token (OP, DEC)},
                                   {"jmp", token (OP, JMP)},
                                   {"jnz", token (OP, JNZ)},
                                   {"jne", token (OP, JNE)},
                                   {"jle", token (OP, JLE)},
                                   {"ax",  token (REG, AX)},
                                   {"bx",  token (REG, BX)},
                                   {"cx",  token (REG, CX)},
                                   {"dx",  token (REG, DX)},
                                   {"+" ,  token (MATH_OP, PLUS)},
                                   {"-" ,  token (MATH_OP, MINUS)},
                                   {"*" ,  token (MATH_OP, MUL)},
                                   {"/" ,  token (MATH_OP, DIV)},
                                   {"$" ,  token (PUN, $)},
                                   {"(" ,  token (PUN, OPEN_BR)},
                                   {")" ,  token (PUN, CLOSE_BR)},
                                   {"=" ,  token (OP, EQUALLY)}};
*/

#endif
