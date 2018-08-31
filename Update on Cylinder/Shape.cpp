
#include "Shape.hpp"
#include <cmath>

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


Shape::Shape() {
	x = y = z = 0.0;
	rotation = 0.0;
	red = green = blue = 1.0;
};

Shape::Shape(double x_, double y_, double z_) {
	x = x_;
	y = y_;
	z = z_;

	rotation = 0.0;
	red = green = blue = 1.0;
};

Shape::Shape(double x_, double y_, double z_, double rotation_) {

	x = x_;
	y = y_;
	z = z_;

	rotation = rotation_;
	red = green = blue = 1.0;
};

Shape::~Shape() {
}

double Shape::getX() {
	return x;
};

double Shape::getY() {
	return y;
};

double Shape::getZ() {
	return z;
};

double Shape::getRotation() {
	return rotation;
};

void Shape::setX(double x_) {
	x = x_;
};

void Shape::setY(double y_) {
	y = y_;
};

void Shape::setZ(double z_) {
	z = z_;
};

void Shape::setRotation(double rotation_) {
	rotation = rotation_;
};


void Shape::setPosition(double x_, double y_, double z_) {
	x = x_;
	y = y_;
	z = z_;
};

void Shape::positionInGL() {
	glTranslated(x, y, z);
	glRotated(-rotation, 0, 1, 0);
};

void Shape::setColorInGL() {
	glColor3f(red, green, blue);
};

double Shape::getRed() {
	return red;
};

double Shape::getGreen() {
	return green;
};

double Shape::getBlue() {
	return blue;
};

void Shape::setColor(float red_, float green_, float blue_) {
	red = red_;
	green = green_;
	blue = blue_;
};

//Draw command for a rectangular prism, rotation is about the initial point
void rectangularprism::draw() {
	//convert degrees to radians and find cosine and sine
	double rc = cos(3.141592765*rotation / 180);
	double rs = sin(3.141592765*rotation / 180);
	//define all vertexes
	double x1 = x;
	double x2 = x1 + xlength * rc;
	double x3 = x1 - zlength * rs;
	double x4 = (x2 + x3) - x1;
	double y1 = y;
	double y2 = y1 + ylength;
	double z1 = z;
	double z2 = z1 + xlength * rs;
	double z3 = z1 + zlength * rc;
	double z4 = z2 + z3 - z1;
	glBegin(GL_QUAD_STRIP);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y1, z2);
	glVertex3d(x3, y1, z3);
	glVertex3d(x4, y1, z4);
	glVertex3d(x3, y2, z3);
	glVertex3d(x4, y2, z4);
	glVertex3d(x1, y2, z1);
	glVertex3d(x2, y2, z2);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3d(x1, y1, z1);
	glVertex3d(x3, y1, z3);
	glVertex3d(x3, y2, z3);
	glVertex3d(x1, y2, z1);
	glVertex3d(x2, y1, z2);
	glVertex3d(x4, y1, z4);
	glVertex3d(x4, y2, z4);
	glVertex3d(x2, y2, z2);
	glEnd();
}
//dimension settings for a rectangular prism
void rectangularprism::setdimensions(double xlength_, double ylength_, double zlength_) {
	xlength = xlength_;
	ylength = ylength_;
	zlength = zlength_;
}
//dimension settings for a triangular prism
void triangularprism::setdimensions(double base_, double height_, double offset_, double length_) {
	base = base_;
	height = height_;
	length = length_;
	offset = offset_;

}
void triangularprism::draw() {
	double rc = cos(3.141592765*rotation / 180);
	double rs = sin(3.141592765*rotation / 180);
	double x1 = x;
	double y1 = y;
	double y2 = y + height;
	double x2 = x1 + base * rc;
	double x3 = x1 + offset * rc;
	double z1 = z;
	double z2 = z1 + base * rs;
	double z3 = z1 + offset * rs;
	double x4 = x1 - length * rs;
	double z4 = z1 + length * rc;
	double x5 = x2 - length * rs;
	double z5 = z2 + length * rc;
	double x6 = x3 - length * rs;
	double z6 = z3 + length * rc;
	glBegin(GL_POLYGON);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y1, z2);
	glVertex3d(x3, y2, z3);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(x4, y1, z4);
	glVertex3d(x5, y1, z5);
	glVertex3d(x6, y2, z6);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glVertex3d(x1, y1, z1);
	glVertex3d(x4, y1, z4);
	glVertex3d(x2, y1, z2);
	glVertex3d(x5, y1, z5);
	glVertex3d(x3, y2, z3);
	glVertex3d(x6, y2, z6);
	glVertex3d(x1, y1, z1);
	glVertex3d(x4, y1, z4);
	glEnd();

}

void cylinder::setdimensions(double baseRadius_, double topRadius_, double height_, double innerRadius_, double outerRadius_, int slices_, int stacks_, int loops_) {

	baseRadius = baseRadius_;
	topRadius = topRadius_;
	height = height_;
	innerRadius = innerRadius_;
	outerRadius = outerRadius_;
	slices = slices_;
	stacks = stacks_;
	loops = loops_;

}

void cylinder::draw() {
	// move the origin to the bottom of the surface
	glMatrixMode(GL_MODELVIEW);
	glTranslated(0, baseRadius, -(height)/2);
	glColor3f(1, 0, 0); // give red color to the surface
	gluCylinder(gluNewQuadric(), baseRadius, topRadius, height, slices, stacks); // draw the surface of cylinder
	glColor3f(0, 1, 0); // give green color to the circle
	gluDisk(gluNewQuadric(), innerRadius, outerRadius, slices, loops); // draw the circle

}
