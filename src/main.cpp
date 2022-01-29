#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "../header/maze.h"
#include "../header/game.h"
#include "../header/matrix.h"
#include "../header/path.h"
using namespace std;

// g++ src/main.cpp src/maze.cpp src/path.cpp src/matrix.cpp src/game.cpp -lncurses

static void rules()
{
    cout << "-----------------< RULES >--------------------" << endl;
    cout << "| For solving a maze:                        |" << endl;
    cout << "| 1º: Your Maze must have a start and an end |" << endl;
    cout << "| 2º: Char for the inicial Coords: 'o'       |" << endl;
    cout << "| 3º: Char for the end Coords: 'x'           |" << endl;
    cout << "| 4º: Char for walls: '#'                    |" << endl;
    cout << "| 5º: Char for empty places: ' '             |" << endl;
    cout << "----------------------------------------------" << endl; 
}

static void interation()
{
    Maze m;
    bool aux = true;
    string str;
    rules();
    while(aux)
    {
        cout << "Maze is in a File or you want to it draw? F: File D: Draw G: Game" << endl;
        cin >> str;
        if(str == "F" || str == "D" || str == "G")
            aux = false;
        else
            cout << "Invalid Command" << endl;
    }
    if(str == "G")
    {
        game();
        return;
    }
    else if(str == "F")
    {
        cout << "Insert the name of the file" << endl;
        cin >> str;
        ifstream file(str);
        while(getline(file,str))
            m.set_maze(str);
    }
    else
    {
        cout << "Start drawing line by line. When the maze is finished write 'Q'" << endl;
        getline(cin,str);
        for(getline(cin,str); str.at(0) != 'Q'; getline(cin,str))
            m.set_maze(str);
    }
    int xi,yi,xe,ye; 
    xi = yi = xe = ye = -1;
    m.give_position(&xi,&yi,&xe,&ye);
    Path cam (xi,yi,xe,ye,m);
    cam.build_path();
    cam.build_maze();
    cam.print_path();
}

int main() { interation(); }
