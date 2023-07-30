#include <iostream>
#include <vector>

enum room_type
{
	bedroom = 1,
	livingroom,
	kitchen,
	bathroom,
	childhood
};

enum building_type
{
	home = 1,
	garage,
	bathroom,
	barn
};

struct house
{
public:

};

struct building
{
public:
	int square;
};

struct region
{
public:

};

int main()
{
	int amount;
	std::cout << "How many regions are there in the village ? " << std::endl;
	std::cin >> amount;



	return 0;
}