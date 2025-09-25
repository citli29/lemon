#include <complex.h>
#include <ncurses.h>
#include <stdio.h>

#define KEY_ESC 27
#define FOOTER_H 4

enum MODE{
	INSERT,
	LIST,
	NORMAL
};

int y,x,input;
WINDOW * main_win;
WINDOW * footer_win;
bool quit;
bool first;

enum MODE mode;

int close(){
	if(main_win!=NULL)
		delwin(main_win);
	if(footer_win!=NULL)
		delwin(footer_win);
	if(stdscr!=NULL)
		endwin(); 
	printf("Caput\n");
	return 0;
}
int setup(){
	//variables
	ESCDELAY = 0;
	mode = NORMAL;
	quit = false;
	first = true;
	//setup windows
	if(initscr()==NULL) {
		printf("Error: initscr is NULL\n");
		return -1;
	}
	if(cbreak()==ERR) {
		printf("Error: cbreak\n");
		return -1;
	}
	if(noecho()==ERR) {
		printf("Error: noecho\n");
		return -1;
	}

	main_win = newwin(LINES-FOOTER_H, COLS, 0, 0);
	if(main_win ==NULL) {
		printf("Error: main_win is NULL\n");
		return -1;
	}
	footer_win = newwin(FOOTER_H, COLS, LINES-FOOTER_H, 0);
	if(footer_win ==NULL) {
		printf("Error: footer_win is NULL\n");
		return -1;
	}

	intrflush(main_win, FALSE);
	keypad(main_win, TRUE);
	intrflush(footer_win, FALSE);
	keypad(footer_win, TRUE);
	
	//
	return 0;
}
//proccess inputs
int process_input_normal(){

	switch (input) {
		case KEY_ESC: 
		case 'q':
			quit = true;
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

	return 0;
}
int process_input(){
	switch (mode) {
		case NORMAL:
			return process_input_normal();
		break;
		default:
		break;
	
	}
	return 0;
}
//drawing functions
void print_log_info(){
	wmove(footer_win,1,15);
	wclrtoeol(footer_win);
	wprintw(footer_win,"%c %d",input, input);
	wmove(footer_win,2,15);
	wclrtoeol(footer_win);
	wprintw(footer_win,"%d|%d",x,y);
	wmove(footer_win,3,15);
	wclrtoeol(footer_win);
	wprintw(footer_win,"%d|%d",LINES,COLS);
}
int draw_footer(){
	//wclear(footer_win);
	if(first){
		wmove(footer_win,0,0);
		whline(footer_win, ACS_HLINE, COLS);
		wmove(footer_win,1,0);
		wprintw(footer_win,"Key Press:");
		wmove(footer_win,2,0);
		wprintw(footer_win,"x|y:");
		wmove(footer_win,3,0);
		wprintw(footer_win,"Lines|Cols:");
		first = false;
	}
	print_log_info();
	wrefresh(footer_win);
}
int draw_main(){
	curs_set(1);
	wclear(main_win);
	wmove(main_win,y,x);
	wrefresh(main_win);
}
int main()
{	

	if(setup()==-1){
		close();
	}


	// main loop
	while(1){
		draw_footer();
		draw_main();
		input = wgetch(main_win);
		process_input();
		if(quit) break;
	}
	
	return close();
}
