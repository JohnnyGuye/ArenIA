#include "GameObject.h"

using namespace std;
using namespace Ogre;

GameObject::GameObject(Ogre::Vector3 position, std::string name)
	: name_(name), 
	position_(position),
	dead_(false)
{
	setStatus();
	setOrientation(Degree(0));
}

GameObject::~GameObject(void)
{
}

//Getters on state

bool GameObject::isImpotent() const
{
	return impotent_;
}

bool GameObject::isSnared() const
{
	return snare_;
}

bool GameObject::isInvincible() const
{
	return invincible_;
}

bool GameObject::isInStase() const
{
	return (impotent_ && snare_ && invincible_);
}

bool GameObject::isDead() const
{
	return dead_;
}

//Getters

Vector3 GameObject::getPosition() const
{
	return position_;
}

Degree GameObject::getOrientation() const
{
	return angle_;
}

Vector3 GameObject::getOrientationVect() const
{
	return orientation_;
}

string GameObject::getName() const
{
	return name_;
}

//Setters

void GameObject::setStatus(const int flag)
{
	snare_		= ((flag & SNARE) == 1);
	invincible_	= ((flag & INVINCIBLE) == 1);
	impotent_	= ((flag & IMPOTENT) == 1);
}

void GameObject::kill()
{
	dead_ = true;
}

void GameObject::setPosition(Ogre::Vector3 const& newPos)
{
	position_ = newPos;
}

void GameObject::setOrientation(const Degree& angle)
{
	angle_ = angle;
	Real cos = Math::Cos(angle.valueRadians());
	Real sin = Math::Sin(angle.valueRadians());

	orientation_ = Ogre::Vector3(sin, 0, cos);
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