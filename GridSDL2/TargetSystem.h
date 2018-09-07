/**********************************************************************************************//**
 * @file	TargetSystem.h.
 *
 * @brief	Declares the target system class
 **************************************************************************************************/

#pragma once
#include "EntityClass.h"

/**********************************************************************************************//**
 * @class	TargetSystem
 *
 * @brief	A target system, inherits from entity, is stored in 
 * 			encounterinstance and controlled by player when they choose to make a ranged attack
 *
 * @author	Brendan B
 * @date	9/7/2018
 **************************************************************************************************/

class TargetSystem : public EntityClass
{
public:

	/**********************************************************************************************//**
	 * @fn	TargetSystem::TargetSystem();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 **************************************************************************************************/

	TargetSystem();

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::HandleTurn(SDL_Event& m_event);
	 *
	 * @brief	Handles the turn described by m_event
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	m_event	The event.
	 **************************************************************************************************/

	void HandleTurn(SDL_Event& m_event);

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::handleEvent(SDL_Event& m_event);
	 *
	 * @brief	Handles the event described by m_event
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	m_event	The event.
	 **************************************************************************************************/

	void handleEvent(SDL_Event& m_event);

	/**********************************************************************************************//**
	 * @fn	bool TargetSystem::move(std::vector<std::vector<Tile>> &TileVector);
	 *
	 * @brief	Moves the given tile vector
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	TileVector	The tile vector.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool move(std::vector<std::vector<Tile>> &TileVector);

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	 *
	 * @brief	Sets a location
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param 		  	x	   	The x coordinate.
	 * @param 		  	y	   	The y coordinate.
	 * @param [in,out]	TileMap	The tile map.
	 **************************************************************************************************/

	void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	 *
	 * @brief	Sets rend location
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	TileVector	The tile vector.
	 **************************************************************************************************/

	void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at

	/**********************************************************************************************//**
	 * @fn	std::pair<int, int> TargetSystem::CalcRendLocation(std::vector<std::vector<Tile>> &Map);
	 *
	 * @brief	Calculates the rend location
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	Map	The map.
	 *
	 * @return	The calculated rend location.
	 **************************************************************************************************/

	std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);

	//returns the location

	/**********************************************************************************************//**
	 * @fn	std::pair<int, int> TargetSystem::GetLocation();
	 *
	 * @brief	Gets the location
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The location.
	 **************************************************************************************************/

	std::pair<int, int> GetLocation();

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::setCamera(SDL_Rect& camera);
	 *
	 * @brief	Sets the camera to be centered over this 
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	camera	The camera.
	 **************************************************************************************************/

	void setCamera(SDL_Rect& camera);

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::render(SDL_Rect& camera, SDL_Renderer *& Renderer);
	 *
	 * @brief	Renders this object
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	camera  	The camera.
	 * @param [in,out]	Renderer	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void render(SDL_Rect& camera, SDL_Renderer *& Renderer);

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::SetPath(std::string Path)
	 *
	 * @brief	Sets a path for the texture location
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	Path	Full pathname of the file.
	 **************************************************************************************************/

	void SetPath(std::string Path) { m_PathTexture = Path; }

	/**********************************************************************************************//**
	 * @fn	std::string TargetSystem::GetPath()
	 *
	 * @brief	Gets the path
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The path.
	 **************************************************************************************************/

	std::string GetPath() { return m_PathTexture; }

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::SetTexture(std::map<std::string, LTexture*> &map, std::string path);
	 *
	 * @brief	Sets a texture, loads it and sets it
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	map 	[in,out] If non-null, the map.
	 * @param 		  	path	Full pathname of the file.
	 **************************************************************************************************/

	void SetTexture(std::map<std::string, LTexture*> &map, std::string path);

	/**********************************************************************************************//**
	 * @fn	LTexture* TargetSystem::GetTexture();
	 *
	 * @brief	Gets the texture
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	Null if it fails, else the texture.
	 **************************************************************************************************/

	LTexture* GetTexture();

	/**********************************************************************************************//**
	 * @fn	bool TargetSystem::GetBlocksMovement()
	 *
	 * @brief	Gets blocks movement
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	True if it doesnt block movement, false if it doesnt.
	 **************************************************************************************************/

	bool GetBlocksMovement() { return m_BlocksMovement; }

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::SwitchBlocksMovement()
	 *
	 * @brief	Switch blocks movement
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 **************************************************************************************************/

	void SwitchBlocksMovement() { m_BlocksMovement = !m_BlocksMovement; }

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::SetBlocksMovement(bool passed)
	 *
	 * @brief	Sets blocks movement
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	passed	new value for blocks movement.
	 **************************************************************************************************/

	void SetBlocksMovement(bool passed) { m_BlocksMovement = passed; }

	/**********************************************************************************************//**
	 * @fn	bool TargetSystem::GetActive()
	 *
	 * @brief	Gets the active unit
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	True if it is active, false if it is not.
	 **************************************************************************************************/

	bool GetActive() { return m_Active; }

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::SetActive(bool passed)
	 *
	 * @brief	Sets active value
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	passed	new value for m_active
	 **************************************************************************************************/

	void SetActive(bool passed) { m_Active = passed;  }

	/**********************************************************************************************//**
	 * @fn	ControlMode TargetSystem::GetControlMode()
	 *
	 * @brief	Gets control mode
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The control mode.
	 **************************************************************************************************/

	ControlMode GetControlMode() { return m_ControlSetting; }

	/**********************************************************************************************//**
	 * @fn	void TargetSystem::SetControlMode(ControlMode NewControl)
	 *
	 * @brief	Sets control mode
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	NewControl	The new control value
	 **************************************************************************************************/

	void SetControlMode(ControlMode NewControl) { m_ControlSetting = NewControl; }

private:
	/** @brief	Name of the level */
	std::string m_LevelName = "";
	/** @brief	The texture */
	LTexture* m_Texture;
	/** @brief	The move direction */
	Direction m_MoveDirection;
	/** @brief	The location */
	std::pair<unsigned, unsigned> m_Location = { 0,0 };
	/** @brief	The path texture */
	std::string m_PathTexture = "Target.png";
	/** @brief	True to active */
	bool m_Active = false;
	/** @brief	True to blocks movement */
	bool m_BlocksMovement = false;
	/** @brief	Width of the target */
	int m_TARGET_WIDTH = 80;
	/** @brief	Height of the target */
	int m_TARGET_HEIGHT = 80;

	/** @brief	The box */
	SDL_Rect m_Box;
	/** @brief	The control setting */
	ControlMode m_ControlSetting = MOVEMODE;
};