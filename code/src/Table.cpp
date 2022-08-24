#include <Table.h>

inline bool is_correct_direction(Direction dir) {
	return dir == left || dir == right || dir == up || dir == down;
}

inline bool is_left_right_direction(Direction dir) {
	return dir == left || dir == right;
}

inline bool is_up_down_direction(Direction dir) {
	return dir == up || dir == down;
}

inline bool is_correct_hvdirection(HVDirection dir) {
	return dir == horizontal || dir == vertical;
}

Table::Table(int size) {
	assert(size >= 3);
	assert(size % 2 == 1);
	field_figure_sizes = size;
	field_wall_sizes = size-1;
	field_sizes = field_figure_sizes*2 + 1;
	
	field.clear();
	field.reserve(field_sizes*field_sizes);
	assert(field.empty());
	for (int i = 0; i < field_sizes*field_sizes; ++i) {
		field.push_back(nullsquare);
	}
	
	//i - vertical, from up to down
	//j - horizontal, from left to right
	for (int i = 0; i < field_sizes; ++i) {
		field[i*field_sizes + 0] = wallsquare;
		field[i*field_sizes + field_sizes-1] = wallsquare;
		field[0*field_sizes + i] = wallsquare;
		field[(field_sizes-1)*field_sizes + i] = wallsquare;
	}
}

FigureType& Table::at(int pos_v, int pos_h) {
	return field[pos_v*field_sizes + pos_h];
}

void Table::spawn_figures(int number_of_figures) {
	assert(number_of_figures == 2 || number_of_figures == 4);
	int position = field_sizes / 2;
	at(1, position) = figuresquare;
	at(field_sizes-2, position) = figuresquare;
	if (number_of_figures == 4) {
		at(position, 1) = figuresquare;
		at(position, field_sizes-2) = figuresquare;
	}
}

int Table::know_field_figure_sizes() const {
	return field_figure_sizes;
}

int Table::know_field_wall_sizes() const {
	return field_wall_sizes;
}

bool Table::is_figure_in_this_field(int pos_v, int pos_h) {
	assert(pos_v >= 0 && pos_v < field_figure_sizes);
	assert(pos_h >= 0 && pos_h < field_figure_sizes);
	int real_pos_v = pos_v*2 + 1;
	int real_pos_h = pos_h*2 + 1;
	return at(real_pos_v, real_pos_h) == figuresquare;
}

void Table::print_all_field() {
	std::cout << "----------" << '\n';
	for (int i = 0; i < field_sizes; ++i) {
		for (int j = 0; j < field_sizes; ++j) {
			if (at(i, j) == nullsquare) {
				std::cout << 'N';
			} else if (at(i, j) == figuresquare) {
				std::cout << 'F';
			} else if (at(i, j) == wallsquare) {
				std::cout << 'W';
			} else {
				std::cout << 'E';
			}
		}
		std::cout << '\n';
	}
	std::cout << "----------" << '\n';
}

int Table::find_deviation_v(Direction dir) {
	assert(is_correct_direction(dir));
	if (dir == left || dir == right) return 0;
	if (dir == up) return -1;
	return 1;
}

int Table::find_deviation_h(Direction dir) {
	assert(is_correct_direction(dir));
	if (dir == up || dir == down) return 0;
	if (dir == left) return -1;
	return 1;
}

void Table::deviate_position_v(int& pos_v, Direction dir, int number_of_steps) {
	pos_v += find_deviation_v(dir)*number_of_steps;
}

void Table::deviate_position_h(int& pos_h, Direction dir, int number_of_steps) {
	pos_h += find_deviation_h(dir)*number_of_steps;
}

FigureType& Table::at_direction(int pos_v, int pos_h, Direction dir, int number_of_steps) {
	deviate_position_v(pos_v, dir, number_of_steps);
	deviate_position_h(pos_h, dir, number_of_steps);
	return at(pos_v, pos_h);
}

Pair Table::at_two_directions_pair(int pos_v, int pos_h, Direction dir1, int number_of_steps1, Direction dir2, int number_of_steps2) {
        deviate_position_v(pos_v, dir1, number_of_steps1);
        deviate_position_h(pos_h, dir1, number_of_steps1);
        deviate_position_v(pos_v, dir2, number_of_steps2);
        deviate_position_h(pos_h, dir2, number_of_steps2);
	Pair p(pos_v, pos_h);
	return p;
}

FigureType& Table::at_two_directions(int pos_v, int pos_h, Direction dir1, int number_of_steps1, Direction dir2, int number_of_steps2) {
	deviate_position_v(pos_v, dir1, number_of_steps1);
	deviate_position_h(pos_h, dir1, number_of_steps1);
	deviate_position_v(pos_v, dir2, number_of_steps2);
	deviate_position_h(pos_h, dir2, number_of_steps2);
	return at(pos_v, pos_h);
}

void Table::go_figure(CardOfStep& card) {
	int pos_v = card.position_of_his_figure.first/2;
	int pos_h = card.position_of_his_figure.second/2;
	Direction dir = card.all_type_of_go_direction;

	assert(pos_v >= 0 && pos_v < field_figure_sizes);
	assert(pos_h >= 0 && pos_h < field_figure_sizes);
	int real_pos_v = pos_v*2 + 1;
	int real_pos_h = pos_h*2 + 1;
	assert(at(real_pos_v, real_pos_h) == figuresquare);

	/*
	if (dir == left) {
		if (at(real_pos_v, real_pos_h-1) != nullsquare) return false;
		if (at(real_pos_v, real_pos_h-2) != nullsquare) return false;
		at(real_pos_v, real_pos_h-2) = figuresquare;
		at(real_pos_v, real_pos_h) = nullsquare;
		return true;
	}
	if (dir == right) {
		if (at(real_pos_v, real_pos_h+1) != nullsquare) return false;
		if (at(real_pos_v, real_pos_h+2) != nullsquare) return false;
		at(real_pos_v, real_pos_h+2) = figuresquare;
		at(real_pos_v, real_pos_h) = nullsquare;
		return true;
	}
	if (dir == up) {
		if (at(real_pos_v-1, real_pos_h) != nullsquare) return false;
		if (at(real_pos_v-2, real_pos_h) != nullsquare) return false;
		at(real_pos_v-2, real_pos_h) = figuresquare;
		at(real_pos_v, real_pos_h) = nullsquare;
		return true;
	}
	if (dir == down) {
		if (at(real_pos_v+1, real_pos_h) != nullsquare) return false;
		if (at(real_pos_v+2, real_pos_h) != nullsquare) return false;
		at(real_pos_v+2, real_pos_h) = figuresquare;
		at(real_pos_v, real_pos_h) = nullsquare;
		return true;
	}
	*/

	assert(is_correct_direction(dir));
	int dir_v = find_deviation_v(dir);
	int dir_h = find_deviation_h(dir);
	if (at(real_pos_v + dir_v, real_pos_h + dir_h) != nullsquare) {
		card.is_step_correct = false;
		card.new_position_of_his_figure = card.position_of_his_figure;
		return;
	}
	if (at(real_pos_v + dir_v*2, real_pos_h + dir_h*2) != nullsquare) {
		card.is_step_correct = false;
                card.new_position_of_his_figure = card.position_of_his_figure;
                return;
	}
	at(real_pos_v + dir_v*2, real_pos_h + dir_h*2) = figuresquare;
	at(real_pos_v, real_pos_h) = nullsquare;

	card.is_step_correct = true;
	card.new_position_of_his_figure.first = real_pos_v + dir_v*2 - 1;
	card.new_position_of_his_figure.second = real_pos_h + dir_h*2 - 1;
	return;
}

void Table::install_wall(CardOfStep& card) {
	int crossroad_v = (card.position_of_crossroad_of_new_wall.first-1)/2;
	int crossroad_h = (card.position_of_crossroad_of_new_wall.second-1)/2;
	HVDirection dir = card.install_wall_direction;

	assert(crossroad_v >= 0 && crossroad_v < field_wall_sizes);
	assert(crossroad_h >= 0 && crossroad_h < field_wall_sizes);
	int real_crossroad_v = crossroad_v*2 + 2;
	int real_crossroad_h = crossroad_h*2 + 2;
	if (at(real_crossroad_v, real_crossroad_h) != nullsquare) {
		card.is_step_correct = false;
		return;
	}

	assert(is_correct_hvdirection(dir));
	if (dir == vertical) {
		if (at(real_crossroad_v-1, real_crossroad_h) != nullsquare ||
				at(real_crossroad_v+1, real_crossroad_h) != nullsquare) {
			card.is_step_correct = false;
                	return;
		} else {
			at(real_crossroad_v, real_crossroad_h) = wallsquare;
			at(real_crossroad_v-1, real_crossroad_h) = wallsquare;
			at(real_crossroad_v+1, real_crossroad_h) = wallsquare;

			card.is_step_correct = true;
			card.first_element_of_wall.first = real_crossroad_v-1-1;
			card.first_element_of_wall.second = real_crossroad_h-1;
			card.second_element_of_wall.first = real_crossroad_v+1-1;
			card.second_element_of_wall.second = real_crossroad_h-1;
			return;
		}
	}
	//dir == horizontal
	if (at(real_crossroad_v, real_crossroad_h-1) != nullsquare ||
				at(real_crossroad_v, real_crossroad_h+1) != nullsquare) {
		card.is_step_correct = false;
                return;
	}
	//at(real_crossroad_v, real_crossroad_h-1) == nullsquare &&
	//		at(real_crossroad_v, real_crossroad_h+1) == nullsquare
	at(real_crossroad_v, real_crossroad_h) = wallsquare;
	at(real_crossroad_v, real_crossroad_h-1) = wallsquare;
	at(real_crossroad_v, real_crossroad_h+1) = wallsquare;
	
	card.is_step_correct = true;
	card.first_element_of_wall.first = real_crossroad_v-1;
	card.first_element_of_wall.second = real_crossroad_h-1-1;
	card.second_element_of_wall.first = real_crossroad_v-1;
	card.second_element_of_wall.second = real_crossroad_h+1-1;
	return;
}

void Table::avoid_figure_opponent(CardOfStep& card) {
        int pos_v = card.position_of_his_figure.first/2;
        int pos_h = card.position_of_his_figure.second/2;
        Direction dir = card.all_type_of_go_direction;

	assert(pos_v >= 0 && pos_v < field_figure_sizes);
	assert(pos_h >= 0 && pos_h < field_figure_sizes);
	int real_pos_v = pos_v*2 + 1;
	int real_pos_h = pos_h*2 + 1;
	assert(at(real_pos_v, real_pos_h) == figuresquare);

	assert(is_correct_direction(dir));
	int dir_v = find_deviation_v(dir);
	int dir_h = find_deviation_h(dir);
	if (at(real_pos_v + dir_v, real_pos_h + dir_h) != nullsquare) {
		card.is_step_correct = false;
                card.new_position_of_his_figure = card.position_of_his_figure;
                return;
	}
	if (at(real_pos_v + dir_v*2, real_pos_h + dir_h*2) != figuresquare) {
		card.is_step_correct = false;
                card.new_position_of_his_figure = card.position_of_his_figure;
                return;
	}
	if (at(real_pos_v + dir_v*3, real_pos_h + dir_h*3) != nullsquare) {
		card.is_step_correct = false;
                card.new_position_of_his_figure = card.position_of_his_figure;
                return;
	}
	if (at(real_pos_v + dir_v*4, real_pos_h + dir_h*4) != nullsquare) {
		card.is_step_correct = false;
                card.new_position_of_his_figure = card.position_of_his_figure;
                return;
        }

	at(real_pos_v, real_pos_h) = nullsquare;
	at(real_pos_v + dir_v*4, real_pos_h + dir_h*4) = figuresquare;

	card.is_step_correct = true;
        card.new_position_of_his_figure.first = real_pos_v + dir_v*4 - 1;
        card.new_position_of_his_figure.second = real_pos_h + dir_h*4 - 1;
        return;
}

void Table::avoid_figure_and_barrier(CardOfStep& card) {
        int pos_v = card.position_of_his_figure.first/2;
        int pos_h = card.position_of_his_figure.second/2;
        Direction dir = card.all_type_of_go_direction;
	Direction deviation = card.avoid_figure_and_barrier_deviation;

	assert(pos_v >= 0 && pos_v < field_figure_sizes);
	assert(pos_h >= 0 && pos_h < field_figure_sizes);
	int real_pos_v = pos_v*2 + 1;
	int real_pos_h = pos_h*2 + 1;
	assert(at(real_pos_v, real_pos_h) == figuresquare);
	
	assert(is_correct_direction(dir));
	assert(deviation == left || deviation == right);
	
	if(at_direction(real_pos_v, real_pos_h, dir, 1) != nullsquare) {
		card.is_step_correct = false;
                card.new_position_of_his_figure = card.position_of_his_figure;
                return;
        }
	if(at_direction(real_pos_v, real_pos_h, dir, 2) != figuresquare) {
		card.is_step_correct = false;
                card.new_position_of_his_figure = card.position_of_his_figure;
                return;
	}
	if(at_direction(real_pos_v, real_pos_h, dir, 3) != wallsquare &&
			at_direction(real_pos_v, real_pos_h, dir, 4) != figuresquare) {
		card.is_step_correct = false;
                card.new_position_of_his_figure = card.position_of_his_figure;
                return;
	}

	while(true) {
		if (dir == left && deviation == left) {
			deviation = down;
			break;
		}
		if (dir == left && deviation == right) {
			deviation = up;
			break;
		}
		if (dir == right && deviation == left) {
			deviation = up;
			break;
		}
		if (dir == right && deviation == right) {
			deviation = down;
			break;
		}
		if (dir == up && deviation == left) {
			deviation = left;
			break;
		}
		if (dir == up && deviation == right) {
			deviation = right;
			break;
		}
		if (dir == down && deviation == left) {
			deviation = right;
			break;
		}
		if (dir == down && deviation == right) {
			deviation = left;
			break;
		}
		assert(false);
	}
	
	if(at_two_directions(real_pos_v, real_pos_h, dir, 2, deviation, 1) != nullsquare) {
		card.is_step_correct = false;
                card.new_position_of_his_figure = card.position_of_his_figure;
                return;
	}
	if(at_two_directions(real_pos_v, real_pos_h, dir, 2, deviation, 2) != nullsquare) {
		card.is_step_correct = false;
                card.new_position_of_his_figure = card.position_of_his_figure;
                return;
	}

	at(real_pos_v, real_pos_h) = nullsquare;
	at_two_directions(real_pos_v, real_pos_h, dir, 2, deviation, 2) = figuresquare;

	card.is_step_correct = true;
        card.new_position_of_his_figure = at_two_directions_pair(real_pos_v, real_pos_h, dir, 2, deviation, 2);
        --card.new_position_of_his_figure.first;
        --card.new_position_of_his_figure.second;
        return;
}
