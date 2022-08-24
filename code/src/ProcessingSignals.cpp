#include <ProcessingSignals.h>

ProcessingSignals::ProcessingSignals(Step* class_step_tmp) {
	class_step = class_step_tmp;
	number_of_step_type = 0;
	number_of_free_command = 1;
}

void ProcessingSignals::get_new_type_of_step(int i) {
	number_of_step_type = i;
	number_of_free_command = 1;
}

void ProcessingSignals::get_new_command(Pair p) {
	if ((number_of_step_type == 1 || number_of_step_type == 3) &&
			number_of_free_command == 1) {
		command_1 = p;
		++number_of_free_command;
		return;
	}
	
	//in other situations we must to call functions from step
	
	command_2 = p;
	number_of_free_command = 1;

	//we reset all settings
	//now we work with number_of_step_type and one or two command
	
	distributor(class_step, number_of_step_type, command_1, command_2);
}
