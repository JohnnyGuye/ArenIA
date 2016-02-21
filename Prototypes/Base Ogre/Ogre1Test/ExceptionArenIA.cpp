#include "ExceptionArenIA.h"

using namespace std;


ExceptionArenIA::ExceptionArenIA(int number, const string& description, const string& source)
	: number_(number), description_(description), source_(source)
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