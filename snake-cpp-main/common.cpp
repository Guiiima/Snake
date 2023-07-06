#include "common.h"

Common::Common(){}

void Common::goToxy(short x, short y) {
        COORD coords {x, y};
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
}