#include "GameObject.h"

using namespace std;
using namespace Ogre;

GameObject::GameObject(Ogre::Vector3 position, std::string name)
	: name_(name), 
	position_(position),
	orientation_(Vector3::UNIT_X)
{
	setStatus();
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

void GameObject::setPosition(Ogre::Vector3 const& newPos)
{
	position_ = newPos;
}

void GameObject::setOrientation(const Degree& angle)
{
	orientation_;
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

Vector3 GameObject::getPosition() const
{
	return position_;
}

Vector3 GameObject::getOrientation() const
{
	return orientation_;
}

string GameObject::getName() const
{
	return name_;
}