#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main(int argc, char *argv[]) {
 int x = 0, y = 0;
 int max_y = 0, max_x = 0;
 int next_x = 0;
 int direction = 1;

 initscr();
 noecho();
 curs_set(FALSE);

 // Global var `stdscr` is created by the call to `initscr()`
 char ch;

 while(1) {
    getmaxyx(stdscr, max_y, max_x);
    clear();
    mvprintw(y, x, "o");
    refresh();

    usleep(DELAY);

    next_x = x + direction;

    if (next_x >= max_x || next_x < 0) {
        //vrati sa naspat
        //direction*= -1;
        x = 0;
    } else {
        x+= direction;
    }
    
    timeout(10);
    if ((ch = getch()) == 100) { // 100 means a "d". Note also that i used getch() not getchar()
      break;
    }
 }

 endwin();
}