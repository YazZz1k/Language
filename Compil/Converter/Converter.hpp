#ifndef __CONVERTER__
#define __CONVERTER__

#include"../Tree/Tree.hpp"
#include"../../Enum_Discriptions.hpp"

#include"stdlib.h"

#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Converter
{
    private:
        Tree* input_tree;
        vector<int> commands;

    public:
        Converter(Tree* tree);
        ~Converter();
        void Start();
        vector<int> Get_Commands();

    private:
        void conv_reg(Tree* tree);
        void conv_num(Tree* tree);

        void conv_push(Tree* tree);
        void conv_pop (Tree* tree);
        void conv_mov (Tree* tree);
        void conv_add (Tree* tree);
        void conv_sub (Tree* tree);
        void conv_in  (Tree* tree);
        void conv_out (Tree* tree);
        void conv_cmp (Tree* tree);
        void conv_dec (Tree* tree);
        void conv_jmp (Tree* tree);
        void conv_jmz (Tree* tree);
        void conv_jle (Tree* tree);
};

#endif