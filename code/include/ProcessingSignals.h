#pragma once
#include "TypeOfStep.h"

class ProcessingSignals {

private:
	Step* class_step;
	//this pointer are getting during making ProcessingSignals
	//exist during all existing of ProcessingSignals
	//delete without class ProcessingSignals
	int number_of_step_type;
	//0 <= ... < 4
	Pair command_1;
	Pair command_2;
	int number_of_free_command;
	//1 or 2

public:
	ProcessingSignals(Step* class_step_tmp);

	void get_new_type_of_step(int i);
	//write new type in own field
	//reset all settings
	
	void get_new_command(Pair p);
	//write new command in free field
	//if we have ready command for step:
	//reset all settings without number_of_step_type
	//call this command from step
	
	//correct call of command:
	//go_figure: final square for step
	//install_wall: crossroad and one part of wall
	//avoid_figure_opponent: final square for step
	//avoid_figure_and_barrier: place of opponent figure and final square for step
	
	//in other situations step is possible and processing about logical
	
};
