#include <iostream>
#include <cmath>
#include "XBoxController.h"
#include "XInputWrapper.h"


using namespace std;

// Set the value of xinput and playerId variable in XBoxController.h.
GamePad::XBoxController::XBoxController(XInputWrapper* xinput, DWORD id) {

	this->xinput = xinput;
	playerId = id;
}

// Get the Id of the controller such as player 1 etc.
DWORD GamePad::XBoxController::GetControllerId() {

	return playerId;
}

// Determine if controller is connected or not.
bool GamePad::XBoxController::IsConnected() {

	XINPUT_STATE connection;
	ZeroMemory(&connection, sizeof(XINPUT_STATE));

	controllerInfo = XInputGetState(playerId, &connection);

	if (controllerInfo == ERROR_SUCCESS) {

		return 1;
	}
	else {

		return 0;
	}
}

// Acknowledge that Button A has been pressed.
bool GamePad::XBoxController::PressedA() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Button B has been pressed.
bool GamePad::XBoxController::PressedB() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Button X has been pressed.
bool GamePad::XBoxController::PressedX() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Button Y has been pressed.
bool GamePad::XBoxController::PressedY() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Button LB has been pressed.
bool GamePad::XBoxController::PressedLeftShoulder() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Button RB has been pressed.
bool GamePad::XBoxController::PressedRightShoulder() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Left Dpad has been pressed.
bool GamePad::XBoxController::PressedLeftDpad() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Right Dpad has been pressed.
bool GamePad::XBoxController::PressedRightDpad() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Up Dpad has been pressed.
bool GamePad::XBoxController::PressedUpDpad() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Down Dpad has been pressed.
bool GamePad::XBoxController::PressedDownDpad() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Button Start has been pressed.
bool GamePad::XBoxController::PressedStart() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_START) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Button Back has been pressed.
bool GamePad::XBoxController::PressedBack() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Left Analog has been pressed.
bool GamePad::XBoxController::PressedLeftThumb() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Right Analog has been pressed.
bool GamePad::XBoxController::PressedRightThumb() {

	xinput->XInputGetState(playerId, &pressedButton);
	if (pressedButton.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) {
		return 1;
	}
	else {
		return 0;
	}
}

// Acknowledge that Left Trigger has been pressed.
BYTE GamePad::XBoxController::LeftTriggerLocation() {

	return pressedButton.Gamepad.bLeftTrigger;
}

// Acknowledge that Right Trigger has been pressed.
BYTE GamePad::XBoxController::RightTriggerLocation() {

	return pressedButton.Gamepad.bRightTrigger;
}

// Locate left analog's coordinates
GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation() {

	double leftX = pressedButton.Gamepad.sThumbLX;
	double leftY = pressedButton.Gamepad.sThumbLY;

	GamePad::Coordinate  xBoxLeftCoordinate(leftX, leftY);

	double leftMag = sqrt(leftX*leftX + leftY * leftY);

	double normalizedLeftX = leftX / leftMag;
	double normalizedLeftY = leftY / leftMag;

	double normMagnitude = 0;

	if (leftMag < deadZoneValue) {

		xBoxLeftCoordinate.SetX(0);
		xBoxLeftCoordinate.SetY(0);
	}
	else {

		normMagnitude = 32767 * (leftMag - deadZoneValue) / (32767 - deadZoneValue);
		xBoxLeftCoordinate.SetX(normalizedLeftX*normMagnitude);
		xBoxLeftCoordinate.SetY(normalizedLeftY*normMagnitude);
	}
	return xBoxLeftCoordinate;
}

// Locate right analog's coordinates
GamePad::Coordinate GamePad::XBoxController::RightThumbLocation() {

	double rightX = pressedButton.Gamepad.sThumbRX;
	double rightY = pressedButton.Gamepad.sThumbRY;

	GamePad::Coordinate  xBoxRightCoordinate(rightX, rightY);

	double rightMag = sqrt(rightX*rightX + rightY * rightY);

	double normalizedRightX = rightX / rightMag;
	double normalizedRightY = rightY / rightMag;

	double normMagnitude = 0;

	if (rightMag < deadZoneValue) {

		xBoxRightCoordinate.SetX(0);
		xBoxRightCoordinate.SetY(0);
	}
	else {

		normMagnitude = 32767 * (rightMag - deadZoneValue) / (32767 - deadZoneValue);
		xBoxRightCoordinate.SetX(normalizedRightX*normMagnitude);
		xBoxRightCoordinate.SetY(normalizedRightY*normMagnitude);
	}
	return xBoxRightCoordinate;
}

// Vibrate the controller
void GamePad::XBoxController::Vibrate(WORD left, WORD right) {

	xinput->XInputSetState(playerId, &vibrate);
	vibrate.wLeftMotorSpeed = left;
	vibrate.wRightMotorSpeed = right;
}

// Set DeadZone value
void GamePad::XBoxController::SetDeadzone(unsigned int radius) {

	deadZoneValue = radius;
}

