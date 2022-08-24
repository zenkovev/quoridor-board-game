#include <Step.h>

Step::Step(int number_of_players_tmp, int field_figure_sizes, int number_of_walls, int size_of_figure_button) {
	number_of_players = number_of_players_tmp;
	number_of_current_player = 0;
	game_table = std::make_shared<Table>(field_figure_sizes);
	game_table->spawn_figures(number_of_players);
	
	vector_participants.clear();
	vector_participants.reserve(number_of_players);
	{
		Participant p1(number_of_walls, 0, field_figure_sizes/2);
		Participant p2(number_of_walls, field_figure_sizes-1, field_figure_sizes/2);
		vector_participants.push_back(p1);
		vector_participants.push_back(p2);
		if (number_of_players == 4) {
			Participant p3(number_of_walls, field_figure_sizes/2, 0);
			Participant p4(number_of_walls, field_figure_sizes/2, field_figure_sizes-1);
			vector_participants.push_back(p3);
			vector_participants.push_back(p4);
		}
	}

	graphic_all_image = std::make_shared<AllImage>(number_of_players, field_figure_sizes, size_of_figure_button, number_of_walls);
	process_signal = std::make_shared<ProcessingSignals>(this);

	graphic_all_image->table_image->add_processing_signals(process_signal);
}

Direction Step::relation_pair_2_to_pair_1(Pair pair_1, Pair pair_2) {
	if (pair_2.first < pair_1.first) {
		return up;
	}
	if (pair_2.first > pair_1.first) {
		return down;
	}
	if (pair_2.second < pair_1.second) {
		return left;
	}
	return right;
}

void Step::distributor(int number_of_step_type, Pair command_1, Pair command_2) {
	CardOfStep card;
	card.number_of_players = number_of_players;
	card.number_of_current_player = number_of_current_player;
	{
		Pair p(2*vector_participants[number_of_current_player].know_v_c(),
				2*vector_participants[number_of_current_player].know_h_c());
		card.position_of_his_figure = p;
	}

	if (number_of_step_type == 0) {
		card.type_of_step = GoFigure;
		card.all_type_of_go_direction = relation_pair_2_to_pair_1(card.position_of_his_figure, command_2);
		return go_figure(card);
	}

	if (number_of_step_type == 1) {
		card.type_of_step = InstallWall;
		card.position_of_crossroad_of_new_wall = command_1;
		{
			Direction dir = relation_pair_2_to_pair_1(command_1, command_2);
			if (dir == left || dir == right) {
				card.install_wall_direction = horizontal;
			} else {
				card.install_wall_direction = vertical;
			}
		}
		return install_wall(card);
	}

	if (number_of_step_type == 2) {
		card.type_of_step = AvoidFigureOpponent;
		card.all_type_of_go_direction = relation_pair_2_to_pair_1(card.position_of_his_figure, command_2);
		return avoid_figure_opponent(card);
	}

	card.type_of_step = AvoidFigureAndBarrier;
	card.all_type_of_go_direction = relation_pair_2_to_pair_1(card.position_of_his_figure, command_1);
	
	if (card.all_type_of_go_direction == left) {
		if (command_2.first < command_1.first) {
			card.avoid_figure_and_barrier_deviation = right;
		} else {
			card.avoid_figure_and_barrier_deviation = left;
		}
	}
	if (card.all_type_of_go_direction == right) {
		if (command_2.first < command_1.first) {
			card.avoid_figure_and_barrier_deviation = left;
		} else {
			card.avoid_figure_and_barrier_deviation = right;
		}
	}
	if (card.all_type_of_go_direction == up) {
		if (command_2.second < command_1.second) {
			card.avoid_figure_and_barrier_deviation = left;
		} else {
			card.avoid_figure_and_barrier_deviation = right;
		}
	}
	if (card.all_type_of_go_direction == down) {
		if (command_2.second < command_1.second) {
			card.avoid_figure_and_barrier_deviation = right;
		} else {
			card.avoid_figure_and_barrier_deviation = left;
		}
	}
	
	return avoid_figure_and_barrier(card);
}

int Step::next_number_of_player(int current_number) {
	//Order of players:
        //0    0
        //    2 3
        //1    1

        //0 -> 1 -> 0
        //0 -> 2 -> 1 -> 3 -> 0
	
	if (number_of_players == 2) {
		return (current_number+1) % 2;
	}

	if (current_number == 0 || current_number == 1) {
		return current_number + 2;
	}

	return (current_number+1)%2;
}

void Step::after_all_go_figure(CardOfStep& card) {
	if (!card.is_step_correct) {
                graphic_all_image->change_condition_of_player(
                                number_of_current_player,
                                true,
                                vector_participants[number_of_current_player].know_number_of_walls(),
                                false);
                return;
        }

        vector_participants[number_of_current_player].change_coordinates(
                        card.new_position_of_his_figure.first/2,
                        card.new_position_of_his_figure.second/2);
        graphic_all_image->table_image->change_figure_position(
                        number_of_current_player,
                        card.new_position_of_his_figure);

        graphic_all_image->change_condition_of_player(
                        number_of_current_player,
                        false,
                        vector_participants[number_of_current_player].know_number_of_walls(),
                        true);

        number_of_current_player = next_number_of_player(number_of_current_player);

        graphic_all_image->change_condition_of_player(
                        number_of_current_player,
                        true,
                        vector_participants[number_of_current_player].know_number_of_walls(),
                        true);
        return;
}

void Step::go_figure(CardOfStep& card) {
	game_table->go_figure(card);
	after_all_go_figure(card);
}

void Step::avoid_figure_opponent(CardOfStep& card) {
	game_table->avoid_figure_opponent(card);
	after_all_go_figure(card);
}

void Step::avoid_figure_and_barrier(CardOfStep& card) {
	game_table->avoid_figure_and_barrier(card);
	after_all_go_figure(card);
}

void Step::install_wall(CardOfStep& card) {
	if (vector_participants[number_of_current_player].know_number_of_walls() <= 0 ||
			!Pair_is_crossroad_square(card.position_of_crossroad_of_new_wall)) {
		graphic_all_image->change_condition_of_player(
                                number_of_current_player,
                                true,
                                vector_participants[number_of_current_player].know_number_of_walls(),
                                false);
                return;
	}

	game_table->install_wall(card);

	if (!card.is_step_correct) {
                graphic_all_image->change_condition_of_player(
                                number_of_current_player,
                                true,
                                vector_participants[number_of_current_player].know_number_of_walls(),
                                false);
                return;
        }

	graphic_all_image->table_image->install_wall(card.position_of_crossroad_of_new_wall);
	graphic_all_image->table_image->install_wall(card.first_element_of_wall);
	graphic_all_image->table_image->install_wall(card.second_element_of_wall);

	vector_participants[number_of_current_player].use_one_wall();

	graphic_all_image->change_condition_of_player(
                        number_of_current_player,
                        false,
                        vector_participants[number_of_current_player].know_number_of_walls(),
                        true);

        number_of_current_player = next_number_of_player(number_of_current_player);

        graphic_all_image->change_condition_of_player(
                        number_of_current_player,
                        true,
                        vector_participants[number_of_current_player].know_number_of_walls(),
                        true);
        return;
}

void distributor(Step* class_step, int number_of_step_type, Pair command_1, Pair command_2) {
	class_step->distributor(number_of_step_type, command_1, command_2);
}
