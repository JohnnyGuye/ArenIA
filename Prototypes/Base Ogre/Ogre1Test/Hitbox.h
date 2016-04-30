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

	inline Hitbox( Ogre::Vector3 position, Ogre::Vector3 offset = Ogre::Vector3::ZERO, BoxType boxType = EMPTY)
		: boxType_(boxType),
		offset_(offset)
	{
		position_ = &position ;
	}

	inline virtual ~Hitbox(void){}

	inline virtual Ogre::Vector3 getCenter() {	return *position_ + offset_;	}
	inline virtual Ogre::Vector3 getPosition()	{	return *position_;	}
	inline virtual Ogre::Vector3 getOffset() const	{	return offset_;	}

	virtual bool intersect( Hitbox* hitbox) const = 0;
	inline virtual Hitbox* clone() const = 0;

protected:
	BoxType			boxType_;
	Ogre::Vector3*	position_;
	Ogre::Vector3	offset_;
};

