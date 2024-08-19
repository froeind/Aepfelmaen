
#include "tools.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned int myT::random(const unsigned int from, const unsigned int to)
{
	if (to < from) { return 0; }
	// das immer hier aufgerufen macht das Programm unsäglich langsam
	//srand((unsigned) time(NULL));
	return (unsigned int)(1.0 * rand() / RAND_MAX * (to - from) + from);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
