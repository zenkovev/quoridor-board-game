#pragma once
#include <iostream>
#include <cassert>

class Participant {

public:
	Participant(int number_of_walls_tmp, int vertical_coordinate_tmp, int horizontal_coordinate_tmp);

	void print_all_information();

	int know_number_of_walls();
	int know_v_c();
	int know_h_c();
	//v_c - vertical_coordinate
	//h_c - horizontal_coordinate
	//this functions called in calling of other functions therefore their names made short

	void use_one_wall();
	//must be: number_of_walls > 0

	void change_coordinates(int vertical_coordinate_tmp, int horizontal_coordinate_tmp);
	
private:
	int number_of_walls;
	//number_of_walls >= 0
	int vertical_coordinate;
	int horizontal_coordinate;

};
