#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <cmath>

struct Point {
	int x, y;

	Point(int x, int y);
	std::string to_string() const;
};


class Grid
{
public:
	char vertical_line_character = '|';
	char horizontal_line_character = '-';
	char point_character = '*';
	int min_x, max_x, min_y, max_y;

	Grid(int min_x, int max_x, int min_y, int max_y);
	void draw_grid_lines();
	void draw_point(const Point& point);
	void draw_points(const std::vector<Point>& points);
	void draw_line(const Point& from, const Point& to);
	void draw_rectangle(const Point& top_left_corner, int width, int height);
	void draw_circle(const Point& center, int radius);

private:
	void gotoxy(int x, int y);
	bool point_in_range(const Point& point);
	void draw_character(int x, int y, char& character);
	void reset_position();
};

