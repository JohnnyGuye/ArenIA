#pragma once

class Hitbox
{
public:
	enum BoxType {
		AABB,
		OBB,
		SPHERE,
		PLANE,
		EMPTY
	};
public:

	Hitbox(BoxType boxType = EMPTY)
	{
	}

	virtual ~Hitbox(void)
	{
	}
	virtual bool intersect( Hitbox* hitbox) const = 0;

protected:
	BoxType boxType_;
};

