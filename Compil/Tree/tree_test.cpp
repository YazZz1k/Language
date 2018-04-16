#include"tree.hpp"


int main()
{
    Tree<int>* tree = tree->Create_Tree(0);
    for(int i=0; i<5; i++)
        tree->Add_Child(tree->Create_Tree(i));

   // tree[0];
    for(int i=0; i<4; i++)
        (*tree)[0]->Add_Child(tree->Create_Tree(i));
    tree->print_DOT();
}
