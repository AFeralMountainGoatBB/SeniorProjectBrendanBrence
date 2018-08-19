#include "EntityClass.h"
#include "Dot.h"
#include "StaticFunctions.h"
#include "Texture.h"
#include "Tile.h"
#include "PickupItemsMenu.h"
#include "EncounterInstance.h"
#include "Armor.h"
#include "InventoryMenu.h"
#include "FeatMenu.h"
#include "PathfindingAlgorithm.h"

EntityClass::EntityClass(int xInitial, int yInitial, int HPMax=0, int HPCurrent=0, EntitySize ThisSize=MEDIUM)
{	
	this->HitPointMaximum = HPMax;
	this->HitPoints = HPCurrent;
	this->ThisSize = ThisSize;
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = ENTITY_WIDTH;
	mBox.h = ENTITY_HEIGHT;
//	SetLocation(xInitial, yInitial);
}

EntityClass::EntityClass()
{
	mBox.x = 0;
	mBox.w = ENTITY_WIDTH;
	mBox.h = ENTITY_HEIGHT;
	std::cout << "Entity size, H, w : " << mBox.w << " " << mBox.h << std::endl;
}

void EntityClass::SetTexture(std::map<std::string, LTexture*> &TextureMap, std::string Path)
{
	if (TextureMap.count(Path + "\\" + mPathTexture)) 
	{
		mTexture = TextureMap[Path + "\\" + mPathTexture];
		//std::cout << mPathTexture << " Loaded into " << EntityName <<  std::endl;
	}
	else
	{
		std::cout << "No matching texture found " << Path << "\\" << mPathTexture << std::endl;
		mTexture = TextureMap[Path + "\\" + "QuestionMark.png"];
	}

	/*if (TeamSide != 1)
	{
		mTexture->setColor(255, 0, 0);
	}*/
	
}

LTexture* EntityClass::GetTexture()
{
	return mTexture;
}
/*--------------START GETTERS -------------------*/

const bool EntityClass::IsBroke()
{
	if (HitPoints <= HitPointMaximum / 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*----------------END GETTERS -------------------*/
/*----------------START MUTATORS-----------------*/

void EntityClass::RemoveHitPoints(int removal)
{
	this->HitPoints -= removal;
}

void EntityClass::SetHitPoints(int SetHP)
{
	HitPoints = SetHP;
}

void EntityClass::AddHitPoints(int Addition)
{
	this->HitPoints += Addition;
	if (this->HitPoints > HitPointMaximum)
	{
		this->HitPoints = HitPointMaximum;
	}
}

std::string EntityClass:: GetName()
{
	return EntityName;
}


/*----------------END MUTATORS-----------------*/

bool EntityClass::EntityMeleeAttack(std::vector<std::vector<Tile>> &TileVector, EncounterInstance& Instance)
{
	//std::cout << "Im attacking now" << std::endl;
	//call EntityMeleeAttackTile, if not null call selected attack roll
	EntityClass* Target = EntityMeleeAttackTile(TileVector);
	if (Target != NULL)
	{
		MeleeAttack Attack;
		if (!AttackBothHands)
		{
			Attack.AttackNormal(*this, *Target, Instance);
		}
		else if(AttackBothHands)
		{
			Attack.AttackDualWield(*this, *Target, Instance);
		}
	}

	return false;
}

bool EntityClass::EntityRangedAttack(std::vector<std::vector<Tile>> &TileVector, EncounterInstance& Instance)
{
	//call EntityRangedAttackTile, if not null call selected attack roll, if null then return false
	EntityClass* Target = EntityRangedAttackTile(TileVector, Instance);
	if (Target != NULL)
	{
		std::cout << Target->EntityName << std::endl;
		RangedAttack Attack;
		if (!AttackBothHands)
		{
			Attack.AttackNormal(*this, *Target, Instance);
		}
		else if (AttackBothHands)
		{
			Attack.AttackDualWield(*this, *Target, Instance);
		}
	}
	else
	{
		std::cout << "Can't attack empty tile" << std::endl;
	}

	return false;
}
bool EntityClass::EntityRangedAttack(std::vector<std::vector<Tile>> &TileVector, EncounterInstance& Instance, EntityClass* Target)
{
	//we have a target, let us attack
	if (Target != NULL)
	{
		std::cout << Target->EntityName << std::endl;
		RangedAttack Attack;
		if (!AttackBothHands)
		{
			Attack.AttackNormal(*this, *Target, Instance);
		}
		else if (AttackBothHands)
		{
			Attack.AttackDualWield(*this, *Target, Instance);
		}
	}
	else
	{
		std::cout << "Can't attack empty tile" << std::endl;
	}

	return false;
}

EntityClass* EntityClass::EntityMeleeAttackTile(std::vector<std::vector<Tile>> &TileVector)
{
	if (MoveDirection == STATIONARY)
	{
		return NULL;
	}

	switch (MoveDirection)
	{
		//check if we can attack the next spot
		//attack the tile if it exists (and anyone in it)
		//change moveDir to stationary, set to move mode
	case NORTH:
		FaceDirection = NORTH;
		if (mLocation.second != 0)
		{
			if (TileVector[mLocation.first][mLocation.second - 1].GetOccupant())
			{
				std::cout << "Attacking: " << TileVector[mLocation.first][mLocation.second - 1].GetOccupant()->GetName() << std::endl;
				MoveDirection = STATIONARY;
				return TileVector[mLocation.first][mLocation.second - 1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				MoveDirection = STATIONARY;
				return NULL;
			}

		}
		else
		{
			std::cout << "Cannot Attack There" << std::endl;
			MoveDirection = STATIONARY;
			return NULL;
		}
		break;

	case EAST:
		FaceDirection = EAST;
		if (mLocation.first < TileVector.size() - 1)
		{
			if (TileVector[mLocation.first+1][mLocation.second].GetOccupant())
			{
				std::cout << "Attacking: " << TileVector[mLocation.first+1][mLocation.second].GetOccupant()->GetName() << std::endl;
				MoveDirection = STATIONARY;
				return TileVector[mLocation.first + 1][mLocation.second].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile " << std::endl;
				MoveDirection = STATIONARY;
				return NULL;
			}

		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			MoveDirection = STATIONARY;
			return NULL;
		}
		break;

	case SOUTH:
		FaceDirection = SOUTH;
		if (mLocation.second < TileVector[0].size() - 1)
		{
			if (TileVector[mLocation.first][mLocation.second + 1].GetOccupant())
			{
				std::cout << "Attacking: " << TileVector[mLocation.first][mLocation.second + 1].GetOccupant()->GetName() << std::endl;
				MoveDirection = STATIONARY;
				return TileVector[mLocation.first][mLocation.second + 1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				MoveDirection = STATIONARY;
				return NULL;
			}

			}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			MoveDirection = STATIONARY;
			return NULL;
		}
		
		break;

	case WEST:
		FaceDirection = WEST;

		if (mLocation.first != 0)
		{
			if (TileVector[mLocation.first-1][mLocation.second].GetOccupant())
			{
				std::cout << "Attacking: " << TileVector[mLocation.first - 1][mLocation.second].GetOccupant()->GetName() << std::endl;
				MoveDirection = STATIONARY;
				return TileVector[mLocation.first - 1][mLocation.second].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				MoveDirection = STATIONARY;
				return NULL;
			}
		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			MoveDirection = STATIONARY;
			return NULL;
		}
		break;

	case NORTHWEST:
		FaceDirection = NORTHWEST;

		if (mLocation.first != 0
			&&
			mLocation.second!=0)
		{
			if (TileVector[mLocation.first - 1][mLocation.second-1].GetOccupant())
			{
				std::cout << "Attacking: " << TileVector[mLocation.first - 1][mLocation.second-1].GetOccupant()->GetName() << std::endl;
				MoveDirection = STATIONARY;
				return TileVector[mLocation.first - 1][mLocation.second-1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				MoveDirection = STATIONARY;
				return NULL;
			}
		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			MoveDirection = STATIONARY;
			return NULL;
		}
		break;

	case SOUTHWEST:
		FaceDirection = SOUTHWEST;

		if (mLocation.first !=0 
			&&
			mLocation.second <(TileVector[mLocation.first].size()-1))
		{
			if (TileVector[mLocation.first - 1][mLocation.second + 1].GetOccupant())
			{
				std::cout << "Attacking: " << TileVector[mLocation.first - 1][mLocation.second + 1].GetOccupant()->GetName() << std::endl;
				MoveDirection = STATIONARY;
				return TileVector[mLocation.first - 1][mLocation.second + 1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				MoveDirection = STATIONARY;
				return NULL;
			}
		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			MoveDirection = STATIONARY;
			return NULL;
		}
		break;

	case SOUTHEAST:
		FaceDirection = SOUTHEAST;

		if (mLocation.first <(TileVector.size()-1)
			&&
			mLocation.second <(TileVector[mLocation.first].size() - 1))
		{
			if (TileVector[mLocation.first + 1][mLocation.second + 1].GetOccupant())
			{
				std::cout << "Attacking: " << TileVector[mLocation.first + 1][mLocation.second + 1].GetOccupant()->GetName() << std::endl;
				MoveDirection = STATIONARY;
				return TileVector[mLocation.first + 1][mLocation.second + 1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				MoveDirection = STATIONARY;
				return NULL;
			}
		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			MoveDirection = STATIONARY;
			return NULL;
		}
		break;

	case NORTHEAST:
		FaceDirection = NORTHEAST;

		if (mLocation.first <(TileVector.size() - 1)
			&&
			mLocation.second !=0)
		{
			if (TileVector[mLocation.first + 1][mLocation.second -1].GetOccupant())
			{
				std::cout << "Attacking: " << TileVector[mLocation.first + 1][mLocation.second -1].GetOccupant()->GetName() << std::endl;
				MoveDirection = STATIONARY;
				return TileVector[mLocation.first + 1][mLocation.second - 1].GetOccupant();
			}
			else
			{
				std::cout << "Attacked an empty tile" << std::endl;
				MoveDirection = STATIONARY;
				return NULL;
			}
		}
		else
		{
			std::cout << "Cannot attack there" << std::endl;
			MoveDirection = STATIONARY;
			return NULL;
		}
		break;


	} //end switch statement
	
	MoveDirection = STATIONARY;
	return NULL;
}

EntityClass* EntityClass::EntityRangedAttackTile(std::vector<std::vector<Tile>> &TileVector, EncounterInstance &Instance)
{
	return TileVector[Instance.GetTargetSystem().GetLocation().first][Instance.GetTargetSystem().GetLocation().second].GetOccupant();
}


void EntityClass::TakeDamage(int Damage, DamageType DamageType)
{
	//find any resistances, immunities calculate as full resistance
	//subtract resisted damage from total damage
	//subtract Damage reduction from total damage
	//finally subtract from health pool
	HitPoints -= Damage;
}

int EntityClass::GetTotalDamageReduction()
{
	int TotalDamageReduction = 0;
	//go through equipment and add up damage reduction.
	for (auto it = Equipment.begin(); it != Equipment.end(); it++)
	{
		if ((*it).second != NULL)
		{
			TotalDamageReduction += (*it).second->GetDamageReduction();
		}
	}
	//go through feats and add up damage reduction + resistances TODO
	//add together, return total

	return TotalDamageReduction;
}

const int EntityClass::GetArmorClass()
{
//	std::cout << EntityName << " has armor class of " << ArmorClass << std::endl;
	return ArmorClass;
}

ObjectClass* EntityClass::GetEquipmentInSlot(BodyLocation Location)
{
	if (Equipment.find(Location) != Equipment.end())
	{
		return Equipment[Location];
	}
	return nullptr;
}
void EntityClass::GenerateUnarmedStrike(EncounterInstance &Instance)
{
	this->UnarmedStrike = Instance.GetObjectFromMasterList("Unarmed Strike");

}
void EntityClass::TwoHandWeapon()
{
	if (Equipment[MAINHAND] != NULL)
	{
		if (Equipment[OFFHAND] != NULL)
		{
			//this means that we are already grasping the wep in two hands we will stop
			if (Equipment[OFFHAND]==Equipment[MAINHAND])
			{
				std::cout << "Offhand Let go" << std::endl;
				Equipment[OFFHAND] = NULL;
			}
			else
			{
				std::cout << "Both Hands Occupied" << std::endl;
				return;
			}	
		}
		else
		{
			Equipment[OFFHAND] = Equipment[MAINHAND];
			std::cout << "Weapon Grasped in both hands" << std::endl;
		}
	} // end mainhand !=null
	else
	{
		if (Equipment[OFFHAND] != NULL)
		{
			std::cout << "Weapon Grasped in both hands" << std::endl;
			Equipment[MAINHAND] = Equipment[OFFHAND];
		}
	}
}

std::vector<FeatClass> EntityClass::GetActiveFeats()
{
	std::vector<FeatClass>ActiveFeats;
	for (auto it = Feats.begin(); it != Feats.end(); it++)
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
	for (auto it = Feats.begin(); it != Feats.end(); it++)
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

bool EntityClass::DoesSlotExist(BodyLocation Location)
{
	bool temp = false;
	if (Equipment.find(Location) != Equipment.end())
	{
		temp = true;
	}
	return temp;
}

bool EntityClass::EquipAsWeapon(ObjectClass* Weapon)
{
	std::cout <<"Number of offhand slots" << Equipment.count(OFFHAND) << std::endl;
	if (Weapon->GetTwoHanded())
	{
		std::cout << "Two handed weapon" << std::endl;
		if (GetEquipmentInSlot(MAINHAND) == nullptr && GetEquipmentInSlot(OFFHAND) == nullptr)
		{
			if (EquipMainHandWeapon(Weapon)==true && EquipOffHandWeapon(Weapon)==true)
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
			std::cout << "Equipment slot available" << std::endl;
			if (EquipMainHandWeapon(Weapon)==false)
			{
				std::cout << "Failed equipping in mainhand, occupied" << std::endl;
				if (EquipOffHandWeapon(Weapon)==false)
				{
					std::cout << "Equipped in offhand" << std::endl;
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
	std::cout << "EquipAsWeapon returning false" << std::endl;
	return false;
}

bool EntityClass::EquipMainHandWeapon(ObjectClass* Weapon)
{
	if (GetEquipmentInSlot(MAINHAND) == nullptr)
	{
		std::cout << "Mainhand Free" << std::endl;
		Equipment.find(MAINHAND)->second = Weapon;
		return true; //successfull equip
	}
	else
	{
		std::cout << "Mainhand Occupied EquipManhand" << std::endl;
		return false;
	}
}

bool EntityClass::EquipOffHandWeapon(ObjectClass* Weapon)
{
	std::cout << "Trying to equip offhand" << std::endl;
	if (GetEquipmentInSlot(OFFHAND) == nullptr)
	{
		std::cout << "Offhand free" << std::endl;
		Equipment.find(OFFHAND)->second = Weapon;
		return true; // succesfull equip
	}
	else
	{
		std::cout << "offhand occupied" << std::endl;
		return false;
	}
}

//void EntityClass::HandleTurn (SDL_Event& e, EncounterInstance & Instance)

void EntityClass::handleEvent(SDL_Event& e, EncounterInstance & Instance)
{
	
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		
		//change the location
		switch (e.key.keysym.sym)
		{
			//move to encounter handle
		case SDLK_i: DisplayEntireInventory(); break;

			//end move to encounter handle
		case SDLK_s:MoveDirection = STATIONARY; break;
		case SDLK_w:MoveDirection = NORTH; break;
		case SDLK_a:MoveDirection = WEST; break;
		case SDLK_d:MoveDirection = EAST; break;
		case SDLK_x:MoveDirection = SOUTH; break;
		
		case SDLK_e:MoveDirection = NORTHEAST; break;
		case SDLK_q:MoveDirection = NORTHWEST; break;
		case SDLK_z:MoveDirection = SOUTHWEST; break;
		case SDLK_c:MoveDirection = SOUTHEAST; break;

		case SDLK_UP: MoveDirection = NORTH; break;
		case SDLK_DOWN: MoveDirection = SOUTH; break;
		case SDLK_LEFT: MoveDirection = WEST; break;
		case SDLK_RIGHT: MoveDirection = EAST; break;
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
			if (this->GetEquipmentInSlot(MAINHAND) != nullptr)
			{
				if (this->GetEquipmentInSlot(MAINHAND)->IsRangedWeapon())
				{
					SetControlMode(RANGEDATTACKMODE);
					Instance.GetTargetSystem().SetActive(true);
					break;
				}
			}
			else if (this->GetEquipmentInSlot(OFFHAND) != nullptr)
			{
				if (this->GetEquipmentInSlot(OFFHAND)->IsRangedWeapon())
				{
					SetControlMode(RANGEDATTACKMODE);
					Instance.GetTargetSystem().SetActive(true);
					break;
				}
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
			//BFS.TestBreadthFirst(Instance.GetTileMap(), this->GetLocation().first, this->GetLocation().second);

			std::cout << "Attempting to pathfind using DIJK" << std::endl << std::endl;
			PathFinder DIJK;
			DIJK.UseDijkstra(Instance.GetTileMap(), this->GetLocation().first, this->GetLocation().second, 4, 5);
			break;

		}
	
	}
}

bool EntityClass::move(std::vector<std::vector<Tile>> &TileVector)
{
	if (MoveDirection == STATIONARY)
	{
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		return false;
	}

	if (this->MovementLeft <= 0)
	{
		//std::cout << "Not enough movement points remaining" << std::endl;
		return false;
	}

	bool success = false;
	switch (MoveDirection)
	{	
	//check if we can move to the tile to next spot
	//move to the tile if we can
	//change moveDir to stationary
	case NORTH:
		FaceDirection = NORTH;
		if (mLocation.second != 0 && TileVector[mLocation.first][mLocation.second-1].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.second--;
			MovementLeft-=1;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		
		break;

	case NORTHEAST:
		FaceDirection = NORTHEAST;
		if (mLocation.second != 0 && TileVector[mLocation.first][mLocation.second - 1].getPassable()
			&&
			mLocation.first < TileVector.size() - 1 && TileVector[mLocation.first + 1][mLocation.second].getPassable()
			&&
			TileVector[mLocation.first + 1][mLocation.second - 1].getPassable()
			&& MovementLeft>=1 )
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.first++;
			mLocation.second--;
			MovementLeft -= 1.5;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there, or not enough movement remaining" << std::endl;
			success = false;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case EAST: 
		FaceDirection = EAST;
		if (mLocation.first < TileVector.size()-1 && TileVector[mLocation.first+1][mLocation.second].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.first++;
			MovementLeft -= 1;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case SOUTHEAST:
		FaceDirection = SOUTHEAST;
		if (mLocation.first < TileVector.size() - 1 && TileVector[mLocation.first + 1][mLocation.second].getPassable()
			&&
			mLocation.second < TileVector[0].size() - 1 && TileVector[mLocation.first][mLocation.second + 1].getPassable()
			&&
			TileVector[mLocation.first + 1][mLocation.second + 1].getPassable()
			&&
			MovementLeft >= 1)
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.first++;
			mLocation.second++;
			MovementLeft -= 1.5;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there or not enough movement left" << std::endl;
			success = false;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case SOUTH: 
		FaceDirection = SOUTH;
		if (mLocation.second < TileVector[0].size() - 1 && TileVector[mLocation.first][mLocation.second+1].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.second++;
			MovementLeft -= 1;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case SOUTHWEST:
		FaceDirection = SOUTHWEST;
		if (mLocation.second < TileVector[0].size() - 1 && TileVector[mLocation.first][mLocation.second + 1].getPassable()
			&&
			mLocation.first != 0 && TileVector[mLocation.first - 1][mLocation.second].getPassable()
			&&
			TileVector[mLocation.first - 1][mLocation.second + 1].getPassable()
			&&
			MovementLeft >= 1)
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.second++;
			mLocation.first--;
			MovementLeft -= 1.5;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there or not enough movement left" << std::endl;
			success = false;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case WEST: 
		FaceDirection = WEST;

		if (mLocation.first !=0 && TileVector[mLocation.first - 1][mLocation.second].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.first--;
			MovementLeft -= 1;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case NORTHWEST:
		FaceDirection = NORTHWEST;

		if (mLocation.first != 0 && TileVector[mLocation.first - 1][mLocation.second].getPassable()
			&&
			mLocation.second != 0 && TileVector[mLocation.first][mLocation.second - 1].getPassable()
			&&
			TileVector[mLocation.first - 1][mLocation.second - 1].getPassable()
			&&
			MovementLeft >= 1)
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.first--;
			mLocation.second--;
			MovementLeft -= 1.5;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there or not enough movement left" << std::endl;
			success = false;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;
	} //end switch statement

	//std::cout << "Man moved in function, setting rend location " << std::endl;
	//std::cout << "Attempted to move" << std::endl;
	if (success)
	{
		std::cout << "Success" << std::endl;
	}
	else
	{
		std::cout << "Failed move" << std::endl;
	}
	SetRendLocation(TileVector);
	MoveDirection = STATIONARY;
	return success;
	}

void EntityClass::setCamera(SDL_Rect& camera)
{
	//Center the camera over the entity
	camera.x = (mBox.x + ENTITY_WIDTH / 2) - SCREEN_WIDTH *0.333;
	camera.y = (mBox.y + ENTITY_HEIGHT / 2) - SCREEN_HEIGHT*0.375;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void EntityClass::SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap)
{
	mLocation.first = x;
	mLocation.second = y;
	TileMap[x][y].SetOccupant(*this);
	this->SetRendLocation(TileMap);
}

std::pair<int, int> EntityClass::GetLocation()
{
	return mLocation;
}

void EntityClass::SetRendLocation(std::vector<std::vector<Tile>> &TileVector)
{
	std::pair<int, int> tempLoc = CalcRendLocation(TileVector);
	mBox.x = tempLoc.first;
	mBox.y = tempLoc.second;
	//std::cout << "New rend location=" << mBox.x << " " << mBox.y << std::endl;
}

std::pair<int, int> EntityClass::CalcRendLocation(std::vector<std::vector<Tile>> &TileVector)
{
	//std::cout << "Calc rend location" << std::endl;
	std::pair <int, int> RetVal;
	int xTempLoc = GetLocation().first;
	int yTempLoc = GetLocation().second;

	std::cout << xTempLoc << "  " << yTempLoc << std::endl;

	int xOffset = 0;
	int yOffset = 0;
	//std::cout << "Accessing vector" << std::endl;
	RetVal.first=TileVector[xTempLoc][yTempLoc].GetXRenderPos();
	RetVal.second = TileVector[xTempLoc][yTempLoc].GetYRenderPos();

	xOffset = 0.5 * (TileVector[xTempLoc][yTempLoc].GetWidth() - ENTITY_WIDTH);
	yOffset = 0.5 * (TileVector[xTempLoc][yTempLoc].GetWidth() - ENTITY_HEIGHT);

	RetVal.first = RetVal.first + xOffset;
	RetVal.second = RetVal.second + yOffset;

	return RetVal;
}

void EntityClass::render(SDL_Rect& camera, SDL_Renderer *& Renderer)
{
	double tempangle;
	switch (FaceDirection)
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
	if (checkCollision(camera, mBox))
	{
		//Show the texture
		mTexture->renderEntity(mBox.x - camera.x, mBox.y - camera.y, Renderer, &mBox, tempangle);
		//std::cout << " Entity size " << mBox.h << " " << mBox.w << std::endl;
	}
}

void EntityClass::SetPath(std::string Path)
{
	mPathTexture = Path;
}

void EntityClass::SetName(std::string PassedName)
{
	EntityName = PassedName;
}

ControlMode EntityClass::GetControlMode()
{
	return this->ControlSetting;
}

void EntityClass::SetControlMode(ControlMode NewControl)
{
	this->ControlSetting = NewControl;
}

int EntityClass::GetAbilityModifier(AbilityScoreType ability)
{
	int temp = (int)(floor((AbilityScore[ability] - 10) / 2));
	std::cout << "Checking dex, normal: " << temp << std::endl;
	if (ability == DEX && temp > GetMaxDex())
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
	for (auto it = Equipment.begin(); it != Equipment.end(); it++)
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
	std::vector<FeatClass> TempFeats = GetActiveFeats();
	int TotalIntBonus = 0;
	for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
	{
		//no feats implemented with init yet
	}

	//add them to the existing dex bonus to get initiative bonus
	TotalIntBonus+= GetAbilityModifier(DEX);
	Initiative = (DiceRoll(D20) + TotalIntBonus);
	std::cout << EntityName << " rolled " << Initiative << " on initiative" << std::endl;

}

bool EntityClass::IsTwoHanding()
{
	if (Equipment[MAINHAND] == Equipment[OFFHAND])
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
				Equipment[MAINHAND] = Equipment[OFFHAND];	
				Equipment[OFFHAND] = TempStore;
			}
			else
			{
				Equipment[OFFHAND] = TempStore;
				Equipment[MAINHAND] = NULL;
			}
		
		}
		else if (GetEquipmentInSlot(OFFHAND) != NULL)
		{
			Equipment[MAINHAND] = Equipment[OFFHAND];
			Equipment[OFFHAND] = NULL;
		}
	}
}

ObjectClass* EntityClass::PickupTile(std::vector<std::vector<Tile>> &TileVector)
{
	PickupItemsMenu PMenu;

	return PMenu.PickupItemsRun(TileVector[mLocation.first][mLocation.second]);
}

void EntityClass::EntityPickup(std::vector<std::vector<Tile>> &TileVector)
{
	ObjectClass* Target = PickupTile(TileVector);
	if (Target != NULL)
	{
		//pickup the item
		
		if (this->EquipObject(Target))
		{
			//std::cout << "Equipping successful" << std::endl;
			TileVector[Target->GetLocation().first][Target->GetLocation().second].RemoveObject(Target);
		}
	}
	//DisplayEntireInventory();
	return;
}

ObjectClass* EntityClass::EntityInventory(std::vector<std::vector<Tile>> &TileVector)
{
	InventoryMenu IMenu;
	return IMenu.InventoryMenuRun(*this, TileVector);

}
void EntityClass::EntityFeatMenu()
{
	FeatMenu FMenu;
	FMenu.FeatMenuRun(*this);
}
ItemContainer& EntityClass::GetBackPack()
{
	return BackPack;
}

void EntityClass::AddToBackPack(ObjectClass * object)
{
	BackPack.AddItem(object);
}

void EntityClass::UnEquip(BodyLocation location)
{
	if (Equipment[location]!=NULL)
	{
		AddToBackPack(Equipment[location]);
		Equipment[location] = NULL;
	}
}
bool EntityClass::EquipArmor(ObjectClass* item)
{
	if (Equipment[BODY] == NULL)
	{
		Equipment[BODY] = item;
		return true;
	}
	else 
	{
		return false;
	}
}

void EntityClass::DropFromEquipment(BodyLocation location, std::vector<std::vector<Tile>>&TileMap)
{
	if (Equipment[location] != NULL)
	{
		Equipment[location]->SetLocation(mLocation.first, mLocation.second, TileMap);
		Equipment[location] = NULL;
	}
}

void EntityClass::DropFromBackPack(int index, std::vector<std::vector<Tile>>& TileMap)
{
	if (index < 0)
	{
		return;
	}
	//get item at index
	if (BackPack.GetItemAtIndex(index)) //will not go if NULL
	{
		BackPack.GetItemAtIndex(index)->SetLocation(mLocation.first, mLocation.second, TileMap);
		BackPack.RemoveItemAtIndex(index);
	}
	//BackPack.DropItemAtIndex(int index);

}

bool EntityClass::EquipObject(ObjectClass* item)
{
	//std::cout << "Equipping " << item->GetName() << " in the " << BodyLocationTextMap[item->GetBodySlot()] << std::endl;
	if (item->GetBodySlot() == MAINHAND || item->GetBodySlot() == OFFHAND)
	{
	//	std::cout << "Attempting to equip as a weapon" << std::endl;
		if (this->EquipAsWeapon(item))
		{
			//std::cout << "Equipped as a legitimate weapon" << std::endl;
			return true;
		}
	}
	if (item->GetBodySlot()==TRADEGOOD)
	{
		if (this->EquipAsWeapon(item))
		{
			std::cout << "Equipped as weapon" << std::endl;
			return true;
		}
		else
		{
			BackPack.AddItem(item);
			std::cout << "Added to backpack" << std::endl;
			return true;
		}

	}
	//BodyLocation location = item->GetBodySlot();
	if (DoesSlotExist(item->GetBodySlot())) 
	{
		if (this->GetEquipmentInSlot(item->GetBodySlot()) == NULL)
		{

			std::cout << "Added to Equipment" << std::endl;
			Equipment[item->GetBodySlot()] = item;
			return true;
		}
	}
	
	BackPack.AddItem(item);
	std::cout << "Added to backpack" << std::endl;
	return true;

//	std::cout << "Couldnt add it anywhere" << std::endl;
	return false;
}

void EntityClass::DisplayEntireInventory()
{
	for (auto iter = Equipment.begin(); iter != Equipment.end(); iter++)
	{
		if ((*iter).second != NULL)
		{
		std::cout << BodyLocationTextMap[iter->first] << "  " << (*iter).second->GetName() << std::endl;
		}
	}
	std::cout << "Backpack items: " << std::endl;
	BackPack.DisplayItems();
}

void EntityClass::SetAbilityScore(AbilityScoreType type, int amount)
{
	AbilityScore[type] = amount;
}

void EntityClass::DisplayAbilityScores()
{
	for (auto i = AbilityScore.begin(); i != AbilityScore.end(); i++)
	{
		std::cout << AbilityScoreTextMap[(*i).first] << "  " << (*i).second << std::endl;
	}
}

//loading functions
bool EntityClass::LoadEntity(std::string name, std::pair<int, int> Location, bool PlayerControlled, int side, EncounterInstance &Instance)
{
	name = Instance.GetCharacterFolderPath() +"\\"+ name;
	std::ifstream reader;
	std::cout << "Reader path: " << name << std::endl;
	reader.open(name);
	LoadNameDescriptionAndTexture(reader);
	LoadAbilityScores(reader);
	LoadEquipment(reader, Instance.GetObjectList());
	LoadFeats(reader, Instance);
	//LoadProperties(reader);
	TeamSide = side;
	this->SetLocation(Location.first, Location.second, Instance.GetTileMap());
	//generate their unarmed attack
	GenerateUnarmedStrike(Instance);

	std::cout << "Loaded entity: " << this->EntityName << std::endl;
	return true;
}

bool EntityClass::LoadNameDescriptionAndTexture(std::ifstream &reader)
{
	reader.clear();
	reader.seekg(0, std::ios::beg);
	std::string line = "";
	bool GotName = false;
	bool GotTexture = false;
	bool GotDescription = false;
	while (getline(reader, line))
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
			//	std::cout << "ResultAfterComment " << line << std::endl;
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
			this->mPathTexture = line;
			GotTexture = true;
		}
	}
	return false;
}

bool EntityClass::LoadAbilityScores(std::ifstream &reader)
{
	reader.clear();
	reader.seekg(0, std::ios::beg);
	if (reader.is_open())
	{
		std::cout << "reader is open to path" << std::endl;
	}
	std::string line;
	while (getline(reader, line))
	{
	//	std::cout << line << std::endl;
		//remove comments
		if (line.find("//") != std::string::npos)
		{
			int endchar = line.find("//");
			line = line.substr(0, endchar);
			//	std::cout << "ResultAfterComment " << line << std::endl;
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
				//std::cout << "Line: " << line << std::endl;
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
				//std::cout << "Line: " << line << std::endl;
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
				//std::cout << "Line: " << line << std::endl;
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
				//std::cout << "Line: " << line << std::endl;
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
			//	std::cout << "Line: " << line << std::endl;
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
			//	std::cout <<"Line: "<< line << std::endl;
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

bool EntityClass::LoadEquipment(std::ifstream & reader, std::map<std::string, ObjectClass*>& MasterObjectList)
{
	bool success = true;
	reader.clear();
	reader.seekg(0, std::ios::beg);
	if (!reader.is_open())
	{
		std::cout << "reader is not open to path" << std::endl;
		success = false;
		return success;
	}
	bool BackPackLoading = false;
	bool EquipmentLoading = false;
	std::string line;
	while (getline(reader, line))
	{
		BodyLocation TempLocation = UNKNOWNBODYSLOTTYPE;
		//	std::cout << line << std::endl;
		//remove comments
		if (line.find("//") != std::string::npos)
		{
			int endchar = line.find("//");
			line = line.substr(0, endchar);
			//	std::cout << "ResultAfterComment " << line << std::endl;
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
			std::cout << "Loading Equipment" << std::endl;
		}

		TempLocation = GetBodyLocation(line);
		//equipment load functions
		if (EquipmentLoading && TempLocation != UNKNOWNBODYSLOTTYPE)
		{
			//std::cout << line << std::endl;
			line = line.substr(line.find(BodyLocationTextMap[TempLocation] + ":")+BodyLocationTextMap[TempLocation].length()+1);
			//std::cout << "Line without location: " << line << std::endl;
			//this line should contain the name of the object now, we search for it in our item functions
			if (this->DoesSlotExist(TempLocation))
			{
				if (line.find("Armor") != std::string::npos)
				{
					//std::cout << "Found armor, adding it to character " << line << std::endl;
					if (MasterObjectList.count(line) == 0)
					{
						std::cout << line << " not found in MasterObjectList, not adding it in" << std::endl;
					}
					else
					{
					//	MasterObjectList[line]->DisplayArmorInfo();
						Equipment[TempLocation] = new ArmorObject(*MasterObjectList[line]);
						//std::cout << "New armor made" << line << std::endl;
						//Equipment[TempLocation]->DisplayArmorInfo();
					}
				}
				else
				{
					if (MasterObjectList.count(line) == 0)
					{
						std::cout << line << " not found in MasterObjectList, not adding it in" << std::endl;
					}
					else
					{
						Equipment[TempLocation] = new ObjectClass(*MasterObjectList[line]);
						Equipment[TempLocation]->DisplayObjectWeaponFacts();
					}
					
				}
				
				if (Equipment[TempLocation]->GetName()!=line)
				{
					std::cout << "Error loading object equipped in " << BodyLocationTextMap[TempLocation]<< std::endl;
					Equipment[TempLocation] = NULL;
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
				//this should be a name then, make a new object and add it to backpack
				if (MasterObjectList.count(line))
				{
					auto tempPtr = new ObjectClass(*MasterObjectList[line]);
					tempPtr->SetName(line);
					BackPack.AddItem(tempPtr);
				}
			
			}
		}	

	}
	std::cout << "Trying to load equipment" << std::endl;
	for (auto i = Equipment.begin(); i != Equipment.end(); i++)
	{
		if ((*i).second != NULL)
		{
		//	success = (*i).second->LoadObject();
		}

	}
	success = BackPack.LoadAll();
	return success;
}

bool EntityClass::LoadFeats(std::ifstream & reader, EncounterInstance& Encounter)
{
	bool success = true;
	reader.clear();
	reader.seekg(0, std::ios::beg);
	bool LoadingFeats=false;

	std::string line;
	while (getline(reader, line))
	{
		//	std::cout << line << std::endl;
		//remove comments
		if (line.find("//") != std::string::npos)
		{
			int endchar = line.find("//");
			line = line.substr(0, endchar);
			//	std::cout << "ResultAfterComment " << line << std::endl;
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
			continue;
		}
		if (LoadingFeats == true)
		{
			if (Encounter.GetMasterFeatList().count(line))
			{
				Feats.push_back(*(Encounter.GetMasterFeatList())[line]);
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
	for (auto it = Feats.begin(); it != Feats.end(); it++)
	{
		(*it).DisplayFeatFullInfo();
	}
}

BodyLocation EntityClass::GetBodyLocation(std::string line)
{
	for (auto i = BodyLocationTextMap.begin(); i != BodyLocationTextMap.end(); i++)
	{
		if (line.find((*i).second) != std::string::npos)
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
				//check if we have the same item in our backpack or in the other hand
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