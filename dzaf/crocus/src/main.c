// // /*
// // ** EPITECH PROJECT, 2026
// // ** main.c
// // ** File description:
// // ** main function for the project
// // */

// // #include "my.h"

// // int main(int argc, char **argv)
// // {
// //     char *str = NULL;
// //     parsing_t *pars = init_parsing();

// //     if (!pars)
// //         return free_ret(str, pars, 84);
// //     handle_parsing(argv, pars);
// //     if (!handle_error(argc, pars))
// //         return free_ret(str, pars, 84);
// //     str = create_string(pars);
// //     if (!str)
// //         return free_ret(str, pars, 84);
// //     print_nbr(pars->flag_n, str);
// //     return free_ret(str, pars, 0);
// // }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SQRT2 0.7071067811865475244

typedef struct move_s {
    char *dir;
    double move;
    double x;
    double y;
} move_t;

int main() {
    move_t struc;
    char dir[3];
    int n;

    struc.x = 0.0;
    struc.y = 0.0;

    if (scanf("%d", &n) != 1) return 84;
    if (n < 1)
        return 0;

    if (scanf("%lf %lf", &struc.x, &struc.y) != 2) return 84;

    for (int i = 0; i < n - 1; i++) {
        if (scanf("%2s %lf", dir, &struc.move) != 2) return 84;

        if (strcmp(dir, "N") == 0)
            struc.y += struc.move;
        else if (strcmp(dir, "S") == 0)
            struc.y -= struc.move;
        else if (strcmp(dir, "E") == 0)
            struc.x += struc.move;
        else if (strcmp(dir, "W") == 0)
            struc.x -= struc.move;
        else if (strcmp(dir, "NE") == 0) {
            struc.x += struc.move * SQRT2;
            struc.y += struc.move * SQRT2;
        }
        else if (strcmp(dir, "NW") == 0) {
            struc.x -= struc.move * SQRT2;
            struc.y += struc.move * SQRT2;
        }
        else if (strcmp(dir, "SE") == 0) {
            struc.x += struc.move * SQRT2;
            struc.y -= struc.move * SQRT2;
        }
        else if (strcmp(dir, "SW") == 0) {
            struc.x -= struc.move * SQRT2;
            struc.y -= struc.move * SQRT2;
        }
    }

    printf("%.8f, %.8f\n", struc.x, struc.y);
    return 0;
}