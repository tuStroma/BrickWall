#pragma once
#include <iostream>

class Row
{
private:
	int* bricks;
	int size;

public:
	Row(int indexes[], int size, int bricks[]);

	int getBrick(int i);

	void print();
};

