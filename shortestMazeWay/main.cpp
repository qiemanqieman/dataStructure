#include <cstring>
#include <iostream>
#include <ctime>


#define R  9
#define C  9

int min(int a, int b)   {return (a < b) ? a : b;}

bool is_valid(int r, int c){
    return r < R and c < C and r >= 0 and c >= 0;
}

bool is_safe(int **maze, int **is_visited, int r, int c) {
    return maze[r][c] and !is_visited[r][c];
}

void find_shortest_way(int **maze, int **is_visited, int start_r, int start_c, int destination_r, int destination_c,
                       int distance, int &min_dist) {
    if (start_c == destination_c and start_r == destination_r){
        min_dist = min(min_dist, distance);
        return;
    }

    is_visited[start_r][start_c] = 1;

    if (is_valid(start_r - 1, start_c) and is_safe(maze, is_visited, start_r - 1, start_c))
        find_shortest_way(maze, is_visited, start_r - 1, start_c, destination_r, destination_c, distance + 1, min_dist);

    if (is_valid(start_r, start_c + 1) and is_safe(maze, is_visited, start_r, start_c + 1))
        find_shortest_way(maze, is_visited, start_r, start_c + 1, destination_r, destination_c, distance + 1, min_dist);

    if (is_valid(start_r + 1, start_c) and is_safe(maze, is_visited, start_r + 1, start_c))
        find_shortest_way(maze, is_visited, start_r + 1, start_c, destination_r, destination_c, distance + 1, min_dist);

    if (is_valid(start_r, start_c - 1) and is_safe(maze, is_visited, start_r, start_c - 1))
        find_shortest_way(maze, is_visited, start_r, start_c - 1, destination_r, destination_c, distance + 1, min_dist);

    is_visited[start_r][start_c] = 0;
}







int main()
{
//    int mat[R][L] = {
//            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//            1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1,
//            1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1,
//            1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1,
//            1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1,
//            1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1,
//            1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1,
//            1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1,
//            1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1,
//            1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1,
//            1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
//            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
////                1, 0, 0, 0,
////                1, 1, 1, 1,
////                0, 1, 0, 0,
////                1, 1, 1, 1
//    };

    int mat[R][C] =
            {
                    { 1, 1, 1, 0, 1, 1, 1, 1, 1},
                    { 1, 0, 1, 0, 1, 1, 1, 1, 1},
                    { 0, 1, 1, 0, 1, 1, 1, 1, 1},
                    { 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    { 1, 0, 1, 1, 0, 1, 1, 1, 1},
                    { 1, 1, 1, 0, 1, 1, 1, 1, 1},
                    { 1, 1, 1, 0, 1, 1, 0, 0, 0},
                    { 1, 1, 1, 0, 1, 1, 1, 1, 1},
                    { 1, 1, 1, 0, 1, 1, 1, 1, 1}
            };
    int **maze = new int*[R];
    for (int i = 0; i < R; ++i){
        maze[i] = mat[i];
    }
    int visit[R][C];
    memset(visit, 0, sizeof(visit));
    int **visited = new int*[R];
    for (int i = 0; i < R; ++i){
        visited[i] = visit[i];
    }
    int min_dist = INT32_MAX;
    std::cout << INT32_MAX << std::endl;

    long time_s = std::clock();
    find_shortest_way(maze, visited, 0, 0, R - 1, C - 1, 0, min_dist);
    long elapsed = std::clock() - time_s;

    if (min_dist < INT32_MAX)  std::cout << "The shortest path from source to destination has length " << min_dist << std::endl;
    else std::cout << "Destination cannot be reached from given source." << std::endl;
    std::cout << "Total time elapsed: " << (double)elapsed / CLOCKS_PER_SEC << "s" << std::endl;

    return 0;

}
