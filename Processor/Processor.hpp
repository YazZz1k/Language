#ifndef __PROCESSOR__
#define __PROCESSOR__

#include<fstream>
#include<assert.h>
#include<iostream>
#include<vector>
using namespace std;

#include"Stack/stack.hpp"
#include"../Enum_Discriptions.hpp"
typedef struct
{
    int ax, bx, cx, dx;
} Registers;

typedef struct
{
    bool ZF, EF, LF;
} Flags;

class Processor
{
    private:
        vector<int> commands;
        int ptr;

        Registers reg;
        Flags     flags;

        Stack stack;
    public:
        Processor(ifstream* input_file);
        ~Processor();
        void execute();

    private:
        void in_commands(ifstream* input_file);

        int  get_reg_value(int reg_name);
        int* get_reg      (int reg_name);

        void push_reg();
        void push_num();
        void pop_reg ();
        void mov_reg_reg();
        void mov_reg_num();
        void mul();
        void div();
        void add();
        void sub();
        void in_reg();
        void out_reg();
        void out_num();
        void cmp_num_reg();
        void cmp_num_num();
        void cmp_reg_reg();
        void cmp_reg_num();
        void dec_reg();
        void jmp();
        void jnz();
        void jne();
        void jle();
};
#endif
