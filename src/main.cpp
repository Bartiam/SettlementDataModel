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
	bool chimney;
	House house;
};

struct Region 
{
	std::vector<Building> buildings;
	int square_region = 0;
};

void fill_type_and_square_room(House& house, const Room_type& type,
	const int* itI, const int* itJ, int* amount, int& building_square)
{ 
	house.floors[*itI].rooms[*itJ].room_type = type;
	*amount = 0;
	while (*amount <= 0)
	{
		std::cout << "Enter the area of the room: ";
		std::cin >> *amount;
		if (*amount <= 0 || *amount >= building_square)
		{
			std::cerr << "Error! The area of the room could not be " <<
				"equal to 0 or less than 0, \nand bigger or equal than building area. " <<
				"Try again. " << std::endl;
		}
		else house.floors[*itI].rooms[*itJ].room_square = *amount;
	}
}

void fill_information_about_floor(House& house, int* amount, int& building_square)
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
			std::cout << "Specify the type of room\n1 - Bedroom,\n2 - livingroom,\n3 - kitchen,\n4 - bathroom,\n5 - childhood\n:";
			std::cin >> *amount;
			if (*amount == Room_type::bedroom)
				fill_type_and_square_room(house, Room_type::bedroom, &i, &j, amount, building_square);
			else if (*amount == Room_type::livingroom)
				fill_type_and_square_room(house, Room_type::livingroom, &i, &j, amount, building_square);
			else if (*amount == Room_type::kitchen)
				fill_type_and_square_room(house, Room_type::kitchen, &i, &j, amount, building_square);
			else if (*amount == Room_type::Bathroom)
				fill_type_and_square_room(house, Room_type::Bathroom, &i, &j, amount, building_square);
			else if (*amount == Room_type::childhood)
				fill_type_and_square_room(house, Room_type::childhood, &i, &j, amount, building_square);
			else
			{
				std::cerr << "Error! You can only select rooms from this list: " <<
					"\nBedroom - 1, livingroom - 2, kitchen - 3, bathroom - 4, childhood - 5. Try again. \n";
			}
		}
	}
}

void fill_type_building_and_square(std::vector<Region>& regions, const int* itI, 
	const int* itJ,const Building_type& type, int* amount, const int square_region)
{
	regions[*itI].buildings[*itJ].type = type;
	*amount = 0;
	while (*amount <= 0)
	{
		std::cout << "Specify the area of this building: ";
		std::cin >> *amount;
		if (*amount <= 0 || *amount >= square_region)
			std::cerr << "Error! The building area cannot be equal to 0 or less than 0, " << 
			"\nAnd the building area cannot be equal or bigger than region area. " << "Try again." << std::endl;
		
		else
			regions[*itI].buildings[*itI].building_square = *amount;
	}
}

void is_there_chimney(std::vector<Region>& regions,
	const int* itI,const int* itJ, std::string check)
{
	while (check != "yes" && check != "no")
	{
		std::cout << "Is there a chimney ? (yes or no) \n:";
		std::cin >> check;
		if (check == "yes")
			regions[*itI].buildings[*itJ].chimney = true;
		else if (check == "no")
			regions[*itI].buildings[*itJ].chimney = false;
		else
			std::cerr << "Error! You can only enter yes or no. Try again." << std::endl;
	}
}

void fill_region_buildings(std::vector<Region>& regions, int* amount, int& village_square)
{
	std::string check;
	std::cout << "Specify the area of the region: ";
	std::cin >> *amount;

	for (int i = 0; i < regions.size(); ++i)
	{
		if (*amount <= 0 || *amount >= village_square)
		{
			std::cerr << "Error! The region area cannot be equal to 0 or less than 0," <<
				"\nand bigger than equal area of the village. Try again.";
			--i;
			continue;
		}
		else
			regions[i].square_region = *amount;
	}

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
			std::cout << "1 - Home,\n2 - garage,\n3 - bathhouse,\n4 - barn.\n:";
			std::cin >> *amount;
			if (*amount == Building_type::home)
			{
				fill_type_building_and_square(regions, &i, &j, Building_type::home, amount, regions[i].square_region);
				is_there_chimney(regions, &i, &j, check);
				fill_information_about_floor(regions[i].buildings[j].house, amount, regions[i].buildings[j].building_square);
			}
			else if (*amount == Building_type::garage)
				fill_type_building_and_square(regions, &i, &j, Building_type::garage, amount, regions[i].square_region);
			else if (*amount == Building_type::Bathhouse)
			{
				fill_type_building_and_square(regions, &i, &j, Building_type::Bathhouse, amount, regions[i].square_region);
				is_there_chimney(regions, &i, &j, check);
			}
			else if (*amount == Building_type::barn)
				fill_type_building_and_square(regions, &i, &j, Building_type::barn, amount, regions[i].square_region);
			else
			{
				std::cerr << "Error! You can only select buildings from this list: " <<
					"\n1 - Home, \ngarage, \nbathhouse - 3, \nbarn - 4.\nTry again. \n";
			}
		}
	}
}

void print(const std::vector<Region>& regions, const int& village_square)
{
	std::cout << "Village area: " << village_square << std::endl;
	for (int i = 0; i < regions.size(); ++i)
	{
		std::cout << "Region area: " << regions[i].square_region << std::endl;
		for (int j = 0; j < regions[i].buildings.size(); ++j)
		{
			if (regions[i].buildings[j].type == Building_type::home)
			{
				if (regions[i].buildings[j].chimney)
				{
					std::cout << "Region: " << i + 1 << "\nBuilding number: " << j + 1 <<
						"\nBuilding type: " << "House." << "\nBuilding square: " <<
						regions[i].buildings[j].building_square << "Chimney: yes." << std::endl;
				}
				else
				{
					std::cout << "Region: " << i + 1 << "\nBuilding number: " << j + 1 <<
						"\nBuilding type: " << "House." << "\nBuilding square: " <<
						regions[i].buildings[j].building_square << "Chimney: no." << std::endl;
				}

				for (int k = 0; k < regions[i].buildings[j].house.floors.size(); ++k)
				{
					std::cout << "Floor: " << k + 1;
					std::cout << "Ceiling height: " << regions[i].buildings[j].house.floors[k].ceilingHeight << std::endl;

					for (int rt = 0; rt < regions[i].buildings[j].house.floors[k].rooms.size(); ++rt)
					{
						std::cout << "Room area: " << regions[i].buildings[j].house.floors[k].rooms[rt].room_square;
						if (regions[i].buildings[j].house.floors[k].rooms[rt].room_type == Room_type::bedroom)
							std::cout << " Room type: " << "bedroom" << std::endl;
						else if (regions[i].buildings[j].house.floors[k].rooms[rt].room_type == Room_type::livingroom)
							std::cout << " Room type: " << "livingroom" << std::endl;
						else if (regions[i].buildings[j].house.floors[k].rooms[rt].room_type == Room_type::kitchen)
							std::cout << " Room type: " << "kitchen" << std::endl;
						else if (regions[i].buildings[j].house.floors[k].rooms[rt].room_type == Room_type::Bathroom)
							std::cout << " Room type: " << "Bathroom" << std::endl;
						else if (regions[i].buildings[j].house.floors[k].rooms[rt].room_type == Room_type::childhood)
							std::cout << " Room type: " << "childhood" << std::endl;
					}
				}
			}
			if (regions[i].buildings[j].type == Building_type::garage)
			{
				std::cout << "Region: " << i + 1 << "\nBuilding number: " << j + 1 <<
					"\nBuilding type: " << "Garage." << "\nBuilding square: " <<
					regions[i].buildings[j].building_square << std::endl;
			}
			if (regions[i].buildings[j].type == Building_type::Bathhouse)
			{
				if (regions[i].buildings[j].chimney)
				{
					std::cout << "Region: " << i + 1 << "\nBuilding number: " << j + 1 <<
						"\nBuilding type: " << "Bathhouse." << "\nBuilding square: " <<
						regions[i].buildings[j].building_square << "Chimney: yes." << std::endl;
				}
				else
				{
					std::cout << "Region: " << i + 1 << "\nBuilding number: " << j + 1 <<
						"\nBuilding type: " << "Bathhouse." << "\nBuilding square: " <<
						regions[i].buildings[j].building_square << "Chimney: no." << std::endl;
				}
			}
			if (regions[i].buildings[j].type == Building_type::barn)
			{
				std::cout << "Region: " << i + 1 << "\nBuilding number: " << j + 1 <<
					"\nBuilding type: " << "Barn." << "\nBuilding square: " <<
					regions[i].buildings[j].building_square << std::endl;
			}
		}
	}
}

int main()
{
	int amount = 0;
	int village_square = 0;
	std::vector<Region> regions;
	while (amount == 0)
	{
		while (village_square == 0)
		{
			std::cout << "Specify the area of the village: ";
			std::cin >> village_square;
			if (village_square <= 0)
				std::cerr << "Error! The village area cannot be equal to 0 or less than 0. Try again.";
		}

		std::cout << "How many regions are there in the village ? " << std::endl;
		std::cin >> amount;
		if (amount <= 0)
			std::cerr << "Error! The building area cannot be equal to 0 or less than 0. Try again.";
		else
		{
			regions.resize(amount);
			fill_region_buildings(regions, &amount, village_square);
		}
	}

	print(regions, village_square);

	return 0;
}