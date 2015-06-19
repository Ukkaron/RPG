#include <iostream>

#include "RPG_source.h"

using namespace std;

int main()
{
    int i;
    int room_size;
    srand(time(NULL));
    room_size = rand() % 9 + 8;
    cell platforms[room_size][room_size];
    cell *y_line[room_size];
    for (i=0; i< room_size; i++)
    {
        y_line[i] = &platforms[i][0];
    }
    room_generator(y_line, room_size);
}

