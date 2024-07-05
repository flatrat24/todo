#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}
