#pragma once
#include "EntityClass.h"

class TargetSystem : public EntityClass
{
public:
	TargetSystem();
	void HandleTurn(SDL_Event& e);
	void handleEvent(SDL_Event& e);
	bool move(std::vector<std::vector<Tile>> &TileVector);

	void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render
	void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at
	std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);

	//returns the location
	std::pair<int, int> GetLocation();

	//Centers the camera over the entity
	void setCamera(SDL_Rect& camera);

	//Shows the entity on the screen
	void render(SDL_Rect& camera, SDL_Renderer *& Renderer);

	void SetPath(std::string Path) { mPathTexture = Path; }
	std::string GetPath() { return mPathTexture; }

	void SetTexture(std::map<std::string, LTexture*> &map, std::string path);

	LTexture* GetTexture();

	bool GetBlocksMovement() { return BlocksMovement; }
	void SwitchBlocksMovement() { BlocksMovement = !BlocksMovement; }
	void SetBlocksMovement(bool passed) { BlocksMovement = passed; }
	
	bool GetActive() { return Active; }
	void SetActive(bool passed) { Active = passed;  }

	ControlMode GetControlMode() { return ControlSetting; }
	void SetControlMode(ControlMode NewControl) { ControlSetting = NewControl; }

private:
	std::string LevelName = "";
	LTexture* mTexture;
	Direction MoveDirection;
	std::pair<unsigned, unsigned> mLocation = { 0,0 };
	std::string mPathTexture = "Target.png";
	bool Active = false;
	bool BlocksMovement = false;
	int TARGET_WIDTH = 80;
	int TARGET_HEIGHT = 80;

	SDL_Rect mBox;
	ControlMode ControlSetting = MOVEMODE;
};