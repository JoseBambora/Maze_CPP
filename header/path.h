class Path{
private:
    struct path *p;
    struct caminho pop();
    void push(struct caminho);
    bool already_end();
    void play_left(struct caminho);
    void play_right(struct caminho);
    void play_up(struct caminho);
    void play_down(struct caminho);
    void play();
    void add_path(struct caminho,char,int,int);
public:
    void initial_play();
    void init_path(int,int,int,int,Maze);
    Path (int,int,int,int,Maze);
    void build_path();
    void build_maze();
    void print_path();
    void free_path();
    void generate_path();
    void c_maze();
    void game_path();
};