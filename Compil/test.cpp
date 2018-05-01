#include"tokenator/tokenator.hpp"
#include"RDP/RDP.hpp"
#include"Converter/Converter.hpp"
#include"Pre_Convert/Pre_Convert.hpp"

#include<fstream>

int main()
{
    ifstream file("input.txt");
    Tokenator t(&file);
    Run_Tokenizator(t);

    RDP rdp(t.arr_token);

    file.close();
    Tree* tree = Parser(rdp);
    rdp.print_Errors();
    tree->print_DOT();
    Pre_Convert pr_conv(tree);
    pr_conv.Start_Pre_Convert();
    pr_conv.print_Errors();
    return 0;
}
