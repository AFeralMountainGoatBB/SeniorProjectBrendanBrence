/**********************************************************************************************//**
 * @file	AIPlayer.h.
 *
 * @brief	Declares the ai player class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "EntityClass.h"
#include "PathfindingAlgorithm.h"

//fwd declaration to prevent circular dependency
class EncounterInstance;

/**********************************************************************************************//**
 * @class	AIPlayer
 *
 * @brief	An ai player, holds information about the ai to develop paths for every ai controlled
 * 			 entity, and call different functions to determine ai actions
 *
 * @author	Brendan B
 * @date	9/7/2018
 **************************************************************************************************/

class AIPlayer
{
public:
	//master function will call other functions and EntityClass Functions as necessary. 
	//if no to either, call finding path and or finding target 

	/**********************************************************************************************//**
	 * @fn	void AIPlayer::AITurn(std::vector<std::vector<Tile>>& TileMap, EntityClass &Entity, EncounterInstance & Instance);
	 *
	 * @brief	Ai turn, calls all other functions, determines what ai is active, if they are a melee unit or ranged,
	 * 			 and what to do with this information
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	TileMap 	The tile map.
	 * @param [in,out]	Entity  	The active entity.
	 * @param [in,out]	Instance	The instance.
	 **************************************************************************************************/

	void AITurn(std::vector<std::vector<Tile>>& TileMap, EntityClass &Entity, EncounterInstance & Instance);
	
	
	/**********************************************************************************************//**
	 * @fn	EntityClass* AIPlayer::SearchForTargetedEntity(std::vector<std::vector<Tile>>&TileMap);
	 *
	 * @brief	Searches for the first targeted entity, and returns them to develop a path to it
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	TileMap	The tile map.
	 *
	 * @return	Null if it fails, else the found targeted entity.
	 **************************************************************************************************/

	EntityClass* SearchForTargetedEntity(std::vector<std::vector<Tile>>&TileMap);

	/**********************************************************************************************//**
	 * @fn	void AIPlayer::SetControlledEntity(EntityClass &NewEntity)
	 *
	 * @brief	Sets controlled entity
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	NewEntity	The new entity.
	 **************************************************************************************************/

	void SetControlledEntity(EntityClass &NewEntity) { m_ControlledEntity = &NewEntity; }

	/**********************************************************************************************//**
	 * @fn	EntityClass* AIPlayer::GetControlledEntity()
	 *
	 * @brief	Gets controlled entity
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	Null if it fails, else the controlled entity.
	 **************************************************************************************************/

	EntityClass* GetControlledEntity() { return m_ControlledEntity; }

	/**********************************************************************************************//**
	 * @fn	void AIPlayer::SetTargetEntity(EntityClass &NewEntity)
	 *
	 * @brief	Sets target entity
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	NewEntity	The new entity.
	 **************************************************************************************************/

	void SetTargetEntity(EntityClass &NewEntity) { m_TargetedEntity = &NewEntity; }

	/**********************************************************************************************//**
	 * @fn	EntityClass* AIPlayer::GetTargetEntity()
	 *
	 * @brief	Gets target entity
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	Null if it fails, else the target entity.
	 **************************************************************************************************/

	EntityClass* GetTargetEntity() { return m_TargetedEntity; }

	//checks to see if the path is blocked

	/**********************************************************************************************//**
	 * @fn	bool AIPlayer::CheckPathBlocked(std::vector<std::vector<Tile>>&TileMap);
	 *
	 * @brief	Check path blocked
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	TileMap	The tile map.
	 *
	 * @return	True if it is blocked, false if it is not blocked.
	 **************************************************************************************************/

	bool CheckPathBlocked(std::vector<std::vector<Tile>>&TileMap);

	//checks to see if the target has moved

	/**********************************************************************************************//**
	 * @fn	bool AIPlayer::CheckTargetMoved(std::vector<std::vector<Tile>>&TileMap);
	 *
	 * @brief	Check if target moved
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	TileMap	The tile map.
	 *
	 * @return	True if target has moved, false if it has not.
	 **************************************************************************************************/

	bool CheckTargetMoved(std::vector<std::vector<Tile>>&TileMap);


	/**********************************************************************************************//**
	 * @fn	bool AIPlayer::CheckResetTargetOrPath(std::vector<std::vector<Tile>>& TileMap);
	 *
	 * @brief	Check reset target or path, checks to see if we need a new target (old target died) 
	 * 			or if the path is blocked and needs to be recalculated
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	TileMap	The tile map.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool CheckResetTargetOrPath(std::vector<std::vector<Tile>>& TileMap);

	/**********************************************************************************************//**
	 * @fn	std::vector<GraphLocation> AIPlayer::DevelopPathing(std::vector<std::vector<Tile>> &TileMap);
	 *
	 * @brief	Develop pathing, calls pathing algorithms to develop a path from source to target
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	TileMap	The tile map.
	 *
	 * @return	A vector of graphlocations that is the path
	 **************************************************************************************************/

	std::vector<GraphLocation> DevelopPathing(std::vector<std::vector<Tile>> &TileMap);


private:
	/** @brief	Target map */
	std::map<EntityClass*, EntityClass*> m_TargetMap;
	/** @brief	The entity paths */
	std::map<EntityClass*, std::vector<GraphLocation>> m_EntityPaths;

	/** @brief	The controlled entity */
	EntityClass* m_ControlledEntity;
	/** @brief	The targeted entity */
	EntityClass* m_TargetedEntity;

	/**********************************************************************************************//**
	 * @fn	Direction AIPlayer::FindDirection();
	 *
	 * @brief	Searches for the correct direction, help function that orients the ai movelocation so it uses the same 
	 * 			functions as the player does
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The found direction.
	 **************************************************************************************************/

	Direction FindDirection();

	/**********************************************************************************************//**
	 * @fn	Direction AIPlayer::FindDirection(int xTarget, int yTarget);
	 *
	 * @brief	Searches for the correct direction to face, used so ai will use the same move and attack functions as the player
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	xTarget	Target for the.
	 * @param	yTarget	Target for the.
	 *
	 * @return	The found direction.
	 **************************************************************************************************/

	Direction FindDirection(int xTarget, int yTarget);

};