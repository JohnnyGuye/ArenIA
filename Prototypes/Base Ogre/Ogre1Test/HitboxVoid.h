#pragma once

#include "hitbox.h"

class HitboxVoid :
	public Hitbox
{
public:

	HitboxVoid(void)
		: Hitbox()
	{
	}

	virtual ~HitboxVoid(void)
	{
	}

	virtual bool intersect(Hitbox* hitbox) const
	{
		return false;
	}
};

