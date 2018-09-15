
#ifndef MTRN3500_SHAPE_H
#define MTRN3500_SHAPE_H

// Abstract class
class Shape {

public:
	Shape();
	Shape(double x_, double y_, double z_);
	Shape(double x_, double y_, double z_, double rotation_);
	virtual ~Shape();
	virtual void draw() = 0;
	virtual void spinup(double speed) {}
	virtual void turnit(double turn){}// spinup and turnit exist as virtual functions so i can override because i'm lazy and don't want to dynamic cast, but they are unneccesary with dynamic casting

	double getX();
	double getY();
	double getZ();
	double getRotation();

	void setX(double x_);
	void setY(double y_);
	void setZ(double z_);
	void setRotation(double rotation_);

	void setPosition(double x_, double y_, double z_);

	void positionInGL();
	void setColorInGL();

	double getRed();
	double getGreen();
	double getBlue();
	void setColor(float red_, float green_, float blue_);

	int getType();

	//double xpoint, ypoint, zpoint; as above, unneccesary

protected:
	double x, y, z;               // position
	double rotation;              // heading of the object in the horizontal plane (degrees)
	float red, green, blue;       // colour of object
	int type;					  // used in vehicle draw function to determine what type of shape is being drawn, only relevant for cylinders


};



class rectangularprism : public Shape{
public:
	rectangularprism(){}
	rectangularprism(double xlength_, double ylength_, double zlength_)
		: xlength(xlength_), ylength(ylength_), zlength(zlength_)
	{
		type = 0;
	}
	void draw();
	void setdimensions(double xlength_, double ylength_, double zlength_);
protected:
	double xlength, ylength, zlength;

};

class triangularprism : public Shape {
public:
	triangularprism(double sidea_, double sideb_, double angle_, double length_)//constructor
		:sidea(sidea_), sideb(sideb_), angle(angle_), length(length_) {
		type = 1;
	}
	void draw();
	void setdimensions(double sidea_, double sideb_, double angle_, double length_);
protected:
	double sidea, sideb, angle, length;//offset is the distance along the x axis of the top point from the starting point
};

class trapezoid : public Shape {
public:
	trapezoid(double base_, double height_, double offset_, double length_, double topwidth_)
		:base(base_), height(height_), offset(offset_), length(length_), topwidth(topwidth_)
	{
		type = 2;
	}
	void draw();
	void setdimensions(double base_, double height_, double offset_, double length_, double topwidth_);


protected:
	double base, height, offset, length, topwidth;//offset is the distance along the x axis of the top point from the starting point

};

class cylinder : public Shape {
	friend class Vehicle;
public:

	cylinder();
	cylinder(double baseRadius_, double height_, int slices_, int stacks_, int loops_, int turning_)
		:Radius(baseRadius_), height(height_), slices(slices_), stacks(stacks_), loops(loops_), turning(turning_)
	{
		spin = 0;
		spinning = 1;
		type = 3 + turning_;
		turn = 0;
	};		
	virtual void turnit(double turn);
	void spinup(double speed);//increments spin for wheels
	void setspinning(int sspin);//changes whether element is spinning or not
	void draw();
	void setdimensions(double baseRadius_, double height_, int slices_, int stacks_, int loops_);
	void setsteering(int steer);
protected:

	double Radius, height, spin, turn, turning;
	int slices, stacks, loops, spinning;
};

#endif // for MTRN3500_SHAPE_H