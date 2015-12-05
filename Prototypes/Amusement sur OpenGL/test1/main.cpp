#include "include/cobble.h"
#include "include/AppWindow.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
	sf::ContextSettings settings = sf::ContextSettings(24, 8, 4, 3, 0);
    AppWindow GameApp = AppWindow(1600,900,"OpenGL test1", settings);
    GameApp.Run();
    return 0;
}
