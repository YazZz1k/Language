#ifndef __TOKENATOR__
#define __TOKENATOR__

#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<cstring>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
using namespace std;


typedef enum
{
    OP ,  //operator
    NUM, //number
    REG, //register
    PUN, //punctuation
    LAB  //label
} Type;


/*ypedef enum
{
    PUSH,
    POP ,
    ADD ,
    SUB ,
    IN  ,
    OUT ,
    CMP ,
    DEC ,
    JMP ,
    JNZ ,
    JNE ,
    JLE ,
    AX  ,
    BX  ,
    CX  ,
    DX  ,

    OTHER
} type_2;
*/

/*typedef struct TOKENS
{
    type_1 t_1;
    type_2 t_2;
}Type;
*/

static map <string,Type> map_tokens = {{"push", OP},
                                   {"pop", OP},
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
                                   {"dx", REG}};
class token
{
    public:
        Type type;
        string value;
        size_t line;

    public:
        token(string str, Type _type);
        ~token();
        token(const token& token);

        token operator= (const token& token);
};


class Tokenator
{
    public:
        ifstream* input;
        vector<string> errors;
        bool error;

    public:
        vector<token> arr_token;

    public:
        Tokenator(ifstream* input);
        ~Tokenator();
        Tokenator(const Tokenator& t);

    public:
        vector<token> convert_string_to_token(string str, size_t line);
        vector<string> get_tokens(string in_str);
        bool isdigit(const char symbol);
        bool Is_Int_Number(const string str);
    public:
        void Error_More_Than_One_Operator_at_Line  (const string err_token, size_t line);
        void Error_Invalid_Token                   (const string err_token, size_t line);
        void Error_There_arent_any_Operator_at_Line(const string err_line,  size_t line);
};


#endif
