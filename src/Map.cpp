#include "Map.h"
#include "TextureManager.h"

// array of tiles
int lvl1[20][25] = {
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

Map::Map()
{
	tile = TextureManager::LoadTexture("../Assets/tile.png");
	tile2 = TextureManager::LoadTexture("../Assets/tile2.png");
	tiledark = TextureManager::LoadTexture("../Assets/tiledark.png");
	tile2dark = TextureManager::LoadTexture("../Assets/tile2dark.png");
	
	tilered = TextureManager::LoadTexture("../Assets/tilered.png");
	tile2red = TextureManager::LoadTexture("../Assets/tile2red.png");
	tileblue = TextureManager::LoadTexture("../Assets/tileblue.png");
	tile2blue = TextureManager::LoadTexture("../Assets/tile2blue.png");


	LoadMap(lvl1);

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;
}

Map::~Map()
{
}

// load from array into map
void Map::LoadMap(int arr[20][25])
{
	for (int row = 0; row < 20; row++)
	{
		for (int col = 0; col < 25; col++)
		{
			map[row][col] = arr[row][col];
		}
	}
}

// render each tile of our array 
void Map::DrawMap()
{
	int type = 0;

	for (int row = 0; row < 20; row++)
	{
		for (int col = 0; col < 25; col++)
		{

			dest.x = col * 32;
			dest.y = row * 32;

			if (row % 2 == 0)
			{
				if (col % 2 == 0)
				{
					TextureManager::Draw(tile, src, dest);

				}
				else
				{
					TextureManager::Draw(tile2, src, dest);
				}
			}
			else
			{
				if (col % 2 == 0)
				{
					TextureManager::Draw(tile2, src, dest);

				}
				else
				{
					TextureManager::Draw(tile, src, dest);
				}
			}



			if (col > 9 && col < 15)
			{
				if (row % 2 == 0)
				{
					if (col % 2 == 0)
					{
						TextureManager::Draw(tiledark, src, dest);

					}
					else
					{
						TextureManager::Draw(tile2dark, src, dest);
					}
				}
				else
				{
					if (col % 2 == 0)
					{
						TextureManager::Draw(tile2dark, src, dest);

					}
					else
					{
						TextureManager::Draw(tiledark, src, dest);
					}
				}
			}

			if (row > 6 && row < 12)
			{
				if (col < 5)
				{


					if (row % 2 == 0)
					{
						if (col % 2 == 0)
						{
							TextureManager::Draw(tilered, src, dest);

						}
						else
						{
							TextureManager::Draw(tile2red, src, dest);
						}
					}
					else
					{
						if (col % 2 == 0)
						{
							TextureManager::Draw(tile2red, src, dest);

						}
						else
						{
							TextureManager::Draw(tilered, src, dest);
						}
					}
				}

				if (col > 19)
				{

					if (row % 2 == 0)
					{
						if (col % 2 == 0)
						{
							TextureManager::Draw(tileblue, src, dest);

						}
						else
						{
							TextureManager::Draw(tile2blue, src, dest);
						}
					}
					else
					{
						if (col % 2 == 0)
						{
							TextureManager::Draw(tile2blue, src, dest);

						}
						else
						{
							TextureManager::Draw(tileblue, src, dest);
						}
					}
				}

				
			}
		}
	}
}



