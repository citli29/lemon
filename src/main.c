#include <complex.h>
#include <ncurses.h>
#include <stdio.h>

#define KEY_ESC 27
#define FOOTER_H 4
int y,x,ch;
WINDOW * main_win;
WINDOW * footer_win;

int close(){
	delwin(main_win);
	delwin(footer_win);
	endwin(); 
	printf("Caput\n");
	return 0;
}

int main()
{	

	ESCDELAY = 0;
	// setup	
	initscr();
	cbreak();
	noecho();

	main_win = newwin(LINES-FOOTER_H, COLS, 0, 0);
	footer_win = newwin(FOOTER_H, COLS, LINES-FOOTER_H, 0);
	
	intrflush(main_win, FALSE);
	keypad(main_win, TRUE);
	intrflush(footer_win, FALSE);
	keypad(footer_win, TRUE);
	//
	wborder(footer_win, ' ',' ',0,' ', ' ', ' ', ' ', ' ');
	wmove(footer_win,1,0);
	wprintw(footer_win,"This is a footer\n:)\n:o");
	wrefresh(footer_win);
	// main loop
	while(1){
		ch = wgetch(main_win);
		wmove(main_win,5,0);
		wprintw(main_win,"%d LINES: %d\n",ch, LINES);
		waddch(main_win,ch);
		switch (ch) {
			case KEY_ESC: 
			case 'q':
			 	goto close;
				break;
			case 'j':
			case KEY_DOWN:
				if(y<LINES-1-FOOTER_H) y++;
				break;
			case 'k':
			case KEY_UP:
				if(y>0) y--;
				break;
			case 'h':
			case KEY_LEFT:
				if(x>0) x--;
				break;
			case 'l':
			case KEY_RIGHT:
				if(x<(COLS-1)) x++;
				break;
		}

		wmove(main_win, y, x);
		wrefresh(main_win);
	}

close:
	
	return close();
}
