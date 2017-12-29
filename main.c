
#include <curses.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>

#define MAXWIDTH 100
#define MAXHEIGHT 40
#define DELAY 40000

int klavesa(void) {    /* kontroluje ci bola stlacena nejaka klavesa */
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0,&read_fd);
    if(select(1, &read_fd, NULL, NULL, &tv) == -1) return 0;
    if(FD_ISSET(0,&read_fd)) return 1;
    return 0;
}

int nabural(int *arrayHad) {    /* kontroluje ci had nabural do steny */
    int x = *arrayHad;
    int y = *(arrayHad+1);
    if (x < 0 || x > MAXWIDTH) {
        return 1;
    } else if (y < 0 || y > MAXHEIGHT) {
        return 1;
    } else return 0;
}

void pohyb(int *arrayHad, int smerX, int smerY, int dlzkaHada) {
    int oldX = 0;
    int oldY = 0;
    int nowX = *arrayHad;
    int nowY = *(arrayHad+1);
    int newX = nowX + smerX;
    int newY = nowY + smerY;

    *(arrayHad) = newX;
    *(arrayHad+1) = newY;
    mvprintw(newY, newX, "o");

    for (size_t i = 2; i < dlzkaHada * 2; i += 2) {
        oldX = nowX;
        oldY = nowY;
        nowX = *(arrayHad + i);
        nowY = *(arrayHad + i + 1);
        newX = oldX;
        newY = oldY;
        *(arrayHad + i) = newX;
        *(arrayHad + i + 1) = newY;
        mvprintw(newY, newX, "o");
    }

    if (smerY != 0) {
        usleep(DELAY);
    }
    usleep(DELAY);
}

void noveJablko(int* jablkoX, int* jablkoY, int *zjedene) {   /* jablko sa spawne na random pozicii, a dokym nie je zjedene tak sa spawnuje stale na tej istej pozicii */
    if (*zjedene) {
        srand(time(0));     //aktualny cas sa pouzije ako seed na radnom
        *jablkoX = (rand() % MAXWIDTH) + 1;
        *jablkoY = (rand() % MAXHEIGHT) + 1;
        *zjedene = 0;
    }
    mvprintw(*jablkoY, *jablkoX,"+");
}

void zjedenieJablka(int *arrayHad, int jablkoX, int jablkoY, int *zjedene, int *dlzkaHada) {
    int hadX = *arrayHad;
    int hadY = *(arrayHad + 1);
    if (hadX == jablkoX && hadY == jablkoY) {
        *zjedene = 1;
        *dlzkaHada += 1;
        int dlzka = *dlzkaHada;
        int lastX = *(arrayHad + dlzka * 2 - 2);
        int lastY = *(arrayHad + dlzka * 2 - 2 + 1);
        *(arrayHad + dlzka * 2) = lastX;
        *(arrayHad + dlzka * 2 + 1) = lastY;
    }
    mvprintw(1, 1, "skore: %d", *dlzkaHada);
}

int main() {
    
    int arrayHad[100][2];
    arrayHad[0][0] = 3;
    arrayHad[0][1] = 3;
    int smerX = 1;
    int smerY = 0;
    int jablkoX = 0;
    int jablkoY = 0;
    int zjedene = 1;
    int dlzkaHada = 3;
    int keyPressed = 0;

    initscr();			/* Start curses mode */
    curs_set(false);              /* Hide cursor */
    noecho();
    getch();           /* Hra zacne po stlaceni hocakej klavesi */
    
    while (!nabural(&arrayHad[0][0])) {
        erase();
        noveJablko(&jablkoX, &jablkoY, &zjedene);
        pohyb(&arrayHad[0][0], smerX, smerY, dlzkaHada);
        zjedenieJablka(&arrayHad[0][0], jablkoX, jablkoY, &zjedene, &dlzkaHada);
        refresh();

        /* ovladanie W-A-S-D */
        if (klavesa()) {
            keyPressed = getch();
            if (keyPressed == 'w') {
                smerY = -1;
                smerX = 0;
            }
            if (keyPressed == 's') {
                smerY = 1;
                smerX = 0;
            }
            if (keyPressed == 'a') {
                smerX = -1;
                smerY = 0;
            }
            if (keyPressed == 'd') {
                smerX = 1;
                smerY = 0;
            }
        }
    }
    
    erase();
    mvprintw(MAXHEIGHT / 2, MAXWIDTH / 4, "Koniec hry! Skore: %d", dlzkaHada);
    refresh();
    getch();
    endwin();			/* End curses mode */
    return 0;
}
