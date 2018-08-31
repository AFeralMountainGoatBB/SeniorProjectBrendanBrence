#include "AIPlayer.h"
#include "Tile.h"
#include "EncounterInstance.h"
#include "MapAlgorithms.h"

void AIPlayer::AITurn(std::vector<std::vector<Tile>>& a_TileMap, EntityClass &a_ControlEntity, EncounterInstance & a_Instance)
{
	//the passed entity is the active unit, set as controlled entity and see if we need to recalculate targets
	SetControlledEntity(a_ControlEntity);
	
	//is the unit primarily a melee unit, true if melee, false if ranged
	bool MeleeUnit = m_ControlledEntity->isMeleeUnit();

	//we keep track of this to see if we need to m_draw a new path or find a new target
	bool ResetTargetOrPath = this->CheckResetTargetOrPath(a_TileMap);

	if (ResetTargetOrPath == true)
	{
	//for whatever reason we need to develop a target for this entity, and develop a path for it
	m_TargetedEntity = SearchForTargetedEntity(a_TileMap);
	if (m_TargetedEntity == nullptr)
	{
		std::cout << "AI has no valid targets, ending turn" << std::endl;
		return;
	}
	m_TargetMap[m_ControlledEntity] = m_TargetedEntity;
	m_EntityPaths[m_ControlledEntity] = DevelopPathing(a_TileMap);
	}
	else
	{
		m_TargetMap[m_ControlledEntity] = m_TargetedEntity;
	}
	
	
	bool endTurn = false;
	bool EndMove = false;
	bool EndAttack = false;
	//we have a target and a path now, we can decide what we want to do, 
	//will move into melee range as a melee unit or move towards target until we can shoot as a ranged unit
	if (MeleeUnit)
	{	
		while (endTurn==false)
		{
			//this if statement checks if target is in melee range
			if ((abs(m_ControlledEntity->GetLocation().first - m_TargetedEntity->GetLocation().first) <= 1)
				&& 
				(abs(m_ControlledEntity->GetLocation().second - m_TargetedEntity->GetLocation().second) <= 1) )
			{
				std::cout << "I want to attack" << std::endl;
				m_ControlledEntity->SetMoveDirection(this->FindDirection());
				m_ControlledEntity->EntityMeleeAttack(a_TileMap, a_Instance);
				endTurn = true;
			}
			else if (m_EntityPaths[m_ControlledEntity].size() > 2 && EndMove == false)
			{
				std::cout << "Moving" << std::endl;
				//get the next spot to move to, then find what direction to face and face that way
				auto Path = m_EntityPaths[m_ControlledEntity];
				//auto it = Path.begin();
				//this loop finds where we are on the path
				int xMoveTo = 0;
				int yMoveTo = 0;
				for (auto it = Path.begin(); it != Path.end(); it++)
				{
					std::cout << "Looking at" << (*it).x << ", " << (*it).y << std::endl;
					if ((*it).x == m_ControlledEntity->GetLocation().first && (*it).y == m_ControlledEntity->GetLocation().second)
					{
						//advance to next graphlocation and store
						it++;
						xMoveTo = (*it).x;
						yMoveTo = (*it).y;
						std::cout << "x: " << xMoveTo << ", y:" << yMoveTo << std::endl;
						std::cout << "currently at: " << m_ControlledEntity->GetLocation().first << ", " << m_ControlledEntity->GetLocation().second << std::endl;
						break;
					}
				}
				 //call facedirection
				std::cout << "trying to move to " << xMoveTo<< "," << yMoveTo << std::endl;
				m_ControlledEntity->SetMoveDirection(this->FindDirection(xMoveTo, yMoveTo));
				bool SuccessMove = true;
				SuccessMove = (m_ControlledEntity->move(a_TileMap));
				std::cout << "successmove" << SuccessMove << std::endl;
				if (SuccessMove==true)
				{
					std::cout << "Moved forward success" << std::endl;
				}
				if (SuccessMove==false)
				{
					std::cout << "SUCCESS MOVE IS FALSE" << std::endl;
					std::cout << m_ControlledEntity->GetName() << " must be out of moves, ending turn" << std::endl;
					m_ControlledEntity->SetMoveDirection(STATIONARY);
					EndMove = true;
				}
			} //end if path size greater than 2
			else
			{
				endTurn = true;
			}
		}
	}//end if melee unit
	else // not a melee unit
	{
		while (endTurn == false)
		{
			std::pair<int, int>Source;
			Source = std::make_pair(m_ControlledEntity->GetLocation().first, m_ControlledEntity->GetLocation().second);
			std::pair<int, int>Target;
			Target = std::make_pair(m_TargetedEntity->GetLocation().first, m_TargetedEntity->GetLocation().second);

			//check if target is visible (not completely blocked)
			SightAlgorithm Sight;
			Sight.DetermineSightAndCover(a_TileMap, Source, Target);
			if (Sight.GetBlockedOrObstructed().first == false)
			{
				m_ControlledEntity->EntityRangedAttack(a_TileMap, a_Instance, m_TargetedEntity);
				endTurn = true;
			}
			else if (m_EntityPaths[m_ControlledEntity].size() > 2 && EndMove==false)
			{
				//get the next spot to move to, then find what direction to face and face that way
				auto Path = m_EntityPaths[m_ControlledEntity];
				//this loop finds where we are on the path
				int xMoveTo = 0;
				int yMoveTo = 0;
				bool Reached = false;
				for (auto it = Path.begin(); it != Path.end(); it++)
				{
					std::cout << "Looking at" << (*it).x << ", " << (*it).y << std::endl;
					if ((*it).x == m_ControlledEntity->GetLocation().first && (*it).y == m_ControlledEntity->GetLocation().second)
					{
						it++;
						xMoveTo = (*it).x;
						yMoveTo = (*it).y;
						std::cout << "x: " << xMoveTo << ", y:" << yMoveTo << std::endl;
						std::cout << "currently at: " << m_ControlledEntity->GetLocation().first << ", " << m_ControlledEntity->GetLocation().second << std::endl;
						break;
					}
				}
				//advance to next graphlocation and call facedirection
				m_ControlledEntity->SetMoveDirection(this->FindDirection(xMoveTo, yMoveTo));
				bool SuccessMove = m_ControlledEntity->move(a_TileMap);
				if (!SuccessMove)
				{
					std::cout << m_ControlledEntity->GetName() << " must be out of moves, ending turn" << std::endl;
					EndMove = true;
				}
			} //end if path size greater than 2
			else
			{
				endTurn = true;
			}
		}
	}
	std::cout << m_ControlledEntity->GetName() << " ends turn" << std::endl;
}

bool AIPlayer::CheckResetTargetOrPath(std::vector<std::vector<Tile>>&a_TileMap)
{
	if (m_TargetMap.find(m_ControlledEntity) == m_TargetMap.end())
	{
		return true;
	}//or if the target has died we need a new target and path
	else if (!m_TargetMap[m_ControlledEntity]->GetIsAlive())
	{
		return true;
	} //if the target has moved at all or the path has become blocked we will change target and path
	else if (CheckPathBlocked(a_TileMap))
	{
		return true;
	}
	else if (CheckTargetMoved(a_TileMap))
	{
		return true;
	}
	
	return false;
}

bool AIPlayer::CheckPathBlocked(std::vector<std::vector<Tile>>&a_TileMap)
{
	auto TempPath =  m_EntityPaths[m_ControlledEntity];

	for (auto it = TempPath.begin(); it != TempPath.end(); it++)
	{
		if (!a_TileMap[(*it).x][(*it).y].getPassable())
		{
			return true;
		}
	}
	return false;
}

bool AIPlayer::CheckTargetMoved(std::vector<std::vector<Tile>>&a_TileMap)
{
	auto TargetPath = m_EntityPaths[m_TargetedEntity];
	if (a_TileMap[TargetPath.back().x][TargetPath.back().y].GetOccupant() != m_TargetedEntity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

EntityClass* AIPlayer::SearchForTargetedEntity(std::vector<std::vector<Tile>>& a_TileMap)
{
	//go through every tile searching for closest enemy entity to move towards or attack
	EntityClass* NewTarget = nullptr;
	int TargetDistance = -1;
	for (int x = 0; x < a_TileMap.size()-1; x++)
	{
		for (int y = 0; y < a_TileMap[x].size()-1; y++)
		{
			//check to see if there is an entity here
			if (a_TileMap[x][y].EntityPresent())
			{
				if (a_TileMap[x][y].GetOccupant()->GetSide() != m_ControlledEntity->GetSide())
				{
					//std::cout << "found a potential target" << std::endl;
					//construct a path and if it is less than the previous path we want to target this entity instead
					PathFinder TempP;
					auto SourceLocation = m_ControlledEntity->GetLocation();
					//std::cout << "Trying to use DIJK to find path to target" << std::endl;
					auto TempPath = TempP.UseDijkstra(a_TileMap, SourceLocation.first, SourceLocation.second, x, y);
					if (TempP.GetTotalDistance(x, y) < TargetDistance || TargetDistance == -1)
					{
						NewTarget = a_TileMap[x][y].GetOccupant();
						TargetDistance = TempP.GetTotalDistance(x, y);
						std::cout << "New target is" << a_TileMap[x][y].GetOccupant()->GetName() << std::endl;
					}
				}
			}//end if entity present
		}//end y loop
	}//end x loop
	//std::cout << "Target alg end" << std::endl;
	return NewTarget;
}

Direction AIPlayer::FindDirection()
{
	int xSource = (m_ControlledEntity->GetLocation().first);
	int ySource = (m_ControlledEntity->GetLocation().second);

	int xTarget = (m_TargetedEntity->GetLocation().first);
	int yTarget = (m_TargetedEntity->GetLocation().second);

	int xDiff = xSource - xTarget;
	int yDiff = ySource - yTarget;

	//going west
	if (xDiff > 0)
	{
		//north is positive yDiff
		if (yDiff > 0)
		{
			std::cout << "Facing NorthWest" << std::endl;
			return NORTHWEST;
		}
		//south is negative yDiff
		else if (yDiff < 0)
		{
			std::cout << "Facing SouthWest" << std::endl;
			return SOUTHWEST;
		}
		//no change
		else if (yDiff == 0)
		{
			std::cout << "Facing West" << std::endl;
			return WEST;
		}
	}
	//east
	else if (xDiff < 0)
	{
		//north is positive yDiff
		if (yDiff > 0)
		{
			std::cout << "Facing Northeast" << std::endl;
			return NORTHEAST;
		}
		//south is negative yDiff
		else if (yDiff < 0)
		{
			std::cout << "Facing southeast" << std::endl;
			return SOUTHEAST;
		}
		//no change
		else if (yDiff == 0)
		{
			std::cout << "Facing east" << std::endl;
			return EAST;
		}
	}
	//no change
	else if (xDiff == 0)
	{
		//north is positive yDiff
		if (yDiff > 0)
		{
			std::cout << "Facing north" << std::endl;
			return NORTH;
		}
		//south is negative yDiff
		else if (yDiff < 0)
		{
			std::cout << "Facing south" << std::endl;
			return SOUTH;
		}
		//no change
		else if (yDiff == 0)
		{
			std::cout << "Facing stationary" << std::endl;
			return STATIONARY;
		}
	}
	return STATIONARY;
}

Direction AIPlayer::FindDirection(int a_xTarget, int a_yTarget)
{
	int xSource = (m_ControlledEntity->GetLocation().first);
	int ySource = (m_ControlledEntity->GetLocation().second);

	int xDiff = xSource - a_xTarget;
	int yDiff = ySource - a_yTarget;

	//going west
	if (xDiff > 0)
	{
		//north is positive yDiff
		if (yDiff > 0)
		{
			return NORTHWEST;
		}
		//south is negative yDiff
		else if (yDiff < 0)
		{
			return SOUTHWEST;
		}
		//no change
		else if (yDiff == 0)
		{
			return WEST;
		}
	}
	//east
	else if (xDiff < 0)
	{
		//north is positive yDiff
		if (yDiff > 0)
		{
			return NORTHEAST;
		}
		//south is negative yDiff
		else if (yDiff < 0)
		{
			return SOUTHEAST;
		}
		//no change
		else if (yDiff == 0)
		{
			return EAST;
		}
	}
	//no change
	else if (xDiff == 0)
	{
		//north is positive yDiff
		if (yDiff > 0)
		{
			return NORTH;
		}
		//south is negative yDiff
		else if (yDiff < 0)
		{
			return SOUTH;
		}
		//no change
		else if (yDiff == 0)
		{
			return STATIONARY;
		}
	}
	return STATIONARY;
}

std::vector<GraphLocation> AIPlayer::DevelopPathing(std::vector<std::vector<Tile>> &a_TileMap)
{
	//use dijkstra's algo and develop the path from the controlled entity to the targeted entity, assume we have these
	PathFinder NewPath;
	int xSource = m_ControlledEntity->GetLocation().first;
	int ySource = m_ControlledEntity->GetLocation().second;

	int xTarget = m_TargetedEntity->GetLocation().first;
	int yTarget = m_TargetedEntity->GetLocation().second;
	//std::cout << "CallingDijkstraAlg:" << std::endl;
	m_EntityPaths[m_ControlledEntity] = NewPath.UseDijkstra(a_TileMap, xSource, ySource, xTarget, yTarget);
	//std::cout << "Path developed" << std::endl;
	
	return m_EntityPaths[m_ControlledEntity];
}