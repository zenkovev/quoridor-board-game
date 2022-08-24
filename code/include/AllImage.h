#pragma once
#include "TableImage.h"
#include <memory>

class AllImage {

public:
	std::shared_ptr<TableImage> table_image;

public:
	Gtk::Box m_Box_Top;

private:
	Gtk::Box m_Box_Left,
		m_Box_Right_Table,
		m_Box_Left1_Steps,
		m_Box_Left2_Players;

	std::vector<Gtk::RadioButton> m_Vector_Radio_Button;
	//contains four buttons of step types
	
	std::vector<Gtk::Frame> m_Vector_Frame;
	std::vector<Gtk::Label> m_Vector_Label;
	//contains information about players

	void construct_radio_buttons();
	//construct buttons and pack them
	//all boxes must be created
	
	void construct_frame_label(int number_of_players, int number_of_walls);
	//construct all text and pack them
	//all boxes must be created

public:
	AllImage(
		int number_of_players,
		int field_figure_sizes,
		int size_of_figure_button,
		int number_of_walls
	);
	//construct AllImage
	
private:
	void radio_button_on_signal_clicked(int i);
	//method for work with signals

public:
	void change_condition_of_player(int number_of_player, bool is_go_now, int new_number_of_walls, bool is_step_correct);
	//change text on label
		
};
