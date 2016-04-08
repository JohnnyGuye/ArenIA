#pragma once

#include <Ogre.h>
#include "Hitbox.h"

class GameObject
{
//Methods
public:
	GameObject(Ogre::Vector3 position = Ogre::Vector3::ZERO, std::string name = "");
	~GameObject(void);

	/** @brief true if the object is Impotent
	** @return the state of the status Impotent **/
	virtual bool isImpotent() const;

	/** @brief true if the object is Snared
	** @return the state of the status snared **/
	virtual bool isSnared() const;

	/** @brief true if the object is Immortal
	**	@return the state of the status immortal **/
	virtual bool isImmortal() const;

	/** @brief true if the object is in stase
	** @return true if all the three flags are true **/
	virtual bool isInStase() const;

	/** @brief set the status of the object
	**	@pram flag : the flags needed to set the status, by exemple, if you want,
	**	this object totally disabled you can set flag to IMMORTAL | SNARE | IMPOTENT (STASE does the same thing)
	**	this object totally able set flag to nothing (ABLE function too)
	**/
	virtual void setStatus	(const int flag = ABLE);

	/** @brief turn the orientation of the object
	*	@param the angle in degrees between the X-axis of the object, and the X-axis of the scene
	**/
	virtual void setOrientation (const Ogre::Degree& angle);

	/** @brief move the object to the location in param
	**  @param newPos : the new location **/
	virtual void setPosition	(Ogre::Vector3 const& newPos);

	/** @brief move the object in the direction given
	**	@param direction : the translation vector **/
	virtual bool move	(Ogre::Vector3 const& direction);
	
	/** @brief deal damages caused by a direct hit into the object
	**	@param other : the object in wich you collide **/
	virtual void dealHitBoxDamages	(GameObject* other) const;

	/** @brief the position of the object
	**	@return : the position **/
	virtual Ogre::Vector3	getPosition() const;

	/** @brief the angle between the Z axis of the map and the one of the object
	**	@return the angle in degrees **/
	virtual Ogre::Degree	getOrientation() const;

	/** @brief the direction the object is looking at
	** @return a vector pointing in the direction **/
	virtual Ogre::Vector3	getOrientationVect() const;

	/** @brief the name of this
	**	@return : the name **/
	virtual std::string		getName() const;
	
//Atributes
protected :
	/* About position **/
	Ogre::Vector3 position_;

	/* ABout rotation **/
	Ogre::Degree angle_;
	Ogre::Vector3 orientation_;

	/* About states **/
	bool	immortal_,
			snare_,
			impotent_;

	/* About properties **/
	std::string name_;

//Constantes
public :
	enum Status{
			ABLE = 0,
			IMMORTAL = 1,
			SNARE = 2,
			IMPOTENT = 4,
			STASE = 7
	};



};