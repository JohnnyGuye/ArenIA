#include "Terrain.h"

using namespace std;

Terrain::Terrain(const string& sourceFile)
	: sourceFile_(sourceFile), width_(1), height_(1)
{
	try{
		LoadFromFile();
	}
	catch (ExceptionArenIA e)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(NULL, e.getDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getDescription().c_str() << std::endl;
#endif
	}
}

void Terrain::LoadFromFile()
{
	const int HEADER = 0;
	const int TILESET = 1;
	const int LAYER = 2;

	std::string path = "../Media/maps/";
	std::ifstream mapFile(path + sourceFile_, ios::in);
	std::string bean;

	if(mapFile)
	{

		int curs = HEADER;

		std::string line;
		while(getline(mapFile, line))
		{
			std::stringstream liness(line);

			if(line == "[header]")			curs = HEADER;
			else if(line == "[tilesets]")	curs = TILESET;
			else if(line == "[layer]")		curs = LAYER;
			else 
			{
				switch(curs)
				{
				case HEADER:
					getline(liness, bean , '=');
					if(bean == "width")
					{
						getline(liness, bean);
						width_ = std::stoi(bean);
					}
					else if(bean == "height")
					{
						getline(liness, bean);
						height_ = std::stoi(bean);
					}
					else
					{
					}
					break;
				case LAYER:
					getline(liness, bean , '=');
					if(bean == "type")
					{
						getline(liness, bean);
					}
					else if(bean == "data")
					{
						//Create the grille, considering the grille is empty
						grille_ = new GameObject**[width_];
						for(int i = 0; i < width_; i++){	grille_[i] = new GameObject*[height_];	}

						for(int i = 0; i < width_;i++)
						{
							for(int j = 0; j < height_ - 1; j++)
							{
								getline(mapFile, bean, ',');
								grille_[i][j] = new GameObject(Ogre::Vector3(100 * i, 0, 100 * j), bean);
							}

							getline(mapFile, bean);
							grille_[i][height_] = new GameObject(Ogre::Vector3(100 * i, 0, 100 * (height_-1)), bean);
						}
					}
					else
					{

					}
					break;
				case TILESET:
				default:
					break;
				}
			}
		}

		mapFile.close();
	}
	else
	{
		throw ExceptionArenIA(ExceptionArenIA::FILE_NOT_FOUND, "Enable to read in file", sourceFile_);
	}
}

bool Terrain::getCollision(GameObject* other)
{
	return false;
}

GameObject*** Terrain::getGrille()
{
	return grille_;
}

unsigned int Terrain::getWidth() const
{
	return width_;
}

unsigned int Terrain::getHeight() const
{
	return height_;
}

Terrain::~Terrain(void)
{

	for(int i = 0; i < width_;i++)
	{	
		for(int j = 0; j < height_; j++)
		{
			delete grille_[i][j];
		}
		delete grille_[i];
	}
	delete grille_;
}
