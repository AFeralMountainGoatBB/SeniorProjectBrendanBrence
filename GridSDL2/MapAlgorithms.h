/**********************************************************************************************//**
 * @file	MapAlgorithms.h.
 *
 * @brief	Declares the map algorithms class
 **************************************************************************************************/

#pragma once
#include "Tile.h"
#include "EncounterInstance.h"

/**********************************************************************************************//**
 * @class	SightAlgorithm
 *
 * @brief	A sight algorithm class, holds algorithms for determining visibility and sightlines
 *
 * @author	Brendan B
 * @date	9/3/2018
 **************************************************************************************************/

class SightAlgorithm
{
public:

	/**********************************************************************************************//**
	 * @fn	void SightAlgorithm::DetermineSightAndCover(std::vector<std::vector<Tile>> & TileMap, std::pair<int, int> Source, std::pair<int, int> Target );
	 *
	 * @brief	Determine sight and cover bools between source and target, result stored in m_blockedOrObstructed calls other functions in class to do this
	 *
	 * @author	Brendan B
	 * @date	9/3/2018
	 *
	 * @param [in,out]	TileMap	The tile map being used
	 * @param 		  	Source 	Source location
	 * @param 		  	Target 	Target location
	 **************************************************************************************************/

	void DetermineSightAndCover(std::vector<std::vector<Tile>> & TileMap, std::pair<int, int> Source, std::pair<int, int> Target );

	/**********************************************************************************************//**
	 * @fn	std::pair<bool, bool> SightAlgorithm::raytrace(std::pair<int, int> Source, std::pair<int, int> Target, std::vector<std::vector<Tile>> & TileMap);
	 *
	 * @brief	Raytraces between the source point and the target point on the passed TileMap, checking every tile inbetween checking for 
	 * 			tiles that block vision entirely and tiles that have units in them that partially obstruct vision
	 *
	 * @author	Brendan B
	 * @date	9/3/2018
	 *
	 * @param 		  	Source 	Source location
	 * @param 		  	Target 	Target location
	 * @param [in,out]	TileMap	The tile map.
	 *
	 * @return	A pair of bools where first represents if it is blocked and second represents obstructed 
	 **************************************************************************************************/

	std::pair<bool, bool> raytrace(std::pair<int, int> Source, std::pair<int, int> Target, std::vector<std::vector<Tile>> & TileMap);

	/**********************************************************************************************//**
	 * @fn	std::pair<bool,bool> SightAlgorithm::CheckAll(std::pair<int, int> Source, std::pair<int, int> Target, std::vector<std::vector<Tile>> & TileMap);
	 *
	 * @brief	calls raytrace with source, target and tilemap, and returns the result
	 *
	 * @author	Brendan B
	 * @date	9/3/2018
	 *
	 * @param 		  	Source 	Source for the.
	 * @param 		  	Target 	Target for the.
	 * @param [in,out]	TileMap	The tile map.
	 *
	 * @return	a pair of bools where the first represents vision being blocked entirely and second being blocked partially
	 **************************************************************************************************/

	std::pair<bool,bool> CheckAll(std::pair<int, int> Source, std::pair<int, int> Target, std::vector<std::vector<Tile>> & TileMap);

	/**********************************************************************************************//**
	 * @fn	std::pair<bool, bool> SightAlgorithm::CheckTile(int x, int y, std::vector<std::vector<Tile>> & TileMap);
	 *
	 * @brief	Checks tile to see if it is blocks sight entirely from different tiletypes or if an entity is present to partially block sight
	 *
	 * @author	Brendan B
	 * @date	9/3/2018
	 *
	 * @param 		  	x	   	The x coordinate of the tile
	 * @param 		  	y	   	The y coordinate of the tile
	 * @param [in,out]	TileMap	The tile map.
	 *
	 * @return	A pair of bools reflecting that first is total blockage and the second one is slight obstruction
	 **************************************************************************************************/

	std::pair<bool, bool> CheckTile(int x, int y, std::vector<std::vector<Tile>> & TileMap);

	/**********************************************************************************************//**
	 * @fn	std::pair<bool, bool> SightAlgorithm::GetBlockedOrObstructed()
	 *
	 * @brief	Gets blocked or obstructed value
	 *
	 * @author	Brendan B
	 * @date	9/3/2018
	 *
	 * @return	The blocked or obstructed.
	 **************************************************************************************************/

	std::pair<bool, bool> GetBlockedOrObstructed() { return m_BlockedOrObstructed; }

private:
	/** @brief	first is blocked, true if los blocked, second is obstructed, true if obstructed shot */
	std::pair<bool, bool> m_BlockedOrObstructed = { false,false };

};