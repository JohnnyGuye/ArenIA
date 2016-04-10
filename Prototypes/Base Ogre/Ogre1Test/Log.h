#pragma once

#include <string>
#include <iostream>
#include <fstream>

namespace ArenIA {
	class Log
	{
	public:
		/** Write something in the log file **/
		void write(std::string text);

		/** Hold the instance of log item **/
		static Log* getInstance();

		/** Destroy the instance of the log item **/
		static void kill();

	private:
		static Log* logArenIA_;

		Log(void);
		~Log(void);
		
		std::string fileName_;

	};
}



