#include "../header/maze.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;

typedef struct maze
{
    vector <string> ll;
} LABIRINTO;

Maze ::Maze()
{
    lab = new LABIRINTO[1];
}

void Maze :: set_maze(string str)
{
    lab->ll.push_back(str);
}

void Maze :: print_maze()
{
    unsigned s = return_size_y();
    for(unsigned i = 0; i < s; i++)
        cout << lab->ll.at(i) << endl;
}

char Maze :: return_piece(unsigned x, unsigned y)
{
    char piece = 0;
    string s;
    if(y < return_size_y()) s = lab->ll.at(y);
    unsigned len = s.length();
    if(len > 0 && x < len) piece = s.at(x);
    return piece;
}

void Maze ::change_piece(int x, int y,char piece)
{
    if(lab->ll.at(y).at(x) != '.' || piece == 'J') lab->ll.at(y).at(x) = piece;
}

void Maze ::change_piece2(int x, int y,char piece)
{
    lab->ll.at(y).at(x) = piece;
}

unsigned int Maze :: return_size_y() const { return lab->ll.size(); }
unsigned int Maze :: return_size_x() const { return lab->ll.at(0).length();}

static bool all_diferent(int x,int y, int xe, int ye)
{
    if(x != -1 && xe != -1) return false;
    return true;
}

void Maze :: give_position(int *xi, int *yi, int *xe, int *ye)
{
    unsigned s = return_size_y();
    for(unsigned i = 0; i < s && all_diferent(*xi,*yi,*xe,*ye); i++)
    {
        string s = lab->ll.at(i);
        for(unsigned j = 0;  j < s.length() && all_diferent(*xi,*yi,*xe,*ye); j++)
        {
            switch (s.at(j))
            {
                case ('o'):
                    (*xi) = j;
                    (*yi) = i;
                    break;
                case ('x'):
                    (*xe) = j;
                    (*ye) = i;
                    break;
            }
        }
    }
}

void Maze :: start_maze(unsigned x, unsigned y)
{
    string s1 (x,'#');
    string s2 (x,' ');
    s2.at(0) = s2.at(x-1) = '#';
    set_maze(s1);
    for(unsigned i = 1; i < y-1; i++)
        set_maze(s2);
    set_maze(s1);
}

void Maze :: complete_maze(int xi,int yi, int xe,int ye)
{
    srand(time(NULL));
    unsigned s = return_size_y() - 1;
    for(unsigned i = 1; i < s; i++)
    {
        string s = lab->ll.at(i);
        for(unsigned j = 1; s.at(j) != '#';j++)
        {
            if(s.at(j) != '.')
            {
                int aux = rand() % 10 + 1;
                if(aux > 5)
                    change_piece(j,i,'#');
                else
                    change_piece(j,i,' ');
            }
            else
                change_piece2(j,i,' ');
        }
    }
    change_piece(xi,yi,'o');
    change_piece(xe,ye,'x');
}

unsigned Maze :: complete_line(unsigned liminf, unsigned limsup, unsigned line)
{
    unsigned i;
    for(i = liminf; i <= limsup; i++)
        change_piece(i,line,'#');
    return i;
}

void Maze :: game_maze(void *g_win )
{
    auto game_win = (WINDOW *) g_win;
    wclear(game_win);
    unsigned s = return_size_y();
    unsigned sx = return_size_x();
    for(unsigned i = 0; i < s; i++)
    {
        string s = lab->ll.at(i);
        for(unsigned j = 0; j < sx ; j++)
            wprintw(game_win,"%c",s.at(j));
        wprintw(game_win,"\n");
    }
}