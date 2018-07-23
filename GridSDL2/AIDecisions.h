#pragma once
#include "GeneralHeaders.h"
#include "EntityClass.h"


class AIPlayer
{
public:
	std::pair<int, int> SelectTarget(std::vector<std::vector<Tile>>);

	void SetEntity(EntityClass &NewEntity) { ControlledEntity = &NewEntity; }
	EntityClass* GetEntity() { return ControlledEntity; }

private:
	
	EntityClass* ControlledEntity;
};