#pragma once

/*
* This source file is a part of the 
*           ______                                  ___   ______
*          /      |                                |   | |      \
*         /       |                                |   | |       \
*        /        |                                |   | |        \
*       /    /|   |  ______     _______   __   __  |   | |   |\    \
*      /    / |   | |      \   |   ____| |  \ |  | |   | |   | \    \
*     /    /__|   | |  |)   |  |  |__    |   \|  | |   | |   |__\    \
*    /    ____    | |      /   |   __|   |       | |   | |    ___     \
*   /    /    |   | |   _  \   |  |      |       | |   | |   |    \    \
*  /    /     |   | |  | \  \  |  |____  |  |\   | |   | |   |     \    \
* /____/      |___| |__|  \__\ |_______| |__| \__| |___| |___|      \____\ project
* 
* Copyright (c) 2016-2017
*
* @author Johnny Guye
* @summary : This class represents a terrain and needs a correct sourceFile to be created.
* 
*/

#include <map>
#include <tuple>
#include <string>
#include <list>

#include "GameObject.h"
#include "SceneryObject.h"
#include "ExceptionArenIA.h"

class Terrain
{
	//typedef std::map<std::string, GameObject*> ObjectDataBase;
	// -- CONSTANTES
public:
	static const int CELL_SIZE = 100;
	static const double I_CELL_SIZE;
	// -- Member classes
protected:

	/** A class made for an easiest reading of the file 
	*	Assuming a tiled object can have all the attributes you want,
	*	this object can also catch all of them **/
	class DOMObject
	{
		typedef std::map<std::string, std::string> MapAttr;
	public:
		DOMObject(void);
		void setAttr(const std::string& attr, const std::string& value);
		std::string getAttr(const std::string& attr) const;
		std::string getName() const;
		std::string getType() const;
		Ogre::Vector2 getPosition() const;
		Ogre::Vector2 getDimension() const;
	protected:
		std::string name_;
		std::string type_;
		Ogre::Vector2 pos_;
		Ogre::Vector2 dim_;
		
		/** A list of the added attributes of an object **/
		MapAttr Attrs_;
	};

public:
	Terrain(const std::string& sourceFile);
	virtual ~Terrain(void);

	/** @brief verify collision between object and wall
	*	@return : true if other and a wall are coliding **/
	bool getCollision(GameObject* other);

	/** @brief verify if there is a wall in this cell
	*	@return : true if there is a wall there **/
	bool IsAWall(const int& x, const int& y);

	/** @brief give width of the terrain
	*	@return : width **/
	unsigned int getWidth() const;

	/** @brief give height of the terrain
	*	@return : height **/
	unsigned int getHeight() const;

	/** @brief get the name of the map
	*	@return a string of the map name **/
	std::string getName() const;

	/** @brief get the dimension of the terrain
	*	@return a Vector2 with the dimensions */
	Ogre::Vector2 getDimension() const;

	/** @brief get the element in the cell (x,y)
	**  @return : the Object in the cell, null if no Object there **/
	GameObject* getObjectInCell(int const& x, int const& y) const;

	/** @brief get the starting position in the map 
	*	@return a list of vectors with the centr positions **/
	std::list<Ogre::Vector3> getStarts() const;

	static int posToCell (const Ogre::Real& val);
	static Ogre::Real cellToPos(const int& val);

	
protected:
	void	LoadFromFile();
	void	InterpreterDOM(const DOMObject& domo);
	void	createObjectInCell (const int& x, const int& y, const std::string& num = "0");

protected:
	/// The name of the sourcefile
	std::string sourceFile_;

	/// The object grille representing the terrain
	GameObject*** grille_;
	
	///A list of vector3 for each position possible for a start
	std::list<Ogre::Vector3> starts_;

	//ObjectDataBase objectDataBase_;

	int		width_,		///Terrain width
			height_;	///Terrain height

	int		tilew_,		///tile width (only used for parsing)
			tileh_;		///tile height (only used for parsing)
};

