#pragma once
#include "GeneralHeaders.h"
#include "Feats.h"

class ProfessionClass
{
public: 
	void SetLevelOne(LevelClass* level) { ProfessionLevelOne = level; }
	void SetLevelTwo(LevelClass* level) { ProfessionLevelTwo = level; }
	void SetLevelThree(LevelClass* level) { ProfessionLevelThree = level; }
	void SetLevelFour(LevelClass* level) { ProfessionLevelFour = level; }
	void SetLevelFive(LevelClass* level) { ProfessionLevelFive = level; }
	void SetLevelSix(LevelClass* level) { ProfessionLevelSix = level; }

	LevelClass* GetLevelOne() { return ProfessionLevelOne; }
	LevelClass* GetLevelTwo() { return ProfessionLevelTwo; }
	LevelClass* GetLevelThree() {return ProfessionLevelThree; }
	LevelClass* GetLevelFour() { return ProfessionLevelFour; }
	LevelClass* GetLevelFive() { return ProfessionLevelFive; }
	LevelClass* GetLevelSix() { return ProfessionLevelSix; }

	//bool LoadLevels(std::string path);

private:
	LevelClass* ProfessionLevelOne;
	LevelClass* ProfessionLevelTwo;
	LevelClass* ProfessionLevelThree;
	LevelClass* ProfessionLevelFour;
	LevelClass* ProfessionLevelFive;
	LevelClass* ProfessionLevelSix;
};


class LevelClass 
{
public:
	void SetStrengthSaveBonus(int Save) { StrengthSaveBonus = Save; }
	int GetStrengthSaveBonus() { return StrengthSaveBonus; }
	void SetWisdomSaveBonus(int Save) { WisdomSaveBonus = Save; }
	int GetWisdomSaveBonus() { return WisdomSaveBonus; }
	int GetCharismaSaveBonus() { return CharismaSaveBonus; }
	void SetCharismaSaveBonus(int Save) { CharismaSaveBonus = Save; }

	void AddFeat(FeatClass* featptr) { AddFeats.push_back(featptr); }
	std::vector<FeatClass*> GetFeats() { return AddFeats; }

	void SetHitDice(int number, DiceType dice) { TotalHitDice.first = number; TotalHitDice.second = dice; }
	std::pair<int, DiceType> GetHitDice() { return TotalHitDice; }

	void SetTotalBaB(int totalbab) { TotalBaseAttackBonus = totalbab; }
	int GetTotalBab() { return TotalBaseAttackBonus; }

private:

	int StrengthSaveBonus=0;
	int WisdomSaveBonus=0;
	int CharismaSaveBonus=0;
	std::vector<FeatClass*> AddFeats;
	std::pair<int, DiceType> TotalHitDice;
	int TotalBaseAttackBonus=0;

};

