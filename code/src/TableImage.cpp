#include <TableImage.h>

void TableImage::construct_images() {
	assert(
		size_of_figure_button >= 50 &&
		size_of_figure_button <= 100 &&
		size_of_figure_button % 10 == 0
	);
	m_Vector_Image_Figure.clear();
	m_Vector_Image_Figure.reserve(5);
	for (int i = 0; i < 5; ++i) {
		std::stringstream ss;
		ss << "../code/image/Figure";
		char c = '0' + i;
		ss << c;
		ss << ',';
		ss << size_of_figure_button-20;
		ss << ".png";
		std::string s = ss.str();
		
		Gtk::Image tmp_image(s);
		m_Vector_Image_Figure.push_back(std::move(tmp_image));
	}

	m_Vector_Pair_Signals.clear();
	m_Vector_Pair_Signals.reserve(5);
	for (int i = 0; i < 5; ++i) {
		pair p(-1, -1);
		m_Vector_Pair_Signals.push_back(p);
	}
	
	m_Vector_Image_Figure_CssProvider.clear();
	m_Vector_Image_Figure_CssProvider.reserve(5);
	{
		Glib::RefPtr<Gtk::CssProvider> c0 = Gtk::CssProvider::create();
		c0->load_from_data(
			"button {background-image: image(white);}\
			button:hover {background-image: image(white);}\
			button:active {background-image: image(grey);}");
			
		Glib::RefPtr<Gtk::CssProvider> c1 = Gtk::CssProvider::create();
		c1->load_from_data(
			"button {background-image: image(purple);}\
			button:hover {background-image: image(purple);}\
			button:active {background-image: image(grey);}");
			
		Glib::RefPtr<Gtk::CssProvider> c2 = Gtk::CssProvider::create();
		c2->load_from_data(
			"button {background-image: image(green);}\
			button:hover {background-image: image(green);}\
			button:active {background-image: image(grey);}");
			
		Glib::RefPtr<Gtk::CssProvider> c3 = Gtk::CssProvider::create();
		c3->load_from_data(
			"button {background-image: image(orange);}\
			button:hover {background-image: image(orange);}\
			button:active {background-image: image(grey);}");
			
		Glib::RefPtr<Gtk::CssProvider> c4 = Gtk::CssProvider::create();
		c4->load_from_data(
			"button {background-image: image(blue);}\
			button:hover {background-image: image(blue);}\
			button:active {background-image: image(grey);}");
			
		m_Vector_Image_Figure_CssProvider.push_back(std::move(c0));
		m_Vector_Image_Figure_CssProvider.push_back(std::move(c1));
		m_Vector_Image_Figure_CssProvider.push_back(std::move(c2));
		m_Vector_Image_Figure_CssProvider.push_back(std::move(c3));
		m_Vector_Image_Figure_CssProvider.push_back(std::move(c4));
	}
}

void TableImage::construct_css_providers() {
	m_CssProvider_Wall_White = Gtk::CssProvider::create();
	m_CssProvider_Wall_Black = Gtk::CssProvider::create();
	m_CssProvider_Wall_White->load_from_data(
		"button {background-image: image(white);}\
		button:hover {background-image: image(white);}\
		button:active {background-image: image(grey);}");
	m_CssProvider_Wall_Black->load_from_data(
		"button {background-image: image(black);}\
		button:hover {background-image: image(black);}\
		button:active {background-image: image(grey);}");
}

Gtk::Button& TableImage::vector_button_row_at(size_t row, size_t column) {
	return m_Vector_Button_Row[row*field_sizes + column];
}

void TableImage::construct_buttons() {
	m_Vector_Button_Row.clear();
	m_Vector_Button_Row.reserve(field_sizes*field_sizes);
	for (int i = 0; i < field_sizes*field_sizes; ++i) {
		Gtk::Button but;
		m_Vector_Button_Row.push_back(std::move(but));
	}

	int vert, horiz;
	//tmp var for install size of button
	for (int i = 0; i < field_sizes; ++i) {
		for (int j = 0; j < field_sizes; ++j) {
			vert = (i % 2 == 0) ? size_of_figure_button : size_of_figure_button/4;
			horiz = (j % 2 == 0) ? size_of_figure_button : size_of_figure_button/4;
			vector_button_row_at(i, j).set_size_request(horiz, vert);
			
			//connect with signals
			pair p(i, j);
			vector_button_row_at(i, j).signal_clicked().connect(sigc::bind<pair>(sigc::mem_fun(*this,
	      				&TableImage::field_square_on_signal_clicked), p));
		}
	}

	//install css_provider for non-figure squares
	for (int i = 0; i < field_sizes; ++i) {
		for (int j = 0; j < field_sizes; ++j) {
			vector_button_row_at(i, j).get_style_context()->add_provider(
				m_CssProvider_Wall_White,
				GTK_STYLE_PROVIDER_PRIORITY_USER);
		}
	}

	m_Vector_Box_Row.clear();
	m_Vector_Box_Row.reserve(field_sizes);

	for (int i = 0; i < field_sizes; ++i) {
		Gtk::Box b(Gtk::ORIENTATION_HORIZONTAL);
		m_Vector_Box_Row.push_back(std::move(b));
		for (int j = 0; j < field_sizes; ++j) {
			m_Vector_Box_Row[i].pack_start(vector_button_row_at(i, j), Gtk::PACK_SHRINK);
		}
	}
}

void TableImage::spawn_figures(int number_of_players) {
	assert(number_of_players == 2 || number_of_players == 4);
	int position = field_sizes / 2;

	vector_button_row_at(0, position).set_image(m_Vector_Image_Figure[1]);
	pair p1(0, position);
	m_Vector_Pair_Signals[1] = p1;
	
	vector_button_row_at(0, position).get_style_context()->add_provider(
		m_Vector_Image_Figure_CssProvider[1],
		GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	vector_button_row_at(field_sizes-1, position).set_image(m_Vector_Image_Figure[2]);
	pair p2(field_sizes-1, position);
	m_Vector_Pair_Signals[2] = p2;
	
	vector_button_row_at(field_sizes-1, position).get_style_context()->add_provider(
		m_Vector_Image_Figure_CssProvider[2],
		GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	if (number_of_players == 4) {
		vector_button_row_at(position, 0).set_image(m_Vector_Image_Figure[3]);
		pair p3(position, 0);
		m_Vector_Pair_Signals[3] = p3;
		
		vector_button_row_at(position, 0).get_style_context()->add_provider(
			m_Vector_Image_Figure_CssProvider[3],
			GTK_STYLE_PROVIDER_PRIORITY_USER);

		vector_button_row_at(position, field_sizes-1).set_image(m_Vector_Image_Figure[4]);
		pair p4(position, field_sizes-1);
		m_Vector_Pair_Signals[4] = p4;
		
		vector_button_row_at(position, field_sizes-1).get_style_context()->add_provider(
			m_Vector_Image_Figure_CssProvider[4],
			GTK_STYLE_PROVIDER_PRIORITY_USER);
	}
}

void TableImage::add_processing_signals(std::shared_ptr<ProcessingSignals> class_processing_signals_tmp) {
	class_processing_signals = class_processing_signals_tmp;
}

void TableImage::field_square_on_signal_clicked(pair p) {
	std::shared_ptr<ProcessingSignals> ptr(class_processing_signals);
	ptr->get_new_command(p);
}

TableImage::TableImage(
		int number_of_players_tmp,
		int field_figure_sizes_tmp,
		int size_of_figure_button_tmp) :
		m_Box_Main(Gtk::ORIENTATION_VERTICAL) {
	assert(number_of_players_tmp == 2 || number_of_players_tmp == 4);
	assert(field_figure_sizes_tmp >= 3 && field_figure_sizes_tmp % 2 == 1);
	assert(size_of_figure_button_tmp >= 50 && size_of_figure_button_tmp <= 100 && size_of_figure_button_tmp % 10 == 0);

	field_sizes = field_figure_sizes_tmp*2 - 1;
	field_figure_sizes = field_figure_sizes_tmp;
	field_wall_sizes = field_sizes - field_figure_sizes;

	size_of_figure_button = size_of_figure_button_tmp;

	construct_images();
	construct_css_providers();
	construct_buttons();
	spawn_figures(number_of_players_tmp);

	for (int i = 0; i < field_sizes; ++i) {
		m_Box_Main.pack_start(m_Vector_Box_Row[i], Gtk::PACK_SHRINK);
	}
};

void TableImage::change_figure_position(int number_of_figure, pair new_position) {
	++number_of_figure;
	assert(number_of_figure >= 1 && number_of_figure <= 4);
	assert(new_position.first >= 0 && new_position.first < field_sizes);
	assert(new_position.second >= 0 && new_position.second < field_sizes);
	for (int i = 0; i < 5; ++i) {
		assert(m_Vector_Pair_Signals[i] != new_position);
	}

	vector_button_row_at(new_position.first, new_position.second).set_image(m_Vector_Image_Figure[number_of_figure]);
	
	vector_button_row_at(m_Vector_Pair_Signals[number_of_figure].first, m_Vector_Pair_Signals[number_of_figure].second).get_style_context()->add_provider(
			m_CssProvider_Wall_White,
			GTK_STYLE_PROVIDER_PRIORITY_USER);
			
	vector_button_row_at(new_position.first, new_position.second).get_style_context()->add_provider(
			m_Vector_Image_Figure_CssProvider[number_of_figure],
			GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	m_Vector_Pair_Signals[number_of_figure] = new_position;
}

void TableImage::install_wall(pair new_square_wall) {
	assert(new_square_wall.first >= 0 && new_square_wall.first <= field_sizes);
        assert(new_square_wall.second >= 0 && new_square_wall.second <= field_sizes);

	vector_button_row_at(new_square_wall.first, new_square_wall.second).get_style_context()->add_provider(
		m_CssProvider_Wall_Black,
		GTK_STYLE_PROVIDER_PRIORITY_USER);
}
