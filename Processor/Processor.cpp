#include"Processor.hpp"

Processor::Processor(ifstream* input_file)
{
    assert(input_file);
    in_commands(input_file);

    ptr = 0;

    reg.ax = 0;
    reg.bx = 0;
    reg.cx = 0;
    reg.dx = 0;

    flags.ZF = false;
    flags.EF = false;
    flags.LF = false;
}


Processor::~Processor()
{

}

void Processor::execute()
{
    bool end = false;

    while(!end)
    {
        //cout<<commands[ptr]<<endl;
        switch(commands[ptr])
        {
            case PUSH_REG:    push_reg();    break;
            case PUSH_NUM:    push_num();    break;
            case POP_REG:     pop_reg ();    break;
            case MOV_REG_REG: mov_reg_reg(); break;
            case MOV_REG_NUM: mov_reg_num(); break;
            case ADD:         add();         break;
            case SUB:         sub();         break;
            case IN_REG:      in_reg();      break;
            case OUT_REG:     out_reg();     break;
            case OUT_NUM:     out_num();     break;
            case CMP_NUM_REG: cmp_num_reg(); break;
            case CMP_NUM_NUM: cmp_num_num(); break;
            case CMP_REG_REG: cmp_reg_reg(); break;
            case CMP_REG_NUM: cmp_reg_num(); break;
            case DEC_REG:     dec_reg();     break;
            case JMP:         jmp();         break;
            case JNZ:         jnz();         break;
            case JNE:         jne();         break;
            case JLE:         jle();         break;
            case EMPTY:       ptr++;         break;

            case END: end = true; break;

            default: assert(0);
        }
    }
}


void Processor::in_commands(ifstream* input_file)
{
    int i=0;
    int tmp;
    while(!(*input_file).eof())
    {
        (*input_file)>>tmp;
        commands.push_back(tmp);
    }
}

int Processor::get_reg_value(int reg_name)
{
    switch(reg_name)
    {
        case AX: return reg.ax;
        case BX: return reg.bx;
        case CX: return reg.cx;
        case DX: return reg.dx;

        default: assert(0);
    }
}


int* Processor::get_reg(int reg_name)
{
    switch(reg_name)
    {
        case AX: return &reg.ax;
        case BX: return &reg.bx;
        case CX: return &reg.cx;
        case DX: return &reg.dx;

        default: assert(0);
    }

}


void Processor::push_reg()
{
    ptr++;
    stack.push(get_reg_value(commands[ptr]));
    ptr+=2;
}


void Processor::push_num()
{
    ptr++;
    stack.push(commands[ptr]);
    ptr+=2;
}


void Processor::pop_reg()
{
    ptr++;
    int* reg = get_reg(commands[ptr]);
    *reg = stack.pop();
    ptr+=2;
}


void Processor::mov_reg_reg()
{
    ptr++;
    int  num_reg = get_reg_value(commands[ptr]);
    ptr++;
    int* reg = get_reg(commands[ptr]);
    *reg = num_reg;
    ptr++;

}


void Processor::mov_reg_num()
{
    ptr++;
    int num = commands[ptr];
    ptr++;
    int* reg = get_reg(commands[ptr]);
    ptr++;
}


void Processor::add()
{
    stack.add();
    ptr+=3;
}


void Processor::sub()
{
    stack.sub();
    ptr+=3;
}


void Processor::in_reg()
{
    ptr++;
    int *reg = get_reg(commands[ptr]);
    scanf("%d", reg);
    ptr+=2;
}


void Processor::out_reg()
{
    ptr++;
    int* reg = get_reg(commands[ptr]);
    cout<<*reg<<endl;
    ptr+=2;
}


void Processor::out_num()
{
    ptr++;
    cout<<commands[ptr]<<endl;
    ptr+=2;
}


void Processor::cmp_reg_reg()
{
    int arg_1, arg_2; 
    ptr++;
    arg_1 = get_reg_value(commands[ptr]);
    ptr++;
    arg_2 = get_reg_value(commands[ptr]);
    ptr++;

    flags.EF = (arg_1 == arg_2) ? (true) : (false);
}



void Processor::cmp_num_reg()
{
    int arg_1, arg_2; 
    ptr++;
    arg_1 = commands[ptr];
    ptr++;
    arg_2 = get_reg_value(commands[ptr]);
    ptr++;

    flags.EF = (arg_1 == arg_2) ? (true) : (false);

}


void Processor::cmp_num_num()
{
    int arg_1, arg_2; 
    ptr++;
    arg_1 = commands[ptr];
    ptr++;
    arg_2 = commands[ptr];
    ptr++;

    flags.EF = (arg_1 == arg_2) ? (true) : (false);
}

void Processor::cmp_reg_num()
{
    int arg_1, arg_2; 
    ptr++;
    arg_1 = get_reg_value(commands[ptr]);
    ptr++;
    arg_2 = commands[ptr];
    ptr++;

    flags.EF = (arg_1 == arg_2) ? (true) : (false);
    flags.LF = (arg_1 <  arg_2) ? (true) : (false);
}


void Processor::dec_reg()
{
    ptr++;
    int* reg = get_reg(commands[ptr]);
    ptr+=2;
    (*reg)--;

    flags.ZF = !(bool)(*reg);
}


void Processor::jmp()
{
    ptr++;
    ptr = commands[ptr];
}


void Processor::jnz()
{
    ptr++;
    (flags.ZF) ? (ptr+=2) : (ptr = commands[ptr]);
}


void Processor::jne()
{
    ptr++;
    (flags.EF) ? (ptr+=2) : (ptr = commands[ptr]);
}


void Processor::jle()
{
    ptr++;
    (flags.LF) ? (ptr = commands[ptr]) : (ptr+=2);
}


