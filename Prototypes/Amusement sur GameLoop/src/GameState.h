#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <chrono>
using namespace std::chrono;


/** GameState is a virtual class for creating Games States
*	It held the game loop.
*/
class GameState {
	public :
		/** Performs a cycle in the GameLoop
		*/
		void Run();
		inline void Init() 
		{
			lag = 0;
			previousTime = high_resolution_clock::now(); 
		}

		/** This function is where all input should be processed.
		*	Will be called before Update and Render
		*/
		virtual void HandleInput() = 0;

		/**	This method is where all updates should take places
		*	i.e all status changes. All updates sould represent
		*	a timespan of UPDATE_TIME
		*/
		virtual void Update() = 0;

		/** This method should held all that is related to drawing
		*	and rendering stuff on the screen.
		*/
		virtual void Render(double  interpolation) = 0;
		
		/** GameState destructor
		*/
		virtual ~GameState() = 0;

	private :
			
		/** Mesures how far behind we are */
		int64_t lag = 0;

		/** Contains the time at the start of the stuff*/
		high_resolution_clock::time_point previousTime;

};



#endif	//_GAME_STATE_H_