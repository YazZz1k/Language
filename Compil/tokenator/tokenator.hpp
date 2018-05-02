#ifndef __TOKENATOR__
#define __TOKENATOR__

#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<cstring>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
using namespace std;

#include"token_struct.hpp"


class Tokenator
{
    private:
        ifstream* input;

        vector<string> arr_Errors;

    public:
        bool error;

        vector<token>  arr_token;

    public:
        Tokenator(ifstream* input);
        ~Tokenator();
        Tokenator(const Tokenator& t);

    private:
        vector<token> convert_string_to_token(string str, size_t line);
        vector<string> cut_string(string in_str);
        bool isdigit(const char symbol);
        bool Is_Int_Number(const string str);
        bool Is_Reg(const string str);
    public:
        void Error_More_Than_One_Operator_at_Line  (const string err_token, size_t line);
        void Error_Invalid_Token                   (const string err_token, size_t line);
        void Error_There_arent_any_Operator_at_Line(const string err_line,  size_t line);

        void print_Errors();

    public:
        friend void Run_Tokenator(Tokenator& tokenator);
};


#endif
