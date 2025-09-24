#include <complex.h>
#include <ncurses.h>
#include <stdio.h>

#define KEY_ESC 27

int close(){
	endwin(); 
	printf("Caput\n");
	return 0;
}
int main()
{	

	int y=0, x=0, ch;	
	ESCDELAY = 0;
	bool exit = false;

	// setup	
	initscr();
	cbreak();
	noecho();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	// main loop
	while(1){
		ch = wgetch(stdscr);
		wmove(stdscr,5,0);
		wprintw(stdscr,"%d\n",ch);
		waddch(stdscr,ch);
		switch (ch) {
			case KEY_ESC: 
			case 'q':
			 	goto close;
				break;
			case 'j':
			case KEY_DOWN:
				if(y<LINES-1) y++;
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

		wmove(stdscr, y, x);
		refresh();
	}

close:
	
	return close();
}
