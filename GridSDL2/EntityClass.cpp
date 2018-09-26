#include "EntityClass.h"
#include "StaticFunctions.h"
#include "Texture.h"
#include "Tile.h"
#include "PickupItemsMenu.h"
#include "EncounterInstance.h"
#include "Armor.h"
#include "InventoryMenu.h"
#include "FeatMenu.h"
#include "PathfindingAlgorithm.h"

EntityClass::EntityClass(int a_xInitial, int a_yInitial, int a_HPMax=0, int a_HPCurrent=0)
{	
	this->m_HitPointMaximum = a_HPMax;
	this->m_HitPoints = a_HPCurrent;
	m_Box.x = 0;
	m_Box.y = 0;
	m_Box.w = m_ENTITY_WIDTH;
	m_Box.h = m_ENTITY_HEIGHT;
//	SetLocation(a_xInitial, a_yInitial);
}

EntityClass::EntityClass()
{
	m_Box.x = 0;
	m_Box.w = m_ENTITY_WIDTH;
	m_Box.h = m_ENTITY_HEIGHT;
	std::cout << "Entity size, H, w : " << m_Box.w << " " << m_Box.h << std::endl;
}

/*
EntityClass::~EntityClass()
{
	for (auto it = m_Equipment.begin(); it != m_Equipment.end(); it++)
	{
		delete (*it).second;
		(*it).second = nullptr;
	}
	delete m_Texture;
	delete m_SideTexture;
}
*/
void EntityClass::SetTexture(std::map<std::string, LTexture*> &a_TextureMap, std::string a_Path)
{
	if (a_TextureMap.count(a_Path + "\\" + m_PathTexture)) 
	{
		m_Texture = a_TextureMap[a_Path + "\\" + m_PathTexture];
		//std::cout << m_PathTexture << " Loaded into " << m_EntityName <<  std::endl;
	}
	else
	{
		std::cout << "No matching texture found " << a_Path << "\\" << m_PathTexture << std::endl;
		m_Texture = a_TextureMap[a_Path + "\\" + "QuestionMark.png"];
	}

	if (m_TeamSide != 1)
	{
		m_SideTexture = a_TextureMap[a_Path + "\\" + "red.png"];
	}
	else
	{
		m_SideTexture = a_TextureMap[a_Path + "\\" + "blue.png"];
	}
	
}

LTexture* EntityClass::GetTexture()
{
	return m_Texture;
}

/*----------------START MUTATORS-----------------*/


void EntityClass::AddHitPoints(int a_addition)
{
	this->m_HitPoints += a_addition;
	if (this->m_HitPoints > m_HitPointMaximum)
	{
		this->m_HitPoints = m_HitPointMaximum;
	}
}

std::string EntityClass:: GetName()
{
	return m_EntityName;
}


/*----------------END MUTATORS-----------------*/

bool EntityClass::EntityMeleeAttack(std::vector<std::vector<Tile>> &a_TileVector, EncounterInstance& a_Instance)
{
	//std::cout << "Im attacking now" << std::endl;
	//call EntityMeleeAttackTile, if not null call selected attack roll
	EntityClass* Target = EntityMeleeAttackTile(a_TileVector);
	if (Target != nullptr)
	{
		if (m_ActionLeft == true)
		{

			MeleeAttack Attack;
			if (!m_AttackBothHands)
			{
				Attack.AttackNormal(*this, *Target, a_Instance);
				this->m_ActionLeft = false;
			}
		}
		else
		{
			std::cout << "No attack left " << std::endl;
		}
	}

	return false;
}

bool EntityClass::EntityRangedAttack(std::vector<std::vector<Tile>> &a_TileVector, EncounterInstance& a_Instance)
{
	//call EntityRangedAttackTile, if not null call selected attack roll, if null then return false
	EntityClass* Target = EntityRangedAttackTile(a_TileVector, a_Instance);
	if (Target != NULL)
	{
		if (m_ActionLeft == true)
		{
			std::cout << Target->m_EntityName << std::endl;
			RangedAttack Attack;
			if (!m_AttackBothHands)
			{
				Attack.AttackNormal(*this, *Target, a_Instance);
				this->m_ActionLeft = false;
			}
			return true;
		}
		else
		{
			std::cout << "No attacks left" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "Can't attack empty tile" << std::endl;
	}

	return false;
}
bool EntityClass::EntityRangedAttack(std::vector<std::vector<Tile>> &a_TileVector, EncounterInstance& a_Instance, EntityClass* a_Target)
{
	//we have a target, let us attack
	if (a_Target != NULL)
	{
		std::cout << a_Target->m_EntityName << std::endl;
		RangedAttack Attack;
		if (!m_AttackBothHands)
		{
			Attack.AttackNormal(*this, *a_Target, a_Instance);
		}
	}
	else
	{
		std::cout << "Can't attack empty tile" << std::endl;
	}

	return false;
}

EntityClass* EntityClass::EntityMeleeAttackTile(std::vector<std::vector<Tile>> &a_TileVector)
{
	if (m_MoveDirection == STATIONARY)
	{
		return NULL;
	}

	switch (m_MoveDirection)
	{
		//check if we can attack the next spot
		//attack the tile if it exists (and anyone in it)
		//change moveDir to stationary, set to move mode
	case NORTH:
		m_FaceDirection = NORTH;
		if (m_Location.second != 0)
		{
			if (a_TileVector[m_Location.first][m_Location.second - 1].GetOccupant()!=nullptr)
			{
				std::cout << "Attacking: " << a_TileVector[m_Location.first][m_Location.second - 1].GetOccupant()->GetName() << std::endl;
				m_MoveDirection = STATIONARY;
				return a_TileVector[m_Location.first][m_Location.second - 1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				m_MoveDirection = STATIONARY;
				return nullptr;
			}

		}
		else
		{
			std::cout << "Cannot Attack There" << std::endl;
			m_MoveDirection = STATIONARY;
			return nullptr;
		}
		break;

	case EAST:
		m_FaceDirection = EAST;
		if (m_Location.first < a_TileVector.size() - 1)
		{
			if (a_TileVector[m_Location.first+1][m_Location.second].GetOccupant())
			{
				std::cout << "Attacking: " << a_TileVector[m_Location.first+1][m_Location.second].GetOccupant()->GetName() << std::endl;
				m_MoveDirection = STATIONARY;
				return a_TileVector[m_Location.first + 1][m_Location.second].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile " << std::endl;
				m_MoveDirection = STATIONARY;
				return nullptr;
			}

		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			m_MoveDirection = STATIONARY;
			return nullptr;
		}
		break;

	case SOUTH:
		m_FaceDirection = SOUTH;
		if (m_Location.second < a_TileVector[0].size() - 1)
		{
			if (a_TileVector[m_Location.first][m_Location.second + 1].GetOccupant())
			{
				std::cout << "Attacking: " << a_TileVector[m_Location.first][m_Location.second + 1].GetOccupant()->GetName() << std::endl;
				m_MoveDirection = STATIONARY;
				return a_TileVector[m_Location.first][m_Location.second + 1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				m_MoveDirection = STATIONARY;
				return nullptr;
			}

			}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			m_MoveDirection = STATIONARY;
			return nullptr;
		}
		
		break;

	case WEST:
		m_FaceDirection = WEST;

		if (m_Location.first != 0)
		{
			if (a_TileVector[m_Location.first-1][m_Location.second].GetOccupant())
			{
				std::cout << "Attacking: " << a_TileVector[m_Location.first - 1][m_Location.second].GetOccupant()->GetName() << std::endl;
				m_MoveDirection = STATIONARY;
				return a_TileVector[m_Location.first - 1][m_Location.second].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				m_MoveDirection = STATIONARY;
				return nullptr;
			}
		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			m_MoveDirection = STATIONARY;
			return nullptr;
		}
		break;

	case NORTHWEST:
		m_FaceDirection = NORTHWEST;

		if (m_Location.first != 0
			&&
			m_Location.second!=0)
		{
			if (a_TileVector[m_Location.first - 1][m_Location.second-1].GetOccupant())
			{
				std::cout << "Attacking: " << a_TileVector[m_Location.first - 1][m_Location.second-1].GetOccupant()->GetName() << std::endl;
				m_MoveDirection = STATIONARY;
				return a_TileVector[m_Location.first - 1][m_Location.second-1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				m_MoveDirection = STATIONARY;
				return nullptr;
			}
		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			m_MoveDirection = STATIONARY;
			return nullptr;
		}
		break;

	case SOUTHWEST:
		m_FaceDirection = SOUTHWEST;

		if (m_Location.first !=0 
			&&
			m_Location.second <(a_TileVector[m_Location.first].size()-1))
		{
			if (a_TileVector[m_Location.first - 1][m_Location.second + 1].GetOccupant())
			{
				std::cout << "Attacking: " << a_TileVector[m_Location.first - 1][m_Location.second + 1].GetOccupant()->GetName() << std::endl;
				m_MoveDirection = STATIONARY;
				return a_TileVector[m_Location.first - 1][m_Location.second + 1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				m_MoveDirection = STATIONARY;
				return nullptr;
			}
		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			m_MoveDirection = STATIONARY;
			return nullptr;
		}
		break;

	case SOUTHEAST:
		m_FaceDirection = SOUTHEAST;

		if (m_Location.first <(a_TileVector.size()-1)
			&&
			m_Location.second <(a_TileVector[m_Location.first].size() - 1))
		{
			if (a_TileVector[m_Location.first + 1][m_Location.second + 1].GetOccupant())
			{
				std::cout << "Attacking: " << a_TileVector[m_Location.first + 1][m_Location.second + 1].GetOccupant()->GetName() << std::endl;
				m_MoveDirection = STATIONARY;
				return a_TileVector[m_Location.first + 1][m_Location.second + 1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				m_MoveDirection = STATIONARY;
				return nullptr;
			}
		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			m_MoveDirection = STATIONARY;
			return nullptr;
		}
		break;

	case NORTHEAST:
		m_FaceDirection = NORTHEAST;

		if (m_Location.first <(a_TileVector.size() - 1)
			&&
			m_Location.second !=0)
		{
			if (a_TileVector[m_Location.first + 1][m_Location.second -1].GetOccupant())
			{
				std::cout << "Attacking: " << a_TileVector[m_Location.first + 1][m_Location.second -1].GetOccupant()->GetName() << std::endl;
				m_MoveDirection = STATIONARY;
				return a_TileVector[m_Location.first + 1][m_Location.second - 1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				m_MoveDirection = STATIONARY;
				return nullptr;
			}
		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			m_MoveDirection = STATIONARY;
			return nullptr;
		}
		break;


	} //end switch statement
	
	m_MoveDirection = STATIONARY;
	return nullptr;
}

EntityClass* EntityClass::EntityRangedAttackTile(std::vector<std::vector<Tile>> &a_TileVector, EncounterInstance &a_Instance)
{
	return a_TileVector[a_Instance.GetTargetSystem().GetLocation().first][a_Instance.GetTargetSystem().GetLocation().second].GetOccupant();
}

int EntityClass::GetTotalDamageReduction()
{
	int TotalDamageReduction = 0;
	//go through equipment and add up damage reduction.
	for (auto it = m_Equipment.begin(); it != m_Equipment.end(); it++)
	{
		if ((*it).second != NULL)
		{
			TotalDamageReduction += (*it).second->GetDamageReduction();
		}
	}
	//add together, return total

	return TotalDamageReduction;
}

int EntityClass::GetArmorClass()
{
//	std::cout << m_EntityName << " has armor class of " << m_ArmorClass << std::endl;
	m_ArmorClass = UpdateArmorClass();
	return m_ArmorClass;
}

int EntityClass::UpdateArmorClass()
{
	int tempAC = 10;
	tempAC += GetAbilityModifier(DEX);
	
	for (auto it = m_Equipment.begin(); it != m_Equipment.end(); it++)
	{
		if ((*it).second != nullptr)
		{
			tempAC+=(*it).second->GetArmorBonus();
		}
	}
	
	for (auto it = m_Feats.begin(); it != m_Feats.end(); it++)
	{
		if ((*it).GetDodgeBonusAdd() > 0)
		{
			tempAC += (*it).GetDodgeBonusAdd();
		}
		if ((*it).GetDodgeBonusSubtract() > 0)
		{
			tempAC -= (*it).GetDodgeBonusSubtract();
		}
	}
	return tempAC;
}

ObjectClass* EntityClass::GetEquipmentInSlot(BodyLocation a_Location)
{
	if (m_Equipment.find(a_Location) != m_Equipment.end())
	{
		return m_Equipment[a_Location];
	}
	return nullptr;
}

void EntityClass::ClearEquipmentInSlot(BodyLocation a_Location)
{
	if (m_Equipment.find(a_Location) != m_Equipment.end())
	{
		delete m_Equipment[a_Location];
		m_Equipment[a_Location] = nullptr;
	}
}

void EntityClass::GenerateUnarmedStrike(EncounterInstance &a_Instance)
{
	this->m_UnarmedStrike = a_Instance.GetObjectFromMasterList("Unarmed Strike");

}
void EntityClass::TwoHandWeapon()
{
	if (m_Equipment[MAINHAND] != NULL)
	{
		if (m_Equipment[OFFHAND] != NULL)
		{
			//this means that we are already grasping the wep in two hands we will stop
			if (m_Equipment[OFFHAND]==m_Equipment[MAINHAND])
			{
				std::cout << "Offhand Let go" << std::endl;
				m_Equipment[OFFHAND] = NULL;
			}
			else
			{
				std::cout << "Both Hands Occupied" << std::endl;
				return;
			}	
		}
		else
		{
			m_Equipment[OFFHAND] = m_Equipment[MAINHAND];
			std::cout << "Weapon Grasped in both hands" << std::endl;
		}
	} // end mainhand !=null
	else
	{
		if (m_Equipment[OFFHAND] != NULL)
		{
			std::cout << "Weapon Grasped in both hands" << std::endl;
			m_Equipment[MAINHAND] = m_Equipment[OFFHAND];
		}
	}
}

std::vector<FeatClass> EntityClass::GetActiveFeats()
{
	std::vector<FeatClass>ActiveFeats;
	for (auto it = m_Feats.begin(); it != m_Feats.end(); it++)
	{
		if ((*it).IsActive())
		{
			ActiveFeats.push_back(*it);
		}
	}
	return ActiveFeats;
}

std::vector<FeatClass*> EntityClass::GetToggleableFeats()
{
	std::vector<FeatClass*> ToggleableFeats;
	for (auto it = m_Feats.begin(); it != m_Feats.end(); it++)
	{
	//	std::cout << "Feat" << (*it).GetName();
		if ((*it).IsToggleAbility())
		{
			FeatClass* TempPtr = &(*it);
			//std::cout << "is toggle" << std::endl;
			ToggleableFeats.push_back(TempPtr);
			continue;
		}
		//std::cout << " not toggle" << std::endl;
	}
/*
	for (auto it = ToggleableFeats.begin(); it != ToggleableFeats.end(); it++)
	{
		std::cout << (*it)->GetName() << std::endl;
	}
	*/
	return ToggleableFeats;
}

bool EntityClass::DoesSlotExist(BodyLocation a_Location)
{
	bool temp = false;
	if (m_Equipment.find(a_Location) != m_Equipment.end())
	{
		temp = true;
	}
	return temp;
}

void EntityClass::EntityDeath(EncounterInstance & a_Instance)
{
	auto location = this->GetLocation();
	//std::cout << "Dropping items" << std::endl;
	DropAllWornItems(a_Instance.GetTileMap()[location.first][location.second], a_Instance.GetTileMap());
	//std::cout << "Dropping items from backpack" << std::endl;
	m_BackPack.DropAllAtTile(location.first, location.second, a_Instance.GetTileMap()[location.first][location.second], a_Instance.GetTileMap());
	//std::cout << "Removing from init" << std::endl;
	a_Instance.RemoveDeadFromLists();
	//std::cout << "Clearing occupant" << std::endl;
	a_Instance.GetTileMap()[location.first][location.second].ClearOccupant();
	delete this;
}

void EntityClass::DropAllWornItems(Tile& a_passedTile, std::vector<std::vector<Tile>> &a_TileMap)
{
	for (auto it = m_Equipment.begin(); it != m_Equipment.end(); it++)
	{
		if ((*it).second != nullptr)
		{
			(*it).second->SetLocation(this->GetLocation().first, this->GetLocation().second, a_TileMap);
			(*it).second == nullptr;
		}
	}
}

bool EntityClass::EquipAsWeapon(ObjectClass* a_Weapon)
{
	if (a_Weapon->GetTwoHanded())
	{
		if (GetEquipmentInSlot(MAINHAND) == nullptr && GetEquipmentInSlot(OFFHAND) == nullptr)
		{
			if (EquipMainHandWeapon(a_Weapon)==true && EquipOffHandWeapon(a_Weapon)==true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false; //unable to equip, one hand is busy
		}
	}
	else
	{
		if (GetEquipmentInSlot(MAINHAND) ==nullptr || GetEquipmentInSlot(OFFHAND) == nullptr)
		{
			
			if (EquipMainHandWeapon(a_Weapon)==false)
			{
			
				if (EquipOffHandWeapon(a_Weapon)==false)
				{
				
					return false;
				}
				else
				{
					return true;
				}
			}
			else 
			{
				return false;
			}
		}
	}
	return false;
}

bool EntityClass::EquipMainHandWeapon(ObjectClass* a_Weapon)
{
	if (GetEquipmentInSlot(MAINHAND) == nullptr)
	{
		std::cout << "Mainhand Free" << std::endl;
		m_Equipment.find(MAINHAND)->second = a_Weapon;
		return true; //successfull equip
	}
	else
	{
		std::cout << "Mainhand Occupied EquipManhand" << std::endl;
		return false;
	}
}

bool EntityClass::EquipOffHandWeapon(ObjectClass* a_Weapon)
{
	std::cout << "Trying to equip offhand" << std::endl;
	if (GetEquipmentInSlot(OFFHAND) == nullptr)
	{
		std::cout << "Offhand free" << std::endl;
		m_Equipment.find(OFFHAND)->second = a_Weapon;
		return true; // succesfull equip
	}
	else
	{
		std::cout << "offhand occupied" << std::endl;
		return false;
	}
}

//void EntityClass::HandleTurn (SDL_Event& a_event, EncounterInstance & a_Instance)

void EntityClass::handleEvent(SDL_Event& a_event, EncounterInstance & a_Instance)
{
	
	//If a key was pressed
	if (a_event.type == SDL_KEYDOWN && a_event.key.repeat == 0)
	{
		
		//change the a_location
		switch (a_event.key.keysym.sym)
		{
			//move to encounter handle
		case SDLK_i: DisplayEntireInventory(); break;

			//end move to encounter handle
		case SDLK_s:m_MoveDirection = STATIONARY; break;
		case SDLK_w:m_MoveDirection = NORTH; break;
		case SDLK_a:m_MoveDirection = WEST; break;
		case SDLK_d:m_MoveDirection = EAST; break;
		case SDLK_x:m_MoveDirection = SOUTH; break;
		
		case SDLK_e:m_MoveDirection = NORTHEAST; break;
		case SDLK_q:m_MoveDirection = NORTHWEST; break;
		case SDLK_z:m_MoveDirection = SOUTHWEST; break;
		case SDLK_c:m_MoveDirection = SOUTHEAST; break;

		case SDLK_UP: m_MoveDirection = NORTH; break;
		case SDLK_DOWN: m_MoveDirection = SOUTH; break;
		case SDLK_LEFT: m_MoveDirection = WEST; break;
		case SDLK_RIGHT: m_MoveDirection = EAST; break;
		case SDLK_1: 
			if (GetControlMode() != MELEEATTACKMODE && GetControlMode()!=NOCONTROLMODE) 
			{
			SetControlMode(MELEEATTACKMODE);
			}
			else if(GetControlMode()!=NOCONTROLMODE)
			{
				SetControlMode(MOVEMODE);
			}
			std::cout << "Switching attack mode" << std::endl;
			break;
		case SDLK_2:
		{
			if (this->GetEquipmentInSlot(MAINHAND) != nullptr && this->GetEquipmentInSlot(MAINHAND)->IsRangedWeapon())
			{
					SetControlMode(RANGEDATTACKMODE);
					a_Instance.GetTargetSystem().SetActive(true);
					break;
			}
			else if (this->GetEquipmentInSlot(OFFHAND) != nullptr && this->GetEquipmentInSlot(OFFHAND)->IsRangedWeapon())
			{
					SetControlMode(RANGEDATTACKMODE);
					a_Instance.GetTargetSystem().SetActive(true);
					break;
			}
			std::cout << "No ranged weapon found" << std::endl;
			break;
		}
		case SDLK_3:
			if (GetControlMode() != PICKUPMODE && GetControlMode() != NOCONTROLMODE)
			{
				SetControlMode(PICKUPMODE);
			}
			else if(GetControlMode()!=NOCONTROLMODE)
			{
				SetControlMode(MOVEMODE);
			}
			break;
		case SDLK_4:
			if (GetControlMode() != INVENTORYMODE && GetControlMode() != NOCONTROLMODE)
			{
				SetControlMode(INVENTORYMODE);
			}
			else if (GetControlMode() != NOCONTROLMODE)
			{
				SetControlMode(MOVEMODE);
			}
			break;
		case SDLK_5:
			if (GetControlMode() != FEATOPTIONMODE && GetControlMode() != NOCONTROLMODE)
			{
				SetControlMode(FEATOPTIONMODE);
			}
			else
			{
				SetControlMode(MOVEMODE);
			}
			break;
		case SDLK_9:
			this->DisplayFeats();
			break;

		case SDLK_o:
			std::cout << "attempting to allow AI to take a turn" << std::endl << std::endl;
			SetControlMode(AIMODE);
			break;

		case SDLK_p:
			//std::cout << "Attempting to pathfind using BFS" << std::endl << std::endl;;
			//PathFinder BFS;
			//BFS.TestBreadthFirst(a_Instance.GetTileMap(), this->GetLocation().first, this->GetLocation().second);

			std::cout << "Attempting to pathfind using DIJK" << std::endl << std::endl;
			PathFinder DIJK;
			DIJK.UseDijkstra(a_Instance.GetTileMap(), this->GetLocation().first, this->GetLocation().second, 4, 5);
			break;

		}
	
	}
}

bool EntityClass::move(std::vector<std::vector<Tile>> &a_TileVector)
{
	if (m_MoveDirection == STATIONARY)
	{
		a_TileVector[m_Location.first][m_Location.second].SetOccupant(*this);
		return false;
	}

	if (this->m_MovementLeft <= 0)
	{
		//std::cout << "Not enough movement points remaining" << std::endl;
		m_MoveDirection = STATIONARY;
		return false;
	}

	bool success = false;
	switch (m_MoveDirection)
	{	
	//check if we can move to the tile to next spot
	//move to the tile if we can
	//change moveDir to stationary
	case NORTH:
		m_FaceDirection = NORTH;
		if (m_Location.second != 0 && a_TileVector[m_Location.first][m_Location.second-1].getPassable())
		{
			a_TileVector[m_Location.first][m_Location.second].ClearOccupant();
			m_Location.second--;
			m_MovementLeft-=1;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		a_TileVector[m_Location.first][m_Location.second].SetOccupant(*this);
		
		break;

	case NORTHEAST:
		m_FaceDirection = NORTHEAST;
		if (m_Location.second != 0 && a_TileVector[m_Location.first][m_Location.second - 1].getPassable()
			&&
			m_Location.first < a_TileVector.size() - 1 && a_TileVector[m_Location.first + 1][m_Location.second].getPassable()
			&&
			a_TileVector[m_Location.first + 1][m_Location.second - 1].getPassable()
			&& m_MovementLeft>=1 )
		{
			a_TileVector[m_Location.first][m_Location.second].ClearOccupant();
			m_Location.first++;
			m_Location.second--;
			m_MovementLeft -= 1.5;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there, or not enough movement remaining" << std::endl;
			success = false;
		}
		a_TileVector[m_Location.first][m_Location.second].SetOccupant(*this);
		break;

	case EAST: 
		m_FaceDirection = EAST;
		if (m_Location.first < a_TileVector.size()-1 && a_TileVector[m_Location.first+1][m_Location.second].getPassable())
		{
			a_TileVector[m_Location.first][m_Location.second].ClearOccupant();
			m_Location.first++;
			m_MovementLeft -= 1;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		a_TileVector[m_Location.first][m_Location.second].SetOccupant(*this);
		break;

	case SOUTHEAST:
		m_FaceDirection = SOUTHEAST;
		if (m_Location.first < a_TileVector.size() - 1 && a_TileVector[m_Location.first + 1][m_Location.second].getPassable()
			&&
			m_Location.second < a_TileVector[0].size() - 1 && a_TileVector[m_Location.first][m_Location.second + 1].getPassable()
			&&
			a_TileVector[m_Location.first + 1][m_Location.second + 1].getPassable()
			&&
			m_MovementLeft >= 1)
		{
			a_TileVector[m_Location.first][m_Location.second].ClearOccupant();
			m_Location.first++;
			m_Location.second++;
			m_MovementLeft -= 1.5;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there or not enough movement left" << std::endl;
			success = false;
		}
		a_TileVector[m_Location.first][m_Location.second].SetOccupant(*this);
		break;

	case SOUTH: 
		m_FaceDirection = SOUTH;
		if (m_Location.second < a_TileVector[0].size() - 1 && a_TileVector[m_Location.first][m_Location.second+1].getPassable())
		{
			a_TileVector[m_Location.first][m_Location.second].ClearOccupant();
			m_Location.second++;
			m_MovementLeft -= 1;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		a_TileVector[m_Location.first][m_Location.second].SetOccupant(*this);
		break;

	case SOUTHWEST:
		m_FaceDirection = SOUTHWEST;
		if (m_Location.second < a_TileVector[0].size() - 1 && a_TileVector[m_Location.first][m_Location.second + 1].getPassable()
			&&
			m_Location.first != 0 && a_TileVector[m_Location.first - 1][m_Location.second].getPassable()
			&&
			a_TileVector[m_Location.first - 1][m_Location.second + 1].getPassable()
			&&
			m_MovementLeft >= 1)
		{
			a_TileVector[m_Location.first][m_Location.second].ClearOccupant();
			m_Location.second++;
			m_Location.first--;
			m_MovementLeft -= 1.5;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there or not enough movement left" << std::endl;
			success = false;
		}
		a_TileVector[m_Location.first][m_Location.second].SetOccupant(*this);
		break;

	case WEST: 
		m_FaceDirection = WEST;

		if (m_Location.first !=0 && a_TileVector[m_Location.first - 1][m_Location.second].getPassable())
		{
			a_TileVector[m_Location.first][m_Location.second].ClearOccupant();
			m_Location.first--;
			m_MovementLeft -= 1;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		a_TileVector[m_Location.first][m_Location.second].SetOccupant(*this);
		break;

	case NORTHWEST:
		m_FaceDirection = NORTHWEST;

		if (m_Location.first != 0 && a_TileVector[m_Location.first - 1][m_Location.second].getPassable()
			&&
			m_Location.second != 0 && a_TileVector[m_Location.first][m_Location.second - 1].getPassable()
			&&
			a_TileVector[m_Location.first - 1][m_Location.second - 1].getPassable()
			&&
			m_MovementLeft >= 1)
		{
			a_TileVector[m_Location.first][m_Location.second].ClearOccupant();
			m_Location.first--;
			m_Location.second--;
			m_MovementLeft -= 1.5;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there or not enough movement left" << std::endl;
			success = false;
		}
		a_TileVector[m_Location.first][m_Location.second].SetOccupant(*this);
		break;
	} //end switch statement

	//std::cout << "Man moved in function, setting rend a_location " << std::endl;
	//std::cout << "Attempted to move" << std::endl;
	if (success)
	{
		std::cout << "Success" << std::endl;
	}
	else
	{
		std::cout << "Failed move" << std::endl;
	}
	SetRendLocation(a_TileVector);
	m_MoveDirection = STATIONARY;
	return success;
	}

void EntityClass::setCamera(SDL_Rect& a_camera)
{
	//Center the m_camera over the entity
	a_camera.x = (m_Box.x + m_ENTITY_WIDTH / 2) - g_SCREEN_WIDTH *0.333;
	a_camera.y = (m_Box.y + m_ENTITY_HEIGHT / 2) - g_SCREEN_HEIGHT*0.375;

	//Keep the m_camera in bounds
	if (a_camera.x < 0)
	{
		a_camera.x = 0;
	}
	if (a_camera.y < 0)
	{
		a_camera.y = 0;
	}
	if (a_camera.x > g_LEVEL_WIDTH - a_camera.w)
	{
		a_camera.x = g_LEVEL_WIDTH - a_camera.w;
	}
	if (a_camera.y > g_LEVEL_HEIGHT - a_camera.h)
	{
		a_camera.y = g_LEVEL_HEIGHT - a_camera.h;
	}
}

void EntityClass::SetLocation(int a_x, int a_y, std::vector < std::vector < Tile> > &a_TileMap)
{
	m_Location.first = a_x;
	m_Location.second = a_y;
	a_TileMap[a_x][a_y].SetOccupant(*this);
	this->SetRendLocation(a_TileMap);
}

std::pair<int, int> EntityClass::GetLocation()
{
	return m_Location;
}

void EntityClass::SetRendLocation(std::vector<std::vector<Tile>> &a_TileVector)
{
	std::pair<int, int> tempLoc = CalcRendLocation(a_TileVector);
	m_Box.x = tempLoc.first;
	m_Box.y = tempLoc.second;
	//std::cout << "New rend a_location=" << m_Box.a_x << " " << m_Box.a_y << std::endl;
}

std::pair<int, int> EntityClass::CalcRendLocation(std::vector<std::vector<Tile>> &a_TileVector)
{
	//std::cout << "Calc rend a_location" << std::endl;
	std::pair <int, int> RetVal;
	int xTempLoc = GetLocation().first;
	int yTempLoc = GetLocation().second;

	std::cout << xTempLoc << "  " << yTempLoc << std::endl;

	int xOffset = 0;
	int yOffset = 0;
	//std::cout << "Accessing vector" << std::endl;
	RetVal.first=a_TileVector[xTempLoc][yTempLoc].GetXRenderPos();
	RetVal.second = a_TileVector[xTempLoc][yTempLoc].GetYRenderPos();

	xOffset = 0.5 * (a_TileVector[xTempLoc][yTempLoc].GetWidth() - m_ENTITY_WIDTH);
	yOffset = 0.5 * (a_TileVector[xTempLoc][yTempLoc].GetWidth() - m_ENTITY_HEIGHT);

	RetVal.first = RetVal.first + xOffset;
	RetVal.second = RetVal.second + yOffset;

	return RetVal;
}

void EntityClass::render(SDL_Rect& a_camera, SDL_Renderer *& a_Renderer)
{
	double tempangle;
	switch (m_FaceDirection)
	{
	case NORTH:
		tempangle = 180;
		break;

	case NORTHEAST:
		tempangle = 225;
		break;

	case NORTHWEST:
		tempangle = 135;
		break;

	case WEST:
		tempangle = 90;
		break;
	
	case EAST:
		tempangle = 270;
		break;

	case SOUTHEAST:
		tempangle = 315;
		break;

	case SOUTHWEST:
		tempangle = 45;
		break;

	case SOUTH:
		tempangle = 0;
		break;
	}
	//If the texture is on screen
	if (checkCollision(a_camera, m_Box))
	{
		//Show the texture
		m_Texture->renderEntity(m_Box.x - a_camera.x, m_Box.y - a_camera.y, a_Renderer, &m_Box, tempangle);
		m_SideTexture->renderEntity(m_Box.x - a_camera.x, m_Box.y - a_camera.y, a_Renderer, &m_Box, tempangle);
		//std::cout << " Entity size " << m_Box.h << " " << m_Box.w << std::endl;
	}
}

void EntityClass::SetPath(std::string a_Path)
{
	m_PathTexture = a_Path;
}

void EntityClass::SetName(std::string a_PassedName)
{
	m_EntityName = a_PassedName;
}

ControlMode EntityClass::GetControlMode()
{
	return this->m_ControlSetting;
}

void EntityClass::SetControlMode(ControlMode a_NewControl)
{
	this->m_ControlSetting = a_NewControl;
}

int EntityClass::GetAbilityModifier(AbilityScoreType a_ability)
{
	int temp = (int)(floor((m_AbilityScore[a_ability] - 10) / 2));
	//std::cout << "Checking dex, normal: " << temp << std::endl;
	if (a_ability == DEX && temp > GetMaxDex())
	{
		return GetMaxDex();
	}
	else
	{
		return temp;
	}
}

int EntityClass::GetMaxDex()
{
	int max=10;
	for (auto it = m_Equipment.begin(); it != m_Equipment.end(); it++)
	{
		if ((*it).second != nullptr)
		{
			if (max > (*it).second->GetMaxDexBonus())
			{
				max = (*it).second->GetMaxDexBonus();
			}		
		}
	}
	return max;
}
void EntityClass::RollInitiative()
{
	//get all active feat bonuses for initiative
	std::vector<FeatClass> m_TempFeats = GetActiveFeats();
	int TotalIntBonus = 0;
	for (auto it = m_TempFeats.begin(); it != m_TempFeats.end(); it++)
	{
		//no feats implemented with init yet
	}

	//add them to the existing dex bonus to get initiative bonus
	TotalIntBonus+= GetAbilityModifier(DEX);
	m_Initiative = (DiceRoll(D20) + TotalIntBonus);
	std::cout << m_EntityName << " rolled " << m_Initiative << " on initiative" << std::endl;

}

bool EntityClass::IsTwoHanding()
{
	if (m_Equipment[MAINHAND] == m_Equipment[OFFHAND])
	{
		//entity is holding the same weapon in both hands, definition of two handing
		return true;
	}
	else
	{
		//entity is not holding the same weapon in both hands, not two handing
		return false;
	}
}

void EntityClass::SwapWeaponHands()
{
	ObjectClass* TempStore;
	if (!this->IsTwoHanding()) //you cant swap two handed weapons to mainhand/offhand
	{
		if (GetEquipmentInSlot(MAINHAND) != NULL)
		{
			TempStore = GetEquipmentInSlot(MAINHAND);
			if (GetEquipmentInSlot(OFFHAND) != NULL)
			{
				m_Equipment[MAINHAND] = m_Equipment[OFFHAND];	
				m_Equipment[OFFHAND] = TempStore;
			}
			else
			{
				m_Equipment[OFFHAND] = TempStore;
				m_Equipment[MAINHAND] = NULL;
			}
		
		}
		else if (GetEquipmentInSlot(OFFHAND) != NULL)
		{
			m_Equipment[MAINHAND] = m_Equipment[OFFHAND];
			m_Equipment[OFFHAND] = NULL;
		}
	}
}

ObjectClass* EntityClass::PickupTile(std::vector<std::vector<Tile>> &a_TileVector)
{
	PickupItemsMenu PMenu;

	return PMenu.PickupItemsRun(a_TileVector[m_Location.first][m_Location.second]);
}

void EntityClass::EntityPickup(std::vector<std::vector<Tile>> &a_TileVector)
{
	ObjectClass* Target = PickupTile(a_TileVector);
	if (Target != NULL)
	{
		//pickup the a_item
		
		if (this->EquipObject(Target))
		{
			//std::cout << "Equipping successful" << std::endl;
			a_TileVector[Target->GetLocation().first][Target->GetLocation().second].RemoveObject(Target);
		}
	}
	//DisplayEntireInventory();
	return;
}

ObjectClass* EntityClass::EntityInventory(std::vector<std::vector<Tile>> &a_TileVector)
{
	InventoryMenu IMenu;
	return IMenu.InventoryMenuRun(*this, a_TileVector);

}
void EntityClass::EntityFeatMenu()
{
	FeatMenu FMenu;
	FMenu.FeatMenuRun(*this);
}
ItemContainer& EntityClass::GetBackPack()
{
	return m_BackPack;
}

void EntityClass::AddToBackPack(ObjectClass * a_object)
{
	m_BackPack.AddItem(a_object);
}

void EntityClass::UnEquip(BodyLocation a_location)
{
	if (m_Equipment[a_location]!=NULL)
	{
		AddToBackPack(m_Equipment[a_location]);
		m_Equipment[a_location] = NULL;
	}
}
bool EntityClass::EquipArmor(ObjectClass* a_item)
{
	if (m_Equipment[BODY] == NULL)
	{
		m_Equipment[BODY] = a_item;
		return true;
	}
	else 
	{
		return false;
	}
}

void EntityClass::DropFromEquipment(BodyLocation a_location, std::vector<std::vector<Tile>>&a_TileMap)
{
	if (m_Equipment[a_location] != NULL)
	{
		m_Equipment[a_location]->SetLocation(m_Location.first, m_Location.second, a_TileMap);
		m_Equipment[a_location] = NULL;
	}
}

void EntityClass::DropFromBackPack(int a_index, std::vector<std::vector<Tile>>& a_TileMap)
{
	if (a_index < 0)
	{
		return;
	}
	//get a_item at a_index
	if (m_BackPack.GetItemAtIndex(a_index)) //will not go if NULL
	{
		m_BackPack.GetItemAtIndex(a_index)->SetLocation(m_Location.first, m_Location.second, a_TileMap);
		m_BackPack.RemoveItemAtIndex(a_index);
	}
	//m_BackPack.DropItemAtIndex(int a_index);

}

bool EntityClass::EquipObject(ObjectClass* a_item)
{
	//std::cout << "Equipping " << a_item->GetName() << " in the " << BodyLocationTextMap[a_item->GetBodySlot()] << std::endl;
	if (a_item->GetBodySlot() == MAINHAND || a_item->GetBodySlot() == OFFHAND)
	{
	//	std::cout << "Attempting to equip as a weapon" << std::endl;
		if (this->EquipAsWeapon(a_item))
		{
			//std::cout << "Equipped as a legitimate weapon" << std::endl;
			return true;
		}
	}
	
	//BodyLocation a_location = a_item->GetBodySlot();
	if (DoesSlotExist(a_item->GetBodySlot())) 
	{
		if (this->GetEquipmentInSlot(a_item->GetBodySlot()) == NULL)
		{

			std::cout << "Added to m_Equipment" << std::endl;
			m_Equipment[a_item->GetBodySlot()] = a_item;
			return true;
		}
	}
	
	m_BackPack.AddItem(a_item);
	std::cout << "Added to backpack" << std::endl;
	return true;

//	std::cout << "Couldnt add it anywhere" << std::endl;
	return false;
}

void EntityClass::DisplayEntireInventory()
{
	for (auto iter = m_Equipment.begin(); iter != m_Equipment.end(); iter++)
	{
		if ((*iter).second != NULL)
		{
		std::cout << BodyLocationTextMap[iter->first] << "  " << (*iter).second->GetName() << std::endl;
		}
	}
	std::cout << "Backpack items: " << std::endl;
	m_BackPack.DisplayItems();
}

void EntityClass::SetAbilityScore(AbilityScoreType a_type, int a_amount)
{
	m_AbilityScore[a_type] = a_amount;
}

void EntityClass::DisplayAbilityScores()
{
	for (auto i = m_AbilityScore.begin(); i != m_AbilityScore.end(); i++)
	{
		std::cout << AbilityScoreTextMap[(*i).first] << "  " << (*i).second << std::endl;
	}
}

//loading functions
bool EntityClass::LoadEntity(std::string a_name, std::pair<int, int> a_Location, bool a_PlayerControlled, int a_side, EncounterInstance &a_Instance)
{
	a_name = a_Instance.GetCharacterFolderPath() +"\\"+ a_name;
	std::ifstream reader;
	std::cout << "Reader path: " << a_name << std::endl;
	reader.open(a_name);
	LoadNameDescriptionAndTexture(reader);
	LoadAbilityScores(reader);
	LoadEquipment(reader, a_Instance.GetObjectList());
	LoadFeats(reader, a_Instance);
	LoadProperties(reader);
	m_TeamSide = a_side;
	this->SetLocation(a_Location.first, a_Location.second, a_Instance.GetTileMap());
	//generate their unarmed attack
	GenerateUnarmedStrike(a_Instance);

	std::cout << "Loaded entity: " << this->m_EntityName << std::endl;
	return true;
}

bool EntityClass::LoadNameDescriptionAndTexture(std::ifstream &a_reader)
{
	a_reader.clear();
	a_reader.seekg(0, std::ios::beg);
	std::string line = "";
	bool GotName = false;
	bool GotTexture = false;
	bool GotDescription = false;
	while (getline(a_reader, line))
	{
		if (GotName &&GotTexture && GotDescription)
		{
			//std::cout<<"Loaded all of Name, Description, texture" << std::endl;
			break;
		}
		//remove comments
		if (line.find("//") != std::string::npos)
		{
			int endchar = line.find("//");
			line = line.substr(0, endchar);
			//	std::cout << "ResultAfterComment " << a_line << std::endl;
		}//end remove comments block

		if (line.find("Name:") != std::string::npos)
		{
			line = line.substr(line.find(":") + 1);
			this->SetName(line);
			GotName = true;
		}

		if (line.find("Texture:") != std::string::npos)
		{
			line = line.substr(line.find(":") + 1);
			this->m_PathTexture = line;
			GotTexture = true;
		}
	}
	return false;
}

bool EntityClass::LoadAbilityScores(std::ifstream &a_reader)
{
	a_reader.clear();
	a_reader.seekg(0, std::ios::beg);
	if (a_reader.is_open())
	{
		std::cout << "a_reader is open to path" << std::endl;
	}
	std::string line;
	while (getline(a_reader, line))
	{
	//	std::cout << a_line << std::endl;
		//remove comments
		if (line.find("//") != std::string::npos)
		{
			int endchar = line.find("//");
			line = line.substr(0, endchar);
			//	std::cout << "ResultAfterComment " << a_line << std::endl;
		}//end remove comments block

		//lowercase the string
		for (std::string::size_type i = 0; i < line.length(); ++i) {
			line[i] = tolower(line[i]);
		}

		int temp = 0;
		if (line.find("strength:") != std::string::npos)
		{
			line = line.substr(line.find(":") + 1);
			try
			{
				temp = stoi(line);
				SetAbilityScore(STR, temp);
				//std::cout << "Line: " << a_line << std::endl;
			}
			catch(std::exception const & error)
			{
				std::cout << "Error in abilityscoreload" << error.what() << std::endl;
			}

		}
		if (line.find("dexterity:") != std::string::npos)
		{
			line = line.substr(line.find(":") + 1);
			try
			{
				temp = stoi(line);
				SetAbilityScore(DEX, temp);
				//std::cout << "Line: " << a_line << std::endl;
			}
			catch (std::exception const & error)
			{
				std::cout << "Error in abilityscoreload" << error.what() << std::endl;
			}
		}

		if (line.find("constitution:") != std::string::npos)
		{
			line = line.substr(line.find(":") + 1);
			try
			{
				temp = stoi(line);
				SetAbilityScore(CON, temp);
				//std::cout << "Line: " << a_line << std::endl;
			}
			catch (std::exception const & error)
			{
				std::cout << "Error in abilityscoreload" << error.what() << std::endl;
			}
		}

		if (line.find("intelligence:") != std::string::npos)
		{
			line = line.substr(line.find(":") + 1);
			try
			{
				temp = stoi(line);
				SetAbilityScore(INT, temp);
				//std::cout << "Line: " << a_line << std::endl;
			}
			catch (std::exception const & error)
			{
				std::cout << "Error in abilityscoreload" << error.what() << std::endl;
			}
		}

		if (line.find("wisdom:") != std::string::npos)
		{
			line = line.substr(line.find(":") + 1);
			try
			{
				temp = stoi(line);
				SetAbilityScore(WIS, temp);
			//	std::cout << "Line: " << a_line << std::endl;
			}
			catch (std::exception const & error)
			{
				std::cout << "Error in abilityscoreload" << error.what() << std::endl;
			}
		}

		if (line.find("charisma:") != std::string::npos)
		{
			line = line.substr(line.find(":") + 1);
			try
			{
				temp = stoi(line);
				SetAbilityScore(CHA, temp);
			//	std::cout <<"Line: "<< a_line << std::endl;
			}
			catch (std::exception const & error)
			{
				std::cout << "Error in abilityscoreload" << error.what() << std::endl;
			}
		}
	
	}
//	DisplayAbilityScores();
	return true;
}

bool EntityClass::LoadEquipment(std::ifstream & a_reader, std::map<std::string, ObjectClass*>& a_MasterObjectList)
{
	bool success = true;
	a_reader.clear();
	a_reader.seekg(0, std::ios::beg);
	if (!a_reader.is_open())
	{
		std::cout << "a_reader is not open to path" << std::endl;
		success = false;
		return success;
	}
	bool BackPackLoading = false;
	bool EquipmentLoading = false;
	std::string line;
	while (getline(a_reader, line))
	{
		BodyLocation TempLocation = UNKNOWNBODYSLOTTYPE;
		//	std::cout << a_line << std::endl;
		//remove comments
		if (line.find("//") != std::string::npos)
		{
			int endchar = line.find("//");
			line = line.substr(0, endchar);
			//	std::cout << "ResultAfterComment " << a_line << std::endl;
		}//end remove comments block

		if (line.find("End Backpack:")!=std::string::npos)
		{
			BackPackLoading = false;
			std::cout << "End loading backpack" << std::endl;
		}
		else if (line.find("Backpack:") != std::string::npos)
		{
			BackPackLoading = true;
			std::cout << "LoadingBackPack" << std::endl;
		}

		if (line.find("End Equipped:") != std::string::npos)
		{
			EquipmentLoading = false;
			std::cout << "End loading equipment" << std::endl;
		}
		else if (line.find("Equipped:") != std::string::npos)
		{
			EquipmentLoading = true;
			std::cout << "Loading m_Equipment" << std::endl;
		}

		TempLocation = GetBodyLocation(line);
		//equipment load functions
		if (EquipmentLoading && TempLocation != UNKNOWNBODYSLOTTYPE)
		{
			//std::cout << a_line << std::endl;
			line = line.substr(line.find(BodyLocationTextMap[TempLocation] + ":")+BodyLocationTextMap[TempLocation].length()+1);
			//std::cout << "Line without a_location: " << a_line << std::endl;
			//this a_line should contain the a_name of the a_object now, we search for it in our a_item functions
			if (this->DoesSlotExist(TempLocation))
			{
				if (line.find("Armor") != std::string::npos)
				{
					//std::cout << "Found armor, adding it to character " << a_line << std::endl;
					if (a_MasterObjectList.count(line) == 0)
					{
						std::cout << line << " not found in a_MasterObjectList, not adding it in" << std::endl;
					}
					else
					{
					//	a_MasterObjectList[a_line]->DisplayArmorInfo();
						m_Equipment[TempLocation] = new ArmorObject(*a_MasterObjectList[line]);
						//std::cout << "New armor made" << a_line << std::endl;
						//m_Equipment[TempLocation]->DisplayArmorInfo();
					}
				}
				else
				{
					if (a_MasterObjectList.count(line) == 0)
					{
						std::cout << line << " not found in a_MasterObjectList, not adding it in" << std::endl;
					}
					else
					{
						m_Equipment[TempLocation] = new ObjectClass(*a_MasterObjectList[line]);
						m_Equipment[TempLocation]->DisplayObjectWeaponFacts();
					}
					
				}
				
				if (m_Equipment[TempLocation]->GetName()!=line)
				{
					std::cout << "Error loading a_object equipped in " << BodyLocationTextMap[TempLocation]<< std::endl;
					m_Equipment[TempLocation] = NULL;
				}

			}
		}
		if (BackPackLoading)
		{
			if (line.find_first_not_of(' ')!=std::string::npos)
			{
				if (line.find("Backpack:")!=std::string::npos)
				{
					continue;
				}
				std::cout << line << std::endl;
				//this should be a a_name then, make a new a_object and add it to backpack
				if (a_MasterObjectList.count(line))
				{
					auto tempPtr = new ObjectClass(*a_MasterObjectList[line]);
					tempPtr->SetName(line);
					m_BackPack.AddItem(tempPtr);
				}
			
			}
		}	

	}
	std::cout << "Trying to load equipment" << std::endl;
	for (auto i = m_Equipment.begin(); i != m_Equipment.end(); i++)
	{
		if ((*i).second != NULL)
		{
		//	success = (*i).second->LoadObject();
		}

	}
	return success;
}

bool EntityClass::LoadFeats(std::ifstream & a_reader, EncounterInstance& a_Encounter)
{
	bool success = true;
	a_reader.clear();
	a_reader.seekg(0, std::ios::beg);
	bool LoadingFeats=false;

	std::string line;
	while (getline(a_reader, line))
	{
		//	std::cout << a_line << std::endl;
		//remove comments
		if (line.find("//") != std::string::npos)
		{
			int endchar = line.find("//");
			line = line.substr(0, endchar);
			//	std::cout << "ResultAfterComment " << a_line << std::endl;
		}//end remove comments block

		if (line.find_first_not_of(' ') == std::string::npos)
		{
			continue;
		}

		if (line.find("End Feats:") != std::string::npos)
		{
			LoadingFeats= false;
			break;
		}
		else if (line.find("Feats:") != std::string::npos)
		{
			LoadingFeats = true;
			std::cout << "YERRRRRRRRR" << std::endl;
			continue;
		}
		if (LoadingFeats == true)
		{
			if (a_Encounter.GetMasterFeatList().count(line))
			{
				m_Feats.push_back(*(a_Encounter.GetMasterFeatList())[line]);
			}
			else
			{
				std::cout << line << " not found in masterlist, not loading feat" << std::endl;
			}
		}
	}
	DisplayFeats();
	return success;
}

void EntityClass::DisplayFeats()
{
	for (auto it = m_Feats.begin(); it != m_Feats.end(); it++)
	{
		(*it).DisplayFeatFullInfo();
	}
}

BodyLocation EntityClass::GetBodyLocation(std::string a_line)
{
	for (auto i = BodyLocationTextMap.begin(); i != BodyLocationTextMap.end(); i++)
	{
		if (a_line.find((*i).second) != std::string::npos)
		{
			//std::cout << "Here" << std::endl;
			return (*i).first;
		}
	}
	return UNKNOWNBODYSLOTTYPE;
}

bool EntityClass::isMeleeUnit()
{
	if (GetEquipmentInSlot(MAINHAND) != nullptr)
	{
		//is the primary weapon in the mainhand of the entity ranged or thrown?
		if (this->GetEquipmentInSlot(MAINHAND)->IsRangedWeapon())
		{
			//if it is thrown do we have backup ammo in our pack?
			if (this->GetEquipmentInSlot(MAINHAND)->IsThrowingWeapon())
			{
				//check if we have the same a_item in our backpack or in the other hand
				if (GetBackPack().isItemPresent(GetEquipmentInSlot(MAINHAND)->GetName()))
				{
					return false;
				}
				if (GetEquipmentInSlot(OFFHAND) != nullptr)
				{
					if (GetEquipmentInSlot(MAINHAND)->GetName() == GetEquipmentInSlot(OFFHAND)->GetName())
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}

bool EntityClass::LoadProperties(std::ifstream &a_reader)
{
		a_reader.clear();
		a_reader.seekg(0, std::ios::beg);
		if (a_reader.is_open())
		{
			//std::cout << "a_reader is open to path" << std::endl;
		}
		std::string line;
		while (getline(a_reader, line))
		{
			std::cout << line << std::endl;
			//remove comments
			if (line.find("//") != std::string::npos)
			{
				int endchar = line.find("//");
				line = line.substr(0, endchar);
				//	std::cout << "ResultAfterComment " << a_line << std::endl;
			}//end remove comments block

			 //lowercase the string
			for (std::string::size_type i = 0; i < line.length(); ++i) {
				line[i] = tolower(line[i]);
			}

			int temp = 0;
			if (line.find("maxhitpoints:") != std::string::npos)
			{
				line = line.substr(line.find(":") + 1);
				try
				{
					temp = stoi(line);
					SetMaxHitPoints(temp);
					std::cout << "Line: " << line << std::endl;
					std::cout << "Hitpoints: " << temp << std::endl;
				}
				catch (std::exception const & error)
				{
					std::cout << "Error in PropertiesLoad" << error.what() << std::endl;
				}

			}
			if (line.find("baseattackbonus:") != std::string::npos)
			{
				line = line.substr(line.find(":") + 1);
				try
				{
					temp = stoi(line);
					SetBaseAttackBonus(temp);
					std::cout << "Line: " << line << std::endl;
					std::cout << "m_BaseAttackBonus: " << temp << std::endl;
				}
				catch (std::exception const & error)
				{
					std::cout << "Error in PropertiesLoad" << error.what() << std::endl;
				}
			}
		}
		return true;

}