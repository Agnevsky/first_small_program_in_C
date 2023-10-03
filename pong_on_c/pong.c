#include <stdio.h>
//основная функция вызывающая остальные функции
void ping_pong(void);
//рисунок поля и остальных элементов
void print_screen(int S1, int S2, int xb, int yb, int yr1, int yr2, int w, int h);
//вывод победителя
void game_over(int S1, int S2, int fin);
//подсчет очков
int score_p1(int xb, int yb, int yr1, int S1, int w);
int score_p2(int xb, int yb, int yr2, int S2);
//движение мячика
int mv_ball_y(int yb, int step, int h);
int mv_ball_x(int xb, int step, int w);
int mv_ball_y_step(int yb, int step, int h);
int mv_ball_x_step(int xb, int yb, int yr1, int yr2, int step, int w);
//движение ракеток
int mv_racket_1(int yr1, char c1, int h);
int mv_racket_2(int yr2, char c1, int h);
//очистка буфера
void clear(void);

int main(void) {
    ping_pong();

    return 0;
}

void ping_pong(void) {
    int HEIGHT = 25;
    int WIDTH = 80;

    int y_rocket_1 = HEIGHT / 2 + 1;  //начальные координаты ракеток
    int y_rocket_2 = HEIGHT / 2 + 1;

    int x_ball = WIDTH / 2;  //начальные координаты мяча
    int y_ball = HEIGHT / 2;
    int end = 21;    // GG
    int step_y = 1;  //шаг для мячика
    int step_x = 1;
    int score_1 = 0, score_2 = 0;  // счет каждого игрока в начале игры

    while (score_1 != end || score_2 != end) {
        clear();

        print_screen(score_1, score_2, x_ball, y_ball, y_rocket_1, y_rocket_2, WIDTH, HEIGHT);

        char c_1 = getc();  //ввод третьего символа - должен быть enter
        //движение ракеток
        y_rocket_1 = mv_racket_1(y_rocket_1, c_1, HEIGHT);
        y_rocket_2 = mv_racket_2(y_rocket_2, c_1, HEIGHT);
        //движение ball
        step_y = mv_ball_y_step(y_ball, step_y, HEIGHT);
        step_x = mv_ball_x_step(x_ball, y_ball, y_rocket_1, y_rocket_2, step_x, WIDTH);
        x_ball = mv_ball_x(x_ball, step_x, WIDTH);
        y_ball = mv_ball_y(y_ball, step_y, HEIGHT);

        if (score_1 == end || score_2 == end) {
            clear();
            game_over(score_1, score_2, end);
            break;
        }
        //подсчет очков
        score_1 = score_p1(x_ball, y_ball, y_rocket_1, score_1, WIDTH);
        score_2 = score_p2(x_ball, y_ball, y_rocket_2, score_2);
        //если счет доешл до 21
    }
}
void print_screen(int S1, int S2, int xb, int yb, int yr1, int yr2, int w, int h) {
    //вывод счета
    printf("SCORE: P1 %d:%d P2 ", S1, S2);
    //вывод поля (заменить имена ракеток и мяча!)
    for (int y = 1; y <= h; y++) {
        for (int x = 1; x <= w; x++) {
            //пустые ячейки под вывод счета
            if (S1 < 10 && S2 < 10) {
                if (x <= 17 && y == 1) continue;
            } else if (S1 < 10 || S2 < 10) {
                if (x <= 18 && y == 1) continue;
            } else if (S1 > 10 && S2 > 10) {
                if (x <= 19 && y == 1) continue;
            }
            //рисунок границ поля
            if (y == 1 || x == 1 || y == h || x == w) printf("*");
            //рисунок левой ракетки
            else if ((x == 3) && (y == yr1 || y == yr1 - 1 || y == yr1 + 1))
                printf("|");
            //рисунок правой ракетки
            else if ((x == w - 2) && (y == yr2 || y == yr2 - 1 || y == yr2 + 1))
                printf("|");
            //рисунок мяча
            else if (x == xb && y == yb)
                printf("o");
            //внутренние пробелы
            else
                printf(" ");
            //перенос на новую строку
            if (x == w) printf("\n");
        }
    }
}
void game_over(int S1, int S2, int fin) {
    if (S1 == fin || S2 == fin) {
        if (S1 == fin) {
            printf("********************************************************************************\n");
            printf("*                                                                              *\n");
            printf("*                                                                              *\n");
            printf("*             *       *   *****   *      *      ****     **                    *\n");
            printf("*             *       *     *     * *    *      *   *     *                    *\n");
            printf("*             *       *     *     *   *  *      *   *     *                    *\n");
            printf("*             *   *   *     *     *     **      ****      *                    *\n");
            printf("*             * *   * *     *     *      *      *         *                    *\n");
            printf("*             *       *   *****   *      *      *       *****                  *\n");
            printf("*                                                                              *\n");
            printf("* ******************************************************************************\n");
            printf("*                       * *      * *    *       *    * * *                     *\n");
            printf("*                     *        *     *  * *   * *  *                           *\n");
            printf("*                     *        *     *  *   *   *  *                           *\n");
            printf("*                     *   * *  * * * *  *       *  * * *                       *\n");
            printf("*                     *     *  *     *  *       *  *                           *\n");
            printf("*                       * *    *     *  *       *    * * *                     *\n");
            printf("*                                                                              *\n");
            printf("*                        * *    *     *    * * *   * * *                       *\n");
            printf("*                      *     *  *     *  *         *     *                     *\n");
            printf("*                      *     *  *     *  *         *     *                     *\n");
            printf("*                      *     *  *   *    * * *     * * *                       *\n");
            printf("*                      *     *  *   *    *         *     *                     *\n");
            printf("*                        * *      *        * * *   *      *                    *\n");
            printf("********************************************************************************\n");
        }
        if (S2 == fin) {
            printf("********************************************************************************\n");
            printf("*                                                                              *\n");
            printf("*                                                                              *\n");
            printf("*             *       *   *****   *      *      ****     ***                   *\n");
            printf("*             *       *     *     * *    *      *   *   *   *                  *\n");
            printf("*             *       *     *     *   *  *      *   *     *                    *\n");
            printf("*             *   *   *     *     *     **      ****    *                      *\n");
            printf("*             * *   * *     *     *      *      *       *                      *\n");
            printf("*             *       *   *****   *      *      *        ****                  *\n");
            printf("*                                                                              *\n");
            printf("* ******************************************************************************\n");
            printf("*                       * *      * *    *       *    * * *                     *\n");
            printf("*                     *        *     *  * *   * *  *                           *\n");
            printf("*                     *        *     *  *   *   *  *                           *\n");
            printf("*                     *   * *  * * * *  *       *  * * *                       *\n");
            printf("*                     *     *  *     *  *       *  *                           *\n");
            printf("*                       * *    *     *  *       *    * * *                     *\n");
            printf("*                                                                              *\n");
            printf("*                        * *    *     *    * * *   * * *                       *\n");
            printf("*                      *     *  *     *  *         *     *                     *\n");
            printf("*                      *     *  *     *  *         *     *                     *\n");
            printf("*                      *     *  *   *    * * *     * * *                       *\n");
            printf("*                      *     *  *   *    *         *     *                     *\n");
            printf("*                        * *      *        * * *   *      *                    *\n");
            printf("********************************************************************************\n");
        }
    }
}
int score_p1(int xb, int yb, int yr1, int S1, int w) {
    if (xb == w - 1 && (yb != yr1 && yb != yr1 - 1 && yb != yr1 + 1)) S1++;
    return S1;
}
int score_p2(int xb, int yb, int yr2, int S2) {
    if (xb == 2 && (yb != yr2 && yb != yr2 - 1 && yb != yr2 + 1)) S2++;
    return S2;
}
int mv_ball_y(int yb, int step, int h) {
    yb += step;
    //если столкнулся с верхней границей меняем направление по оси у
    if (yb == 1) step *= -1;
    //если столкнулся с нижней границей
    if (yb == h) step *= -1;
    return yb;
}
int mv_ball_x(int xb, int step, int w) {
    xb += step;
    //меняем направление по оси х
    if (xb == 1) step *= -1;
    if (xb == w) step *= -1;
    return xb;
}
int mv_ball_y_step(int yb, int step, int h) {
    yb += step;
    //если столкнулся с верхней границей меняем направление по оси у
    if (yb == 1) step *= -1;
    //если столкнулся с нижней границей
    if (yb == h) step *= -1;
    return step;
}
int mv_ball_x_step(int xb, int yb, int yr1, int yr2, int step, int w) {
    xb += step;
    //если столкнулся с ракеткой меняем направление по оси х
    if (xb == 3 && (yb == yr1 || yb == yr1 - 1 || yb == yr1 + 1)) step *= -1;
    if (xb == w - 3 && (yb == yr2 || yb == yr2 - 1 || yb == yr2 + 1)) step *= -1;
    if (xb == 1) step *= -1;
    if (xb == w) step *= -1;
    return step;
}
int mv_racket_1(int yr1, char c1, int h) {
    if (c1 == 'A' || c1 == 'a') {
        if (yr1 > 3) yr1--;
    }
    if (c1 == 'Z' || c1 == 'z') {
        if (yr1 < h - 2) yr1++;
    }

    return yr1;
}
int mv_racket_2(int yr2, char c1, int h) {
    if (c1 == 'K' || c1 == 'k') {
        if (yr2 > 3) yr2--;
    }
    if (c1 == 'M' || c1 == 'm') {
        if (yr2 < h - 2) yr2++;
    }

    return yr2;
}
void clear(void) { printf("\033[H\033[J"); }