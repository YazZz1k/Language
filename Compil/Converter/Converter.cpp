#include"Converter.hpp"

Converter::Converter(Tree* tree, map<string, int> _labels)
{
    input_tree = Copy_Tree(tree);
    map_labels = _labels;
}


Converter::~Converter()
{
    input_tree->~Tree();
}


void Converter::Run_Converter()
{
    size_t size = input_tree->get_number_of_children();

    for(int i=0; i<size; i++)
    {
        Tree* tmp_tree = (*input_tree)[i];
        switch(tmp_tree->value.type)
        {
            case OP:
                if(tmp_tree->value.value == "push") conv_push(tmp_tree);
                else if(tmp_tree->value.value == "pop")conv_pop (tmp_tree);
                else if(tmp_tree->value.value == "mov")conv_mov (tmp_tree);
                else if(tmp_tree->value.value == "add")conv_add (tmp_tree);
                else if(tmp_tree->value.value == "sub")conv_sub (tmp_tree);
                else if(tmp_tree->value.value == "in")conv_in  (tmp_tree);
                else if(tmp_tree->value.value == "out")conv_out (tmp_tree);
                else if(tmp_tree->value.value == "cmp")conv_cmp (tmp_tree);
                else if(tmp_tree->value.value == "dec")conv_dec (tmp_tree);
                else if(tmp_tree->value.value == "jmp")conv_jmp (tmp_tree);
                else if(tmp_tree->value.value == "jnz")conv_jnz (tmp_tree);
                else if(tmp_tree->value.value == "jne")conv_jne (tmp_tree);
                else if(tmp_tree->value.value == "jle")conv_jle (tmp_tree);
                else assert(0);
                break;

            case LAB:
                conv_label();
                break;

            default:
                assert(0);
        }
    }

    commands.push_back(END);
}


void Converter::conv_label()
{
    for(int i=0; i<3; i++)
        commands.push_back(EMPTY);
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
    assert(tree);
    assert(tree->value.type == OP);

    Tree* arg = (*tree)[0];
    assert(arg);

    switch(arg->value.type)
    {
        case REG:
            commands.push_back(PUSH_REG);
            conv_reg(arg);
            break;
        case NUM:
            commands.push_back(PUSH_NUM);
            conv_num(arg);
            break;
        default:
            assert(0);
    }

    commands.push_back(EMPTY);
}


void Converter::conv_pop (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    Tree* arg = (*tree)[0];
    assert(arg);

    if(arg->value.type == REG)
    {
        commands.push_back(POP_REG);
        conv_reg(arg);
    }
    else assert(0);

    commands.push_back(EMPTY);
}


void Converter::conv_mov (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    Tree *arg_1 = (*tree)[0],
         *arg_2 = (*tree)[1];
    assert(arg_1&&arg_2);

    if(arg_1->value.type == REG)
    {
        switch(arg_2->value.type)
        {
            case REG:
                commands.push_back(MOV_REG_REG);
                conv_reg(arg_1);
                conv_reg(arg_2);
                break;

            case NUM:
                commands.push_back(MOV_REG_NUM);
                conv_reg(arg_1);
                conv_num(arg_2);
                break;

            default:
                assert(0);
        }
    }
    else assert(0);
}


void Converter::conv_add (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    commands.push_back(ADD);
    commands.push_back(EMPTY);
    commands.push_back(EMPTY);
}


void Converter::conv_sub (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    commands.push_back(SUB);
    commands.push_back(EMPTY);
    commands.push_back(EMPTY);
}


void Converter::conv_in  (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    Tree* arg = (*tree)[0];
    assert(arg);

    if(arg->value.type == REG)
    {
        commands.push_back(IN_REG);
        conv_reg(arg);
    }
    else assert(0);

    commands.push_back(EMPTY);
}


void Converter::conv_out (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    Tree* arg = (*tree)[0];
    assert(arg);

    switch(arg->value.type)
    {
        case REG:
            commands.push_back(OUT_REG);
            conv_reg(arg);
            break;
        case NUM:
            commands.push_back(OUT_NUM);
            conv_num(arg);
            break;
        default:
            assert(0);
    }

    commands.push_back(EMPTY);
}


void Converter::conv_cmp (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    Tree *arg_1 = (*tree)[0],
         *arg_2 = (*tree)[1];
    assert(arg_1&&arg_2);

    Type arg_1_type = arg_1->value.type,
         arg_2_type = arg_2->value.type;

    if(arg_1_type == REG)
    {
        switch(arg_2_type)
        {
            case REG:
                commands.push_back(CMP_REG_REG);
                conv_reg(arg_1);
                conv_reg(arg_2);
                break;

            case NUM:
                commands.push_back(CMP_REG_NUM);
                conv_reg(arg_1);
                conv_num(arg_2);
                break;

            default:
                assert(0);
        }
    }
    else if(arg_1_type == NUM)
    {
        switch(arg_2_type)
        {
            case REG:
                commands.push_back(CMP_NUM_REG);
                conv_num(arg_1);
                conv_reg(arg_2);
                break;

            case NUM:
                commands.push_back(CMP_NUM_NUM);
                conv_num(arg_1);
                conv_num(arg_2);
                break;

            default:
                assert(0);
        }
    }
    else
        assert(0);
}


void Converter::conv_dec (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    Tree* arg = (*tree)[0];
    assert(arg);

    if(arg->value.type == REG)
    {
        commands.push_back(DEC_REG);
        conv_reg(arg);
        commands.push_back(EMPTY);
    }
    else
        assert(0);
}


void Converter::conv_jmp (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    Tree* arg = (*tree)[0];
    assert(arg);

    if(arg->value.type == LAB)
    {
        commands.push_back(JMP);
        int line = map_labels[arg->value.value];
        commands.push_back(3*(line-1));
        commands.push_back(EMPTY);
    }
    else
        assert(0);
}


void Converter::conv_jnz (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    Tree* arg = (*tree)[0];
    assert(arg);

    if(arg->value.type == LAB)
    {
        commands.push_back(JNZ);
        int line = map_labels[arg->value.value];
        commands.push_back(3*(line-1));
        commands.push_back(EMPTY);
    }
    else
        assert(0);
}


void Converter::conv_jle (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    Tree* arg = (*tree)[0];
    assert(arg);

    if(arg->value.type == LAB)
    {
        if(map_labels.count(arg->value.value))
        {
            commands.push_back(JLE);
            int line = map_labels[arg->value.value];
            commands.push_back(3*(line-1));
            commands.push_back(EMPTY);
        }
        else
            assert(0);
    }
    else
        assert(0);
}


void Converter::conv_jne (Tree* tree)
{
    assert(tree);
    assert(tree->value.type == OP);

    Tree* arg = (*tree)[0];
    assert(arg);

    if(arg->value.type == LAB)
    {
        commands.push_back(JNE);
        int line = map_labels[arg->value.value];
        commands.push_back(3*(line-1));
        commands.push_back(EMPTY);
    }
    else
        assert(0);
}


vector<int> Converter::Get_Commands()
{
    return commands;
}


