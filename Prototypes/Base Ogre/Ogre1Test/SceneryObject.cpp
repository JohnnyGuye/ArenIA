#include "SceneryObject.h"

using namespace std;

SceneryObject::SceneryObject(Ogre::Vector3 position, std::string name)
	: 
	GameObject(position, name), 
	cellType(name)
{
}

string SceneryObject::getType() const
{
	return cellType;
}


SceneryObject::~SceneryObject(void)
{
}
