#pragma once
#include "GeneralHeaders.h"
#include "EntityClass.h"


class Tile;
class LTexture;

class PlayerCharacter: public EntityClass
{
public:
	std::string GetImagePath();
	void SetImagePath(std::string ImagePath);
	
protected:

private:
	std::string ImagePath;
	std::string CharacterName="Anonymous";

	std::map<AbilityType, int> AbilityScores =
	{
		{ STR, NULL },
		{ DEX, NULL },
		{ CON, NULL },
		{ INT, NULL },
		{ WIS, NULL },
		{ CHA, NULL }
	};

	std::vector<CreatureType> Type;
	//RaceType Race;
	//std::vector<ClassLevels> Levels;
};