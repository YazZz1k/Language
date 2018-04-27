#include"Tree.hpp"


Tree::Tree()
{

}


Tree::Tree(token _value)
{
    value = _value;
}


Tree::~Tree()
{
    size_t size = children.size();

    if(size)
    {
        for(int i = 0; i<size; i++)
        {
            children[i]->~Tree();
            free(children[i]);
        }
    }
}


Tree* Copy_Tree(Tree* tree)
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


Tree* Create_Tree(token _value)
{
    Tree* ret = (Tree*)calloc(1, sizeof(Tree));
    assert(ret);
    ret->value = _value;
    return ret;
}


void Tree::Add_Child(Tree* tree)
{
    Tree* added = tree;
    assert(added);
    children.push_back(added);
}


Tree* Tree::operator[](int index)
{
    size_t size = children.size();
    if(index<size)
        return children[index];
    else
        return NULL;
}


void Tree::print_DOT()
{
    FILE* fout = fopen("print_DOT", "w");

    fprintf(fout, "digraph G{\n");

    _print_DOT(fout);

    fprintf(fout, "\n}");
    fclose(fout);

    system("xdot print_DOT");
}


void Tree::_print_DOT(FILE* fout)
{
    size_t size = children.size();
    fprintf(fout, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n",(int)this, value.value.c_str());
    for(int i=0; i<size; i++)
    {
        fprintf(fout, "%d -> %d [color = blue]\n",(int)this, (int)children[i]);
        children[i]->_print_DOT(fout);
    }
}

