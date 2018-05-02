#ifndef __Compiler__
#define __Compiler__

#include<fstream>

#include"../tokenator/tokenator.hpp"
#include"../RDP/RDP.hpp"
#include"../Pre_Convert/Pre_Convert.hpp"
#include"../Converter/Converter.hpp"

class Compiler
{
    private:
        ifstream* input_file;
        ofstream* output_file;

        bool error;
    public:
        bool errors();
        Compiler(ifstream* input_file, ofstream* output_file);
        ~Compiler();

        void Run_Compiler();
};

#endif
