#pragma once

#include <OGRE/OgreString.h>

class ExceptionArenIA
{
public:
	ExceptionArenIA(int number, const Ogre::String& description, const Ogre::String& source);
	virtual ~ExceptionArenIA(void);

	enum ExceptionArenIACode {
		FILE_NOT_FOUND,
		CANNOT_WRITE_IN_FILE,
		ERROR_NOT_KNOW
	};

	virtual int getErrorCode() const;
	virtual const Ogre::String getDescription() const;

protected :
	int number_;
	std::string description_;
	std::string source_;
};

