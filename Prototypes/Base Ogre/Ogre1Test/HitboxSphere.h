#pragma once
#include "Hitbox.h"

class HitboxSphere :
	public Hitbox
{
public:

	inline HitboxSphere(Ogre::Vector3 position, const Ogre::Real& rad = 50, Ogre::Vector3 offset = Ogre::Vector3::ZERO)
		: Hitbox(position, offset, SPHERE),
		radius_(rad)
	{
	}

	inline HitboxSphere(const HitboxSphere& rhs)
		: Hitbox(*(rhs.position_), rhs.offset_, SPHERE),
		radius_(rhs.radius_)
	{

	}
	inline virtual ~HitboxSphere(void)
	{
	}

	inline virtual Ogre::Real getRadius()	{	return radius_;	}

	inline virtual bool intersect(Hitbox* hitbox) const
	{
		switch(hitbox->boxType_)
		{
		case SPHERE:
			HitboxSphere * sphere = (HitboxSphere*)hitbox;
			Ogre::Real rad2(radius_ + sphere->radius_);
			return (sphere->position_->squaredDistance(*position_) < (rad2 * rad2) ? true : false);
		default:
			return false;
		}
	}

	inline virtual HitboxSphere* clone() const { return new HitboxSphere(*this);	};

protected:
	Ogre::Real		radius_;
};

