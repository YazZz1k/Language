#include"RDP.hpp"

RDP::RDP(vector<token> _arr)
{
    arr  = _arr;
    ptr  = 1;
    arr_size = arr.size();
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

    if(arg&&(arr[ptr].line != line))
        ret->Add_Child(arg);
    else
        Error_Invalid_Arguments("push", line);

    return ret;
}


Tree* RDP::Get_Pop ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Reg(line);

    if(arg&&(arr[ptr].line != line))
        ret->Add_Child(arg);
    else
    {
        cout<<arr[ptr].line;
        Error_Invalid_Arguments("pop", line);
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

    if((arg_1&&arg_2)&&(arr[ptr].line!= line))
    {
        ret->Add_Child(arg_1);
        ret->Add_Child(arg_2);
    }
    else
        Error_Invalid_Arguments("mov", line);

    return ret;
}

Tree* RDP::Get_Add ()
{
    Tree* ret = Create_Tree(arr[ptr++]);

    if(arr[ptr].line == arr[ptr-1].line)
        Error_Invalid_Arguments("add", arr[ptr].line);

    return ret;
}


Tree* RDP::Get_Sub ()
{
    Tree* ret = Create_Tree(arr[ptr++]);

    if(arr[ptr].line == arr[ptr-1].line)
        Error_Invalid_Arguments("sub", arr[ptr].line);

    return ret;
}


Tree* RDP::Get_In()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Reg(line);

    if(arg&&(arr[ptr].line != line))
        ret->Add_Child(arg);
    else
        Error_Invalid_Arguments("in", line);

    return ret;
}


Tree* RDP::Get_Out ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Reg_or_Num(line);

    if(arg&&(arr[ptr].line != line))
        ret->Add_Child(arg);
    else
        Error_Invalid_Arguments("out", line);

    return ret;
}


Tree* RDP::Get_Cmp ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg_1 = Get_Reg_or_Num(line);
    Tree* arg_2 = Get_Reg_or_Num(line);

    if((arg_1&&arg_2)&&(arr[ptr].line != line))
    {
        ret->Add_Child(arg_1);
        ret->Add_Child(arg_2);
    }
    else
        Error_Invalid_Arguments("cmp", line);

    return ret;
}


Tree* RDP::Get_Dec()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Reg(line);

    if(arg&&(arr[ptr].line != line))
        ret->Add_Child(arg);
    else
        Error_Invalid_Arguments("dec", line);

    return ret;
}


Tree* RDP::Get_Jmp ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Lab(line);

    if(arg&&(arr[ptr].line != line))
        ret->Add_Child(arg);
    else
        Error_Invalid_Arguments("jmp", line);

    return ret;
}


Tree* RDP::Get_Jnz ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Lab(line);

    if(arg&&(arr[ptr].line != line))
        ret->Add_Child(arg);
    else
        Error_Invalid_Arguments("jnz", line);

    return ret;
}


Tree* RDP::Get_Jne ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Lab(line);

    if(arg&&(arr[ptr].line != line))
        ret->Add_Child(arg);
    else
        Error_Invalid_Arguments("jne", line);

    return ret;

}


Tree* RDP::Get_Jle ()
{
    size_t line = arr[ptr].line;

    Tree* ret = Create_Tree(arr[ptr++]);
    assert(ret);

    Tree* arg = Get_Lab(line);

    if(arg&&(arr[ptr].line != line))
        ret->Add_Child(arg);
    else
        Error_Invalid_Arguments("jle", line);

    return ret;
}


Tree* RDP::Get_Root()
{
    token t("ROOT", OP, 0);
    Tree* root = Create_Tree(t);


    Tree* added;

    while(arr[ptr].line < 100000)
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
                Error_Unknown_Operator(arr[ptr].value, arr[ptr].line);
        }
        else if(arr[ptr].type == REG)
            added = Get_Expr(arr[ptr].line);
        else if(arr[ptr].type == LAB)
            added = Create_Tree(arr[ptr++]);
        else
            Error_Need_Operator(arr[ptr].line);

        if(added)
            root->Add_Child(added);
    }
    errors = (bool)Errors.size();
    root->print_DOT();
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

    Tree* ret;

    Tree* reg = Get_Reg(line);
    assert(reg);
    if(!reg)
        cout<<"Ты обосрался и прога это поняла в Get_Expr\n";
    ret = reg;

    Tree* own = Get_Own(line);
    if(!own)
    {
        if(!errors)Error_Need_Own(line);
        return NULL;
    }
    reg->Add_Child(own);

    Tree* expr = Get_E(line);
    if(!expr)
    {
        if(!errors)Error_Invalid_Expression(line);
        return NULL;
    }
    own->Add_Child(expr);

    return ret;
}


Tree* RDP::Get_E(size_t line)
{
    Tree *added_left,
         *added_right,
         *ret;
    int copy_ptr;

    added_left = Get_T(line);

    if(!added_left)
    {
        if(Is_Math_Op("+", line)||Is_Math_Op("-", line))
            if(!errors)Error_Invalid_Arg_for_Math_Op(ptr, line);
        return NULL;
    }

    if(Is_Math_Op("+", line)||Is_Math_Op("-", line))
    {
        ret = Create_Tree(arr[ptr++]);
        ret->Add_Child(added_left);
    }
    else
        return added_left;

    copy_ptr = ptr;
    added_right = Get_E(line);
    if(!added_right)
    {
        if(!errors)Error_Invalid_Arg_for_Math_Op(copy_ptr, line);
        return NULL;
    }
    ret->Add_Child(added_right);

    return ret;
}


Tree* RDP::Get_T(size_t line)
{
    Tree *added_left,
         *added_right,
         *ret;
    int copy_ptr;

    added_left = Get_P(line);
    if(!added_left)
    {
        if(Is_Math_Op("*", line)||Is_Math_Op("/", line))
            if(!errors)Error_Invalid_Arg_for_Math_Op(ptr, line);
        return NULL;
    }


    if(Is_Math_Op("*", line)||Is_Math_Op("/", line))
    {
        ret = Create_Tree(arr[ptr++]);
        ret->Add_Child(added_left);
    }
    else
        return added_left;

    copy_ptr = ptr;
    added_right = Get_T(line);
    if(!added_right)
    {
        if(!errors)Error_Invalid_Arg_for_Math_Op(copy_ptr, line);
        return NULL;
    }
    ret->Add_Child(added_right);

    return ret;

}


Tree* RDP::Get_P(size_t line)
{
    Tree* ret;

    if(Is_PUN("(", line))
    {
        ptr++;
        ret = Get_E(line); //TO DO

        if(Is_PUN(")", line))
        {
            ptr++;
            return ret;
        }
        else
            if(!errors)Error_Need_Bracket(line);
    }

    return Get_Reg_or_Num(line);
}


bool RDP::Is_Math_Op(string op_name, size_t line)
{
    return ((arr[ptr].type == MATH_OP)&&(arr[ptr].value == op_name)&&(arr[ptr].line == line));
}

bool RDP::Is_PUN(string pun_name, size_t line)
{
    return ((arr[ptr].type == PUN)&&(arr[ptr].value == pun_name)&&(arr[ptr].line == line));
}


void RDP::skip_line(size_t skiped_line)
{
    size_t size = arr.size();

    while((ptr<size)&&(arr[ptr].line == skiped_line))
    {
        ptr++;
    }
}

string RDP::Get_Error_line(int error_ptr, size_t line)
{
    string tmp_error_str;
    int tmp_ptr = error_ptr;
    int err_ptr = error_ptr;
    int size_arr = arr.size();

    err_ptr++;
    while((arr[tmp_ptr].line == line)&&(tmp_ptr != 0))
    {
        tmp_ptr--;
    }

    if(arr[tmp_ptr].line != line)
        tmp_ptr++;


    while(tmp_ptr != err_ptr)
    {
        tmp_error_str+=arr[tmp_ptr++].value;
    }

    tmp_error_str+="(!)";

    while((tmp_ptr<size_arr)&&(arr[tmp_ptr].line == line))
    {
        tmp_error_str+=arr[tmp_ptr++].value;
    }

    tmp_error_str+='\n';

    return tmp_error_str;
}


void RDP::Error_Invalid_Arguments(const string op_name, size_t line)
{
    errors = true;
    char error_str[256];
    char tmp_str[128];

    strncpy(tmp_str, op_name.c_str(), 128);
    sprintf(error_str, "\nОшибка в строке %d. Неправильные аргументы для функци %s\n", line, tmp_str);

    Errors.push_back(error_str);

    skip_line(line);
}

void RDP::Error_Need_Operator(size_t line)
{
    errors = true;
    char error_str[256];

    sprintf(error_str, "\nОшибка в строке %d. Необходим оператор\n", line);

    Errors.push_back(error_str);

    skip_line(line);
}


void RDP::Error_Unknown_Operator(string op_name,size_t line)
{
    errors = true;
    char error_str[256];
    char tmp_str[128];

    strncpy(tmp_str, op_name.c_str(), 128);
    sprintf(error_str, "\nОшибка в строке %d. Неизвестный оператор %s\n", line, tmp_str);

    Errors.push_back(error_str);

    skip_line(line);
}


void RDP::Error_Unknown_Error(size_t line)
{
    errors = true;
    char error_str[256];

    sprintf(error_str, "\nНеизвестная ошибка в строке %d\n", line);

    Errors.push_back(error_str);
}


void RDP::Error_Invalid_Expression(size_t line)
{
    errors = true;
    char error_str[256];

    sprintf(error_str, "\nНеправильное выражение в строке %d\n", line);

    Errors.push_back(error_str);
}


void RDP::Error_Need_Own(size_t line)
{
    errors = true;
    char error_str[256];

    sprintf(error_str, "\nОшибка в строке %d.\nНеобходимо присваивание после регистра\n", line);

    Errors.push_back(error_str);

    skip_line(line);
}


void RDP::Error_Need_Bracket(size_t line)
{
    errors = true;
    char error_str[256];

    sprintf(error_str, "\nОшибка в строке %d.\nНеобходима закрываюшая скобка\n", line);

    Errors.push_back(error_str+Get_Error_line(ptr-1, line)+'\n');

    skip_line(line);
}

void RDP::Error_Invalid_Arg_for_Math_Op(int error_ptr, size_t line)
{
    errors = true;
    char error_str[256];

    sprintf(error_str, "\nОшибка в строке %d.\nНеправильный аргумент для математического оператора\n", line);

    Errors.push_back(error_str+Get_Error_line(error_ptr-1, line)+'\n');

    skip_line(line);
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


void Run_RDP(RDP& rdp)
{
    rdp.ret_tree = rdp.Get_Root();
    rdp.print_Errors();
}

