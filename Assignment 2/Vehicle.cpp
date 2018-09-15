
#include "Vehicle.hpp"


#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif




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
custVehicle::custVehicle() {

	setPosition(0, 0, 0);
	setRotation(0);
	rectangularprism *Vrectangle1 = new rectangularprism(2, 0.75, 3);
	Vrectangle1->setPosition(1.5, 0.25, -1);
	Vrectangle1->setColor(1, 0, 0);
	Vrectangle1->setRotation(90);
	addShape(Vrectangle1);
	trapezoid *Vtrap1 = new trapezoid(2.5, 0.6, 0.75, 2, 1.25);
	Vtrap1->setPosition(1.75, 1, -1);
	Vtrap1->setRotation(0);
	Vtrap1->setColor(0, 0, 1);
	addShape(Vtrap1);
	triangularprism *Vtriangle1 = new triangularprism(0.5, 0.4, 90, -2);
	Vtriangle1->setRotation(0);
	Vtriangle1->setPosition(0.25, 1, -1);
	Vtriangle1->setColor(0, 1, 0);
	addShape(Vtriangle1);
	cylinder *Vcylinder1 = new cylinder(0.75, 0.4, 8, 1, 1, 0);
	Vcylinder1->setPosition(0.7, 0.75, 0.2);
	Vcylinder1->setRotation(0);
	Vcylinder1->setColor(1, 1, 1);
	addShape(Vcylinder1);
	cylinder *Vcylinder2 = new cylinder(0.75, 0.4, 8, 1, 1, 0);
	Vcylinder2->setPosition(0.7, 0.75, -2.2);
	Vcylinder2->setRotation(0);
	Vcylinder2->setColor(1, 1, 1);
	addShape(Vcylinder2);
	cylinder *Vcylinder3 = new cylinder(0.25, 0.4, 8, 1, 1, 1);
	Vcylinder3->setPosition(2.5, 0.25, 0.2);
	Vcylinder3->setRotation(0);
	Vcylinder3->setColor(1, 1, 1);
	addShape(Vcylinder3);
	cylinder *Vcylinder4 = new cylinder(0.25, 0.4, 8, 1, 1, 1);
	Vcylinder4->setPosition(2.5, 0.25, -2.2);
	Vcylinder4->setRotation(0);
	Vcylinder4->setColor(1, 1, 1);
	addShape(Vcylinder4);

}

void custVehicle::draw() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(-rotation, 0, 1, 0);

	for (std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
		if ((*it)->getType() == 3) {
			(*it)->spinup(speed);
		}
		if ((*it)->getType() == 4) {
			(*it)->spinup(speed);
			(*it)->turnit(-steering);
		}
		(*it)->setColorInGL();
		(*it)->draw();
	}

	glPopMatrix();
}
