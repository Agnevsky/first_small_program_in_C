#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define W 80
#define H 25
#define LIVE '*'
#define DEAD ' '

void start_field(char array[H][W]);
int start_field_txt(char array[H][W]);
void print_field(char array[H][W]);
void rebuild_field(char array[H][W]);
int menu(char array[H][W]);
int wrap(int coord, int size);

int main() {
    char field[H][W];
    start_field(field);

    initscr();
    start_color();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    if (freopen("/dev/tty", "r", stdin)) {
        int speed = 100000;
        while (1) {
            int ch;
            ch = getch();

            if (ch == 'q') {
                return 0;
            }
            if (ch == 'a') {
                speed /= 5;
            }
            if (ch == 'z') {
                speed *= 5;
            }
            if (ch == 'r') {
                speed = 100000;
            }
            print_field(field);
            rebuild_field(field);

            usleep(speed);
        }
    }
    endwin();
    return 0;
}

void start_field(char array[H][W]) {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W + 1; x++) {
            char cell;
            if (scanf("%c", &cell) == 1) {
                if (cell == LIVE) {
                    array[y][x] = LIVE;

                } else {
                    array[y][x] = ' ';
                }
            }
        }
    }
}

void print_field(char array[H][W]) {  //печать массива и вывод инструкции

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            mvaddch(y, x, array[y][x]);
        }
    }
    printw(
        "\nInstruction:\n 1) For speed up or down press - 'a' or 'z'!\n 2) Refresh speed press - 'r'!\n 3) "
        "For quit press - 'q'!");
}

void rebuild_field(char array[H][W]) {
    char new_field[H][W];
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            int alive_count = 0;

            for (int y1 = -1; y1 <= 1; y1++) {
                for (int x1 = -1; x1 <= 1; x1++) {
                    if (x1 == 0 && y1 == 0) {
                        continue;
                    }
                    int nx = wrap(x + x1, W);
                    int ny = wrap(y + y1, H);
                    if (array[ny][nx] == LIVE) alive_count++;
                }
            }

            if (array[y][x] == LIVE) {
                if (alive_count < 2 || alive_count > 3) {
                    new_field[y][x] = DEAD;
                } else {
                    new_field[y][x] = LIVE;
                }
            } else {
                if (alive_count == 3) {
                    new_field[y][x] = LIVE;
                } else {
                    new_field[y][x] = DEAD;
                }
            }
        }
    }

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            array[y][x] = new_field[y][x];
        }
    }
}

int wrap(int coord, int size) {
    if (coord < 0) {
        return size - 1;
    } else if (coord >= size) {
        return 0;
    }
    return coord;
}
