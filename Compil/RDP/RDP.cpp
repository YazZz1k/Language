#include"RDP.hpp"

RDP::RDP(vector<token> _arr)
{
    arr  = _arr;
    ptr  = 0;
}


RDP::~RDP()
{

}


Tree* RDP::Get_Push()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Reg_or_Num(line);

    if(arg)
        ret->Add_Child(arg);
    else
    {
        Error_Invalid_Arguments("push", line);
        skip_line(line);
    }

    return ret;
}


Tree* RDP::Get_Pop ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Reg(line);

    if(arg)
        ret->Add_Child(arg);
    else
    {
        Error_Invalid_Arguments("pop", line);
        skip_line(line);
    }

    return ret;
}

Tree* RDP::Get_Mov ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg_1 = Get_Reg(line);
    Tree* arg_2 = Get_Reg_or_Num(line);

    if(arg_1&&arg_2)
    {
        ret->Add_Child(arg_1);
        ret->Add_Child(arg_2);
    }
    else
    {
        Error_Invalid_Arguments("mov", line);
        skip_line(line);
    }

    return ret;
}

Tree* RDP::Get_Add ()
{
    return Create_Tree(arr[ptr++]);
}


Tree* RDP::Get_Sub ()
{
    return Create_Tree(arr[ptr++]);
}


Tree* RDP::Get_In()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Reg(line);

    if(arg)
        ret->Add_Child(arg);
    else
    {
        Error_Invalid_Arguments("in", line);
        skip_line(line);
    }

    return ret;
}


Tree* RDP::Get_Out ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Reg_or_Num(line);

    if(arg)
        ret->Add_Child(arg);
    else
    {
        Error_Invalid_Arguments("out", line);
        skip_line(line);
    }

    return ret;
}


Tree* RDP::Get_Cmp ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg_1 = Get_Reg_or_Num(line);
    Tree* arg_2 = Get_Reg_or_Num(line);

    if(arg_1&&arg_2)
    {
        ret->Add_Child(arg_1);
        ret->Add_Child(arg_2);
    }
    else
    {
        Error_Invalid_Arguments("cmp", line);
        skip_line(line);
    }

    return ret;
}


Tree* RDP::Get_Dec()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Reg(line);

    if(arg)
        ret->Add_Child(arg);
    else
    {
        Error_Invalid_Arguments("dec", line);
        skip_line(line);
    }

    return ret;
}


Tree* RDP::Get_Jmp ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Lab(line);

    if(arg)
        ret->Add_Child(arg);
    else
    {
        Error_Invalid_Arguments("jmp", line);
        skip_line(line);
    }

    return ret;
}


Tree* RDP::Get_Jnz ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Lab(line);

    if(arg)
        ret->Add_Child(arg);
    else
    {
        Error_Invalid_Arguments("jnz", line);
        skip_line(line);
    }

    return ret;
}


Tree* RDP::Get_Jne ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Lab(line);

    if(arg)
        ret->Add_Child(arg);
    else
    {
        Error_Invalid_Arguments("jne", line);
        skip_line(line);
    }

    return ret;

}


Tree* RDP::Get_Jle ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Lab(line);

    if(arg)
        ret->Add_Child(arg);
    else
    {
        Error_Invalid_Arguments("jle", line);
        skip_line(line);
    }

    return ret;
}


Tree* RDP::Get_Root()
{
    token t("ROOT", OP, 0);
    Tree* root = Create_Tree(t);


    Tree* added;
    size_t arr_size = arr.size();

    while(ptr < arr_size)
    {
        if(arr[ptr].type == OP)
        {
            if      ( arr[ptr].value == "push" )  added = Get_Push();
            else if ( arr[ptr].value == "pop"  )  added = Get_Pop ();
            else if ( arr[ptr].value == "add"  )  added = Get_Add ();
            else if ( arr[ptr].value == "mov"  )  added = Get_Mov ();
            else if ( arr[ptr].value == "sub"  )  added = Get_Sub ();
            else if ( arr[ptr].value == "in"   )  added = Get_In  ();
            else if ( arr[ptr].value == "out"  )  added = Get_Out ();
            else if ( arr[ptr].value == "cmp"  )  added = Get_Cmp ();
            else if ( arr[ptr].value == "dec"  )  added = Get_Dec ();
            else if ( arr[ptr].value == "jmp"  )  added = Get_Jmp ();
            else if ( arr[ptr].value == "jnz"  )  added = Get_Jnz ();
            else if ( arr[ptr].value == "jne"  )  added = Get_Jne ();
            else if ( arr[ptr].value == "jle"  )  added = Get_Jle ();
            else
            {
                Error_Unknown_Operator(arr[ptr].value, arr[ptr].line);
                skip_line(arr[ptr].line);
            }
        }
        else if((arr[ptr].type == PUN)&&(arr[ptr].value == "$"))
        {
            added = Get_Expr(arr[ptr].line);
        }
        else if(arr[ptr].type == LAB)
        {
            added = Create_Tree(arr[ptr++]);
        }
        else
        {
            Error_Need_Operator(arr[ptr].line);
            skip_line(arr[ptr].line);
        }

        if(!added)
        {
            Error_Unknown_Error(arr[ptr].line);
            skip_line(arr[ptr].line);
        }
        else
        {
            root->Add_Child(added);
        }
    }

    return root;
}


Tree* RDP::Get_Reg_or_Num(size_t line)
{
    if(arr[ptr].line != line)
        return NULL;

    return ((arr[ptr].type == NUM)||(arr[ptr].type == REG)) ? (Create_Tree(arr[ptr++])) : (NULL);
}


Tree* RDP::Get_Reg(size_t line)
{
    if(arr[ptr].line != line)
        return NULL;

    return (arr[ptr].type == REG) ? (Create_Tree(arr[ptr++])) : (NULL);
}


Tree* RDP::Get_Lab(size_t line)
{
    if(arr[ptr].line != line)
        return NULL;

    return (arr[ptr].type == LAB) ? (Create_Tree(arr[ptr++])) : (NULL);
}


Tree* RDP::Get_Own(size_t line)
{
    return ((arr[ptr].type == OP)&&(arr[ptr].value == "=")) ? (Create_Tree(arr[ptr++])) : (NULL);
}


Tree* RDP::Get_Expr(size_t line)
{
    errors = false;

    Tree* ret = Create_Tree(arr[ptr++]);
    Tree* added = Get_Reg(line);

    if(!added)
    {
        cout<<"Error 1 in Get_Expr\n";
        //Error_Need_Reg();
        skip_line(line);
        return ret;
    }
    ret->Add_Child(added);


    Tree* own = Get_Own(line);
    if(!own)
    {
        cout<<"Error2 in Get_Expr\n";
        //Error_Need_Owm();
        skip_line(line);
        return ret;
    }
    (*ret)[0]->Add_Child(own);


    Tree* Expr = Get_E(line);
    if(!Expr)
    {
        cout<<"Херовое выражение\n";
        skip_line(line);
        return ret;
    }
    own->Add_Child(Expr);


    if(!((arr[ptr].type == PUN)&&(arr[ptr].value == "$")))
    {
        if(!errors)
        {
            Error_Need_Dollar(line);
            skip_line(line);
            return ret;
        }
    }
    else
    {
        ptr++;
    }

    return ret;
}


bool RDP::Is_Math_Op(string op_name, size_t line)
{
    return ((arr[ptr].type == MATH_OP)&&(arr[ptr].value == op_name)&&(arr[ptr].line == line));
}


Tree* RDP::Get_E(size_t line)   //в дереве будет стоять только  +/-, а информация о знаке будет лежать в LINE  0 - "-", !0 - "+";
{
    Tree* added = Get_T(line);

    if(!(Is_Math_Op("+", line)||Is_Math_Op("-", line)))
        return added;

    token plus("PLUS/MINUS", OP, 0);
    Tree* ret = Create_Tree(plus);
    ret->Add_Child(added);

    size_t size = arr.size();
    int get_plus_or_minus; //0 - '-' !0 - "+"

    while(ptr<size)
    {
        if     (Is_Math_Op("+", line)) {ptr++; get_plus_or_minus = 1;}
        else if(Is_Math_Op("-", line)) {ptr++; get_plus_or_minus = 0;}
        else
        {
            return ret;
        }

        added = Get_T(line);
        if(!added)
        {
            Error_Invalid_Arg_for_Math_Op(arr[ptr-1].value, line);
            skip_line(line);
            return ret;
        }

        added->value.line = get_plus_or_minus;
        ret->Add_Child(added);
    }

    return ret;
}


Tree* RDP::Get_T(size_t line)
{
    Tree *ret,
         *added_right,
         *added_left = Get_P(line);

    if(Is_Math_Op("/", line)||Is_Math_Op("*", line))
    {
        ret = Create_Tree(arr[ptr++]);
    }
    else
    {
        return added_left;
    }

    ret->Add_Child(added_left);
    added_right = Get_T(line);

    if(!added_right)
    {
        Error_Invalid_Arg_for_Math_Op(arr[ptr-1].value, line);
        skip_line(line);
        return ret;
    }

    ret->Add_Child(added_right);

    return ret;

}


Tree* RDP::Get_P(size_t line)
{
    Tree* ret;

    if(arr[ptr].value == "(")
    {
        ptr++;
        ret = Get_E(line);
        if(arr[ptr].value == ")")
        {
            ptr++;
            return ret;
        }
        else
        {
            skip_line(line);
            return NULL;
        }
    }

    ret = Get_Reg_or_Num(line);

    return ret;
}

void RDP::skip_line(size_t skiped_line)
{
    size_t size = arr.size();

    cout<<"in skip_line\n";
    while((ptr<size)&&(arr[ptr].line == skiped_line))
    {
        cout<<arr[ptr].value<<'\n';
        ptr++;
    }

    cout<<"at end of skip_line  "<<arr[ptr].value<<'\n';
}

void RDP::Error_Invalid_Arg_for_Math_Op(const string op_name, size_t line)
{
    errors = true;
    char error_str[256];
    char tmp_str[128];

    strncpy(tmp_str, op_name.c_str(), 128);

    string tmp_error_str = "";
    int tmp_ptr = ptr;
    int err_ptr = ptr;

    while((arr[tmp_ptr].line == line)&&(tmp_ptr != 0))
    {
        tmp_ptr--;
    }

    while(tmp_ptr != err_ptr)
    {
        tmp_error_str+=arr[tmp_ptr++].value;
    }

    tmp_error_str+="(!Ошибка!)";

    while(arr[tmp_ptr].line == line)
    {
        tmp_error_str+=arr[tmp_ptr++].value;
    }

    tmp_error_str+='\n';

    sprintf(error_str, "\nОшибка в обработке выражения на строке %d. Неправильный аргумент для математического оператора %s\n", line, tmp_str);
    string string_error_str(error_str);
    string_error_str+=tmp_error_str;

    Errors.push_back(string_error_str);
}

void RDP::Error_Invalid_Arguments(const string op_name, size_t line)
{
    errors = true;
    char error_str[256];
    char tmp_str[128];

    strncpy(tmp_str, op_name.c_str(), 128);
    sprintf(error_str, "\nОшибка в строке %d. Неправильные аргументы для функци %s\n", line, tmp_str);

    Errors.push_back(error_str);

}


void RDP::print_Errors()
{
    if(Errors.size())
    {
        size_t size = Errors.size();

        for(int i=0; i<size; i++)
           cout<<Errors[i];
    }
    else
    {
        cout<<"В процессе построения дерева не выявлено ошибок\n";
    }
}


void RDP::Error_Need_Operator(size_t line)
{
    errors = true;
    char error_str[256];

    sprintf(error_str, "\nОшибка в строке %d. Необходим оператор\n", line);

    Errors.push_back(error_str);
}


void RDP::Error_Unknown_Operator(string op_name,size_t line)
{
    errors = true;
    char error_str[256];
    char tmp_str[128];

    strncpy(tmp_str, op_name.c_str(), 128);
    sprintf(error_str, "\nОшибка в строке %d. Неизвестный оператор %s\n", line, tmp_str);

    Errors.push_back(error_str);
}


void RDP::Error_Unknown_Error(size_t line)
{
    errors = true;
    char error_str[256];

    sprintf(error_str, "\nНеизвестная ошибка в строке %d\n", line);

    Errors.push_back(error_str);
}


void RDP::Error_Need_Dollar(size_t line)
{
    errors = true;
    char error_str[256];

    sprintf(error_str, "\nНеобходим $ в конце выражения на строке %d\n", line);

    Errors.push_back(error_str);
}


Tree* Parser(RDP& rdp)
{
    rdp.ret_tree = rdp.Get_Root();
    return Copy_Tree(rdp.ret_tree);
}


