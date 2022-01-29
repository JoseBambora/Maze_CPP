class Matrix{
    unsigned int sizex;
    unsigned int sizey;
    struct matriz *lines_columns;
public:
    void init_Matrix(int,int);
    void inc_elem(int,int);
    void all_zeros();
    bool loop_matrix(int,int);
    void free_matrix();
    void print_matrix();
};
