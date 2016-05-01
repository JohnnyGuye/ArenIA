#pragma once

#include "hitbox.h"

class HitboxVoid :
	public Hitbox
{
public:

	HitboxVoid(void)
		: Hitbox(nullptr)
	{
	}

	virtual HitboxVoid* clone() const {	return new HitboxVoid(*this);	}

	virtual ~HitboxVoid(void)
	{
	}

	virtual bool intersect(Hitbox* hitbox) const
	{
		return false;
	}
};

