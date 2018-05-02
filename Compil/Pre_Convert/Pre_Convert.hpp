#ifndef __PRE_CONVERT__
#define __PRE_CONVERT__

#include<string.h>
#include<stdio.h>

#include<vector>
#include<map>
#include<string>
#include<cstring>
using namespace std;

#include"../Tree/Tree.hpp"


class Pre_Convert
{
    private:
        Tree* input_tree;
        Tree* output_tree;

        map<string, int> labels;
        Tree* conv_Expr;

        vector<string> Errors;
    public:
        bool error;

    public:
        Pre_Convert(Tree* in_tree);
        ~Pre_Convert();

        Tree* get_Pre_Converted_Tree();
        map<string, int> get_labels();

        void Run_Pre_Convert();
    private:
        void Init_Labels();
        void Convert_Expr(Tree* Expr);

    private:
        void Push_Tree(Tree* subtree);
        void Push_Reg_or_Num(Tree* subtree);
        void Push_Math_Op(Tree* subtree);

        bool Is_jmp_function(Tree* tree);
    private:
        void Error_Invalid_Data();
        void Error_Mult_Init_Label(string name_label, size_t line);
        void Error_Dont_Init_Label(string name_label, size_t line);
    public:
        void print_Errors();
        void print_labels();
};

#endif
