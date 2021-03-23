//
// Created by q on 3/21/21.
//

#ifndef SHORTESTMAZEWAY_MAZE_H
#define SHORTESTMAZEWAY_MAZE_H


#include <iostream>


class maze{
private:
    int **routine;
    int row, column;

public:
    maze(int r, int c);
    void find_shortest_way() const;
};


maze::maze(int r, int c) {
    row = r; column = c;
    routine = new int*[r];
    std::cout << "Creating a maze with " << r << " rows, " << c << " columns('1' for road, '0' for non_road):\n"
    for (int i = 0; i < r; ++i){
        routine[r] = new int[c];
        std::cout << "row " << i << ": ";
        for (int j = 0; j < c; ++j)
            cin >> routine[r][j];
    }
}

void maze::find_shortest_way() const {

}
#endif //SHORTESTMAZEWAY_MAZE_H
