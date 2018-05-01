#include"Converter.hpp"

Converter::Converter(Tree* tree)
{
    input_tree = Copy_Tree(tree);
}


Converter::~Converter()
{
    input_tree->~Tree();
}


void Converter::Start()
{
    size_t size = input_tree->get_number_of_children();

    for(int i=0; i<size; i++)
    {
        Tree* tmp_tree = (*input_tree)[i];

        if(tmp_tree->value.value == "push") conv_push(tmp_tree);
    }
}


void Converter::conv_reg(Tree* tree)
{
    string reg_name = tree->value.value;

    if     (reg_name == "ax") commands.push_back(AX);
    else if(reg_name == "bx") commands.push_back(BX);
    else if(reg_name == "cx") commands.push_back(CX);
    else if(reg_name == "dx") commands.push_back(DX);
    else assert(0);
}


void Converter::conv_num(Tree* tree)
{
    string number = tree->value.value;
    commands.push_back(atoi(number.c_str()));
}


void Converter::conv_push(Tree* tree)
{
    Tree* child = (*tree)[0];
    switch(child->value.type)
    {
        case REG:
            commands.push_back(PUSH_REG);
            conv_reg(child);
            break;
        case NUM:
            commands.push_back(PUSH_NUM);
            conv_num(child);
            break;
        default:
            assert(0);
    }
}


vector<int> Converter::Get_Commands()
{
    return commands;
}


