#include <iostream>
#include <list>
#include <time.h>

#include "Row.h"

#define DEBUG true

bool removeTail(int* bricks, int& bricks_sum, int& current_brick_index, int& current_brick_size_index, int* row)
{
	current_brick_index--;										// Remove last brick
	if (current_brick_index < 0) return false;					// Exit

	current_brick_size_index = row[current_brick_index];		// Update current brick size

	bricks_sum -= bricks[current_brick_size_index];				// Update sum

	return true;
}

std::list<Row*> generateRows(int x, int* bricks, int bricks_num)
{
	int current_brick_index = 0;
	int current_brick_size_index = 0;

	int bricks_sum = 0;


	int* row = (int*)malloc(x * sizeof(int));

	std::list<Row*> rows;

	// Loop until reached end of searching (first brick moved to illegal size)
	while (!(current_brick_index == 0 && current_brick_size_index == bricks_num))
	{
		// Add next brick
		bricks_sum += bricks[current_brick_size_index];
		row[current_brick_index] = current_brick_size_index;
		current_brick_index++;
		current_brick_size_index = 0;

		if (DEBUG)
		{
			std::cout << "Add brick  \t";
			for (int i = 0; i < current_brick_index; i++) std::cout << row[i] << ' '; std::cout << ": Sum : " << bricks_sum << '\n';
		}

		// If reached end of the row
		if (bricks_sum >= x)
		{
			// If last brick fits
			if (bricks_sum == x)
			{
				// TODO: add row to the list
				Row* new_row = new Row(row, current_brick_index, bricks);
				rows.push_back(new_row);
			}

			// TODO:
			// Remove all biggest bricks from tail
			// Remove at least 2 bricks
			int i = 0;
			while (i < 2 || current_brick_size_index == bricks_num - 1)
			{
				if (removeTail(bricks, bricks_sum, current_brick_index, current_brick_size_index, row) == false)
					break;

				i++;

				if (DEBUG)
				{
					std::cout << "Remove brick\t";
					for (int j = 0; j < current_brick_index; j++) std::cout << row[j] << ' '; std::cout << ": Sum : " << bricks_sum << '\n';
				}
			}
			if (current_brick_index < 0) 
				break;

			// Increase size of current tail brick
			current_brick_size_index++;
		}
	}

	return rows;
}

uint64_t createWall(int x, int y, int* bricks, int bricks_num)
{
	return 0;
}

void time_test()
{
	int tab[] = { 1, 2, 3, 4 };
	clock_t start, generate, reduce;

	start = clock();

	std::list<Row*> rows = generateRows(10, tab, 4);

	generate = clock();

	//for (Row* r : rows)
	//	r->print();
	int gen_num = rows.size();

	for (std::list<Row*>::iterator iterator = rows.begin(); iterator != rows.end();) {
		Row* r = *iterator;

		int ones_counter = 0;
		int index = 0;
		int current_brick = r->getBrick(index);
		while (current_brick > 0)
		{
			if (current_brick == 1)
				ones_counter++;
			else
				ones_counter = 0;

			if (ones_counter == 4)
				break;

			index++;
			current_brick = r->getBrick(index);
		}

		if (ones_counter == 4) { r->print(); iterator = rows.erase(iterator); }// Erase from list
		else
			iterator++;

	}

	reduce = clock();

	std::cout << "Rows number: " << gen_num << '\n';
	std::cout << "Rows number: " << rows.size() << '\n';
	std::cout << "Genaration time: " << (double)(generate - start) / CLOCKS_PER_SEC << '\n';
	std::cout << "Reduction time:  " << (double)(reduce - start) / CLOCKS_PER_SEC << '\n';
}

int main()
{
	int tab[] = { 1, 2, 3, 4 };

	std::list<Row*> rows = generateRows(10, tab, 4);


	for (Row* r : rows)
		r->print();


	std::cout << "Rows number: " << rows.size() << '\n';

	
	return 0;
}