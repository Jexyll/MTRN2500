
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#elif defined(WIN32)
	#include <Windows.h>
	#include <tchar.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#endif


#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"

void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
//   can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;

// default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

//int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	//   with the name of the class you want to show as the current 
	//   custom vehicle.
	// -------------------------------------------------------------------------

	vehicle = new custVehicle();


	// add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10,-10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,-10, 1));

	// add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);


	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

void drawGoals()
{
	for (int i = 0; i < goals.size(); ++i) {
		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}

void drawnewquad(){
	glBegin(GL_QUADS);
	glVertex2d(0,0);
	glVertex2d(0,200);
	glVertex2d(200, 200);
	glVertex2d(200,0);
	glEnd();
}


void drawnewdisk() {
	GLUquadric*disk= gluNewQuadric();
	gluDisk(disk, 0, 2000, 1, 1);
}
void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();
	
	// draw other vehicles
	for(std::map<int, Vehicle *>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) 
		iter->second->draw();

	// draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();

	}

	// draw obstacles
	ObstacleManager::get()->drawAll();

	// draw goals
	drawGoals();

	// draw HUD
	HUD::Draw();
	//draw a thing example
	/*
	rectangularprism rprsm1(15,15,15);
	rprsm1.setPosition(0, 0, 0);
	rprsm1.setRotation(15);
	rprsm1.setColor(0, 0, 1);
	rprsm1.setColorInGL();
	rprsm1.draw();


	trapezoid trap1(15,15,2.5,15,10);
	trap1.setPosition(rprsm1.xp[4],rprsm1.yp[4], rprsm1.zp[4]);//rprsm1.?p[4] is point 4 on rprsm 1, rprsm1 can be moved and the trapezoid will be attached
	trap1.setRotation(15);
	trap1.setColor(1, 1, 1);
	trap1.setColorInGL();
	trap1.draw();
	
	
	*/
	


	//vehicle1.newtriangularprism(0, 1, 0, 0.5, 0.4, 90, -2, 90, 0, 1, 0);
	//vehicle1.newcylinder(0, 0, 0.5, 0.25, 0.25, 0.4, 128, 1, 1, 90, 1, 0, 1);
	//vehicle1.newcylinder(2, 0, 0.5, 0.25, 0.25, 0.4, 128, 1, 1, 90, 1, 0, 1);
	//vehicle1.newcylinder(0, 0, 2.25, 0.25, 0.25, 0.4, 128, 1, 1, 90, 1, 0, 1);
	//vehicle1.newcylinder(2, 0, 2.25, 0.25, 0.25, 0.4, 128, 1, 1, 90, 1, 0, 1);


	/*
	cylinder cylinder1(5, 3, 5, 256, 5, 5);
	cylinder1.setPosition(0, 0, 0);
	cylinder1.setRotation(15);
	cylinder1.draw();
	*/

	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;
}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if(QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {

	if (KeyManager::get()->isAsciiKeyPressed('a')) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c')) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d')) {
		Camera::get()->strafeRight();
	}

	if (KeyManager::get()->isAsciiKeyPressed('s')) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w')) {
		Camera::get()->moveForward();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ')) {
		Camera::get()->strafeUp();
	}

	speed = 0;
	steering = 0;

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;   
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}

	// attempt to do data communications every 4 frames if we've created a local vehicle
	if(frameCounter % 4 == 0 && vehicle != NULL) {

		// if not connected, attempt to connect every 2 seconds
		if(!RemoteDataManager::IsConnected()) {
			if(frameCounter % 120 == 0) {
		
				// erase other vehicles
				for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au","18081");

				// on connect, let's tell the server what we look like
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					vm.remoteID = 0;

					//
					// student code goes here
					// Code that adds shapes to a Vehiclemodel for the remote server to read
					ShapeInit Rectangle1;
					Rectangle1.type = RECTANGULAR_PRISM;
					Rectangle1.xyz[0] = 1.5;
					Rectangle1.xyz[1] = 0.25;
					Rectangle1.xyz[2] = -1;
					Rectangle1.rgb[0] = 1;
					Rectangle1.rgb[1] = 0;
					Rectangle1.rgb[2] = 0;
					Rectangle1.rotation = 90;
					Rectangle1.params.rect.xlen=2;
					Rectangle1.params.rect.ylen = 0.75;
					Rectangle1.params.rect.zlen = 3;
					vm.shapes.push_back(Rectangle1);

					ShapeInit Trapezoid1;
					Trapezoid1.type = TRAPEZOIDAL_PRISM;
					Trapezoid1.xyz[0] = 1.75;
					Trapezoid1.xyz[1] = 1;
					Trapezoid1.xyz[2] = -1;
					Trapezoid1.rgb[0] = 0;
					Trapezoid1.rgb[1] = 0;
					Trapezoid1.rgb[2] = 1;
					Trapezoid1.rotation = 0;
					Trapezoid1.params.trap.alen = 2.5;
					Trapezoid1.params.trap.blen = 1.25;
					Trapezoid1.params.trap.height = 0.6;
					Trapezoid1.params.trap.aoff = 0.75;
					Trapezoid1.params.trap.depth = 2;
					vm.shapes.push_back(Trapezoid1);

					ShapeInit Triangle1;
					Triangle1.type = TRIANGULAR_PRISM;
					Triangle1.xyz[0] = 0.25;
					Triangle1.xyz[1] = 1;
					Triangle1.xyz[2] = -1;
					Triangle1.rgb[0] = 0;
					Triangle1.rgb[1] = 1;
					Triangle1.rgb[2] = 0;
					Triangle1.rotation = 0;
					Triangle1.params.tri.alen = 0.5;
					Triangle1.params.tri.blen = 0.4;
					Triangle1.params.tri.angle = 90;
					Triangle1.params.tri.depth = -2;
					vm.shapes.push_back(Triangle1);
				

					ShapeInit Cylinder1;
					Cylinder1.type = CYLINDER;
					Cylinder1.xyz[0] = 0.4;
					Cylinder1.xyz[1] = 0.0001;
					Cylinder1.xyz[2] = 0.2;
					Cylinder1.rgb[0] = 1;
					Cylinder1.rgb[1] = 1;
					Cylinder1.rgb[2] = 1;
					Cylinder1.rotation = 0;
					Cylinder1.params.cyl.depth = 0.4;
					Cylinder1.params.cyl.radius = 0.75;
					Cylinder1.params.cyl.isRolling = TRUE;
					Cylinder1.params.cyl.isSteering = FALSE;
					vm.shapes.push_back(Cylinder1);

					ShapeInit Cylinder2;
					Cylinder2.type = CYLINDER;
					Cylinder2.xyz[0] = 0.4;
					Cylinder2.xyz[1] = 0.0001;
					Cylinder2.xyz[2] = -2.2;
					Cylinder2.rgb[0] = 1;
					Cylinder2.rgb[1] = 1;
					Cylinder2.rgb[2] = 1;
					Cylinder2.rotation = 0;
					Cylinder2.params.cyl.depth = 0.4;
					Cylinder2.params.cyl.radius = 0.75;
					Cylinder2.params.cyl.isRolling = TRUE;
					Cylinder2.params.cyl.isSteering = FALSE;
					vm.shapes.push_back(Cylinder2);

					ShapeInit Cylinder3;
					Cylinder3.type = CYLINDER;
					Cylinder3.xyz[0] = 2.5;
					Cylinder3.xyz[1] = 0.0001;
					Cylinder3.xyz[2] = 0.2;
					Cylinder3.rgb[0] = 1;
					Cylinder3.rgb[1] = 1;
					Cylinder3.rgb[2] = 1;
					Cylinder3.rotation = 0;
					Cylinder3.params.cyl.depth = 0.4;
					Cylinder3.params.cyl.radius = 0.25;
					Cylinder3.params.cyl.isRolling = TRUE;
					Cylinder3.params.cyl.isSteering = TRUE;
					vm.shapes.push_back(Cylinder3);

					ShapeInit Cylinder4;
					Cylinder4.type = CYLINDER;
					Cylinder4.xyz[0] = 2.5;
					Cylinder4.xyz[1] = 0.0001;
					Cylinder4.xyz[2] = -2.2;
					Cylinder4.rgb[0] = 1;
					Cylinder4.rgb[1] = 1;
					Cylinder4.rgb[2] = 1;
					Cylinder4.rotation = 0;
					Cylinder4.params.cyl.depth = 0.4;
					Cylinder4.params.cyl.radius = 0.25;
					Cylinder4.params.cyl.isRolling = TRUE;
					Cylinder4.params.cyl.isSteering = TRUE;
					vm.shapes.push_back(Cylinder4);

					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// if we're connected, send our vehicle state to the server
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			vs.rotation = vehicle->getRotation();
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// if we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for(unsigned int i = 0; i < msgs.size(); i++ ) {

				RemoteMessage msg = msgs[i];
				//cout << msg.payload << endl;

				switch(msg.type) {
					// new models
					case 'M':
						{
							std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
							for(unsigned int i = 0; i < models.size(); i++) {
								VehicleModel vm = models[i];
								
								// uncomment the line below to create remote vehicles
								otherVehicles[vm.remoteID] = new custVehicle(1);
								for (std::vector<ShapeInit>::iterator it = vm.shapes.begin(); it != vm.shapes.end(); ++it) {//iterate through vehicle model shapeinit vector

									if (it->type == TRAPEZOIDAL_PRISM) {//write trapezoidal prisms to a vehicle
										trapezoid *Vtrap = new trapezoid(it->params.trap.alen, it->params.trap.height, it->params.trap.aoff, it->params.trap.depth, it->params.trap.blen);
										Vtrap->setPosition(it->xyz[0], it->xyz[1], it->xyz[2]);
										Vtrap->setRotation(it->rotation);
										Vtrap->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
										otherVehicles[vm.remoteID]->addShape(Vtrap);
									}
									else if (it->type == RECTANGULAR_PRISM){//write rectangular prism to a vehicle
										rectangularprism *Vrect = new rectangularprism(it->params.rect.xlen, it->params.rect.ylen, it->params.rect.zlen);
										Vrect->setPosition(it->xyz[0], it->xyz[1], it->xyz[2]);
										Vrect->setRotation(it->rotation);
										Vrect->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
										otherVehicles[vm.remoteID]->addShape(Vrect);
									}
									else if (it->type == TRIANGULAR_PRISM) {//write triangular prism to a vehicle
										triangularprism *Vtri = new triangularprism(it->params.tri.alen, it->params.tri.blen, it->params.tri.angle, it->params.tri.depth);
										Vtri->setPosition(it->xyz[0], it->xyz[1], it->xyz[2]);
										Vtri->setRotation(it->rotation);
										Vtri->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
										otherVehicles[vm.remoteID]->addShape(Vtri);
									} 
									
									else if (it->type == CYLINDER) {// write cylinder to vehicle
										cylinder *Vcyl = new cylinder(it->params.cyl.radius, it->params.cyl.depth, 8, 3, 1, 0);//add steering later
										Vcyl->setPosition(it->xyz[0], it->xyz[1]+it->params.cyl.radius, it->xyz[2]);
										Vcyl->setRotation(it->rotation);
										Vcyl->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
										if (it->params.cyl.isSteering == TRUE)
											Vcyl->setsteering(1);
										if (it->params.cyl.isRolling == FALSE)
											Vcyl->setspinning(0);
										otherVehicles[vm.remoteID]->addShape(Vcyl);

									}
									else{}
										//donothing
								}

							}
							break;
						}

					// vehicle states
					case 'S': 
						{
							std::vector<VehicleState> states = GetVehicleStates(msg.payload);
							for(unsigned int i = 0; i < states.size(); i++) {
								VehicleState vs = states[i];

								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
								if(iter != otherVehicles.end()) {
									Vehicle * veh = iter->second;
									remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
								}
							}
							break;
						}

					// goal state
					case 'G':
						{
							goals = GetGoals(msg.payload);
							break;
						}

					// obstacle state
					case 'O':
						{
							std::vector<ObstacleState> obs = GetObstacles(msg.payload);
							for(unsigned int i = 0; i < obs.size(); i++) {
								Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
								ObstacleManager::get()->addObstacle(o);
							}
							break;
						}

					// disconnect list
					case 'D':
						{
							std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
							for(unsigned int i = 0; i < disconnectedIDs.size(); i++) {
								int id = disconnectedIDs[i];
								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
								if(iter != otherVehicles.end()) {
									delete iter->second;
									otherVehicles.erase(iter);
								}
							}
							break;
						}

					// error message
					case 'E':
						{
							cerr << "Server error: " << msg.payload << endl;
							break;
						}

				}
			} 
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// do a simulation step
	if (vehicle != NULL) {
		vehicle->update(speed, steering, elapsedTime);
	}
	for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// keys that will be held down for extended periods of time will be handled
	//   in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// keys that react ocne when pressed rather than need to be held down
	//   can be handles normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;      
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;
	}

};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {  
	KeyManager::get()->specialKeyReleased(keycode);  
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};

