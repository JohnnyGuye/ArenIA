#pragma once

#include "GameObject.h"
#include <map>
#include <string>
#include "ExceptionArenIA.h"

class Terrain
{
	typedef std::map<std::string, GameObject*> ObjectDataBase;

public:
	Terrain(const std::string& sourceFile = "essai1.txt");
	virtual ~Terrain(void);

	
	virtual bool getCollision(GameObject* other);

	virtual unsigned int getWidth() const;
	virtual unsigned int getHeight() const;

	virtual GameObject*** getGrille();
	
protected:
	virtual void LoadFromFile();

protected:
	std::string sourceFile_;
	GameObject*** grille_;
	ObjectDataBase objectDataBase_;

	int width_;
	int height_;
	int caseDim_;

};

