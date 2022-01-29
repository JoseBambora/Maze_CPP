#include <iostream>
#include <cstring>
#include <ncurses.h>
#include <queue>
#include "../header/maze.h"
#include "../header/matrix.h"
#include "../header/path.h"
using namespace std;

bool g = false;

typedef struct caminho{
    char *str;
    unsigned int len;
    int cx,cy;
}CAMINHO;

typedef struct path{
    queue <CAMINHO> queue_path;
    int xe,ye;
    int xi,yi;
    bool finish;
    Maze m;
    Matrix li_co;
}PATH;

void Path :: initial_play()
{
    CAMINHO c;
    c.cx = p->xi;
    c.cy = p->yi;
    c.len = 0;
    play_left(c);
    play_right(c);
    play_up(c);
    play_down(c);
}

void Path :: init_path(int x_i, int y_i, int x_e, int y_e, Maze m_)
{
    p = new PATH[1];
    p->xi = x_i;
    p->yi = y_i;
    p->xe = x_e;
    p->ye = y_e;
    p->m = m_;
    p->finish = false;
    p->li_co.init_Matrix(p->m.return_size_x(),p->m.return_size_y());
    initial_play();
}

Path ::Path(int x_i, int y_i, int x_e, int y_e, Maze m_)
{
    p = new PATH[1];
    p->xi = x_i;
    p->yi = y_i;
    p->xe = x_e;
    p->ye = y_e;
    p->m = m_;
    p->finish = false;
    p->li_co.init_Matrix(p->m.return_size_x(),p->m.return_size_y());
    initial_play();
}

void Path :: c_maze(){ p->m.complete_maze(p->xi,p->yi,p->xe,p->ye); }
bool Path :: already_end(){ return p->finish; }
void Path :: free_path() { delete p; }

CAMINHO Path ::pop()
{
    CAMINHO r = p->queue_path.front();
    r.str = strdup(p->queue_path.front().str);
    p->queue_path.pop();
    return r;
}

void Path ::push(CAMINHO c)
{
    if(!already_end())
    {
        if(c.cx == p->xe && c.cy == p->ye) p->finish = true;
        p->queue_path.push(c);
    }
}

void Path :: add_path(CAMINHO c, char move, int x, int y)
{
    CAMINHO pa = c;
    pa.str = new char [c.len + 1];
    if(c.len > 0) strcpy(pa.str,c.str);
    pa.cx = x;
    pa.cy = y;
    pa.str[pa.len] = move;
    pa.len++;
    p->li_co.inc_elem(x,y);
    push(pa);
}

void Path ::play_left(CAMINHO c)
{
    char piece = p->m.return_piece(c.cx - 1, c.cy);
    if(piece != '#' && (g || ((c.len == 0 || c.str[c.len - 1] != 'R') &&  !p->li_co.loop_matrix(c.cx-1,c.cy))))
        add_path(c,'L',c.cx-1,c.cy);
}

void Path ::play_right(CAMINHO c)
{
    char piece = p->m.return_piece(c.cx + 1, c.cy);
    if(piece != '#' && (g || ((c.len == 0 || c.str[c.len - 1] != 'L') && !p->li_co.loop_matrix(c.cx+1,c.cy))))
        add_path(c,'R',c.cx+1,c.cy);
}

void Path ::play_up(CAMINHO c)
{
    char piece = p->m.return_piece(c.cx, c.cy - 1);
    if(piece != '#' && (g || ((c.len == 0 || c.str[c.len - 1] != 'D') && !p->li_co.loop_matrix(c.cx,c.cy-1))))
        add_path(c,'U',c.cx,c.cy-1);
}
void Path ::play_down(CAMINHO c)
{
    char piece = p->m.return_piece(c.cx, c.cy + 1);
    if(piece != '#' && (g || (( c.len == 0 || c.str[c.len - 1] != 'U') && !p->li_co.loop_matrix(c.cx,c.cy+1))))
        add_path(c,'D',c.cx,c.cy+1);
}

void Path ::play()
{
    CAMINHO p = pop();
    play_left(p);
    play_up(p);
    play_right(p);
    play_down(p);
    if(p.len > 0) delete p.str;
}

void Path ::build_path()
{
    if(p->m.return_piece(p->xe,p->ye) == '#')
        cout << "Invalid Coords\n" << endl;
    else
        while(!already_end() && p->queue_path.size() > 0)
            play();
}

void Path ::build_maze()
{
    if(already_end())
    {
        CAMINHO c = p->queue_path.back();
        unsigned int i;
        unsigned int x = p->xi;
        unsigned int y = p->yi;
        for(i = 0; i < c.len - 1; i++)
        {
            switch (c.str[i])
            {
                case 'L':
                    x--;
                    break;
                case 'R':
                    x++;
                    break;
                case 'U':
                    y--;
                    break;
                case 'D':
                    y++;
                    break;
            }
            p->m.change_piece(x,y,'.');
        }
    }
    else
        cout << "Impossible Maze" << endl;
}

void Path ::print_path ()
{
    if(already_end())
    {
        p->m.print_maze();
        cout << "Initial coords: (" << p->xi << "," << p->yi << ")" << endl;
        cout << "Final coords:(" << p->xe << "," << p->ye << ")" << endl;
        CAMINHO aux = p->queue_path.back();
        cout << "Path: ";
        for(unsigned int j = 0; j < aux.len; j++)
            cout << aux.str[j];
        cout << endl;
    }
}

void Path :: generate_path()
{
    srand(time(NULL));
    while(!already_end())
    {
        CAMINHO c = pop();
        int aux = rand() % 8 + 1;
        switch (aux)
        {
            case 1:
                play_left(c);
                play_right(c);
                play_up(c);
                play_down(c);
                break;
            case 2:
                play_right(c);
                play_up(c);
                play_down(c);
                play_left(c);
                break;
            case 3:
                play_up(c);
                play_down(c);
                play_left(c);
                play_right(c);
                break;
            case 4:
                play_down(c);
                play_left(c);
                play_right(c);
                play_up(c);
                break;
            case 5:
                play_right(c);
                play_up(c);
                play_left(c);
                play_down(c);
                break;
            case 6:
                play_up(c);
                play_left(c);
                play_down(c);
                play_right(c);
                break;
            case 7:
                play_left(c);
                play_down(c);
                play_right(c);
                play_up(c);
                break;
            case 8:
                play_down(c);
                play_right(c);
                play_up(c);
                play_left(c);
                break;
        }
    }
}

void Path :: game_path()
{
    while(p->queue_path.size() > 0) pop();
    g = true;
    p->li_co.all_zeros();
    p->finish = false;
    CAMINHO c;
    c.cx = p->xi;
    c.cy = p->yi;
    c.len = 0;
    push(c);
    WINDOW *game_win;
    initscr();
	game_win = newwin(80,80, 0, 0);
	keypad(game_win, TRUE);
    while(!already_end())
    {
        c = pop();
        p->m.change_piece(c.cx,c.cy,'J');
        p->m.game_maze(game_win);
        int aux = wgetch(game_win);
        switch (aux)
        {
            case KEY_LEFT:
                play_left(c);
                break;
            case KEY_RIGHT:
                play_right(c);
                break;
            case KEY_UP:
                play_up(c);
                break;
            case KEY_DOWN:
                play_down(c);
                break;
            default:
                break;
        }
        if(p->queue_path.size() == 0) push(c);
        p->m.change_piece(c.cx,c.cy,' ');

    }
    wprintw(game_win,"Congratulation\n");
    wgetch(game_win);
    endwin();
}