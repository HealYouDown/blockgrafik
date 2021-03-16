#include "Grid.h"
#include <iostream>
#include <vector>

Grid::Grid(int min_x_, int max_x_, int min_y_, int max_y_)
{
	// Some small checks:
	// min x/y have to be <= 0 for the program to work.
	if (min_x > 0 || min_y > 0) {
		throw std::invalid_argument("Invalid grid size. Min x/y have to be <= 0.");
	}

	min_x = min_x_;
	max_x = max_x_;
	min_y = min_y_;
	max_y = max_y_;
}

void Grid::draw_grid_lines()
{
	// Draws the grid lines.

	const int x_axis_length = max_x - min_x;
	const int y_axis_length = max_y - min_y;
	const int offset_y_axis_on_x = abs(min_x);
	const int offset_x_axis_on_y = max_y;

	// Draw x-axis
	for (int i = 0; i <= x_axis_length; ++i) {
		draw_character(i, offset_x_axis_on_y, horizontal_line_character);
	}

	// Draw y-axis
	for (int i = 0; i <= y_axis_length; ++i) {
		draw_character(offset_y_axis_on_x, i, vertical_line_character);
	}

	reset_position();
}

void Grid::draw_point(const Point& point)
{
	// Draws a point to the grid.

	if (!point_in_range(point)) {
		throw std::invalid_argument(point.to_string() + " is not inside the grid boundaries.");
	}

	// A point cannot be drawn with a negative x/y-value.
	// Therefore, we calculate some offsets to draw them.
	int x_offset = abs(min_x - point.x);
	int y_offset = max_y - point.y;

	draw_character(x_offset, y_offset, point_character);
}

void Grid::draw_points(const std::vector<Point>& points)
{
	// Draws multiple points, using the draw_point function.
	for (const Point& point : points) {
		draw_point(point);
	}
}

void Grid::draw_line(const Point& from, const Point& to)
{
	// Draws a line from point to point.
	std::vector<Point> points;

	if (from.x == to.x) {
		// Vertical line
		for (int i = from.y; i <= to.y; ++i) {
			Point p(from.x, i);
			points.push_back(p);
		}
	}
	// If the points have different x values, use the formular ax + b.
	else {
		// Formular: a * x + b
		// a can be calculated by dividng the differences of height and width
		float diff_y = from.y - to.y;
		float diff_x = from.x - to.x;
		float a = diff_y / diff_x;
		// b can be calculated from any point (e.g. a = 2, point is (-5|4))
		// y = ax + b ==> -b = ax - y ==> b = -ax + y
		int b = ((a * -1) * from.x) + from.y;

		// Now we calculate all points for the line.
		// The values are rounded, as we cannot draw floating point numbers.
		for (int i = from.x; i <= to.x; ++i) {
			Point p(i, a * i + b);
			points.push_back(p);
		}
	}

	draw_points(points);
}

void Grid::draw_rectangle(const Point& top_left, int width, int height)
{
	Point top_right(top_left.x + width, top_left.y);
	Point bottom_left(top_left.x, top_left.y + height);
	Point bottom_right(top_left.x + width, top_left.y + height);

	draw_line(top_left, top_right);
	draw_line(bottom_left, bottom_right);
	draw_line(top_left, bottom_left);
	draw_line(top_right, bottom_right);
}

void Grid::draw_circle(const Point& center, int radius)
{
	std::vector<Point> points;
	int step = 10;

	for (int angle = 0; angle < 360; angle += step) {
		// X = Center X + (radius * cos(angle))
		// Y = Center Y + (radius * sin(angle))
		Point p(center.x + (radius * cos(angle)), center.y + (radius * sin(angle)));
		points.push_back(p);
	}

	draw_points(points);
}

void Grid::gotoxy(int x, int y)
{
	// Uses the windows api to go to a specific point in the
	// windows terminal.
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool Grid::point_in_range(const Point& point)
{
	// Check, if a given point is in the range of the grid.
	return point.x >= min_x && point.x <= max_x && point.y >= min_y && point.y <= max_y;
}

void Grid::draw_character(int x, int y, char& character)
{
	// Draws the given character at the given point.
	gotoxy(x, y);
	std::cout << character;
	reset_position();
}

void Grid::reset_position()
{
	// Resets the position to the bottom of the grid to allow for
	// further std::couts, so that they do not overlap with the grid.
	int bottom = max_y - min_y;
	gotoxy(0, bottom + 1);
}

Point::Point(int x, int y) : x(x), y(y) {}

std::string Point::to_string() const
{
	return "Point(x=" + std::to_string(x) + ", y=" + std::to_string(y) + ")";
}
