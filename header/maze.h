#include <string>
class Maze
{
private:
    struct maze *lab;
    unsigned complete_line(unsigned,unsigned,unsigned);
public:
    Maze ();
    unsigned return_size_y() const;
    unsigned return_size_x() const;
    char return_piece(unsigned, unsigned);
    void set_maze(std :: string);
    void print_maze();
    void change_piece(int,int, char );
    void change_piece2(int,int, char );
    void give_position(int *,int *,int *,int *);
    void start_maze(unsigned,unsigned);
    void complete_maze(int,int,int,int);
    void game_maze(void *);
};