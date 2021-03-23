#include <iostream>
#include "binarytree.h"


int main() {
    binaryTree<char> tree;
    tree.create_tree('@');
    tree.pre_order();
    tree.mid_order();
    tree.post_order();
    tree.level_order();
    print_tree(tree, '@');
    tree.del_left('L');
    tree.del_right('C');
    tree.del_left('C');
    print_tree(tree, '@');
    return 0;
}
