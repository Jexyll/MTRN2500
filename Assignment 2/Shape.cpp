
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
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(-rotation, 0, 1, 0);
	//define all vertexes

	glBegin(GL_QUAD_STRIP);
	glVertex3d(0, 0, 0);
	glVertex3d(xlength, 0, 0);
	glVertex3d(0, ylength, 0);
	glVertex3d(xlength, ylength, 0);
	glVertex3d(0, ylength, zlength);
	glVertex3d(xlength, ylength, zlength);
	glVertex3d(0, 0, zlength);
	glVertex3d(xlength, 0, zlength);
	glVertex3d(0, 0, 0);
	glVertex3d(xlength, 0, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(0, ylength, 0);
	glVertex3d(0, ylength, zlength);
	glVertex3d(0, 0, zlength);
	glVertex3d(xlength, 0, 0);
	glVertex3d(xlength, ylength, 0);
	glVertex3d(xlength, ylength, zlength);
	glVertex3d(xlength, 0, zlength);
	glEnd();
	glPopMatrix();
}
//dimension settings for a rectangular prism
void rectangularprism::setdimensions(double xlength_, double ylength_, double zlength_) {
	xlength = xlength_;
	ylength = ylength_;
	zlength = zlength_;
}
//dimension settings for a triangular prism
void triangularprism::setdimensions(double sidea_, double sideb_, double angle_, double length_) {
	sidea = sidea_;
	sideb = sideb_;
	length = length_;
	angle = angle_;

}
void triangularprism::draw() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(-rotation, 0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(sidea, 0, 0);
	glVertex3d(sideb* cos(3.141592765*angle / 180), sideb*sin(3.141592765*angle / 180), 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, length);
	glVertex3d(sidea, 0, length);
	glVertex3d(sideb* cos(3.141592765*angle / 180), sideb*sin(3.141592765*angle / 180), length);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length);
	glVertex3d(sidea, 0, 0);
	glVertex3d(sidea, 0, length);
	glVertex3d(sideb* cos(3.141592765*angle / 180), sideb*sin(3.141592765*angle / 180), 0);
	glVertex3d(sideb* cos(3.141592765*angle / 180), sideb*sin(3.141592765*angle / 180), length);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length);
	glEnd();
	glPopMatrix();
}

//dimension settings for a trapezoidal prism
void trapezoid::setdimensions(double base_, double height_, double offset_, double length_, double topwidth_) {
	base = base_;
	height = height_;
	length = length_;
	offset = offset_;
	topwidth = topwidth_;
}
//draw a trapezoidal prism
void trapezoid::draw() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(-rotation, 0, 1, 0);
	double rc = cos(3.141592765*rotation / 180);
	double rs = sin(3.141592765*rotation / 180);


	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(offset, height, 0);
	glVertex3d(offset+topwidth, height, 0);
	glVertex3d(base, 0, 0);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, length);
	glVertex3d(offset, height, length);
	glVertex3d(offset + topwidth, height, length);
	glVertex3d(base, 0, length);

	glEnd();
	glBegin(GL_QUAD_STRIP);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length);
	glVertex3d(offset, height, 0);
	glVertex3d(offset, height, length);
	glVertex3d(offset + topwidth, height, 0);
	glVertex3d(offset + topwidth, height, length);
	glVertex3d(base, 0, 0);
	glVertex3d(base, 0, length);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length);
	glEnd();
	glPopMatrix();
}

void cylinder::setdimensions(double baseRadius_, double topRadius_, double height_, int slices_, int stacks_, int loops_) {

	baseRadius = baseRadius_;
	topRadius = topRadius_;
	height = height_;
	slices = slices_;
	stacks = stacks_;
	loops = loops_;

}

cylinder::cylinder()
{
}

void cylinder::draw() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(-rotation,0,1,0); // to rotate the shape about y axis
	glTranslated(0, baseRadius, -(height) / 2);
	

	//glColor3f(1, 0, 0); // give red color to the surface
	gluCylinder(gluNewQuadric(), baseRadius, topRadius, height, slices, stacks); // draw the surface of cylinder

	//glColor3f(0, 0, 1);
	gluDisk(gluNewQuadric(), 0, baseRadius, slices, loops);

	glTranslated(0, 0, height);
	//glColor3f(0, 1, 0); // give green color to the circle
	gluDisk(gluNewQuadric(), 0, topRadius, slices, loops); // draw the circle
	glPopMatrix();
}
//grab a point from a trapezoidal prism
/* obsolete, see Shape.hpp for reasoning
void Shape::getpoint(int i) {
	xpoint = xp[i];
	ypoint = yp[i];
	zpoint = zp[i];
}
*/