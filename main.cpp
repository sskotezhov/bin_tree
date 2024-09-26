#include <iostream>
#include "tree.cpp"
int main()
{
    SearchingTree<int, std::string> tree(1, "bebra");
    tree.insert(3, "bebra");
    tree.insert(4, "bb124");
    tree.insert(5, "fasgbb");
    tree.insert(6, "basd");
    tree.insert(9, "ddasdasdb");
    tree.insert(7, "gasbas");
    tree.insert(8, "aaaaaa");
    tree.insert(2, "lkhkjk");
    typename SearchingTree<int, std::string>::Node *node;
    for (auto i : tree)
    std::cout << i.key << "\n";
    SearchingTree<int, std::string>::Iterator iter = tree.find(4);
    std::cout << iter->key << iter->value << std::endl;
    return 0;
}