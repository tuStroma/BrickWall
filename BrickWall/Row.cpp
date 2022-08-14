#include "Row.h"

Row::Row(int indexes[], int size, int bricks[])
{
	this->size = size;
	this->bricks = (int*)std::malloc(sizeof(int) * size);
	if (!this->bricks)
	{
		std::cout << "Can't alloc Row\n";
		exit(1);
	}

	for (int i = 0; i < size; i++)
		this->bricks[i] = bricks[indexes[i]];
}

int Row::getBrick(int i)
{
	if (i >= 0 && i < size)
		return bricks[i];

	return 0;
}

void Row::print()
{
	for (int i = 0; i < size; i++)
		std::cout << bricks[i] << ' ';

	std::cout << '\n';
}
