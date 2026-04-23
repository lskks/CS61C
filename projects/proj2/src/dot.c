#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void matmul(int* a0, int a1, int a2, int* a3, int a4, int a5, int* a6);
void relu(int* arr, int size);
int argmax(int* arr, int size);

int* read_matrix(char* filename, int* row, int* col)
{
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
        exit(27);

    read(fd, row, sizeof(int*));
    read(fd, col, sizeof(int*));

    int size = sizeof(int)* (*row) * (*col);

    int* matrix = (int*)malloc(size);

    if (matrix == NULL)
        exit(26);

    if (read(fd, matrix, size) != size)
        exit(29);
    

    if (close(fd) == -1)
        exit(28);

    return matrix;
}

void write_matrix(char* filename, int* matrix, int row, int col)
{
    int fd = open(filename, O_WRONLY);

    int* r = &row;
    int* c = &col;
    write(fd, r, 4);
    write(fd, c, 4);

    int size = row * col * 4;
    write(fd, matrix, size);

    close(fd);
}

int classify(int argc, char** argv, int is_print)
{
    if (argc != 5)
        exit(31);
    char* m0 = *(argv + 4); // first matrix file 
    char* m1 = *(argv + 8); // second matrix file 
    char* input = *(argv + 12);
    char* output = *(argv + 16);

    int* row0 = malloc(4);
    if (row0 == 0)
        exit(26);

    int* col0 = malloc(4);
    if (col0 == 0)
        exit(26);
    
    int* matrix0 = read_matrix(m0, row0, col0);
    if (matrix0 == 0)
        exit(26);
    
    int* row1 = malloc(4);
    if (row1 == 0)
        exit(26);

    int* col1 = malloc(4);
    if (col1 == 0)
        exit(26);

    int* matrix1 = read_matrix(m1, row1, col1);
    if (matrix1 == 0)
        exit(26);
    
    int* row2 = malloc(4);
    if (row2 == 0)
        exit(26);

    int* col2 = malloc(4);
    if (col2 == 0)
        exit(26);

    int* matrix_input = read_matrix(input, row2, col2);
    if (matrix_input == 0)
        exit(26);

    int* h = malloc(*col0 * *row2 * 4);
    matmul(matrix0, *row0, *col0, matrix_input, *row2, *col2, h);
    relu(h, *col0 * *row2);
    int *o = malloc(*col1 * *col0 * 4);
    matmul(matrix1, *row1, *col1, h, *col0, *row2, o);
    write_matrix(output, o, *col1, *col0);
    int ret = argmax(o, *col1 * *col0);

    if (is_print == 0)
        printf("%d", ret); // print_int(ret)

    free(row0);
    free(row1);
    free(row2);
    free(col0);
    free(col1);
    free(col2);
    free(matrix0);
    free(matrix1);
    free(matrix_input);
    free(h);
    free(o);
    
    return ret;
}