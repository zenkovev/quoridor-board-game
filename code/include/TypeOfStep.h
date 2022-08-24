#pragma once
#include <utility>

using Pair = std::pair<int, int>;
//show number of square on game field
//these squares includes all type of squares as figuresquare, wallsquare, crossroadsquare
//numeration consist of figuresquares on border and inside and layers of wallsquares between them

//Example for game field 3*3
//F W F W F
//W C W C W
//F W F W F
//W C W C W
//F W F W F

//F - figuresquare
//W - wallsquare
//C - crossroadsquare

//Correct Pair is (i, j), where 0 <= i < 5, 0 <= j < 5

bool Pair_is_correct_square(Pair p, int field_sizes);
//field_sizes includes all type of squares as figuresquare, wallsquare, crossroadsquare
bool Pair_is_figure_square(Pair p);
bool Pair_is_wall_square(Pair p);
bool Pair_is_crossroad_square(Pair p);





class Step;
void distributor(Step* class_step, int number_of_step_type, Pair command_1, Pair command_2);





/*
Big constructor of game: Parametres:
	int number_of_players
	//2 or 4
	int field_figure_sizes
	int number_of_walls
	int size_of_figure_button
*/

enum StepTypeValue {
	GoFigure,
	InstallWall,
	AvoidFigureOpponent,
	AvoidFigureAndBarrier
};

enum Direction {left, right, up, down};
enum HVDirection {horizontal, vertical};

struct CardOfStep {
	//contains all information about step
	//during step some fields can be unused

	int number_of_players;
	//2 or 4
	int number_of_current_player;
	//0 <= number_of_current_player < number_of_players
	
	StepTypeValue type_of_step;
	bool is_step_correct;

	Pair position_of_his_figure;
	Direction all_type_of_go_direction;
	Direction avoid_figure_and_barrier_deviation;
	Pair new_position_of_his_figure;

	Pair position_of_crossroad_of_new_wall;
	HVDirection install_wall_direction;
	Pair first_element_of_wall;
	Pair second_element_of_wall;
};
