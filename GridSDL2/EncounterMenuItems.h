#pragma once
#include "GeneralHeaders.h"

//this class is for the objects that will be always present during the encounter, namely on the left side of the screen and the bottom
//will have labels for relevant information and a log on bottom
class EncounterMenuItems
{
public:

	kiss_array objects;
	kiss_window window;
	kiss_label AttackLabel = { 0 };
	kiss_label MoveLabel1 = { 0 };
	kiss_label MoveLabel2 = { 0 };
	kiss_button AttackButton = { 0 };
	kiss_button MoveButton = { 0 };
	char message[KISS_MAX_LENGTH];



};