#include "Grid.h"
#include <vector>

int main()
{
    // Calculate points
    std::vector<Point> points;
    for (int x = -5; x <= 5; ++x) {
        Point point(x, x * x);
        points.push_back(point);
    }

    // Create Grid
    Grid grid(-15, 15, -5, 25);
    grid.draw_grid_lines();

    // Draw Points (default character is *)
    grid.draw_points(points);

    // Draw a single point to (0|-3) with the character ^
    grid.point_character = '^';
    Point p1(0, -3);
    grid.draw_point(p1);

    // Draw a line
    grid.point_character = '+';
    Point p2(-5, 2);
    Point p3(7, 14);
    grid.draw_line(p2, p3);

    // Draw a rectangle
    grid.point_character = ',';
    Point p4(4, 4);
    grid.draw_rectangle(p4, 4, 2);

    // Draw a circle
    grid.point_character = '.';
    Point p5(-7, 15);
    grid.draw_circle(p5, 5);
}
