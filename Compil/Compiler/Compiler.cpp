#include"Compiler.hpp"


Compiler::Compiler(ifstream* _input_file, ofstream* _output_file)
{
    assert(_input_file);
    assert(_output_file);

    output_file = _output_file;
    input_file  = _input_file;

    error = true;
}


Compiler::~Compiler()
{

}


bool Compiler::errors()
{
    return error;
}

void Compiler::Run_Compiler()
{
    Tokenator tokenator(input_file);
    Run_Tokenator(tokenator);
    if(!tokenator.error)
    {
        RDP rdp(tokenator.arr_token);
        Run_RDP(rdp);
        if(!rdp.errors)
        {
            Pre_Convert pre_conv(rdp.ret_tree);
            pre_conv.Run_Pre_Convert();
            if(!pre_conv.error)
            {
                Converter conv(pre_conv.get_Pre_Converted_Tree(), pre_conv.get_labels());
                conv.Run_Converter();

                vector<int> commands = conv.Get_Commands();
                for(int i=0; i<commands.size(); i++)
                   *output_file<<commands[i]<<endl;

                error = false;
            }
        }
    }
}
