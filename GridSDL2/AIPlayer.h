#pragma once
#include "GeneralHeaders.h"
#include "EntityClass.h"
#include "PathfindingAlgorithm.h"

class EncounterInstance;

class AIPlayer
{
public:
	//master function will call other functions and EntityClass Functions as necessary. 
	//Flow idea: Will see if the currently controlled entity has a path and target already. 
	//if no to either, call finding path and or finding target 
	void AITurn(std::vector<std::vector<Tile>>& TileMap, EntityClass &Entity, EncounterInstance & Instance);
	
	//determines what enemy entity to target and returns a pointer to them when found
	EntityClass* SearchForTargetedEntity(std::vector<std::vector<Tile>>&TileMap);

	void SetControlledEntity(EntityClass &NewEntity) { ControlledEntity = &NewEntity; }
	EntityClass* GetControlledEntity() { return ControlledEntity; }

	void SetTargetEntity(EntityClass &NewEntity) { TargetedEntity = &NewEntity; }
	EntityClass* GetTargetEntity() { return TargetedEntity; }

	//checks to see if the path is blocked
	bool CheckPathBlocked(std::vector<std::vector<Tile>>&TileMap);

	//checks to see if the target has moved
	bool CheckTargetMoved(std::vector<std::vector<Tile>>&TileMap);
	
	//checks in map to see if there is a corresponding target and returns it if it exists, null if not
	EntityClass* FindCorrespondingTarget();

	//returns empty vector if no path found, full path if it exists
	std::vector<GraphLocation> GetEntityPath();

	bool CheckResetTargetOrPath(std::vector<std::vector<Tile>>& TileMap);

	std::vector<GraphLocation> DevelopPathing(std::vector<std::vector<Tile>> &TileMap);

private:
	std::map<EntityClass*, EntityClass*> TargetMap;
	std::map<EntityClass*, std::vector<GraphLocation>> EntityPaths;

	EntityClass* ControlledEntity;
	EntityClass* TargetedEntity;

	Direction FindDirection();
	Direction FindDirection(int xTarget, int yTarget);
	
};