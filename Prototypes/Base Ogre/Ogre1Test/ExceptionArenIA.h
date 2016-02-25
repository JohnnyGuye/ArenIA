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
* /____/      |___| |__|  \__\ |_______| |__| \__| |___| |___|project____\
* 
* Copyright (c) 2016-2017
*
* @author Johnny Guye
* @summary : This class is only for exception. Sometimes things goes truly wrong.
* The only way to catch it is to create our own exception system. I already 
* needed three of them. Feel free to add yours and complete the class.
*/


#include <OGRE/OgreString.h>

class ExceptionArenIA
{
public:
	enum ExceptionArenIACode {
		FILE_NOT_FOUND,
		CANNOT_WRITE_IN_FILE,
		ERROR_NOT_KNOW
	};

	ExceptionArenIA(const ExceptionArenIACode& code, const Ogre::String& description, const Ogre::String& source);
	virtual ~ExceptionArenIA(void);

	
	virtual int getErrorCode() const;
	virtual const Ogre::String getDescription() const;

protected :
	ExceptionArenIACode number_;
	std::string description_;
	std::string source_;
};

