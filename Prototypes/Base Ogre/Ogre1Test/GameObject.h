#pragma once

#include <Ogre.h>
#include <OgreAxisAlignedBox.h>

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

	/** @brief move the object to the location in param
	**  @param newPos : the new location **/
	virtual bool setPosition	(Ogre::Vector3 const& newPos);

	/** @brief move the object in the direction given
	**	@param direction : the translation vector **/
	virtual bool move	(Ogre::Vector3 const& direction);

	/** @brief deal damages caused by a direct hit into the object
	**	@param other : the object in wich you collide **/
	virtual void dealHitBoxDamages	(GameObject* other) const;

	/** @brief the position of the object
	**	@return : the position **/
	virtual Ogre::Vector3	getPosition() const;

	/** @brief the name of this
	**	@return : the name **/
	virtual std::string		getName() const;
	
//Atributes
protected :
	Ogre::Vector3 position_;
	bool	immortal_,
			snare_,
			impotent_;
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