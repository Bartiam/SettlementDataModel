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
	building_type type;
};

struct region
{
public:
	std::vector<building> buildings;
};

void foo(std::vector<region>& regions, const int* itI, const int* itJ,
	const building_type& type, int* amount)
{
	regions[*itI].buildings[*itJ].type = type;
	std::cout << "Specify the area of this building: ";
	std::cin >> *amount;
	regions[*itI].buildings[*itI].square = *amount;
}

void fill_region_buildings(std::vector<region>& regions, int* amount)
{
	for (int i = 0; i < regions.size(); ++i)
	{
		std::cout << "How many buildings are there " << i << " region ? ";
		std::cin >> *amount;
		if (*amount < 0)
		{
			std::cerr << "Error! The number of buildings cannot be negative. Try again. \n";
			--i;
		}
		else
			regions[i].buildings.resize(*amount);
	}

	for (int i = 0; i < regions.size(); ++i)
	{
		for (int j = 0; j < regions[i].buildings.size(); ++j)
		{
			std::cout << "What buildings are there " << i << " region ? " << std::endl;
			std::cout << "Home - 1, garage - 2, bathroom - 3, barn - 4.\n:";
			std::cin >> *amount;
			if (*amount == building_type::home)
			{
				foo(regions, &i, &j, building_type::home, amount);
			}
			else if (*amount == building_type::garage)
				foo(regions, &i, &j, building_type::garage, amount);
			else if (*amount == building_type::bathroom)
				foo(regions, &i, &j, building_type::bathroom, amount);
			else if (*amount == building_type::barn)
				foo(regions, &i, &j, building_type::barn, amount);
			else
			{
				std::cerr << "Error! You can only select buildings from this list: " <<
					"\nHome - 1, garage - 2, bathroom - 3, barn - 4. Try again. \n";
			}
		}
	}
}

int main()
{
	int amount;
	std::cout << "How many regions are there in the village ? " << std::endl;
	std::cin >> amount;

	std::vector<region> regions(amount);
	fill_region_buildings(regions, &amount);

	return 0;
}