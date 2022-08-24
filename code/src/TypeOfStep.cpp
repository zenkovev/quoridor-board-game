#include <TypeOfStep.h>

bool Pair_is_correct_square(Pair p, int field_sizes) {
	return (0 <= p.first && p.first < field_sizes &&
			0 <= p.second && p.second < field_sizes);
}

bool Pair_is_figure_square(Pair p) {
	return (p.first % 2 == 0 && p.second % 2 == 0);
}

bool Pair_is_crossroad_square(Pair p) {
	return (p.first % 2 == 1 && p.second % 2 == 1);
}

bool Pair_is_wall_square(Pair p) {
	return (!Pair_is_figure_square(p) && !Pair_is_crossroad_square(p));
}
