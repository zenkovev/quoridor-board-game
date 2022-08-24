#pragma once
#include "TypeOfStep.h"
#include "Table.h"
#include "Participant.h"
#include "AllImage.h"
#include "ProcessingSignals.h"
#include <iostream>
#include <cassert>

class Step {

private:
	int number_of_players;
	std::shared_ptr<Table> game_table;
	std::vector<Participant> vector_participants;
	std::shared_ptr<ProcessingSignals> process_signal;

	int number_of_current_player;

public:
	std::shared_ptr<AllImage> graphic_all_image;

public:
	Step(int number_of_players_tmp, int field_figure_sizes, int number_of_walls, int size_of_figure_button);
	//main constructor of all game
	
	Direction relation_pair_2_to_pair_1(Pair pair_1, Pair pair_2);
	
	void distributor(int number_of_step_type, Pair command_1, Pair command_2);

	int next_number_of_player(int current_number);

	void after_all_go_figure(CardOfStep& card);
	
	void go_figure(CardOfStep& card);
        void install_wall(CardOfStep& card);
        void avoid_figure_opponent(CardOfStep& card);
        void avoid_figure_and_barrier(CardOfStep& card);
        
};
