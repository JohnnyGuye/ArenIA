#include "Terrain.h"

#include "Log.h"

using namespace std;
using namespace Ogre;

//============= CONSTANTS ====================

const double Terrain::I_CELL_SIZE = 1 / (double)CELL_SIZE;

// ============ DOMObject METHODS ============

Terrain::DOMObject::DOMObject(void)
	: name_(""), 
	type_(""), 
	pos_(Vector2::ZERO), 
	dim_(Vector2::ZERO)
{
}

void Terrain::DOMObject::setAttr(const string& attr, const string& value)
{
	if(attr == "#")				name_ = value;
	else if(attr == "type")		type_ = value;
	else if(attr == "X" || attr == "x")		pos_.x = Real(stoi(value));
	else if(attr == "Y" || attr == "y")		pos_.y = Real(stoi(value));
	else if(attr == "width" || attr == "w")		dim_.x = Real(stoi(value));
	else if(attr == "height" || attr == "h")	dim_.y = Real(stoi(value));
	else Attrs_.insert(pair<string, string>(attr, value));
}

string Terrain::DOMObject::getName() const
{
	return name_;
}

string Terrain::DOMObject::getType() const
{
	return type_;
}

string Terrain::DOMObject::getAttr(const string& attr) const
{
	MapAttr::const_iterator it = Attrs_.find(attr);
	if(it != Attrs_.cend())
		return it->second;
	else
		return "NOT_KNOWN";
}

Vector2 Terrain::DOMObject::getPosition() const
{
	return pos_;
}

Vector2 Terrain::DOMObject::getDimension() const
{
	return dim_;
}

// ============= TERRAIN METHODS =============

Terrain::Terrain(const string& sourceFile)
	: sourceFile_(sourceFile), 
	width_(0), 
	height_(0),
	grille_(nullptr),
	starts_()
{
	try{
		LoadFromFile();
	}
	catch (ExceptionArenIA e)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(NULL, e.getDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		ArenIA::Log::getInstance()->write(e.getDescription());
#else
            std::cerr << "An exception has occurred: " <<
                e.getDescription().c_str() << std::endl;
#endif
	}
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

//--------------------------------------------Private

void Terrain::LoadFromFile()
{
	enum ZONE {
		HEADER, 
		TILESET, 
		LAYER, 
		OBJECTS
		};

	ArenIA::Log::getInstance()->write("Parsing the map");

	std::string path = "../Media/maps/";
	std::ifstream mapFile(path + sourceFile_, ios::in);
	std::string sRead;

	if(mapFile)
	{

		ZONE curs = HEADER;

		while(getline(mapFile, sRead))
		{
			std::stringstream mainFlux(sRead);

			if(sRead == "[header]")			curs = HEADER;
			else if(sRead == "[tilesets]")	curs = TILESET;
			else if(sRead == "[layer]")		curs = LAYER;
			else if(sRead.length() > 0 && sRead.at(0) == '[')		curs = OBJECTS;
			else 
			{
				switch(curs)
				{
				case HEADER:
					getline(mainFlux, sRead , '=');
					if(sRead == "width")
					{
						getline(mainFlux, sRead);
						width_ = std::stoi(sRead);
					}
					else if(sRead == "height")
					{
						getline(mainFlux, sRead);
						height_ = std::stoi(sRead);
					}
					else if(sRead == "tilewidth")
					{
						getline(mainFlux, sRead);
						tilew_ = std::stoi(sRead);
					}
					else if(sRead == "tileheight")
					{
						getline(mainFlux, sRead);
						tileh_ = std::stoi(sRead);
					}
					else
					{
					}
					break;
				case LAYER:
					getline(mainFlux, sRead , '=');
					if(sRead == "type")
					{
						getline(mainFlux, sRead);
					}
					else if(sRead == "data")
					{
						if(grille_ != nullptr)//Don't be a fool, only one layer per map
						{
							std::stringstream ss;
							ss << "WARNING !!! Two layers or more created on the map " << sourceFile_;
							ArenIA::Log::getInstance()->write(ss.str());
							for(int i = 0; i < height_;i++)
							{	
								for(int j = 0; j < width_; j++)
								{
									delete grille_[i][j];
								}
								delete grille_[i];
							}
							delete grille_;
						}
						grille_ = new GameObject**[width_];
						for(int i = 0; i < height_; i++){	grille_[i] = new GameObject*[width_];	}

						for(int i = 0; i < height_-1;i++)
						{
							for(int j = 0; j < width_; j++)
							{
								getline(mapFile, sRead, ',');
								createObjectInCell(i, j, sRead);
							}
						}
						for(int j = 0; j < width_ -1; j++)
						{
							getline(mapFile, sRead, ',');
							createObjectInCell(height_ - 1, j, sRead);
						}
						getline(mapFile, sRead);
						createObjectInCell(height_ - 1, width_ -1, sRead);
					}
					else
					{

					}
					break;
				case OBJECTS:
					{
						DOMObject domo = DOMObject();
						string value;
						
						//Get the name of the object
						if(sRead != "")
						{
							std::stringstream liness(sRead);
							getline(liness, sRead, ' ');
							getline(liness, value);
							domo.setAttr(sRead, value);
						}

						getline(mapFile, sRead);
						while(!sRead.empty() && !mapFile.eof())
						{

							std::stringstream liness(sRead);

							getline(liness, sRead, '=');//Separate it 
							
							//sRead: the attribute, value: the value
							if(sRead == "type")
							{
								getline(liness, value);
								domo.setAttr(sRead, value);
							}
							else if(sRead == "location")
							{
								getline(liness, value, ',');
								domo.setAttr("X", value);
								getline(liness, value, ',');
								domo.setAttr("Y", value);
								getline(liness, value, ',');
								domo.setAttr("width", value);
								getline(liness, value, ',');
								domo.setAttr("height", value);
							}
							else
							{
								getline(liness, value);
								domo.setAttr(sRead, value);
							}
							liness.flush();
							getline(mapFile, sRead);
						}
						
						InterpreterDOM(domo);
						
					}//--OBJECTS anonym-bloc
					
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

void Terrain::InterpreterDOM(const DOMObject& domo)
{
	std::stringstream ss;
	ss << "Domo: " << domo.getName() << " " << domo.getType() << " " << domo.getPosition() << " " << domo.getDimension();
	ArenIA::Log::getInstance()->write(ss.str());
	if(domo.getType() == "Start")
	{
		Vector2 pos = domo.getPosition();
		starts_.push_back(Vector3(cellToPos((int)pos.x), 0, cellToPos((int)pos.y)));
	}
}

void Terrain::createObjectInCell(const int& x, const int& y, const string& nums)
{	
	if(nums == "0" || nums == "256")
		grille_[x][y] = nullptr;
	else
		grille_[x][y] = new SceneryObject(Vector3(Real(100.0 * y), 0, Real(100.0 * x)), nums);
}

//---------------------------------------------Public
bool Terrain::getCollision(GameObject* other)
{
	Vector3 pos = other->getPosition();
	if(grille_[posToCell(pos.z)][posToCell(pos.x)] == nullptr) return false;
	return true;
}

Vector3 Terrain::resolveCollision(GameObject* object) const
{
	Vector3 pos = object->getPosition();
	return pos;
}

bool Terrain::IsAWall(const int& x, const int& y) const
{
	return (((SceneryObject*)grille_[x][y])->getType() == "0");
}

GameObject* Terrain::getObjectInCell(const int& x, const int& y) const
{
	return grille_[x][y];
}

unsigned int Terrain::getWidth() const
{
	return width_;
}

unsigned int Terrain::getHeight() const
{
	return height_;
}

string Terrain::getName() const
{
	return sourceFile_;
}

Vector2 Terrain::getDimension() const
{
	return Vector2(Real(width_) * CELL_SIZE, Real(height_) * CELL_SIZE);
}

std::list<Ogre::Vector3> Terrain::getStarts() const
{
	return starts_;
}

//--------------------------------------------Static
int Terrain::posToCell(const Ogre::Real& p)
{
	return (int)(p * I_CELL_SIZE);
}

Real Terrain::cellToPos(const int& val)
{
	return Real(((float)val + 0.5f) * CELL_SIZE);
}
