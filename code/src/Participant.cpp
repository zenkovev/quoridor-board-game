#include <Participant.h>

Participant::Participant(int number_of_walls_tmp, int vertical_coordinate_tmp, int horizontal_coordinate_tmp) {
	assert(number_of_walls_tmp >= 0);
	number_of_walls = number_of_walls_tmp;
	vertical_coordinate = vertical_coordinate_tmp;
	horizontal_coordinate = horizontal_coordinate_tmp;
}

void Participant::print_all_information() {
	std::cout << "----------" << '\n';
	std::cout << "Participant\n";
	std::cout << "number_of_walls " << number_of_walls << '\n';
	std::cout << "vertical_coordinate " << vertical_coordinate << '\n';
	std::cout << "horizontal_coordinate " << horizontal_coordinate << '\n';
	std::cout << "----------" << '\n';
}

int Participant::know_number_of_walls() {
	return number_of_walls;
}

int Participant::know_v_c() {
	return vertical_coordinate;
}

int Participant::know_h_c() {
	return horizontal_coordinate;
}

void Participant::use_one_wall() {
	assert(number_of_walls > 0);
	--number_of_walls;
}

void Participant::change_coordinates(int vertical_coordinate_tmp, int horizontal_coordinate_tmp) {
	vertical_coordinate = vertical_coordinate_tmp;
	horizontal_coordinate = horizontal_coordinate_tmp;
}
