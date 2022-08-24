#include <AllImage.h>

void AllImage::construct_radio_buttons() {
	m_Vector_Radio_Button.clear();
	m_Vector_Radio_Button.reserve(4);

	Gtk::RadioButton rb1("Ходить фигурой");
	Gtk::RadioButton rb2("Установить стенку");
	Gtk::RadioButton rb3("Обойти фигуру противника");
	Gtk::RadioButton rb4("Обойти фигуру противника с препятствием");

	m_Vector_Radio_Button.push_back(std::move(rb1));
	m_Vector_Radio_Button.push_back(std::move(rb2));
	m_Vector_Radio_Button.push_back(std::move(rb3));
	m_Vector_Radio_Button.push_back(std::move(rb4));

	Gtk::RadioButton::Group group = m_Vector_Radio_Button[0].get_group();
	m_Vector_Radio_Button[1].set_group(group);
	m_Vector_Radio_Button[2].set_group(group);
	m_Vector_Radio_Button[3].set_group(group);

	for (int i = 0; i < 4; ++i) {
		m_Vector_Radio_Button[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
			&AllImage::radio_button_on_signal_clicked), i));
	}
	
	m_Box_Left1_Steps.set_border_width(10);
	for (int i = 0; i < 4; ++i) {
		m_Box_Left1_Steps.pack_start(m_Vector_Radio_Button[i]);
	}
	m_Vector_Radio_Button[0].set_active();
}

void AllImage::construct_frame_label(int number_of_players, int number_of_walls) {
	m_Vector_Frame.clear();
	m_Vector_Frame.reserve(number_of_players);
	m_Vector_Label.clear();
	m_Vector_Label.reserve(number_of_players);

	Gtk::Frame f1("ФИОЛЕТОВЫЙ");
	Gtk::Frame f2("ЗЕЛЁНЫЙ");
	Gtk::Label l1(std::string("Ходит\nОсталось стенок: ") + std::to_string(number_of_walls));
	Gtk::Label l2(std::string("Ожидает\nОсталось стенок: ") + std::to_string(number_of_walls));

	m_Vector_Frame.push_back(std::move(f1));
	m_Vector_Frame.push_back(std::move(f2));
	m_Vector_Label.push_back(std::move(l1));
	m_Vector_Label.push_back(std::move(l2));

	if (number_of_players == 4) {
		Gtk::Frame f3("ОРАНЖЕВЫЙ");
		Gtk::Frame f4("СИНИЙ");
		Gtk::Label l3(std::string("Ожидает\nОсталось стенок: ") + std::to_string(number_of_walls));
		Gtk::Label l4(std::string("Ожидает\nОсталось стенок: ") + std::to_string(number_of_walls));

		m_Vector_Frame.push_back(std::move(f3));
		m_Vector_Frame.push_back(std::move(f4));
		m_Vector_Label.push_back(std::move(l3));
		m_Vector_Label.push_back(std::move(l4));
	}

	for (int i = 0; i < number_of_players; ++i) {
		m_Vector_Label[i].set_justify(Gtk::JUSTIFY_LEFT);
		m_Vector_Frame[i].add(m_Vector_Label[i]);
	}
	
	m_Box_Left2_Players.set_border_width(10);
	for (int i = 0; i < number_of_players; ++i) {
		m_Box_Left2_Players.pack_start(m_Vector_Frame[i]);
	}
}

AllImage::AllImage(int number_of_players, int field_figure_sizes, int size_of_figure_button, int number_of_walls) :
	m_Box_Top(Gtk::ORIENTATION_HORIZONTAL),
	m_Box_Left(Gtk::ORIENTATION_VERTICAL),
	m_Box_Right_Table(Gtk::ORIENTATION_VERTICAL),
	m_Box_Left1_Steps(Gtk::ORIENTATION_VERTICAL),
	m_Box_Left2_Players(Gtk::ORIENTATION_VERTICAL)
{
	construct_radio_buttons();
	//made m_Box_Left1_Steps
	construct_frame_label(number_of_players, number_of_walls);
	//made m_Box_Left2_Players
	table_image = std::make_shared<TableImage>(number_of_players, field_figure_sizes, size_of_figure_button);
	m_Box_Right_Table.set_border_width(10);
	m_Box_Right_Table.pack_start(table_image->m_Box_Main, Gtk::PACK_SHRINK);
	//made m_Box_Right_Table
	
	m_Box_Top.pack_start(m_Box_Left);
	m_Box_Top.pack_start(m_Box_Right_Table);
	m_Box_Left.pack_start(m_Box_Left1_Steps);
	m_Box_Left.pack_start(m_Box_Left2_Players);
}

void AllImage::radio_button_on_signal_clicked(int i) {
	if (m_Vector_Radio_Button[i].get_active()) {
		std::shared_ptr<ProcessingSignals> ptr(table_image->class_processing_signals);
		ptr->get_new_type_of_step(i);
	}
}

void AllImage::change_condition_of_player(int number_of_player, bool is_go_now, int new_number_of_walls, bool is_step_correct) {
	std::string new_condition;
	if (is_go_now) {
		new_condition = "Ходит";
	} else {
		new_condition = "Ожидает";
	}
	new_condition += "\nОсталось стенок: ";
	new_condition += std::to_string(new_number_of_walls);
	if (!is_step_correct) {
		new_condition += "\nХод не корректен\nСделайте ход повторно";
	}
	m_Vector_Label[number_of_player].set_text(new_condition);
}
