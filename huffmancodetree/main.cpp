#include <iostream>
#include "huffmancodetree.h"


int main() {
    char ch[] = "aeistdn";
    int w[] = {10, 15, 12, 3, 4, 13, 1};
    hfTree<char> tree(ch, w, 7);
    hfTree<char>::hfCode huffman_code[7];

    tree.get_code(huffman_code);
    std::cout << "Huffman code for '" << ch << "': \n";
    for (int i = 0; i < 7; ++i)
        std::cout << huffman_code[i].data << ' ' << huffman_code[i].code << std::endl;
    return 0;
}
