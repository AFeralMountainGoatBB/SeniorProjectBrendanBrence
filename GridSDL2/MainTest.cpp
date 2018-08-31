/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, strings, and file streams


#include "GeneralHeaders.h"
#include "GameInstance.h"
#include "Tile.h"
#include "Texture.h"
#include "StaticFunctions.h"


//Find all "^(?!(\s*\*))(?!(\s*\-\-\>))(?!(\s*\<\!\-\-))(?!(\s*\n))(?!(\s*\*\/))(?!(\s*\/\*))(?!(\s*\/\/\/))(?!(\s*\/\/))(?!(\s*\}))(?!(\s*\{))(?!(\s(using))).*$"

int main(int argc, char* args[])
{
	//make new seed
	srand(time(NULL));

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	GameInstance Master;
	
	//int m_retval = Master.EncounterRun(Master.GetScenarioPath()+"\\"+"Battle of the bridge.txt");
	int m_retval = Master.MenuOperation();
	return m_retval;
}
