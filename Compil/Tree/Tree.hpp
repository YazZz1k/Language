#ifndef __NOT__BIN__TREE__
#define __NOT__BIN__TREE__

#include<iostream>
#include<vector>
using namespace std;
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

#include"../tokenator/token_struct.hpp"

class Tree
{
    public:
        token value;
        vector<Tree*> children;

    public:
        Tree();
        Tree(token tok);

    public:
        ~Tree();

        void Add_Child(token value);
        void Add_Child(Tree* tree);
        Tree* operator[](int index);

        friend Tree* Copy_Tree(Tree* tree);
        friend Tree* Create_Tree(token value, ...);

        void print_DOT();
        void _print_DOT(FILE* file);
};

Tree* Copy_Tree(Tree* tree);
Tree* Create_Tree(token value);

#endif

