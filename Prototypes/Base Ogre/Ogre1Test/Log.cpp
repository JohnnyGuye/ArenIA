#include "Log.h"

#include <ctime>

using namespace ArenIA;
using namespace std;

Log* Log::logArenIA_ = NULL;

void Log::write(std::string text)
{
	std::ofstream file(fileName_, std::ios::app);
	if(file)
	{
		file << text << std::endl;
		file.close();
	}
}

Log* Log::getInstance()
{
	if(!Log::logArenIA_)	Log::logArenIA_ = new Log();
	return Log::logArenIA_;
}

void Log::kill()
{
	if(Log::logArenIA_)	delete Log::logArenIA_;
	Log::logArenIA_ = nullptr;
}

Log::Log(void)
	: fileName_("ArenIA_Log.log")
{
	std::ofstream file(fileName_, std::ios::trunc);
	if (file)
	{
		file << "/** " << time(NULL) << " **/" << endl;
		file.close();
	}
}


Log::~Log(void)
{
}
