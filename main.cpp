/* g++ -g main.cpp -o quoridor `pkg-config gtkmm-3.0 --cflags --libs` */

#include "code/include/Step.h"
#include "main.h"

static const int ConstNumberOfPlayers = NumberOfPlayers;
static const int ConstFieldSizesForFigure = FieldSizesForFigure;
static const int ConstNumberOfWalls = NumberOfWalls;
static const int ConstSquarePixelSizes = SquarePixelSizes;

class Choose : public Gtk::Window {

protected:
	Gtk::Box box;
	
	Gtk::Box box_choose_number_of_players;
	Gtk::Box box_choose_field_size_for_figure;
	Gtk::Box box_choose_number_of_walls;
	Gtk::Box box_choose_square_pixel_size;
	
	std::vector<Gtk::RadioButton> choose_number_of_players;
	std::vector<Gtk::RadioButton> choose_field_size_for_figure;
	std::vector<Gtk::RadioButton> choose_number_of_walls;
	std::vector<Gtk::RadioButton> choose_square_pixel_size;
	
	void choose_number_of_players_on_signal_clicked(int i) {
		if (i == 0) {
			NumberOfPlayers = ConstNumberOfPlayers;
			return;
		}
		if (i == 1) {
			NumberOfPlayers = 2;
			return;
		}
		if (i == 2) {
			NumberOfPlayers = 4;
			return;
		}
		return;
	}
	
	void choose_field_size_for_figure_on_signal_clicked(int i) {
		if (i == 0) {
			FieldSizesForFigure = ConstFieldSizesForFigure;
			return;
		}
		if (i >= 1 && i < 8) {
			FieldSizesForFigure = i*2+1;
			return;
		}
		return;
	}
	
	void choose_number_of_walls_on_signal_clicked(int i) {
		if (i == 0) {
			NumberOfWalls = ConstNumberOfWalls;
			return;
		}
		if (i >= 1 && i < 3) {
			NumberOfWalls = i;
			return;
		}
		if (i >= 3 && i < 7) {
			NumberOfWalls = (i-2)*5;
			return;
		}
		return;
	}
	
	void choose_square_pixel_size_on_signal_clicked(int i) {
		if (i == 0) {
			SquarePixelSizes = ConstSquarePixelSizes;
			return;
		}
		if (i >= 1 && i < 7) {
			SquarePixelSizes = (i+4)*10;
			return;
		}
		return;
	}
	
	void construct_radio_buttons_choose_number_of_players() {
		choose_number_of_players.clear();
		choose_number_of_players.reserve(3);

		Gtk::RadioButton rb1("Выберите количество игроков:\nЗначение по умолчанию");
		Gtk::RadioButton rb2("Два игрока");
		Gtk::RadioButton rb3("Четыре игрока");
		
		choose_number_of_players.push_back(std::move(rb1));
		choose_number_of_players.push_back(std::move(rb2));
		choose_number_of_players.push_back(std::move(rb3));
		
		Gtk::RadioButton::Group group = choose_number_of_players[0].get_group();
		choose_number_of_players[1].set_group(group);
		choose_number_of_players[2].set_group(group);
		
		for (int i = 0; i < 3; ++i) {
			choose_number_of_players[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
				&Choose::choose_number_of_players_on_signal_clicked), i));
		}
		
		box_choose_number_of_players.set_border_width(10);
		for (int i = 0; i < 3; ++i) {
			box_choose_number_of_players.pack_start(choose_number_of_players[i]);
		}
		choose_number_of_players[0].set_active();
	}
	
	void construct_radio_buttons_choose_field_size_for_figure() {
		choose_field_size_for_figure.clear();
		choose_field_size_for_figure.reserve(8);

		Gtk::RadioButton rb1("Выберите размер поля:\nЗначение по умолчанию");
		Gtk::RadioButton rb2("3");
		Gtk::RadioButton rb3("5");
		Gtk::RadioButton rb4("7");
		Gtk::RadioButton rb5("9");
		Gtk::RadioButton rb6("11");
		Gtk::RadioButton rb7("13");
		Gtk::RadioButton rb8("15");
		
		choose_field_size_for_figure.push_back(std::move(rb1));
		choose_field_size_for_figure.push_back(std::move(rb2));
		choose_field_size_for_figure.push_back(std::move(rb3));
		choose_field_size_for_figure.push_back(std::move(rb4));
		choose_field_size_for_figure.push_back(std::move(rb5));
		choose_field_size_for_figure.push_back(std::move(rb6));
		choose_field_size_for_figure.push_back(std::move(rb7));
		choose_field_size_for_figure.push_back(std::move(rb8));
		
		Gtk::RadioButton::Group group = choose_field_size_for_figure[0].get_group();
		for (int i = 1; i < 8; ++i) {
			choose_field_size_for_figure[i].set_group(group);
		}
		
		for (int i = 0; i < 8; ++i) {
			choose_field_size_for_figure[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
				&Choose::choose_field_size_for_figure_on_signal_clicked), i));
		}
		
		box_choose_field_size_for_figure.set_border_width(10);
		for (int i = 0; i < 8; ++i) {
			box_choose_field_size_for_figure.pack_start(choose_field_size_for_figure[i]);
		}
		choose_field_size_for_figure[0].set_active();
	}
	
	void construct_radio_buttons_choose_number_of_walls() {
		choose_number_of_walls.clear();
		choose_number_of_walls.reserve(7);

		Gtk::RadioButton rb1("Выберите количество стенок:\nЗначение по умолчанию");
		Gtk::RadioButton rb2("1");
		Gtk::RadioButton rb3("2");
		Gtk::RadioButton rb4("5");
		Gtk::RadioButton rb5("10");
		Gtk::RadioButton rb6("15");
		Gtk::RadioButton rb7("20");
		
		choose_number_of_walls.push_back(std::move(rb1));
		choose_number_of_walls.push_back(std::move(rb2));
		choose_number_of_walls.push_back(std::move(rb3));
		choose_number_of_walls.push_back(std::move(rb4));
		choose_number_of_walls.push_back(std::move(rb5));
		choose_number_of_walls.push_back(std::move(rb6));
		choose_number_of_walls.push_back(std::move(rb7));
		
		Gtk::RadioButton::Group group = choose_number_of_walls[0].get_group();
		for (int i = 1; i < 7; ++i) {
			choose_number_of_walls[i].set_group(group);
		}
		
		for (int i = 0; i < 7; ++i) {
			choose_number_of_walls[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
				&Choose::choose_number_of_walls_on_signal_clicked), i));
		}
		
		box_choose_number_of_walls.set_border_width(10);
		for (int i = 0; i < 7; ++i) {
			box_choose_number_of_walls.pack_start(choose_number_of_walls[i]);
		}
		choose_number_of_walls[0].set_active();
	}
			
	
	void construct_radio_buttons_choose_square_pixel_size() {
		choose_square_pixel_size.clear();
		choose_square_pixel_size.reserve(7);

		Gtk::RadioButton rb1("Выберите размер клетки поля:\nЗначение по умолчанию");
		Gtk::RadioButton rb2("50");
		Gtk::RadioButton rb3("60");
		Gtk::RadioButton rb4("70");
		Gtk::RadioButton rb5("80");
		Gtk::RadioButton rb6("90");
		Gtk::RadioButton rb7("100");
		
		choose_square_pixel_size.push_back(std::move(rb1));
		choose_square_pixel_size.push_back(std::move(rb2));
		choose_square_pixel_size.push_back(std::move(rb3));
		choose_square_pixel_size.push_back(std::move(rb4));
		choose_square_pixel_size.push_back(std::move(rb5));
		choose_square_pixel_size.push_back(std::move(rb6));
		choose_square_pixel_size.push_back(std::move(rb7));
		
		Gtk::RadioButton::Group group = choose_square_pixel_size[0].get_group();
		for (int i = 1; i < 7; ++i) {
			choose_square_pixel_size[i].set_group(group);
		}
		
		for (int i = 0; i < 7; ++i) {
			choose_square_pixel_size[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
				&Choose::choose_square_pixel_size_on_signal_clicked), i));
		}
		
		box_choose_square_pixel_size.set_border_width(10);
		for (int i = 0; i < 7; ++i) {
			box_choose_square_pixel_size.pack_start(choose_square_pixel_size[i]);
		}
		choose_square_pixel_size[0].set_active();
	}
	
public:
	Choose() :
		box(Gtk::ORIENTATION_HORIZONTAL),
		box_choose_number_of_players(Gtk::ORIENTATION_VERTICAL),
		box_choose_field_size_for_figure(Gtk::ORIENTATION_VERTICAL),
		box_choose_number_of_walls(Gtk::ORIENTATION_VERTICAL),
		box_choose_square_pixel_size(Gtk::ORIENTATION_VERTICAL) {
		
		construct_radio_buttons_choose_number_of_players();
		construct_radio_buttons_choose_field_size_for_figure();
		construct_radio_buttons_choose_number_of_walls();
		construct_radio_buttons_choose_square_pixel_size();
		
		set_title("Выбор параметров игры");
		set_border_width(0);
		add(box);
		
		box.pack_start(box_choose_number_of_players);
		box.pack_start(box_choose_field_size_for_figure);
		box.pack_start(box_choose_number_of_walls);
		box.pack_start(box_choose_square_pixel_size);
		
		show_all_children();
	}
	
	virtual ~Choose() {}
	
};

class Show : public Gtk::Window {

protected:
	Gtk::Box box;
	Step game;

public:
	Show() : box(Gtk::ORIENTATION_HORIZONTAL), game(NumberOfPlayers, FieldSizesForFigure, NumberOfWalls, SquarePixelSizes) {
		set_title("Настольная игра \"Коридор\"");
		set_border_width(0);
		add(box);
		box.pack_start(game.graphic_all_image->m_Box_Top);
		show_all_children();
	}

	virtual ~Show() {}

};

int main(int argc, char *argv[]) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	Choose choose;
	app->run(choose);
	Glib::RefPtr<Gtk::Application> app2 = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	Show show;
	return app2->run(show);
}
