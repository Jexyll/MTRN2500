
#ifndef MTRN3500_VEHICLE_H
#define MTRN3500_VEHICLE_H

#include <iostream>
#include "Shape.hpp"
#include "VectorMaths.hpp"
#include <vector>

class Vehicle : public Shape {
	friend void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_);
public:

	Vehicle();
	virtual ~Vehicle();

	virtual void update(double dt);
	virtual void update(double speed_, double steering_, double dt);

	virtual void draw() = 0;

	static const int MAX_FORWARD_SPEED_MPS = 10;
	static const int MAX_BACKWARD_SPEED_MPS = -4;
	static const int MAX_LEFT_STEERING_DEGS = 15;
	static const int MAX_RIGHT_STEERING_DEGS = -15;
	static const int VEHICLE_BOUNDS = 3;

	double getSpeed() const { return speed; }
	double getSteering() const { return steering; }

	void addShape(Shape * shape);
protected:
	double speed;     // m/s
	double steering;  // degrees

	std::vector<Shape *> shapes;
};

double clamp(double a, double n, double b);

class custVehicle : public Vehicle {
public:
	custVehicle(double test_){}
	void newtriangularprism(double x_, double y_, double z_, double base_, double height_, double offset_, double length_, double rotation_, double red_, double green_, double blue_);
	void newrectangularprism(double x_,double y_, double z_, double xlength_, double ylength_, double zlength_, double rotation_, double red_, double green_, double blue_);
	void newtrapezoid(double x_, double y_, double z_, double base_, double height_, double offset_, double length_, double topwidth_, double rotation_, double red_, double green_, double blue_);
	void newcylinder(double x_, double y_, double z_, double baseRadius_, double topRadius_, double height_, int slices_, int stacks_, int loops_, double rotation_, double red_, double green_, double blue_);
	void draw();
protected:
	std::vector<trapezoid> trapezoids;
	std::vector<rectangularprism> rectangularprisms;
	std::vector<triangularprism> triangularprisms;
	std::vector<cylinder> cylinders;
	int trapezoidcount = 0;
	int rectanglecount = 0;
	int trianglecount = 0;
	int cylindercount = 0;
};
#endif // for MTRN3500_VEHICLE_H

