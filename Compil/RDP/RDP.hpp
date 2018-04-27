#ifndef ___RDP___
#define ___RDP___

#include<vector>
#include<string>
using namespace std;

#include"../Tree/Tree.hpp"
#include"../tokenator/tokenator.hpp"
class RDP
{
    private:
        vector<token> arr;
        int ptr;

        bool errors;
        vector<string> Errors;

        Tree* ret_tree;
    public:
        RDP(vector<token> _arr);
        ~RDP();

        friend Tree* Parser(RDP& rdp);

    private:
        Tree* Get_Root();
        Tree* Get_Reg_or_Num(size_t line);
        Tree* Get_Reg(size_t line);
        Tree* Get_Lab(size_t line);

        Tree* Get_Push();
        Tree* Get_Pop ();
        Tree* Get_Add ();
        Tree* Get_Mov ();
        Tree* Get_Sub ();
        Tree* Get_In  ();
        Tree* Get_Out ();
        Tree* Get_Cmp ();
        Tree* Get_Dec ();
        Tree* Get_Jmp ();
        Tree* Get_Jnz ();
        Tree* Get_Jne ();
        Tree* Get_Jle ();

        Tree* Get_Expr(size_t line);
        Tree* Get_E(size_t line);
        Tree* Get_T(size_t line);
        Tree* Get_P(size_t line);

        Tree* Get_Own(size_t line);

        bool Is_Math_Op(string op_name, size_t line);
    private:
        void skip_line(size_t line);
        void Error_Invalid_Arguments            (string op_name, size_t line);
        void Error_Invalid_Arg_for_Math_Op(string op_name, size_t line);
        void Error_Need_Operator(size_t line);
        void Error_Unknown_Operator(string op_name, size_t line);
        void Error_Unknown_Error(size_t line);
        void Error_Need_Dollar(size_t line);
    public:
        void print_Errors();
};

Tree* Parser();

#endif
