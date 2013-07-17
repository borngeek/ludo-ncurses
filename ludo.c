/*****************************************
* Developer - Anirban Chakraborty        *
* Name - ludo-ncurses                    *
* Date - Wed Jul 17 18:56:26 IST 2013    *
* Project - NCURSES based ludo.          * 
* License - Developers and users are     *
*           not supposed to remove or    *
*           alter this block of comment  *
*           although they are free to    *
*           alter the status of the      *
*           project. I must be intimated *
*           of any developments about    *
*           this project whatsoever.     *
* Status - Abandoned                     *
******************************************/

#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<curses.h>
#include<stdbool.h>
#define PATH_LENGTH 56		/*Includes path only. */
#define MS 1000

	/* Everywhere the sequence blue, red, green, yellow is maintained */
struct cell {
    short int presence;		// Presence of a pawn in cell can range from 0-4.
    short int x;		// coordinates of a pawn in a cell varies from 1-5 to 85-90.
    short int y;		// coordinates of a pawn in a cell varies from 1 to 30.
};

struct cell BLUE[PATH_LENGTH];
struct cell RED[PATH_LENGTH];
struct cell GREEN[PATH_LENGTH];
struct cell YELLOW[PATH_LENGTH];

struct cell blue_sp[4];
struct cell red_sp[4];
struct cell green_sp[4];
struct cell yellow_sp[4];

struct cell blue_h[4];
struct cell red_h[4];
struct cell green_h[4];
struct cell yellow_h[4];

short int toss[4];		//starting point stack tos
short int tohs[4];		//home stack tos

short int dice[3];		// A user can throw atmost 6,6,5 ie 3 times.

struct cell msg[4];

void init_ludo()
{				/* Initializes all the cell with there respective coordinates with no pawns 
				 * placed in the starting points.
				 */
    short int i, j;

    /* path cells */
    for (i = 0; i < PATH_LENGTH; i++)
	BLUE[i].presence = RED[i].presence = GREEN[i].presence =
	    YELLOW[i].presence = 0;
    for (i = 0; i < PATH_LENGTH; i++) {
	if (i >= 0 && i <= 4) {
	    BLUE[i].x = 37;
	    BLUE[i].y = 27 - (2 * i);
	    RED[i].x = 8 + (6 * i);
	    RED[i].y = 13;
	    GREEN[i].x = 52;
	    GREEN[i].y = 3 + (2 * i);
	    YELLOW[i].x = 83 - (6 * i);
	    YELLOW[i].y = 17;
	} else if (i >= 5 && i <= 10) {
	    BLUE[i].x = 31 - (6 * (i - 5));
	    BLUE[i].y = 17;
	    RED[i].x = 38;
	    RED[i].y = 11 - (2 * (i - 5));
	    GREEN[i].x = 58 + (6 * (i - 5));
	    GREEN[i].y = 13;
	    YELLOW[i].x = 53;
	    YELLOW[i].y = 19 + (2 * (i - 5));
	} else if (i >= 11 && i <= 12) {
	    BLUE[i].x = 1;
	    BLUE[i].y = 15 - (2 * (i - 11));
	    RED[i].x = 44 + (6 * (i - 11));
	    RED[i].y = 1;
	    GREEN[i].x = 88;
	    GREEN[i].y = 15 + (2 * (i - 11));
	    YELLOW[i].x = 47 - (6 * (i - 11));
	    YELLOW[i].y = 29;
	} else if (i >= 13 && i <= 17) {
	    BLUE[i].x = 7 + (6 * (i - 13));
	    BLUE[i].y = 13;
	    RED[i].x = 50;
	    RED[i].y = 3 + (2 * (i - 13));
	    GREEN[i].x = 82 - (6 * (i - 13));
	    GREEN[i].y = 17;
	    YELLOW[i].x = 41;
	    YELLOW[i].y = 27 - (2 * (i - 13));
	} else if (i >= 18 && i <= 23) {
	    BLUE[i].x = 37;
	    BLUE[i].y = 11 - (2 * (i - 18));
	    RED[i].x = 56 + (6 * (i - 18));
	    RED[i].y = 13;
	    GREEN[i].x = 52;
	    GREEN[i].y = 19 + (2 * (i - 18));
	    YELLOW[i].x = 35 - (6 * (i - 18));
	    YELLOW[i].y = 17;
	} else if (i >= 24 && i <= 25) {
	    BLUE[i].x = 43 + (6 * (i - 24));
	    BLUE[i].y = 1;
	    RED[i].x = 86;
	    RED[i].y = 15 + (2 * (i - 24));
	    GREEN[i].x = 46 - (6 * (i - 24));
	    GREEN[i].y = 29;
	    YELLOW[i].x = 5;
	    YELLOW[i].y = 15 - (2 * (i - 24));
	} else if (i >= 26 && i <= 30) {
	    BLUE[i].x = 49;
	    BLUE[i].y = 3 + (2 * (i - 26));
	    RED[i].x = 80 - (6 * (i - 26));
	    RED[i].y = 17;
	    GREEN[i].x = 40;
	    GREEN[i].y = 27 - (2 * (i - 26));
	    YELLOW[i].x = 11 + (6 * (i - 26));
	    YELLOW[i].y = 13;
	} else if (i >= 31 && i <= 36) {
	    BLUE[i].x = 55 + (6 * (i - 31));
	    BLUE[i].y = 13;
	    RED[i].x = 50;
	    RED[i].y = 19 + (2 * (i - 31));
	    GREEN[i].x = 34 - (6 * (i - 31));
	    GREEN[i].y = 17;
	    YELLOW[i].x = 41;
	    YELLOW[i].y = 11 - (2 * (i - 31));
	} else if (i >= 37 && i <= 38) {
	    BLUE[i].x = 85;
	    BLUE[i].y = 15 + (2 * (i - 37));
	    RED[i].x = 44 - (6 * (i - 37));
	    RED[i].y = 29;
	    GREEN[i].x = 4;
	    GREEN[i].y = 15 - (2 * (i - 37));
	    YELLOW[i].x = 47 + (6 * (i - 37));
	    YELLOW[i].y = 1;
	} else if (i >= 39 && i <= 43) {
	    BLUE[i].x = 79 - (6 * (i - 39));
	    BLUE[i].y = 17;
	    RED[i].x = 38;
	    RED[i].y = 27 - (2 * (i - 39));
	    GREEN[i].x = 10 + (6 * (i - 39));
	    GREEN[i].y = 13;
	    YELLOW[i].x = 53;
	    YELLOW[i].y = 3 + (2 * (i - 39));
	} else if (i >= 44 && i <= 49) {
	    BLUE[i].x = 49;
	    BLUE[i].y = 19 + (2 * (i - 44));
	    RED[i].x = 32 - (6 * (i - 44));
	    RED[i].y = 17;
	    GREEN[i].x = 40;
	    GREEN[i].y = 11 - (2 * (i - 44));
	    YELLOW[i].x = 59 + (6 * (i - 44));
	    YELLOW[i].y = 13;
	} else if (i >= 50 && i < PATH_LENGTH) {
	    BLUE[i].x = 45;
	    BLUE[i].y = 29 - (2 * (i - 50));
	    RED[i].x = 3 + (6 * (i - 50));
	    RED[i].y = 15;
	    GREEN[i].x = 45;
	    GREEN[i].y = 1 + (2 * (i - 50));
	    YELLOW[i].x = 87 - (6 * (i - 50));
	    YELLOW[i].y = 15;
	}
    }

    /* start point cells */
    for (i = 0; i < 4; i++)
	blue_sp[i].presence = red_sp[i].presence = green_sp[i].presence =
	    yellow_sp[i].presence = 0;

    blue_sp[0].y = 22;
    blue_sp[0].x = 9;
    blue_sp[1].y = 26;
    blue_sp[1].x = 9;
    blue_sp[2].y = 22;
    blue_sp[2].x = 27;
    blue_sp[3].y = 26;
    blue_sp[3].x = 27;

    red_sp[0].y = 4;
    red_sp[0].x = 9;
    red_sp[1].y = 8;
    red_sp[1].x = 9;
    red_sp[2].y = 4;
    red_sp[2].x = 27;
    red_sp[3].y = 8;
    red_sp[3].x = 27;

    green_sp[0].y = 4;
    green_sp[0].x = 63;
    green_sp[1].y = 8;
    green_sp[1].x = 63;
    green_sp[2].y = 4;
    green_sp[2].x = 81;
    green_sp[3].y = 8;
    green_sp[3].x = 81;

    yellow_sp[0].y = 22;
    yellow_sp[0].x = 63;
    yellow_sp[1].y = 26;
    yellow_sp[1].x = 63;
    yellow_sp[2].y = 22;
    yellow_sp[2].x = 81;
    yellow_sp[3].y = 26;
    yellow_sp[3].x = 81;

    for (i = 0; i < 4; i++)
	toss[i] = -1;


    /* home cells */
    for (i = 0; i < 4; i++)
	blue_h[i].presence = green_h[i].presence = red_h[i].presence =
	    yellow_h[i].presence = 0;

    for (i = 0; i < 4; i++) {
	blue_h[i].y = 17;
	blue_h[i].x = 42 + (2 * i);

	green_h[i].y = 13;
	green_h[i].x = 42 + (2 * i);
    }
    if (i % 2 == 0) {
	red_h[i].x = 37;
	yellow_h[i].x = 52;
    } else if (i % 2 != 0) {
	red_h[i].x = 38;
	yellow_h[i].x = 53;
    }
    red_h[i].y = 13 + i;
    yellow_h[i].y = 14 + i;

    for (i = 0; i < 4; i++)
	tohs[i] = -1;

    msg[0].presence = msg[1].presence = msg[2].presence = msg[3].presence =
	0;
    msg[0].y = 29;
    msg[0].x = 5;
    msg[1].y = 1;
    msg[1].x = 5;
    msg[2].y = 1;
    msg[2].x = 60;
    msg[3].y = 29;
    msg[3].x = 60;
}

void push(short int colour, short int num_of_pawns)	// Pushes pawn(s) back to starting point.
{
    short int i;
    if (colour == 1) {
	for (i = 0; i < num_of_pawns; i++) {
	    blue_sp[++toss[0]].presence = 1;
	}
	return;
    } else if (colour == 2) {
	for (i = 0; i < num_of_pawns; i++) {
	    red_sp[++toss[1]].presence = 1;
	}
	return;
    } else if (colour == 3) {
	for (i = 0; i < num_of_pawns; i++) {
	    green_sp[++toss[2]].presence = 1;
	}
	return;
    } else if (colour == 4) {
	for (i = 0; i < num_of_pawns; i++) {
	    yellow_sp[++toss[3]].presence = 1;
	}
	return;
    }
}

void pop(short int colour)	// Pops pawn out of starting point.
{
    if (colour == 1) {
	BLUE[0].presence++;
	blue_sp[toss[0]--].presence = 0;
	return;
    }
    if (colour == 2) {
	RED[0].presence++;
	red_sp[toss[1]--].presence = 0;
	return;
    }
    if (colour == 3) {
	GREEN[0].presence++;
	green_sp[toss[2]--].presence = 0;
	return;
    }
    if (colour == 4) {
	YELLOW[0].presence++;
	yellow_sp[toss[3]--].presence = 0;
	return;
    }
}

void push_home(short int colour, short int num_of_pawns)	// Pushes pawn(s) back to starting point.
{
    short int i;
    if (colour == 1) {
	for (i = 0; i < num_of_pawns; i++) {
	    blue_h[++tohs[0]].presence = 1;
	}
	return;
    } else if (colour == 2) {
	for (i = 0; i < num_of_pawns; i++) {
	    red_h[++tohs[1]].presence = 1;
	}
	return;
    } else if (colour == 3) {
	for (i = 0; i < num_of_pawns; i++) {
	    green_h[++tohs[2]].presence = 1;
	}
	return;
    } else if (colour == 4) {
	for (i = 0; i < num_of_pawns; i++) {
	    yellow_h[++tohs[3]].presence = 1;
	}
	return;
    }
}

void draw_board()		// Draws board.
{
    short int i;

    system("clear");
    initscr();
    start_color();
    wresize(stdscr, 31, 91);
    refresh();
    wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
    mvvline(1, 36, '|', 29);
    mvvline(1, 42, '|', 29);
    mvvline(1, 48, '|', 29);
    mvvline(1, 54, '|', 29);

    mvhline(12, 1, '-', 89);
    mvhline(14, 1, '-', 89);
    mvhline(16, 1, '-', 89);
    mvhline(18, 1, '-', 89);

    for (i = 0; i <= 90; i += 6) {
	mvprintw(12, i, "+");
	mvprintw(13, i, "|");
	mvprintw(14, i, "+");
	mvprintw(15, i, "|");
	mvprintw(16, i, "+");
	mvprintw(17, i, "|");
	mvprintw(18, i, "+");
    }

    for (i = 0; i <= 30; i += 2) {
	mvprintw(i, 36, "+-----+");
	mvprintw(i, 42, "+-----+");
	mvprintw(i, 48, "+-----+");
    }
    mvhline(14, 37, ' ', 17);
    mvhline(16, 37, ' ', 17);
    mvvline(13, 42, ' ', 5);
    mvvline(13, 48, ' ', 5);

    mvprintw(15, 42, "H O M E");
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvprintw(27, 37, "  *  ");
    for (i = 19; i <= 28; i += 2) {
	mvprintw(i, 43, "  ");
	mvprintw(i, 46, "  ");
    }
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(13, 7, "  *  ");
    for (i = 7; i <= 35; i += 3)
	mvprintw(15, i, "  ");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    mvprintw(3, 49, "  *  ");
    for (i = 3; i <= 12; i += 2) {
	mvprintw(i, 43, "  ");
	mvprintw(i, 46, "  ");
    }
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(4));
    mvprintw(17, 79, "  *  ");
    for (i = 55; i <= 84; i += 3)
	mvprintw(15, i, "  ");
    attroff(COLOR_PAIR(4));

    mvprintw(5, 37, "  *  ");
    mvprintw(13, 73, "  *  ");
    mvprintw(17, 13, "  *  ");
    mvprintw(25, 49, "  *  ");

    attron(COLOR_PAIR(5));
    mvprintw(22, 6, "[");
    mvprintw(22, 12, "]");
    mvprintw(26, 6, "[");
    mvprintw(26, 12, "]");
    mvprintw(22, 24, "[");
    mvprintw(22, 30, "]");
    mvprintw(26, 24, "[");
    mvprintw(26, 30, "]");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(6));
    mvprintw(4, 6, "[");
    mvprintw(4, 12, "]");
    mvprintw(8, 6, "[");
    mvprintw(8, 12, "]");
    mvprintw(4, 24, "[");
    mvprintw(4, 30, "]");
    mvprintw(8, 24, "[");
    mvprintw(8, 30, "]");
    attroff(COLOR_PAIR(6));

    attron(COLOR_PAIR(7));
    mvprintw(4, 60, "[");
    mvprintw(4, 66, "]");
    mvprintw(8, 60, "[");
    mvprintw(8, 66, "]");
    mvprintw(4, 78, "[");
    mvprintw(4, 84, "]");
    mvprintw(8, 78, "[");
    mvprintw(8, 84, "]");
    attroff(COLOR_PAIR(7));

    attron(COLOR_PAIR(8));
    mvprintw(22, 60, "[");
    mvprintw(22, 66, "]");
    mvprintw(26, 60, "[");
    mvprintw(26, 66, "]");
    mvprintw(22, 78, "[");
    mvprintw(22, 84, "]");
    mvprintw(26, 78, "[");
    mvprintw(26, 84, "]");
    attroff(COLOR_PAIR(8));

    refresh();
}

short int msg_gen(short int colour)
{
    short int i, ret_val, x, y, msgno;
    ret_val = -1;
    y = msg[colour - 1].y;
    x = msg[colour - 1].x;
    msgno = msg[colour - 1].presence;
    msg[colour - 1].presence = 0;

    if (msgno == 0) {
	mvprintw(y, x, "                        ");
	refresh();
	return ret_val;
    } else if (msgno == 1) {
	y--;
	for (i = 0; i < 3; i++) {
	    if (dice[i] != 0) {
		mvprintw(y + i, x, "       Dice[%d] : %d        ", i + 1,
			 dice[i]);
		refresh();
	    } else
		break;
	}
    } else if (msgno == 2) {
	mvprintw(y, x, "That pawn isn't out yet.");
	refresh();
	napms(MS);
	mvprintw(y, x, "  Enter valid pawnid:   ");
	ret_val = mvgetch(y, (x + 22)) - 48;
    } else if (msgno == 3) {
	mvprintw(y, x, "   Invalid pawnid.      ");
	refresh();
	napms(MS);
	mvprintw(y, x, "  Enter valid pawnid:   ");
	ret_val = mvgetch(y, (x + 22)) - 48;
    } else if (msgno == 4) {
	dice[0] = dice[1] = dice[2] = 0;
	mvprintw(y, x, "  Bad! Bad! Bad dice.   ");
	refresh();
	napms(MS);
	msg_gen(colour);
    } else if (msgno == 5) {
	mvprintw(y, x, " Your pawn(s) captured. ");
	refresh();
	napms(MS);
	msg_gen(colour);
    } else if (msgno == 6) {
	mvprintw(y, x, "   All pawns are out.    ");
	refresh();
	napms(MS);
	mvprintw(y, x, "   Enter valid pawnid:   ");
	ret_val = mvgetch(y, (x + 22)) - 48;
    }
    return ret_val;
}

void die(short int colour)
{
    short int tmp, i;
    dice[0] = dice[1] = dice[2] = 0;
    i = 0;
    do {
	do {
//          tmp = rand() % 7;
	    tmp = 6;
	} while (tmp == 0);
	dice[i] = tmp;
	if (dice[2] == 6) {
	    msg[colour - 1].presence = 4;
	    msg_gen(colour);
	    return;
	}
	i++;
    } while (i < 3 && dice[i - 1] == 6);
    return;
}

short int pontopos(short int colour, short int pon)
			// Returns the index of the array in which pawn of the said colour resides.
{
    int i, num;
    num = 0;
    if (pon > 4) {
	msg[colour - 1].presence = 3;
	pon = msg_gen(colour);
	return pontopos(colour, pon);
    } else if (pon >= 0 && pon <= 4) {
	if (colour > 0 && colour <= 4) {
	    if ((4 - (toss[colour-1] + 1) < pon) && (pon > 0)) {
		msg[colour - 1].presence = 2;
		pon = msg_gen(colour);
		return pontopos(colour, pon);
	    }
	    if ((4 - (toss[colour-1] + 1) != 4) && (pon == 0))
		return -1;
	    if ((4 - (toss[colour-1] + 1) == 4) && (pon == 0)) {
		msg[colour - 1].presence = 6;
		pon = msg_gen(colour);
		return pontopos(colour, pon);
	    }
	    for (i = 0; i < PATH_LENGTH && pon != 0; i++) {
		if (colour == 1)
			num += BLUE[i].presence;
		else if (colour == 2)
			num += RED[i].presence;
		else if (colour == 3)
			num += GREEN[i].presence;
		else if (colour == 4) 
			num += YELLOW[i].presence;
		if (num >= pon)
		    return i;
	    }
	}
    }
}

void check(short int colour, short int numofpawn, short int pos)
{				/* Checks the existence of pieces of other colours 
				 * and sends captured piece(s) back to starting point
				 * of their respective colours.
				 */
    if (pos < 52) {
	if (colour == 1) {
	    if (RED[pos - 13].presence == numofpawn && pos >= 13) {
		msg[1].presence = 5;
		msg_gen(2);
		push(2, numofpawn);
		RED[pos - 13].presence = 0;
	    } else if (RED[pos + 39].presence == numofpawn && pos <= 13) {
		msg[1].presence = 5;
		msg_gen(2);
		push(2, numofpawn);
		RED[pos + 39].presence = 0;
	    } else if (GREEN[pos - 26].presence == numofpawn && pos >= 26) {
		msg[2].presence = 5;
		msg_gen(3);
		push(3, numofpawn);
		GREEN[pos - 26].presence = 0;
	    } else if (GREEN[pos + 26].presence == numofpawn && pos <= 26) {
		msg[2].presence = 5;
		msg_gen(3);
		push(3, numofpawn);
		GREEN[pos + 26].presence = 0;
	    } else if (YELLOW[pos - 39].presence == numofpawn && pos >= 39) {
		msg[3].presence = 5;
		msg_gen(4);
		push(4, numofpawn);
		YELLOW[pos - 39].presence = 0;
	    } else if (YELLOW[pos + 13].presence == numofpawn && pos <= 39) {
		msg[3].presence = 5;
		msg_gen(4);
		push(4, numofpawn);
		YELLOW[pos + 13].presence = 0;
	    }
	} else if (colour == 2) {
	    if (BLUE[pos + 13].presence == numofpawn && pos <= 39) {
		msg[0].presence = 5;
		msg_gen(1);
		push(1, numofpawn);
		BLUE[pos + 13].presence = 0;
	    } else if (BLUE[pos - 39].presence == numofpawn && pos >= 39) {
		msg[0].presence = 5;
		msg_gen(1);
		push(1, numofpawn);
		BLUE[pos - 39].presence = 0;
	    } else if (GREEN[pos - 13].presence == numofpawn && pos >= 13) {
		msg[2].presence = 5;
		msg_gen(3);
		push(3, numofpawn);
		GREEN[pos - 13].presence = 0;
	    } else if (GREEN[pos + 13].presence == numofpawn && pos <= 13) {
		msg[2].presence = 5;
		msg_gen(3);
		push(3, numofpawn);
		GREEN[pos + 13].presence = 0;
	    } else if (YELLOW[pos - 26].presence == numofpawn && pos >= 26) {
		msg[3].presence = 5;
		msg_gen(4);
		push(4, numofpawn);
		YELLOW[pos - 26].presence = 0;
	    } else if (YELLOW[pos + 26].presence == numofpawn && pos <= 26) {
		msg[3].presence = 5;
		msg_gen(4);
		push(4, numofpawn);
		YELLOW[pos + 26].presence = 0;
	    }
	} else if (colour == 3) {
	    if (BLUE[pos + 26].presence == numofpawn && pos <= 26) {
		msg[0].presence = 5;
		msg_gen(1);
		push(1, numofpawn);
		BLUE[pos + 26].presence = 0;
	    } else if (BLUE[pos - 26].presence == numofpawn && pos >= 26) {
		msg[0].presence = 5;
		msg_gen(1);
		push(1, numofpawn);
		BLUE[pos - 26].presence = 0;
	    } else if (RED[pos + 13].presence == numofpawn && pos <= 39) {
		msg[1].presence = 5;
		msg_gen(2);
		push(2, numofpawn);
		RED[pos + 13].presence = 0;
	    } else if (RED[pos - 13].presence == numofpawn && pos >= 39) {
		msg[1].presence = 5;
		msg_gen(2);
		push(2, numofpawn);
		RED[pos - 13].presence = 0;
	    } else if (YELLOW[pos - 13].presence == numofpawn && pos >= 13) {
		msg[3].presence = 5;
		msg_gen(4);
		push(4, numofpawn);
		YELLOW[pos - 13].presence = 0;
	    } else if (YELLOW[pos + 39].presence == numofpawn && pos <= 13) {
		msg[3].presence = 5;
		msg_gen(4);
		push(4, numofpawn);
		YELLOW[pos - 13].presence = 0;
	    }
	} else if (colour == 4) {
	    if (BLUE[pos + 39].presence == numofpawn && pos >= 13) {
		msg[0].presence = 5;
		msg_gen(1);
		push(1, numofpawn);
		BLUE[pos + 39].presence = 0;
	    } else if (RED[pos + 26].presence == numofpawn && pos <= 30) {
		msg[1].presence = 5;
		msg_gen(2);
		push(2, numofpawn);
		RED[pos + 26].presence = 0;
	    } else if (GREEN[pos + 13].presence == numofpawn && pos <= 43) {
		msg[2].presence = 5;
		msg_gen(3);
		push(3, numofpawn);
		GREEN[pos + 13].presence = 0;
	    }
	}
    }
}

void move_pawns(short int colour, short int numofpawn, short int pon, short int moveby)	//Moves the pieces.
{
    short int i, j, pos, temp;
    temp = 0;

	if ((toss[colour - 1] < 3)
	    || (toss[colour - 1] <= 3 && moveby == 6))
	    pos = pontopos(colour, pon);
	i = pos;
	if (moveby % numofpawn == 0)
	    temp = moveby / numofpawn;
	j = pos + temp;
	if (pon != 0 && pos != -1 && j <= PATH_LENGTH) {
	    if (j == PATH_LENGTH) {
		push_home(colour, numofpawn);
	    } else if (j < PATH_LENGTH) {
		if (moveby % numofpawn == 0) {
		    if (colour == 1 && BLUE[i].presence > 0) {
			BLUE[i].presence -= numofpawn;
			BLUE[j].presence += numofpawn;
		    } else if (colour == 2 && RED[i].presence > 0) {
			RED[i].presence -= numofpawn;
			RED[j].presence += numofpawn;
		    } else if (colour == 3 && GREEN[i].presence > 0) {
			GREEN[i].presence -= numofpawn;
			GREEN[j].presence += numofpawn;
		    } else if (colour == 4 && YELLOW[i].presence > 0) {
			YELLOW[i].presence -= numofpawn;
			YELLOW[j].presence += numofpawn;
		    }
		} else if (moveby % numofpawn != 0) {
		    if (colour == 1 && BLUE[i].presence > 0) {
			BLUE[i].presence--;
			BLUE[j].presence++;
		    } else if (colour == 2 && RED[i].presence > 0) {
			RED[i].presence--;
			RED[j].presence++;
		    } else if (colour == 3 && GREEN[i].presence > 0) {
			GREEN[i].presence--;
			GREEN[j].presence++;
		    } else if (colour == 4 && YELLOW[i].presence > 0) {
			YELLOW[i].presence--;
			YELLOW[j].presence++;
		    }
		}
		if (j != 0 && j != 8 && j != 13 && j != 21 && j != 26
		    && j != 34 && j != 39 && j != 47) {
		    check(colour, numofpawn, j);
		}
	    }
	} else if (moveby == 6 && pos == -1)
	    pop(colour);
	return;
}

void draw_pawns(short int colour)
{
    short int i, num;
    num = 1;

    if (colour == 1) {
	for (i = 0; i < 4; i++)
	    if (blue_sp[i].presence == 0)
		mvprintw(blue_sp[i].y, blue_sp[i].x, " ");
	    else if (blue_sp[i].presence == 1)
		mvprintw(blue_sp[i].y, blue_sp[i].x, "B");

	for (i = 0; i < PATH_LENGTH; i++) {
	    if (BLUE[i].presence == 1) {
		attron(COLOR_PAIR(5));
		mvprintw(BLUE[i].y, BLUE[i].x, "%d", num);
		attroff(COLOR_PAIR(5));
		num++;
	    } else if (BLUE[i].presence > 1) {
		attron(COLOR_PAIR(1));
		mvprintw(BLUE[i].y, BLUE[i].x, "%d", num);
		attroff(COLOR_PAIR(1));
		num += BLUE[i].presence;
	    } else if (BLUE[i].presence == 0) {
		if (i != 0 && i != 13 && i != 26 && i != 39) {
		    mvprintw(BLUE[i].y, BLUE[i].x, " ");
		    refresh();
		} else if (i == 0) {
		    attron(COLOR_PAIR(1));
		    mvprintw(BLUE[i].y, BLUE[i].x, " ");
		    attroff(COLOR_PAIR(1));
		} else if (i == 13) {
		    attron(COLOR_PAIR(2));
		    mvprintw(BLUE[i].y, BLUE[i].x, " ");
		    attroff(COLOR_PAIR(2));
		} else if (i == 26) {
		    attron(COLOR_PAIR(3));
		    mvprintw(BLUE[i].y, BLUE[i].x, " ");
		    attroff(COLOR_PAIR(3));
		} else if (i == 39) {
		    attron(COLOR_PAIR(4));
		    mvprintw(BLUE[i].y, BLUE[i].x, " ");
		    attroff(COLOR_PAIR(4));
		}
	    }
	}
    } else if (colour == 2) {
	for (i = 0; i < 4; i++)
	    if (red_sp[i].presence == 0)
		mvprintw(red_sp[i].y, red_sp[i].x, " ");
	    else if (red_sp[i].presence == 1)
		mvprintw(red_sp[i].y, red_sp[i].x, "R");

	for (i = 0; i < PATH_LENGTH; i++) {
	    if (RED[i].presence == 1) {
		attron(COLOR_PAIR(6));
		mvprintw(RED[i].y, RED[i].x, "%d", num);
		attroff(COLOR_PAIR(6));
		num++;
	    } else if (RED[i].presence > 1) {
		attron(COLOR_PAIR(2));
		mvprintw(RED[i].y, RED[i].x, "%d", num);
		attroff(COLOR_PAIR(2));
		num += RED[i].presence;
	    } else if (BLUE[i].presence == 0) {
		if (i != 0 && i != 13 && i != 26 && i != 39) {
		    mvprintw(RED[i].y, RED[i].x, " ");
		    refresh();
		} else if (i == 0) {
		    attron(COLOR_PAIR(2));
		    mvprintw(RED[i].y, RED[i].x, " ");
		    attroff(COLOR_PAIR(2));
		} else if (i == 13) {
		    attron(COLOR_PAIR(3));
		    mvprintw(RED[i].y, RED[i].x, " ");
		    attroff(COLOR_PAIR(3));
		} else if (i == 26) {
		    attron(COLOR_PAIR(4));
		    mvprintw(RED[i].y, RED[i].x, " ");
		    attroff(COLOR_PAIR(4));
		} else if (i == 39) {
		    attron(COLOR_PAIR(1));
		    mvprintw(RED[i].y, RED[i].x, " ");
		    attroff(COLOR_PAIR(1));
		}
	    }
	}
    } else if (colour == 3) {
	for (i = 0; i < 4; i++)
	    if (green_sp[i].presence == 0)
		mvprintw(green_sp[i].y, green_sp[i].x, " ");
	    else if (green_sp[i].presence == 1)
		mvprintw(green_sp[i].y, green_sp[i].x, "G");

	for (i = 0; i < PATH_LENGTH; i++) {
	    if (GREEN[i].presence == 1) {
		attron(COLOR_PAIR(7));
		mvprintw(GREEN[i].y, GREEN[i].x, "%d", num);
		attroff(COLOR_PAIR(7));
		num++;
	    } else if (GREEN[i].presence > 1) {
		attron(COLOR_PAIR(3));
		mvprintw(GREEN[i].y, GREEN[i].x, "%d", num);
		attroff(COLOR_PAIR(3));
		num += GREEN[i].presence;
	    } else if (BLUE[i].presence == 0) {
		if (i != 0 && i != 13 && i != 26 && i != 39) {
		    mvprintw(GREEN[i].y, GREEN[i].x, " ");
		    refresh();
		} else if (i == 0) {
		    attron(COLOR_PAIR(3));
		    mvprintw(GREEN[i].y, GREEN[i].x, " ");
		    attroff(COLOR_PAIR(3));
		} else if (i == 13) {
		    attron(COLOR_PAIR(4));
		    mvprintw(GREEN[i].y, GREEN[i].x, " ");
		    attroff(COLOR_PAIR(4));
		} else if (i == 26) {
		    attron(COLOR_PAIR(1));
		    mvprintw(GREEN[i].y, GREEN[i].x, " ");
		    attroff(COLOR_PAIR(1));
		} else if (i == 39) {
		    attron(COLOR_PAIR(2));
		    mvprintw(GREEN[i].y, GREEN[i].x, " ");
		    attroff(COLOR_PAIR(2));
		}
	    }
	}
    } else if (colour == 4) {
	for (i = 0; i < 4; i++)
	    if (yellow_sp[i].presence == 0)
		mvprintw(yellow_sp[i].y, yellow_sp[i].x, " ");
	    else if (yellow_sp[i].presence == 1)
		mvprintw(yellow_sp[i].y, yellow_sp[i].x, "Y");

	for (i = 0; i < PATH_LENGTH; i++) {
	    if (YELLOW[i].presence == 1) {
		attron(COLOR_PAIR(8));
		mvprintw(YELLOW[i].y, YELLOW[i].x, "%d", num);
		attroff(COLOR_PAIR(8));
		num++;
	    } else if (YELLOW[i].presence > 1) {
		attron(COLOR_PAIR(4));
		mvprintw(YELLOW[i].y, YELLOW[i].x, "%d",
			 YELLOW[i].presence);
		attroff(COLOR_PAIR(4));
		num += YELLOW[i].presence;
	    } else if (BLUE[i].presence == 0) {
		if (i != 0 && i != 13 && i != 26 && i != 39) {
		    mvprintw(YELLOW[i].y, YELLOW[i].x, " ");
		    refresh();
		} else if (i == 0) {
		    attron(COLOR_PAIR(4));
		    mvprintw(YELLOW[i].y, YELLOW[i].x, " ");
		    attroff(COLOR_PAIR(4));
		} else if (i == 13) {
		    attron(COLOR_PAIR(1));
		    mvprintw(YELLOW[i].y, YELLOW[i].x, " ");
		    attroff(COLOR_PAIR(1));
		} else if (i == 26) {
		    attron(COLOR_PAIR(2));
		    mvprintw(YELLOW[i].y, YELLOW[i].x, " ");
		    attroff(COLOR_PAIR(2));
		} else if (i == 39) {
		    attron(COLOR_PAIR(3));
		    mvprintw(YELLOW[i].y, YELLOW[i].x, " ");
		    attroff(COLOR_PAIR(3));
		}
	    }
	}
    }
    refresh();
    return;
}

void init_pawns()
{
    short int i;
    for (i = 1; i <= 4; i++) {
	push(i, 4);
	draw_pawns(i);
	refresh();
    }
}

void moves(short int colour, short int numofpawn, short int pon, short int moveby)	//Moves the pieces.
{
    short int i;
    napms(MS);
    if ((colour > 0 && colour <= 4) && (numofpawn > 0 && numofpawn < 4)) {
    	move_pawns(colour, numofpawn, pon, moveby);
    }
    for (i = 1; i <= 4; i++)
	draw_pawns(i);
    refresh();
    return;
}

main()
{
    short int tmp, player;
    short int nop, pid, mv;
    draw_board();
    init_ludo();
    init_pawns();
//    noecho();
    tmp = 0;
//    do {
//      tmp = rand() % 5;
//    } while (tmp == 0);
//    player = tmp;
    while ((tohs[0] != 3) || (tohs[1] != 3) || (tohs[2] != 3)
	   || (tohs[3] != 3)) {
	player = mvgetch(0, 0) - 48;
	nop = mvgetch(1, 0) - 48;
	pid = mvgetch(2, 0) - 48;
	mv = mvgetch(3, 0) - 48;
	moves(player, nop, pid, mv);
//      mvprintw(13,19,"%d",RED[0].presence);
//      refresh();
//      napms(MS);
    }
    /*
       moves(2, 1, 0, 6);
       moves(2, 1, 1, 6);
       moves(2, 1, 1, 6);
       moves(3, 1, 0, 6);
       moves(3, 1, 1, 1);
       moves(2, 1, 1, 2);
       moves(2, 1, 1, 5);
       moves(2, 1, 1, 6);
       moves(4, 1, 0, 6);
       moves(2, 1, 1, 1);
       moves(4, 1, 1, 1);
       moves(2, 1, 1, 1);
       moves(2, 1, 1, 5);
       moves(2, 1, 1, 6);
       moves(1, 1, 0, 6);
       moves(1, 1, 1, 1);
       moves(2, 1, 1, 2);
       moves(1, 1, 0, 6);
       moves(1, 1, 1, 6);
       moves(1, 1, 1, 6);
       moves(2, 1, 0, 6);
       moves(1, 1, 1, 2);
       moves(2, 1, 1, 1);
     */
    endwin();
    exit(0);

}
