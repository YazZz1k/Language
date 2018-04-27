#include"tokenator/tokenator.hpp"
#include"RDP/RDP.hpp"
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
    return 0;
}
