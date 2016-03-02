#include "GameObject.h"

using namespace std;

GameObject::GameObject(Ogre::Vector3 position, std::string name)
	: name_(name), position_(position)
{
}


GameObject::~GameObject(void)
{
}

bool GameObject::isImpotent() const
{
	return impotent_;
}

bool GameObject::isSnared() const
{
	return snare_;
}

bool GameObject::isImmortal() const
{
	return immortal_;
}
bool GameObject::isInStase() const
{
	return (impotent_ && snare_ && immortal_);
}

void GameObject::setStatus(const int flag)
{
	snare_		= ((flag & SNARE) == 1);
	immortal_	= ((flag & IMMORTAL) == 1);
	impotent_	= ((flag & IMPOTENT) == 1);
}

bool GameObject::setPosition(Ogre::Vector3 const& newPos)
{
	if(isSnared())	return false;
	position_ = newPos;
	return true;
}

bool GameObject::move(Ogre::Vector3 const& direction)
{
	if(isSnared())	return false;
	position_ += direction;
	return true;
}

//TODO
void GameObject::dealHitBoxDamages(GameObject* other) const
{

}

Ogre::Vector3 GameObject::getPosition() const
{
	return position_;
}

string GameObject::getName() const
{
	return name_;
}