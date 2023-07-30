#include <iostream>
#include <vector>
#include <string>

enum Room_type
{
	bedroom = 1,
	livingroom,
	kitchen,
	Bathroom,
	childhood
};

enum Building_type
{
	home = 1,
	garage,
	Bathhouse,
	barn
};

struct Room 
{ 
	int room_square = 0;
	Room_type room_type;
};

struct Floor
{
	int ceilingHeight = 0;
	std::vector<Room> rooms;
};

struct House { std::vector<Floor> floors; };

struct Building
{
	int building_square = 0;
	Building_type type;
	bool chimney = false;
	House house;
};

struct Region 
{
	std::vector<Building> buildings;
	int square_region = 0;
};

void fill_type_and_square_room(House& house, const
	Room_type& type, const int* itI, const int* itJ, int* amount) 
{ 
	house.floors[*itI].rooms[*itJ].room_type = type;
	*amount = 0;
	while (*amount <= 0)
	{
		std::cout << "Enter the area of the room: ";
		std::cin >> *amount;
		if (*amount <= 0)
		{
			std::cerr << "Error! The area of the room could not be " <<
				"equal to 0 or less than 0. Try again. " << std::endl;
		}
		else house.floors[*itI].rooms[*itJ].room_square = *amount;
	}
}

void fill_information_about_floor(House& house, int* amount)
{
	while (house.floors.size() == 0)
	{
		std::cout << "Specify the number of floors(1-3): ";
		std::cin >> *amount;
		if (*amount < 1 || *amount > 3)
			std::cerr << "Error! Floors cannot be less than 1 or more than 3. Try again." << std::endl;
		else house.floors.resize(*amount);
	}

	for (int i = 0; i < house.floors.size(); ++i)
	{
		std::cout << "Enter the ceiling height on the " << i + 1 << " floor: ";
		std::cin >> *amount;
		if (*amount < 2 || *amount > 4)
		{
			std::cerr << "Error! The ceiling cannot be lower than 2 meters or " <<
				" higher than 4 meters. Try again. " << std::endl;
			--i;
			continue;
		}
		else
			house.floors[i].ceilingHeight = *amount;

		while (house.floors[i].rooms.size() == 0)
		{
			std::cout << "Specify the number of rooms on the " << i + 1 << " floor: ";
			std::cin >> *amount;
			if (*amount < 2 || *amount > 4)
			{
				std::cerr << "Error! The number of rooms cannot be less than 2 or more than 4. Try again. " << std::endl;
				continue;
			}
			else house.floors[i].rooms.resize(*amount);
		}

		for (int j = 0; j < house.floors[i].rooms.size(); ++j)
		{
			std::cout << "Specify the type of room(Bedroom - 1,livingroom - 2,kitchen - 3,bathroom - 4,childhood - 5)\n:";
			std::cin >> *amount;
			if (*amount == Room_type::bedroom)
				fill_type_and_square_room(house, Room_type::bedroom, &i, &j, amount);
			else if (*amount == Room_type::livingroom)
				fill_type_and_square_room(house, Room_type::livingroom, &i, &j, amount);
			else if (*amount == Room_type::kitchen)
				fill_type_and_square_room(house, Room_type::kitchen, &i, &j, amount);
			else if (*amount == Room_type::Bathroom)
				fill_type_and_square_room(house, Room_type::Bathroom, &i, &j, amount);
			else if (*amount == Room_type::childhood)
				fill_type_and_square_room(house, Room_type::childhood, &i, &j, amount);
			else
			{
				std::cerr << "Error! You can only select rooms from this list: " <<
					"\Bedroom - 1, livingroom - 2, kitchen - 3, bathroom - 4, childhood - 5. Try again. \n";
			}
		}
	}
}

void fill_type_building_and_square(std::vector<Region>& regions, 
	const int* itI, const int* itJ,const Building_type& type, int* amount)
{
	regions[*itI].buildings[*itJ].type = type;
	*amount = 0;
	while (*amount <= 0)
	{
		std::cout << "Specify the area of this building: ";
		std::cin >> *amount;
		if (*amount <= 0) 
			std::cerr << "Error! The building area cannot be equal to 0 or less than 0. Try again." << std::endl;
		else
			regions[*itI].buildings[*itI].building_square = *amount;
	}
}

void is_there_chimney(std::vector<Region>& regions,
	const int* itI,const int* itJ, std::string check)
{
	std::cout << "Is there a chimney ? (yes or no) \n:";
	std::cin >> check;
	if (check == "yes")
		regions[*itI].buildings[*itJ].chimney = true;
}

void fill_region_buildings(std::vector<Region>& regions, int* amount)
{
	std::string check;
	for (int i = 0; i < regions.size(); ++i)
	{
		std::cout << "How many buildings are there " << i + 1 << " region ? ";
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
			std::cout << "What type of building is under the number " << j + 1 << ", in " << i + 1 << " region ? " << std::endl;
			std::cout << "Home - 1, garage - 2, bathhouse - 3, barn - 4.\n:";
			std::cin >> *amount;
			if (*amount == Building_type::home)
			{
				fill_type_building_and_square(regions, &i, &j, Building_type::home, amount);
				is_there_chimney(regions, &i, &j, check);
				fill_information_about_floor(regions[i].buildings[j].house, amount);
			}
			else if (*amount == Building_type::garage)
				fill_type_building_and_square(regions, &i, &j, Building_type::garage, amount);
			else if (*amount == Building_type::Bathhouse)
			{
				fill_type_building_and_square(regions, &i, &j, Building_type::Bathhouse, amount);
				is_there_chimney(regions, &i, &j, check);
			}
			else if (*amount == Building_type::barn)
				fill_type_building_and_square(regions, &i, &j, Building_type::barn, amount); 
			else
			{
				std::cerr << "Error! You can only select buildings from this list: " <<
					"\nHome - 1, garage - 2, bathhouse - 3, barn - 4. Try again. \n";
			}
		}
	}
}

void print(const std::vector<Region>& regions)
{
	for (int i = 0; i < regions.size(); ++i)
	{
		for (int j = 0; j < regions[i].buildings.size(); ++j)
		{
			if (regions[i].buildings[j].type == Building_type::home)
			{
				std::cout << "Region: " << i << "\tBuilding number: " << j <<
					"\tBuilding type: " << "House." << "\tBuilding square: " <<
					regions[i].buildings[j].building_square << std::endl;
			}
			if (regions[i].buildings[j].type == Building_type::garage)
			{
				std::cout << "Region: " << i << "\tBuilding number: " << j <<
					"\tBuilding type: " << "Garage." << "\tBuilding square: " <<
					regions[i].buildings[j].building_square << std::endl;
			}
			if (regions[i].buildings[j].type == Building_type::Bathhouse)
			{
				std::cout << "Region: " << i << "\tBuilding number: " << j <<
					"\tBuilding type: " << "Bathroom." << "\tBuilding square: " <<
					regions[i].buildings[j].building_square << std::endl;
			}
			if (regions[i].buildings[j].type == Building_type::barn)
			{
				std::cout << "Region: " << i << "\tBuilding number: " << j <<
					"\tBuilding type: " << "Barn." << "\tBuilding square: " <<
					regions[i].buildings[j].building_square << std::endl;
			}
		}
	}
}

int main()
{
	int amount;
	std::cout << "How many regions are there in the village ? " << std::endl;
	std::cin >> amount;
	
	if (amount <= 0)
	{
		std::cerr << "Error! The number of buildings is negative or equal to null." << std::endl;
		return 0;
	}
	else
	{
		std::vector<Region> regions(amount);
		for (int i = 0; i < regions.size(); ++i)
		{
			std::cout << "Specify the area of the region: ";
			std::cin >> amount;
			if (amount <= 0)
			{
				std::cerr << "Error! The area of the region could not be " <<
					"equal to 0 or less than 0. Try again. " << std::endl;
				--i;
			}
			else
				regions[i].square_region = amount;
		}
		fill_region_buildings(regions, &amount);
	}

	return 0;
}