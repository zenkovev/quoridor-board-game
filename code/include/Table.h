#pragma once
#include <cstdint>
#include <vector>
#include "TypeOfStep.h"
#include <iostream>
#include <cassert>

using square = uint8_t;

enum FigureType {nullsquare, figuresquare, wallsquare};
//null is a void square for all types of square
//wall is an element of wall in crossroad or on broads of simple squares
//figure is a figure

//in the comments below:
//must be: else assert
//should be: else false without changes

class Table {

public:
	Table(int size);
	//size is a field_figure_sizes
	//must be: size is integer, odd_numbered, >= 3
	
	void spawn_figures(int number_of_figures);
	//must be: number_of_figures == 2 or 4
	//two figures install in centre of up and down rows
	//if it is not all still two figures install in centre of left and right columns
	
	int know_field_figure_sizes() const;
	int know_field_wall_sizes() const;

	void print_all_field();
	
	int find_deviation_v(Direction dir);
	int find_deviation_h(Direction dir);
	//must be: direction == left, right, up or down
	//left 0 -1
	//right 0 1
	//up -1 0
	//down 1 0

	bool is_figure_in_this_field(int pos_v, int pos_h);
	//must be: 0 <= pos_v (and pos_h) < field_figure_sizes
	
	/* Old version:
	bool go_figure(int pos_v, int pos_h, Direction dir);
	//must be: 0 <= pos_v (and pos_h) < field_figure_sizes
	//must be: in this position figure stands
	//must be: dir == left, right, up or down
	//should be: free motion in the direction without wall and other figure */
	
	/* New version: */
	void go_figure(CardOfStep& card);
	//must be installed:
	//- position_of_his_figure
	//- all_type_of_go_direction
	//must correct fields:
	//- is_step_correct
	//- new_position_of_his_figure
	
	/* Old version:	
	bool install_wall(int crossroad_v, int crossroad_h, HVDirection dir);
	//must be: 0 <= crossroad_v (and crossroad_h) < field_wall_sizes
	//must be: dir == vertical or horizontal */
	
	/* New version: */
	void install_wall(CardOfStep& card);
	//must be installed:
	//- position_of_crossroad_of_new_wall
	//- install_wall_direction
	//must correct fields:
	//- is_step_correct
	//- first_element_of_wall (if last is true)
	//- second_element_of_wall (if last is true)
	
	/* Old version:
	bool avoid_figure_opponent(int pos_v, int pos_h, Direction dir);
	//must be: 0 <= pos_v (and pos_h) < field_figure_sizes
	//must be: dir == left, right, up or down
	//should be: figure in the direction and free motion without wall and other figure */
	
	/* New version: */
	void avoid_figure_opponent(CardOfStep& card);
	//must be installed:
        //- position_of_his_figure
        //- all_type_of_go_direction
        //must correct fields:
        //- is_step_correct
        //- new_position_of_his_figure
	
	/* Old version:
	bool avoid_figure_and_barrier(int pos_v, int pos_h, Direction dir, Direction deviation);
	//must_be: 0 <= pos_v (and pos_h) < field_figure_sizes
	//must be: dir == left, right, up or down
	//must_be: deviation == left or right
	//should be: see rules of game (it is hard for comment writing) */
	
	/* New version: */
	void avoid_figure_and_barrier(CardOfStep& card);
	//must be installed:
        //- position_of_his_figure
        //- all_type_of_go_direction
	//- avoid_figure_and_barrier_deviation
        //must correct fields:
        //- is_step_correct
        //- new_position_of_his_figure

private:
	std::vector<FigureType> field;
	int field_sizes;
	int field_figure_sizes;
	int field_wall_sizes;
	//field_figure_sizes is a size of field for figures
	//field_wall_sizes is a size of field of internal crossroads
	//(internal crossroad is a crossroad, which is a corner of four figure squares)
	//field_sizes is an absolute field size
	//field is a two_dimensional square (in meaning quality of two dimensions) array for game
	//field includes external broad of wall for convience of code writing
	
	FigureType& at(int pos_v, int pos_h);
	//return this square of field
	
	void deviate_position_v(int& pos_v, Direction dir, int number_of_steps);
	void deviate_position_h(int& pos_h, Direction dir, int number_of_steps);
	//return deviation in find_deviation_v (or find_deviation_h) form
	//does not see correctness
	
	FigureType& at_direction(int pos_v, int pos_h, Direction dir, int number_of_steps);
	Pair at_two_directions_pair(int pos_v, int pos_h, Direction dir1, int number_of_steps1, Direction dir2, int number_of_steps2);
	FigureType& at_two_directions(int pos_v, int pos_h, Direction dir1, int number_of_steps1, Direction dir2, int number_of_steps2);
	//return square of field (in sizes of field_sizes) after going in direction in number_of_step
	//does not see correctness

};
