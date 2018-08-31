#pragma once
#include "GeneralHeaders.h"
#include "EntityClass.h"


class Tile;
class LTexture;

class PlayerCharacter: public EntityClass
{
public:
	std::string GetImagePath();
	void SetImagePath(std::string m_ImagePath);
	
protected:

private:
	std::string m_ImagePath;
	std::string m_CharacterName="Anonymous";

	std::map<AbilityScoreType, int> m_AbilityScores =
	{
		{ STR, NULL },
		{ DEX, NULL },
		{ CON, NULL },
		{ INT, NULL },
		{ WIS, NULL },
		{ CHA, NULL }
	};

	//RaceType Race;
	//std::vector<ClassLevels> Levels;
};