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
    public:
        ifstream* input;

        vector<string> arr_Errors;
        bool error;

    public:
        vector<token>  arr_token;

    public:
        Tokenator(ifstream* input);
        ~Tokenator();
        Tokenator(const Tokenator& t);

    public:
        vector<token> convert_string_to_token(string str, size_t line);
        vector<string> cut_string(string in_str);
        bool isdigit(const char symbol);
        bool Is_Int_Number(const string str);
    public:
        void Error_More_Than_One_Operator_at_Line  (const string err_token, size_t line);
        void Error_Invalid_Token                   (const string err_token, size_t line);
        void Error_There_arent_any_Operator_at_Line(const string err_line,  size_t line);

        void print_Errors();

    public:
        friend void Run_Tokenizator(Tokenator& tokenator);
};


#endif
