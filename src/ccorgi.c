// Uses ncurses to move corgis across the screen.
// See README.md for sample usage.

#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CORGI_WIDTH 12
#define CORGI_HEIGHT 4
#define CORGI_DELIM 6
#define MOVE_DELAY 100000  // Micro-seconds

int FLAG_corgi_count = 3;

// Two different corgis to print
// Printing two different corgis creates the illusion that the corgis are moving
// their legs.
char CORGI_1[CORGI_HEIGHT][CORGI_WIDTH] = {
    "      & &  ",
    " {___{  ' ;",
    " {      }` ",
    " //----\\\\ |",
};
char CORGI_2[CORGI_HEIGHT][CORGI_WIDTH] = {
    "      & &  ",
    " }___{  ' ;",
    " {      }' ",
    " \\\\----// |",
};


// Parses out flags from the command line.
// Currently parse:
// * -n [INTEGER]
void parse_flags(int argc, char* argv[]) {
  for (int i = 0; i < argc; ++i) {
    if (strcmp(argv[i], "-n") == 0) {
      if (i < argc - 1) {
        FLAG_corgi_count = atoi(argv[++i]);
        FLAG_corgi_count = FLAG_corgi_count < 1 ? 1 : FLAG_corgi_count;
      }
    }
  }
}


// Runs initializations for ncurses
void init_ncurses() {
  initscr();
  noecho();
  curs_set(FALSE);
}


// Prints the ground on which the corgis "walk".
void print_ground(int length) {
  for (int x = 0; x < length; ++x) {
    mvprintw(CORGI_HEIGHT - 1, x, "|");
  }
}


// Prints a corgi on the screen.
//
// |width| tells how much of the corgi to print - this is especially useful when
// the corgi reaches the end of the screen and only part of it can be displayed.
// If |width| is greater than CORGI_WIDTH, The |filler| character will be
// appended to the corgi on that given line.
// |x_0| and |y_0| tell the coordinates at which to print the corgi; |max_x| and
// |max_y| tell the dimensions of the screen. These dimensions make it possible
// to make sure no characters are printed out of bounds.
void print_corgi(char corgi[CORGI_HEIGHT][CORGI_WIDTH], int width, char filler,
                 int y_0, int x_0, int max_y, int max_x) {
  for (int y = 0; y < CORGI_HEIGHT; ++y) {
    if (y_0 + y < 0 || y_0 + y > max_y) continue;
    for (int x = 0; x < width; ++x) {
      if (x_0 + x < 0 || x_0 + x > max_x) continue;
      if (x >= CORGI_WIDTH) {
        mvprintw(y_0 + y, x_0 + x, "%c", filler);
      } else {
        mvprintw(y_0 + y, x_0 + x, "%c", corgi[y][x]);
      }
    }
  }
}


int main(int argc, char* argv[]) {
  int max_x;
  int max_y;
  bool corgi_type = false;

  parse_flags(argc, argv);
  init_ncurses();
  getmaxyx(stdscr, max_y, max_x);

  while (true) {
    for (int x = -(CORGI_WIDTH * FLAG_corgi_count +
                   CORGI_DELIM * (FLAG_corgi_count - 1));
         x < max_x; ++x) {
      getmaxyx(stdscr, max_y, max_x);
      erase();

      print_ground(max_x);

      // Alternate the printing of the corgis
      // |which_corgi| makes it such that each alternate corgi is different, and
      // when i increments all of the corgis switch, causing them to "walk".
      for (int i = 0; i < FLAG_corgi_count; ++i) {
        bool which_corgi = corgi_type ^ (i & 1);
        print_corgi(which_corgi ? CORGI_1 : CORGI_2, CORGI_WIDTH, ' ', 0,
                    x + i * (CORGI_WIDTH + CORGI_DELIM), max_y, max_x);
      }

      refresh();
      usleep(MOVE_DELAY);
      corgi_type = !corgi_type;
    }
  }

  endwin();
  return 0;
}
