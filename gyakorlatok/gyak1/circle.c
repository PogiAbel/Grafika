#include <math.h>
#include <stdio.h>

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Circle
{
	double x;
	double y;
	double radius;
} Circle;

/**
 * Set the data of the circle
 */
void set_circle_data(Circle* circle, double x, double y, double radius);

/**
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle* circle);


void set_circle_data(Circle* circle, double x, double y, double radius)
{
	circle->x = x;
	circle->y = y;
	if (radius > 0.0) {
		circle->radius = radius;
	} else {
		circle->radius = NAN;
	}
}

double calc_circle_area(const Circle* circle)
{
	double area = circle->radius * circle->radius * M_PI;
	return area;
}

int main(int argc, char const *argv[])
{
    struct Circle circle;
    set_circle_data(&circle, 0.0, 0.0, 1.0);
    double area = calc_circle_area(&circle);
    printf("Area of the circle: %f", area);
    return 0;
}
