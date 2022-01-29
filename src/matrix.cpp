#include "../header/matrix.h"
#include <iostream>
#include <vector>
using namespace std;

typedef struct matriz
{
    vector <vector <int>> ml;
} MATRIZ;

void Matrix :: init_Matrix (int x, int y)
{
    lines_columns = new MATRIZ[1];
    sizex = x;
    sizey = y;
    unsigned int i;
    vector <int> aux (x,0);
    for(i = 0; i  < sizey; i++)
        lines_columns->ml.push_back(aux);
}

void Matrix ::inc_elem(int x, int y)
{
    lines_columns->ml.at(y).at(x)++;
}

void Matrix ::all_zeros()
{
    unsigned int i,j;
    for(i = 0; i < sizey ;i++)
        for(j = 0; j < sizex; j++)
            lines_columns->ml.at(i).at(j) = 0;
}

bool Matrix ::loop_matrix(int x, int y)
{
    if(x < 0 || y < 0 || lines_columns->ml.at(y).at(x) == 1) return true;
    else return false;
}

void Matrix ::free_matrix()
{
    unsigned int i;
    for(i = 0; i < sizey ;i++)
        lines_columns->ml.at(i).clear();
    lines_columns->ml.clear();
}

void Matrix ::print_matrix()
{
    unsigned int i,j;
    for(i = 0; i < sizey ;i++)
    {
        for(j = 0; j < sizex; j++)
            cout << lines_columns->ml.at(i).at(j) << " ";
        cout << endl;
    }
    cout << "============================" << endl;
}