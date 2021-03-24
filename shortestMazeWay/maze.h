//
// Created by q on 3/21/21.
//

#ifndef SHORTESTMAZEWAY_MAZE_H
#define SHORTESTMAZEWAY_MAZE_H


#include "../linkqueue.h"
#include "../linkStack.h"
#include <iostream>


struct cordination{
    int x;
    int y;
};


class maze{
private:
    int **routine;
    int row, column;

public:
    maze(int r, int c);
    maze(int **mat, int r, int c);
    [[nodiscard]] bool is_road(const cordination &c) const;
    [[nodiscard]] int find_shortest_way() const;
};


maze::maze(int r, int c) {
    row = r; column = c;
    routine = new int*[r];
    std::cout << "Creating a maze with " << r << " rows, " << c << " columns('0' for roads, " << row * column << " for walls):\n";
    for (int i = 0; i < r; ++i){
        routine[r] = new int[c];
        std::cout << "row " << i << ": ";
        for (int j = 0; j < c; ++j)
            std::cin >> routine[r][j];
    }
}

maze::maze(int **mat, int r, int c) {
    routine = mat;row = r; column = c;
    int t = r * c;
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            if (routine[i][j] == 1)
                routine[i][j] = t;
}

int maze::find_shortest_way() const {
    int **tmp = new int*[row];
    for (int i = 0; i < row; ++i) {
        tmp[i] = new int[column];
        for (int j = 0; j < column; ++j)
            tmp[i][j] = routine[i][j];
    }
    cordination cur, last;
    int count = 0;
    linkQueue<cordination> que;
    linkStack<cordination> s;
    cur = {0, 0};
    que.push(cur);
    while(!que.empty()){
        last = que.pop();

        cur = {last.x - 1, last.y};
        if ((cur.x!= 0 or cur.y != 0) and cur.x < row and cur.x >= 0 and cur.y < column and cur.y >= 0
                                         and tmp[cur.x][cur.y] == 0){
            que.push(cur);
            tmp[cur.x][cur.y] = tmp[last.x][last.y] + 1;
        }

        cur = {last.x, last.y + 1};
        if (cur.x == row - 1 and cur.y == column - 1) break;
        if (cur.x < row and cur.x >= 0 and cur.y < column and cur.y >= 0
            and tmp[cur.x][cur.y] == 0){
            que.push(cur);
            tmp[cur.x][cur.y] = tmp[last.x][last.y] + 1;
        }

        cur = {last.x + 1, last.y};
        if (cur.x == row - 1 and cur.y == column - 1) break;
        if (cur.x < row and cur.x >= 0 and cur.y < column and cur.y >= 0
            and tmp[cur.x][cur.y] == 0){
            que.push(cur);
            tmp[cur.x][cur.y] = tmp[last.x][last.y] + 1;
        }

        cur = {last.x, last.y - 1};
        if ((cur.x!= 0 or cur.y != 0) and cur.x < row and cur.x >= 0 and cur.y < column and cur.y >= 0
                                         and tmp[cur.x][cur.y] == 0){
            que.push(cur);
            tmp[cur.x][cur.y] = tmp[last.x][last.y] + 1;
        }
    }
    tmp[cur.x][cur.y] = tmp[last.x][last.y] + 1;
    
    if (cur.x != row - 1 or cur.y != column - 1) {
        std::cout << "There is no road to destination from source.\n";
        return -1;
    }
    
    count = tmp[row - 1][column - 1];
    s.push(cur);
    while(count--){
        last = cur;
        cur = {last.x - 1, last.y};
        if (cur.x < row and cur.x >= 0 and cur.y < column and cur.y >= 0 and tmp[cur.x][cur.y] == count){
            s.push(cur);
            continue;
        }
        
        cur = {last.x, last.y + 1};
        if (cur.x < row and cur.x >= 0 and cur.y < column and cur.y >= 0 and tmp[cur.x][cur.y] == count){
            s.push(cur);
            continue;
        }

        cur = {last.x + 1, last.y};
        if (cur.x < row and cur.x >= 0 and cur.y < column and cur.y >= 0 and tmp[cur.x][cur.y] == count){
            s.push(cur);
            continue;
        }

        cur = {last.x, last.y - 1};
        if (cur.x < row and cur.x >= 0 and cur.y < column and cur.y >= 0 and tmp[cur.x][cur.y] == count){
            s.push(cur);
            continue;
        }
    }
    
    std::cout << "Shortest road from source to destination: \n";
    while(!s.empty()){
        ++count;
        if (count % 5 == 0 and count > 0) std::cout << std::endl;
        cur = s.pop();
        std::cout << "(" << cur.x << ", " << cur.y<< ") -> ";
        std::flush(std::cout);
    }
    std::cout << "\b\b\b";

    return tmp[row - 1][column - 1];
}

bool maze::is_road(const cordination &c) const
{
    return c.x < row and c.x >= 0 and c.y < column and c.y >= 0
         and routine[c.x][c.y] == 0;
}

#endif //SHORTESTMAZEWAY_MAZE_H
