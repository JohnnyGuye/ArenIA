#pragma once
#include "hitbox.h"
#include <OgreSphere.h>

class HitboxSphere :
	public Hitbox
{
public:

	HitboxSphere(void)
		: Hitbox(SPHERE)
	{
	}

	virtual ~HitboxSphere(void)
	{
	}

	virtual Ogre::Sphere getSphere() const
	{
		return sphere_;
	}

	virtual bool intersect(Hitbox* hitbox) const
	{
		switch(hitbox->boxType_)
		{
		case SPHERE:
			HitboxSphere * sphere = (HitboxSphere*)hitbox;
			sphere_.intersects(sphere->getSphere());
		}
	}

protected:
	Ogre::Sphere sphere_;
};

