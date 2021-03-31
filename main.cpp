#include <iostream>
#include "binarytree.h"
#include "linklist.h"
#include "seqlist.h"


int main() {
//    binaryTree<char> tree;
//    tree.create_tree('@');
//    tree.pre_order();
//    tree.mid_order();
//    tree.post_order();
//    tree.level_order();
//    print_tree(tree, '@');
//    tree.del_left('L');
//    tree.del_right('C');
//    tree.del_left('C');
//    print_tree(tree, '@');
//    std::cout << tree.empty();
//    char pre[7] = "ABDEFC";
//    char mid[7] = "DBEFAC";
//    tree.build_tree(pre, mid, 6);
//    print_tree(tree, '@');
    seqList<int> ls;
    std::cout << ls.empty();
    for (int i = 0; i < 10; ++i){
        ls.insert(i, i*i);
    }
    ls.traverse();
    std::cout << ls.empty();
    ls.remove(5);
    ls.traverse();
    std::cout << ls.length() << ls.visit(8);
    return 0;
}
