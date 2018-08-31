#pragma once
#include "EntityClass.h"

class TargetSystem : public EntityClass
{
public:
	TargetSystem();
	void HandleTurn(SDL_Event& m_event);
	void handleEvent(SDL_Event& m_event);
	bool move(std::vector<std::vector<Tile>> &TileVector);

	void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render
	void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at
	std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);

	//returns the location
	std::pair<int, int> GetLocation();

	//Centers the m_camera over the entity
	void setCamera(SDL_Rect& camera);

	//Shows the entity on the screen
	void render(SDL_Rect& camera, SDL_Renderer *& Renderer);

	void SetPath(std::string Path) { m_PathTexture = Path; }
	std::string GetPath() { return m_PathTexture; }

	void SetTexture(std::map<std::string, LTexture*> &map, std::string path);

	LTexture* GetTexture();

	bool GetBlocksMovement() { return m_BlocksMovement; }
	void SwitchBlocksMovement() { m_BlocksMovement = !m_BlocksMovement; }
	void SetBlocksMovement(bool passed) { m_BlocksMovement = passed; }
	
	bool GetActive() { return m_Active; }
	void SetActive(bool passed) { m_Active = passed;  }

	ControlMode GetControlMode() { return m_ControlSetting; }
	void SetControlMode(ControlMode NewControl) { m_ControlSetting = NewControl; }

private:
	std::string m_LevelName = "";
	LTexture* m_Texture;
	Direction m_MoveDirection;
	std::pair<unsigned, unsigned> m_Location = { 0,0 };
	std::string m_PathTexture = "Target.png";
	bool m_Active = false;
	bool m_BlocksMovement = false;
	int m_TARGET_WIDTH = 80;
	int m_TARGET_HEIGHT = 80;

	SDL_Rect m_Box;
	ControlMode m_ControlSetting = MOVEMODE;
};