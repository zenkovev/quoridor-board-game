#pragma once
#include <gtkmm.h>
#include <vector>
#include <sstream>
#include <string>
#include <utility>
#include "ProcessingSignals.h"
#include <memory>
#include <iostream>
#include <cassert>

class TableImage {

//fields and methods located in logical order

public:
	Gtk::Box m_Box_Main;
	//contains all graphic elements of game table

private:
	int field_sizes;
	int field_figure_sizes;
	int field_wall_sizes;
	//field_sizes is real number of squares in row (== in column)
	//field_figure_sizes is number of squares for figures in row (== in column)
	//field_wall_sizes is number of squares for crossroads in row (== in column)
	
	std::vector<Gtk::Box> m_Vector_Box_Row;
	//contains all horizontal strings of elements of game table
	std::vector<Gtk::Button> m_Vector_Button_Row;
	//keep all horizontal strings of elements of game table
	
	int size_of_figure_button;
	//size_of_figure_button == 50, 60, 70, 80, 90 or 100 pixels
	//size_of_wall_crossroad_button should be size_of_figure_button/4
	
	std::vector<Gtk::Image> m_Vector_Image_Figure;
	//keep four images of figures and void square image
	
	std::vector<Glib::RefPtr<Gtk::CssProvider>> m_Vector_Image_Figure_CssProvider;
	//save appearance if we have problems with images
	
	Glib::RefPtr<Gtk::CssProvider> m_CssProvider_Wall_White;
	//keep style of white (void) element of wall
	Glib::RefPtr<Gtk::CssProvider> m_CssProvider_Wall_Black;
	//keep style of black (real) element of wall
	
	void construct_images();
	//size_of_figure_button must be installed
	//also construct m_Vector_Pair_Signals with default values
	
	void construct_css_providers();
	
	Gtk::Button& vector_button_row_at(size_t row, size_t column);
	//field_sizes, field_figure_sizes and field_wall_sizes must be installed
	//return absolute position, it can be figure or wall square
	
	void construct_buttons();
	//all sizes, images and css_providers were constructed
	//construct m_Vector_Box_Row and m_Vector_Button_Row
	//make correct void field
	//connect buttons with signals
	
	void spawn_figures(int number_of_players);
	//number_of_players == 2 or 4

public:
	std::weak_ptr<ProcessingSignals> class_processing_signals;
	
public:
	void add_processing_signals(std::shared_ptr<ProcessingSignals> class_processing_signals_tmp);
	
	using pair = std::pair<int, int>;
	//struct for work with signals

private:	
	std::vector<pair> m_Vector_Pair_Signals;
	//keep where image with this number is situated

	void field_square_on_signal_clicked(pair p);
	//method for work with signals

public:
	TableImage(int number_of_players_tmp, int field_figure_sizes_tmp, int size_of_figure_button_tmp);
	//construct TableImage
	//parametres must be correct
	
	void change_figure_position(int number_of_figure, pair new_position);
	//new_position must be free
	//does not differentiate figure and wall squares
	
	void install_wall(pair new_square_wall);
	//does not differentiate figure and wall squares

};
