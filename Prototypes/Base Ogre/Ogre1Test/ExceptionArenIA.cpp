#include "ExceptionArenIA.h"

using namespace std;


ExceptionArenIA::ExceptionArenIA(const ExceptionArenIACode& code, const string& description, const string& source)
	: number_(code), description_(description), source_(source)
{
}


ExceptionArenIA::~ExceptionArenIA(void)
{
}

int ExceptionArenIA::getErrorCode(void) const
{
	return number_;
}

const Ogre::String ExceptionArenIA::getDescription(void) const
{
	return description_;
}