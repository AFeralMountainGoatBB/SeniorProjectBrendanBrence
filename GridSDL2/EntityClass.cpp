#include "EntityClass.h"
#include "Dot.h"
#include "StaticFunctions.h"
#include "Texture.h"
#include "Tile.h"
#include "PickupItemsMenu.h"

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
	mBox.y = 0;
	mBox.w = ENTITY_WIDTH;
	mBox.h = ENTITY_HEIGHT;
	std::cout << "Entity size, H, w : " << mBox.w << " " << mBox.h << std::endl;
}

void EntityClass::SetTexture(std::map<std::string, LTexture*> &TextureMap, std::string Path)
{
	if (TextureMap.count(Path + "\\" + mPathTexture)) 
	{
		mTexture = TextureMap[Path + "\\" + mPathTexture];
		std::cout << mPathTexture << " Loaded into " << EntityName <<  std::endl;
	}
	else
	{
		std::cout << "No matching texture found " << Path << "\\" << mPathTexture << std::endl;
	}
	
}


LTexture* EntityClass::GetTexture()
{
	return mTexture;
}
/*--------------START GETTERS -------------------*/

const int EntityClass::GetHitPoints()
{
	return this->HitPoints;
}

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

bool EntityClass::EntityAttack(std::vector<std::vector<Tile>> &TileVector)
{
	//call EntityAttackTile, if not null call selected attack roll
	EntityClass* Target = EntityAttackTile(TileVector);
	if (Target != NULL)
	{
		//do the roll and see if it hits
		if (MeleeAttackRoll(*Target))
		{
			int Damage = MeleeAttackDamage(*Target); //calculate damage
			//deal damage
			Target->TakeDamage(Damage, PIERCE);
			//if target is dead/unconscious, 
			//and this entity has cleave or GreaterCleave, then activate cleave todo
		}
	}

	return false;
}

bool EntityClass::MeleeAttackRoll(EntityClass &Target)
{
	//get total bonuses
	//roll d20+bonuses
	//compare to target's AC
	//return true if hit, return false if miss
	
	int TotalBonuses = BaseAttackBonus;
	int AttackRoll = TotalBonuses + DiceRoll(D20);
	std::cout << EntityName << " attack roll = " << AttackRoll << std::endl;
	if (AttackRoll >= Target.GetArmorClass())
	{
		//then the attack was a success, return true
		return true;
	}
	else
	{
		//then the attack fails
		return false;
	}
}

int EntityClass::MeleeAttackDamage(EntityClass &Target)
{
	int TotalDamage = 0;
	//get weapon type and required proficency
	TotalDamage += DiceRoll(D3);
	//add all bonuses to damage together, including proficiency bonuses
	//roll damage and add together
	//return total damage
	std::cout << "Dealing " << TotalDamage << " damage";
	return TotalDamage;
}

void EntityClass::TakeDamage(int Damage, DamageType DamageType)
{
	//find any resistances, immunities calculate as full resistance
	//subtract resisted damage from total damage
	//subtract Damage reduction from total damage
	//finally subtract from health pool
	HitPoints -= Damage;
}

EntityClass* EntityClass::EntityAttackTile(std::vector<std::vector<Tile>> &TileVector)
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
	} //end switch statement
	
	MoveDirection = STATIONARY;
	return NULL;
}

const int EntityClass::GetArmorClass()
{
	std::cout << EntityName << " has armor class of " << ArmorClass << std::endl;
	return ArmorClass;
}

ObjectClass* EntityClass::GetEquipmentInSlot(BodyLocation Location)
{
	return Equipment.find(Location)->second;
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
	if (Weapon->GetTwoHanded())
	{
		if (GetEquipmentInSlot(MAINHAND) == NULL && GetEquipmentInSlot(OFFHAND) == NULL)
		{
			if (EquipMainHandWeapon(Weapon) && EquipOffHandWeapon(Weapon))
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
		if (GetEquipmentInSlot(MAINHAND) == NULL || GetEquipmentInSlot(OFFHAND) == NULL)
		{
			if (!EquipMainHandWeapon(Weapon))
			{
				if (!EquipOffHandWeapon(Weapon))
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
				return true;
			}
		}
	}	
}

bool EntityClass::EquipMainHandWeapon(ObjectClass* Weapon)
{
	if (GetEquipmentInSlot(MAINHAND) == NULL)
	{
		Equipment.find(MAINHAND)->second = Weapon;
		return true; //successfull equip
	}
	else
	{
		return false;
	}
}

bool EntityClass::EquipOffHandWeapon(ObjectClass* Weapon)
{
	if (GetEquipmentInSlot(OFFHAND) == NULL)
	{
		Equipment.find(OFFHAND)->second = Weapon;
		return true; // succesfull equip
	}
	else
	{
		return false;
	}
}

void EntityClass::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//change the location
		switch (e.key.keysym.sym)
		{
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
			if (GetControlMode() != ATTACKMODE && GetControlMode()!=NOCONTROLMODE) 
			{
			SetControlMode(ATTACKMODE);
			}
			else if(GetControlMode()!=NOCONTROLMODE)
			{
				SetControlMode(MOVEMODE);
			}
			std::cout << "Switching attack mode" << std::endl;
			break;
		case SDLK_2:
			if (GetControlMode() != PICKUPMODE && GetControlMode() != NOCONTROLMODE)
			{
				SetControlMode(PICKUPMODE);
			}
			else if(GetControlMode()!=NOCONTROLMODE)
			{
				SetControlMode(MOVEMODE);
			}
		}
	
	}
}

void EntityClass::move(std::vector<std::vector<Tile>> &TileVector)
{
	if (MoveDirection == STATIONARY)
	{
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		return;
	}

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
			
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case NORTHEAST:
		FaceDirection = NORTHEAST;
		if (mLocation.second != 0 && TileVector[mLocation.first][mLocation.second - 1].getPassable()
			&&
			mLocation.first < TileVector.size() - 1 && TileVector[mLocation.first + 1][mLocation.second].getPassable()
			&&
			TileVector[mLocation.first + 1][mLocation.second - 1].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.first++;
			mLocation.second--;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case EAST: 
		FaceDirection = EAST;
		if (mLocation.first < TileVector.size()-1 && TileVector[mLocation.first+1][mLocation.second].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.first++;
			
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case SOUTHEAST:
		FaceDirection = SOUTHEAST;
		if (mLocation.first < TileVector.size() - 1 && TileVector[mLocation.first + 1][mLocation.second].getPassable()
			&&
			mLocation.second < TileVector[0].size() - 1 && TileVector[mLocation.first][mLocation.second + 1].getPassable()
			&&
			TileVector[mLocation.first + 1][mLocation.second + 1].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.first++;
			mLocation.second++;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case SOUTH: 
		FaceDirection = SOUTH;
		if (mLocation.second < TileVector[0].size() - 1 && TileVector[mLocation.first][mLocation.second+1].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
		mLocation.second++; 
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case SOUTHWEST:
		FaceDirection = SOUTHWEST;
		if (mLocation.second < TileVector[0].size() - 1 && TileVector[mLocation.first][mLocation.second + 1].getPassable()
			&&
			mLocation.first != 0 && TileVector[mLocation.first - 1][mLocation.second].getPassable()
			&&
			TileVector[mLocation.first-1][mLocation.second+1].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.second++;
			mLocation.first--;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case WEST: 
		FaceDirection = WEST;

		if (mLocation.first !=0 && TileVector[mLocation.first - 1][mLocation.second].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.first--;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;

	case NORTHWEST:
		FaceDirection = NORTHWEST;

		if (mLocation.first != 0 && TileVector[mLocation.first - 1][mLocation.second].getPassable()
			&&
			mLocation.second != 0 && TileVector[mLocation.first][mLocation.second - 1].getPassable()
			&&
			TileVector[mLocation.first - 1][mLocation.second -1].getPassable())
		{
			TileVector[mLocation.first][mLocation.second].ClearOccupant();
			mLocation.first--;
			mLocation.second--;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
		}
		TileVector[mLocation.first][mLocation.second].SetOccupant(*this);
		break;
	} //end switch statement

	//std::cout << "Man moved in function, setting rend location " << std::endl;
	//std::cout << "Attempted to move" << std::endl;

	SetRendLocation(TileVector);
	MoveDirection = STATIONARY;
	}


void EntityClass::setCamera(SDL_Rect& camera)
{
	//Center the camera over the entity
	camera.x = (mBox.x + ENTITY_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (mBox.y + ENTITY_HEIGHT / 2) - SCREEN_HEIGHT / 2;

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
	std::cout << "New rend location=" << mBox.x << " " << mBox.y << std::endl;
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

ObjectClass* EntityClass:: PickupTile(std::vector<std::vector<Tile>> &TileVector)
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
	DisplayEntireInventory();
	return;
}

bool EntityClass::EquipObject(ObjectClass* item)
{
	std::cout << "Equipping " << item->GetName() << " in the " << BodyLocationTextMap[item->GetBodySlot()] << std::endl;
	if (item->GetBodySlot() == MAINHAND || item->GetBodySlot() == OFFHAND)
	{
		std::cout << "Attempting to equip as a weapon" << std::endl;
		if (this->EquipAsWeapon(item))
		{
			std::cout << "Equipped as a legitimate weapon" << std::endl;
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
