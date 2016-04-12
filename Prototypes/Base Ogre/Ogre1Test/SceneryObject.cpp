#include "SceneryObject.h"

using namespace std;

SceneryObject::SceneryObject(Ogre::Vector3 position, const int& num)
	: 
	GameObject(position, "Wall"), 
	cellType(num)
{
}

int SceneryObject::getType() const
{
	return cellType;
}


SceneryObject::~SceneryObject(void)
{
}
