#pragma once

#include <OgreVector3.h>

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

	inline Hitbox(BoxType boxType = EMPTY, Ogre::Vector3* position = nullptr, Ogre::Vector3 offset = Ogre::Vector3::ZERO)
		: boxType_(boxType),
		position_(position),
		offset_(offset)
	{
	}

	inline virtual ~Hitbox(void)
	{
	}

	inline virtual Ogre::Vector3 getCenter() {	return *position_ + offset_;	}
	inline virtual Ogre::Vector3* getPosition() const	{	return position_;	}
	inline virtual Ogre::Vector3 getOffset() const	{	return offset_;	}
	virtual bool intersect( Hitbox* hitbox) const = 0;

protected:
	BoxType			boxType_;
	Ogre::Vector3*	position_;
	Ogre::Vector3	offset_;
};

