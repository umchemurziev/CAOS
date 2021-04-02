#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>


void write_matrix(int32_t *matrix, int rows, int col) {
    int32_t i = 1;
    int min_col = 0;
    int min_row = 0;
    int max_col = col;
    int max_row = rows;

    while (min_col < max_col && min_row < max_row) {
        int hl = min_col;
        while (max_col > hl) {
            matrix[hl + col * min_row] = i;
            ++hl;
            ++i;
        }
        min_row++;
        if (min_row >= max_row) break;
        int vl = min_row;
        while (max_row > vl) {
            matrix[vl * col + (max_col - 1)] = i;
            ++vl;
            ++i;
        }
        max_col--;
        if (min_col >= max_col) break;
        int hr = max_col;
        while (hr > min_col) {
            matrix[hr + col * (max_row - 1) - 1] = i;
            --hr;
            ++i;
        }
        max_row--;
        if (min_row >= max_row) break;
        int vr = max_row - 1;
        while (vr > min_row - 1) {
            matrix[vr * col + min_col] = i;
            --vr;
            ++i;
        }
        ++min_col;
    }
}


int main(int argc, char ** argv) {
    int rows = atoi(argv[2]);
    int col = atoi(argv[3]);
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0600, 0);
    int64_t sz = rows * col * sizeof(int32_t);
    ftruncate(fd, sz);
    int32_t *matrix = mmap(NULL, sz, PROT_WRITE, MAP_SHARED, fd, 0);
    write_matrix(matrix, rows, col);
    munmap(matrix, sz);
    close(fd);


    return 0;
}
