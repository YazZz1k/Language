#include"Pre_Convert.hpp"

Pre_Convert::Pre_Convert(Tree* in_tree)
{
    input_tree = Copy_Tree(in_tree);
    token root("ROOT", OP, 0);
    output_tree = Create_Tree(root);

    error = false;
}


Pre_Convert::~Pre_Convert()
{
    if(input_tree)
        input_tree->~Tree();

    if(output_tree)
        output_tree->~Tree();
}


Tree* Pre_Convert::get_Pre_Converted_Tree()
{
    return Copy_Tree(output_tree);
}


map<string, int> Pre_Convert::get_labels()
{
    return labels;
}

void Pre_Convert::Run_Pre_Convert()
{
    int size = input_tree->get_number_of_children();
    Tree *current,
         *Expr;

    for(int i=0; i<size; i++)
    {
        current = (*input_tree)[i];
        switch(current->value.type)
        {
            case OP:
                output_tree->Add_Child(Copy_Tree(current));
                break;

            case LAB:
                output_tree->Add_Child(Copy_Tree(current));

                if(labels.count(current->value.value))
                    Error_Mult_Init_Label(current->value.value, current->value.line);
                else
                    labels.insert(pair<string, int>(current->value.value, -1));
                break;

            case REG:
                Convert_Expr(current);
                break;

            default:
                Error_Invalid_Data();
        }
    }

    Init_Labels();

    print_Errors();
}


bool Pre_Convert::Is_jmp_function(Tree* tree)
{
    assert(tree);

    if(tree->value.type == OP)
    {
        string op_name = tree->value.value;
        return ((op_name == "jmp")||(op_name == "jnz")||(op_name == "jle"));
    }
    else
        return false;
}


void Pre_Convert::Init_Labels()
{
    int size = output_tree->get_number_of_children();
    Tree* current;

    for(int i=0; i<size; i++)
    {
        current = (*output_tree)[i];
        if((current->value.type != OP)&&(current->value.type != LAB))
            Error_Invalid_Data();

        if(current->value.type == LAB)
        {
            assert(labels.count(current->value.value));

            labels[current->value.value] = i+1;
        }
        else if(Is_jmp_function(current))
        {
            if(!labels.count((*current)[0]->value.value))
                Error_Dont_Init_Label((*current)[0]->value.value, current->value.line);
        }

        current->value.line = i+1;
    }
}


void Pre_Convert::Convert_Expr(Tree* Expr)
{
    assert(Expr);
    if(Expr->value.type != REG)
        Error_Invalid_Data();

    assert(Expr->get_number_of_children());
    Tree* own = (*Expr)[0];
    if(own->value.type != OP)
        Error_Invalid_Data();

    assert(own->get_number_of_children());
    Tree* main_Expr = (*own)[0];

    Push_Tree(main_Expr);

    token tok_pop("pop", OP, Expr->value.line);
    Tree* tree_push = Create_Tree(tok_pop);
    tree_push->Add_Child(Create_Tree(Expr->value));

    output_tree->Add_Child(tree_push);
}


void Pre_Convert::Push_Tree(Tree* subtree)
{
    assert(subtree);

    switch(subtree->value.type)
    {
        case REG:
            Push_Reg_or_Num(subtree);
            break;
        case NUM:
            Push_Reg_or_Num(subtree);
            break;
        case MATH_OP:
            Push_Math_Op(subtree);
            break;

        default:
            Error_Invalid_Data();
    }
}


void Pre_Convert::Push_Reg_or_Num(Tree* subtree)
{
    assert(!subtree->get_number_of_children());

    token tok_push("push", OP, 0);
    Tree* tree_push = Create_Tree(tok_push);
    tree_push->Add_Child(Copy_Tree(subtree));
    output_tree->Add_Child(tree_push);
}


void Pre_Convert::Push_Math_Op(Tree* subtree)
{
    assert(subtree);

    string str_Math_Op = subtree->value.value;

    if( str_Math_Op == "+" )
    {
        Push_Tree((*subtree)[0]);
        Push_Tree((*subtree)[1]);

        token tok_add("add", OP, 0);
        output_tree->Add_Child(Create_Tree(tok_add));
    }
    else if( str_Math_Op == "-" )
    {
        Push_Tree((*subtree)[0]);
        Push_Tree((*subtree)[1]);

        token tok_add("sub", OP, 0);
        output_tree->Add_Child(Create_Tree(tok_add));
    }
    else if( str_Math_Op == "*" )
    {
        Push_Tree((*subtree)[0]);
        Push_Tree((*subtree)[1]);

        token tok_add("mul", OP, 0);
        output_tree->Add_Child(Create_Tree(tok_add));

    }
    else if( str_Math_Op == "/" )
    {
        Push_Tree((*subtree)[0]);
        Push_Tree((*subtree)[1]);

        token tok_add("div", OP, 0);
        output_tree->Add_Child(Create_Tree(tok_add));
    }


    else
       Error_Invalid_Data();
}


void Pre_Convert::Error_Invalid_Data()
{
    error = true;
    Errors.push_back("\nНеправильные данные в процессе Pre-Convert.\nОшибка скорее всего произошла в процессе построения дерева\nОбратитесь к криворукому дауну, который жто написал.\n");
}


void Pre_Convert::Error_Mult_Init_Label(string name_label, size_t line)
{
    error = true;

    char char_name_label[128];
    char error_str[256];

    strncpy(char_name_label, name_label.c_str(), 128);

    sprintf(error_str, "\nОшибка в строке %d. Повторная инициализация метки %s.\n", line, char_name_label);

    Errors.push_back(error_str);
}


void Pre_Convert::Error_Dont_Init_Label(string name_label, size_t line)
{
    error = true;

    char char_name_label[128];
    char error_str      [256];

    strncpy(char_name_label, name_label.c_str(), 128);

    sprintf(error_str, "\nОшибка в строке %d. Прыжок по неинициализированной метке %s.\n", line, char_name_label);

    Errors.push_back(error_str);
}


void Pre_Convert::print_Errors()
{
    int size = Errors.size();

    if(error)
    {
        for(int i=0; i<size; i++)
            cout<<Errors[i];
    }
    else
        cout<<"В процессе Pre-Convert не встречено ошибок\n";
}


void Pre_Convert::print_labels()
{
    for (auto it = labels.begin(); it != labels.end(); ++it)
        cout << it->first << " : "<< it->second << endl;
}
