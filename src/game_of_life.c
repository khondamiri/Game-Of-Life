#include <stdio.h>
#include <unistd.h>

#define ROWS 25
#define COLS 80
#define EPLISON 1e-6
#define SECONDS 999999

void initialize_pattern(int grid[ROWS][COLS]);
void draw_grid(const int grid[ROWS][COLS]);
int count_neighbors(int grid[ROWS][COLS], int x, int y);
void check_neighbors(int current[ROWS][COLS], int next[ROWS][COLS]);
void copy_grid(int grid[ROWS][COLS], int next_grid[ROWS][COLS]);

int main() {
    int grid[ROWS][COLS] = {0};
    int next_grid[ROWS][COLS] = {0};
    double speed;

    initialize_pattern(grid);

    if (scanf("%lf", &speed) != 1 || speed < 0.1 || speed > 1.0 + EPLISON) {
        printf("n/a");
        return 1;
    }

    while (1) {
        draw_grid(grid);
        check_neighbors(grid, next_grid);
        copy_grid(grid, next_grid);

        usleep(speed * SECONDS);
    }
    return 0;
}

void initialize_pattern(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (scanf("%d", &grid[i][j]) != 1) {
                grid[i][j] = 0;
            }
        }
    }
}

void draw_grid(const int grid[ROWS][COLS]) {
    printf("\033[H\033[J");  // terminal tozalash

    for (int i = 0; i < ROWS; i++) {  // grid chizish
        for (int j = 0; j < COLS; j++) {
            printf("%c", grid[i][j] ? '0' : '.');
        }
        printf("\n");
    }
}

int count_neighbors(int grid[ROWS][COLS], int x, int y) {
    int sum = 0;

    for (int i = -1; i < 2; i++) {  // atrofidegi cell-larni check qiladi
        for (int j = -1; j < 2; j++) {
            if (i != 0 || j != 0) {              // o'zini hisobga olmaydi
                int nx = (x + i + ROWS) % ROWS;  // vertikal
                int ny = (y + j + COLS) % COLS;  // gorizontal
                sum += grid[nx][ny];
            }
        }
    }
    return sum;
}

void check_neighbors(int current[ROWS][COLS], int next[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int live_neigbors = count_neighbors(current, i, j);
            if (current[i][j] == 1) {  // tirik bo'sa
                next[i][j] = (live_neigbors == 2 || live_neigbors == 3)
                                 ? 1
                                 : 0;  // tirik bo'sa, 2 yoki 3 ta qo'shnisi bo'lishi kk tirik qolish uchun
            } else {                   // o'lik b'osa
                next[i][j] =
                    (live_neigbors == 3) ? 1 : 0;  // o'lik bo'sa, 3 ta qo'shnisi bo'lishi kk tirilishi uchun
            }
        }
    }
}

void copy_grid(int grid[ROWS][COLS], int next_grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = next_grid[i][j];
        }
    }
}
