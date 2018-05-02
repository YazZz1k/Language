
#include<iostream>
#include<fstream>
#include<string.h>

#include"Compil/Compiler/Compiler.hpp"
#include"Processor/Processor.hpp"

bool Compil(ifstream* in_f, ofstream* out_f)
{
    Compiler compiler(in_f, out_f);
    compiler.Run_Compiler();

    return compiler.errors();
}

void Run(ifstream* in_f)
{
    Processor proc(in_f);
    proc.execute();
}


void Error_Cant_Open_File(string input)
{
    cout<<"Не удалось открыть файл "<<input<<endl;
}


void Error_Invalid_Arg()
{
    cout<<"Получены неправильные аргументы командной строки.\nДля вызова недоМана вызовите программу с ключём -h.\n"<<endl;
}


void Help()
{
    cout<<
    "Как это запускать::\n"<<
    "-o - ключ для выбора файла, в котором после компиляции будет храниться \"машиный\" код.\n"<<
    "В случае, если ключ не указан программой создаётся файл \"output.my\"\n\n"<<
    "-с  - компиляция\n"<<
    "пример использования:\n"<<
    "./kir-- -c <имя файла с кодом> -o <выходной файл>\n"<<
    "или же:\n"<<
    "./kir-- -c <имя файла с кодом>\n\n"<<
    "-r  - запуск\n"<<
    "пример использования:\n"<<
    "./kir-- -r <имя файла с \"машинным\" кодом>\n\n"<<
    "-cr - компиляция и запуск\n"<<
    "пример использования:\n"<<
    "./kir-- -cr <имя файла с кодом> -o <выходной файл>\n"<<
    "или же:\n"<<
    "./kir-- -cr <имя файла с кодом>\n\n"
    <<endl;
}

int main(int argv, char** argc)
{
    bool compil         = false;   //-c
    bool run            = false;   //-r
    bool compil_and_run = false;   //-rc
    string output = "output.my";
    string input  = "";

    if((argv<2)||(argv>5))
    {
        Error_Invalid_Arg();
        return 1;
    }

    if(!strcmp(argc[1], "-h")) Help();
    else if(!strcmp(argc[1], "-c"))
    {
        if(argv == 3)
        {
            input = argc[2];
            compil = true;
        }
        else if(argv == 5)
        {
            input = argc[2];
            if(!strcmp(argc[3], "-o"))
            {
                compil = true;
                output = argc[4];
            }
            else
            {
                Error_Invalid_Arg();
                return 1;
            }
        }
        else
        {
            Error_Invalid_Arg();
            return 1;
        }
    }
    else if(!strcmp(argc[1], "-r"))
    {
        if(argv == 3)
        {
            run = true;
            input = argc[2];
        }
    }
    else if(!strcmp(argc[1], "-cr"))
    {
        if(argv == 3)
        {
            input = argc[2];
            compil_and_run = true;
        }
        else if(argv == 5)
        {
            input = argc[2];
            if(!strcmp(argc[3], "-o"))
            {
                compil_and_run = true;
                output = argc[4];
            }
            else
            {
                Error_Invalid_Arg();
                return 1;
            }
        }
        else
        {
            Error_Invalid_Arg();
            return 1;
        }

    }
    else
    {
        Error_Invalid_Arg();
        return 1;
    }


    ifstream in_f;
    ofstream out_f;

    if(compil)
    {
        in_f. open(input);
        out_f.open(output);

        if(!in_f)
        {
            Error_Cant_Open_File(input);
            return 1;
        }

        Compil(&in_f, &out_f);
        in_f.close();
        out_f.close();
    }
    else if(run)
    {
        in_f. open(input);

        if(!in_f)
        {
            Error_Cant_Open_File(input);
            return 1;
        }

        Run(&in_f);
        in_f.close();
    }
    else if(compil_and_run)
    {
        in_f. open(input);
        out_f.open(output);

        if(!in_f)
        {
            Error_Cant_Open_File(input);
            return 1;
        }

        Compil(&in_f, &out_f);
        out_f.close();
        in_f.close();

        in_f.open(output);
        Run(&in_f);
        in_f.close();
    }


    return 0;
}
