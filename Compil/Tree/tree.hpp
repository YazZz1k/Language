#ifndef __NOT__BIN__TREE__
#define __NOT__BIN__TREE__

#include<vector>
#include<fstream>
using namespace std;
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

template <typename T>
class Tree
{
    private:
        T value;
        vector<Tree<T>*> children;

    public:
        Tree();
        Tree(T _value);
        ~Tree();

        Tree<T>* Copy_Tree(Tree<T>* tree);
        Tree<T>* Create_Tree(T value);
        void Add_Child(T value);
        void Add_Child(Tree<T>* tree);
        Tree<T>* operator[](int index);

        void print_DOT();
        void _print_DOT(FILE* file);
};


template <typename T>
Tree<T>::Tree()
{

}


template <typename T>
Tree<T>::Tree(T _value)
{
    value = T(_value);
}


template <typename T>
Tree<T>::~Tree()
{
    size_t size = children.size();
    if(size)
    {
        for(int i=0; i<size; i++)
        {
            children[i]->~Tree();
            delete children[i];
        }
    }
}


template <typename T>
Tree<T>* Tree<T>::Copy_Tree(Tree<T>* tree)
{
    if(tree)
    {
        Tree* ret = Create_Tree(tree->value);
        size_t size = tree->children.size();
        for(int i=0; i<size; i++)
        {
            ret->children.push_back(Copy_Tree(tree->children[i]));
        }
        return ret;
    }
}


template <typename T>
Tree<T>* Tree<T>::Create_Tree(T _value)
{
    Tree<T>* ret = new Tree<T>;
    assert(ret);
    ret->value = T(_value);
    return ret;
}


template <typename T>
void Tree<T>::Add_Child(Tree<T>* tree)
{
    Tree<T>* added = Create_Tree(tree->value);
    assert(added);
    children.push_back(Copy_Tree(added));
}


template <typename T>
Tree<T>* Tree<T>::operator[](int index)
{
    size_t size = children.size();
    if(index<size)
        return children[index];
    else
        return NULL;
}


template <typename T>
void Tree<T>::print_DOT()
{
    FILE* fout = fopen("print_DOT", "w");

    fprintf(fout, "digraph G{\n");

    _print_DOT(fout);

    fprintf(fout, "\n}");
    fclose(fout);

    system("xdot print_DOT");
}


template <typename T>
void Tree<T>::_print_DOT(FILE* fout)
{
    size_t size = children.size(); 
    fprintf(fout, "%d [shape = box, style = rounded, color = blue, label = \"%d\"]\n",(int)this, value);
    for(int i=0; i<size; i++)
    {
        fprintf(fout, "%d -> %d [color = blue]\n",(int)this, (int)children[i]);
        children[i]->_print_DOT(fout);
    }
}


#endif
