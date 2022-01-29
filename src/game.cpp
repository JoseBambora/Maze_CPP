#include <ncurses.h>
#include <iostream>
#include "../header/maze.h"
#include "../header/matrix.h"
#include "../header/path.h"
#include "../header/game.h"
using namespace std;

void game()
{
    Maze m;
    string str;
    cout << "Size of maze:" << endl;
    cout << "X:" << endl;
    cin >> str;
    int x = stoi(str);
    cout << "Y:" << endl;
    cin >> str;
    int y = stoi(str);
    m.start_maze(x,y);
    srand(time(NULL));
    int xi = rand() % x;
    int yi = rand() % y;
    int xe = rand() % x;
    int ye = rand() % y;
    if(xi < 1) xi++;
    else if(xi == x - 1) xi--;
    if(xe < 1) xe++;
    else if(xe == x - 1) xe--;
    if(yi < 1) yi++;
    else if(yi == y - 1) yi--;
    if(ye < 1) ye++;
    else if(ye == y - 1) ye--;
    Path p (xi,yi,xe,ye,m);
    p.generate_path();
    p.build_maze();
    p.c_maze();
    p.game_path();
}