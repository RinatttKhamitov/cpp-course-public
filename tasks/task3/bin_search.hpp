#pragma once

int* LowerBound(int* first, int* last, int value) { 
	int* it = first; 
	int len = last-first;
	int step = len;

	while (len > 0)
    { 
        step = len / 2; 
        it = first+step;
 
        if (*it < value)
        {
            first = ++it; 
            len -= step + 1; 
        }
        else
            len = step;
    }
	if (value != *first){
		return last;
	}
    return first;
}
