
#include "Vehicle.hpp"


Vehicle::Vehicle() {
	speed = steering = 0;
};

Vehicle::~Vehicle()
{
	// clean-up added shapes
	for (int i = 0; i < shapes.size(); i++) {
		delete shapes[i];
	}
}

void Vehicle::update(double dt)
{
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * 3.1415926535 / 180.0);
	z += speed * dt * sin(rotation * 3.1415926535 / 180.0);

	// update heading
	rotation += dt * steering * speed;

	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;


	if (fabs(speed) < .1)
		speed = 0;
	if (fabs(steering) < .1)
		steering = 0;

}

void Vehicle::update(double speed_, double steering_, double dt)
{
	speed = speed + ((speed_)-speed)*dt * 4;
	steering = steering + (steering_ - steering)*dt * 6;

	update(dt);
}

void Vehicle::addShape(Shape * shape)
{
	shapes.push_back(shape);
}

double clamp(double a, double n, double b) {

	if (a < b) {
		if (n < a) n = a;
		if (n > b) n = b;
	}
	else {
		if (n < b) n = b;
		if (n > a) n = a;
	}

	return n;

};

void custVehicle::newrectangularprism(double x_, double y_, double z_, double xlength_, double ylength_, double zlength_,double rotation_, double red_, double green_, double blue_) {
	rectangularprism vehiclerectangle(xlength_, ylength_, zlength_);
	vehiclerectangle.relx = x_;
	vehiclerectangle.rely = y_;
	vehiclerectangle.relz = z_;
	vehiclerectangle.relr = rotation_;
	vehiclerectangle.setColor(red_, green_, blue_);
	double tx = x + cos(3.141592765*rotation / 180)*x_-sin(3.141592765*rotation / 180)*z_;
	double ty = y + y_;
	double tz = z + cos(3.141592765*rotation / 180)*z_+sin(3.141592765*rotation / 180)*x_;
	vehiclerectangle.setPosition(tx, ty, tz);
	vehiclerectangle.setRotation(rotation+rotation_);
	rectangularprisms.push_back(vehiclerectangle);
	++rectanglecount;
}

void custVehicle::newtriangularprism(double x_, double y_, double z_, double base_, double height_, double offset_, double length_,double rotation_, double red_, double green_, double blue_) {
	triangularprism vehicletriangle(base_, height_, offset_, length_);
	vehicletriangle.relx = x_;
	vehicletriangle.rely = y_;
	vehicletriangle.relz = z_;
	vehicletriangle.relr = rotation_;
	vehicletriangle.setColor(red_, green_, blue_);
	double tx = x + cos(3.141592765*rotation / 180)*x_ - sin(3.141592765*rotation / 180)*z_;
	double ty = y + y_;
	double tz = z + cos(3.141592765*rotation / 180)*z_ + sin(3.141592765*rotation / 180)*x_;
	vehicletriangle.setPosition(tx, ty, tz);
	vehicletriangle.setRotation(rotation+rotation_);
	triangularprisms.push_back(vehicletriangle);
	++trianglecount;
}

void custVehicle::newtrapezoid(double x_, double y_, double z_, double base_, double height_, double offset_, double length_, double topwidth_,double rotation_, double red_, double green_, double blue_) {
	trapezoid vehicletrapezoid(base_, height_, offset_, length_, topwidth_);
	vehicletrapezoid.relx = x_;
	vehicletrapezoid.rely = y_;
	vehicletrapezoid.relz = z_;
	vehicletrapezoid.relr = rotation_;
	vehicletrapezoid.setColor(red_, green_, blue_);
	double tx = x + cos(3.141592765*rotation / 180)*x_ - sin(3.141592765*rotation / 180)*z_;
	double ty = y + y_;
	double tz = z + cos(3.141592765*rotation / 180)*z_ + sin(3.141592765*rotation / 180)*x_;
	vehicletrapezoid.setPosition(tx, ty, tz);
	vehicletrapezoid.setRotation(rotation+rotation_);
	trapezoids.push_back(vehicletrapezoid);
	++trapezoidcount;
}
void custVehicle::newcylinder(double x_, double y_, double z_, double baseRadius_, double topRadius_, double height_, int slices_, int stacks_, int loops_, double rotation_, double red_, double green_, double blue_) {
	cylinder vehiclecylinder(baseRadius_,topRadius_,height_,slices_, stacks_,loops_);
	vehiclecylinder.relx = x_;
	vehiclecylinder.rely = y_;
	vehiclecylinder.relz = z_;
	vehiclecylinder.relr = rotation_;
	vehiclecylinder.setColor(red_, green_, blue_);
	double tx = x + cos(3.141592765*rotation / 180)*x_ - sin(3.141592765*rotation / 180)*z_;
	double ty = y + y_;
	double tz = z + cos(3.141592765*rotation / 180)*z_ + sin(3.141592765*rotation / 180)*x_;
	vehiclecylinder.setPosition(tx, ty, tz);
	vehiclecylinder.setRotation(rotation + rotation_);
	cylinders.push_back(vehiclecylinder);
	++cylindercount;
}
//void custVehicle::newcylinder(double x_, double y_, double z_, double) {

//}

void custVehicle::draw() {

	int i = 0;
	while (i < rectanglecount) {
		rectangularprisms[i].setColorInGL();
		rectangularprisms[i].setRotation(rectangularprisms[i].relr + rotation);
		rectangularprisms[i].draw();
		++i;
	}
	i = 0;
	while (i < trianglecount) {
		triangularprisms[i].setColorInGL();
		triangularprisms[i].setRotation(triangularprisms[i].relr + rotation);
		triangularprisms[i].draw();
		++i;
	}
	i = 0;
	while (i < trapezoidcount) {
		trapezoids[i].setColorInGL();
		trapezoids[i].setRotation(trapezoids[i].relr + rotation);
		trapezoids[i].draw();
		++i;
	}
	i = 0;
	while (i < cylindercount) {
		cylinders[i].setColorInGL();
		cylinders[i].setRotation(cylinders[i].relr + rotation);
		cylinders[i].draw();
		++i;
	}
}
