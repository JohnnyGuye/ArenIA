#include "AppWindow.h"

AppWindow::AppWindow(unsigned int width,
                     unsigned int height,
                     const char* title,
                     const sf::ContextSettings settings
                     )
:       m_width(width), m_height(height),
        m_clock(),
        m_window(sf::VideoMode(width, height, 32), title, sf::Style::Close, settings),
        m_mark(),
        m_cob1(20, 10, 10)
{
    m_window.getSettings();
    std::cout << "=== OPENGL ACTIVE CONFIGURATION ===" <<  std::endl;
    std::cout << "DepthBuffer : " <<settings.depthBits << std::endl
        << "StencilBuffer : " <<settings.stencilBits << std::endl
        << "Anti-aliasing : " <<settings.antialiasingLevel << std::endl
        << "Flags : " <<settings.attributeFlags << std::endl;

        m_mapGrid[0][0] = 1;
}

void AppWindow::Run()
{
    //If not initialize, the game stops immediately
    bool running = Init();

    //Loop
    sf::Time timer;

    while (running)
    {
        //HANDLE EVENTS
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // stop the programme
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // resize the viewport
                m_width = event.size.width;
                m_height = event.size.height;
                glViewport(0, 0, m_width, m_height);
            }
            else if (event.type == sf::Event::MouseWheelMoved)
            {

            }

        }

        timer = m_clock.getElapsedTime();
        Update(timer);
        Render(timer);
    }

    Cleanup();
}

bool AppWindow::Init()
{
    m_window.setVerticalSyncEnabled(true);

    //Initialize the color of the clear buffer
    glClearDepth(1.f);
    glClearColor(0.8f, 0.7f, 0.7f, 0.f);
    //glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

    //Generating the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.f, m_width/m_height, 1.f, 500.f);

    //Activate r/w on depth buffer
    glEnable(GL_DEPTH_TEST);

    //LUMOS !
    int MatSpec [4] = {0,0,0,0};    //Color of specular light (r,v,b, alpha)

    glEnable(GL_COLOR_MATERIAL);
    glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float LightDif[4] = {.5f,.5f,.5f,1.f};
    glLightfv(GL_LIGHT0,GL_DIFFUSE, LightDif );

    gluLookAt(30.0, 30, 30,
        0, 0, 0,
        0, 0, 1);

    //Add content

    return true;
}

void AppWindow::Update(sf::Time& time)
{
    glMatrixMode(GL_PROJECTION);
    glRotated(1.f, 0.f, 0.f, 1.f);
}

void AppWindow::Render(sf::Time& time)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for(int i = 0; i < 2 ; i++)
    {
        glLoadIdentity();
        m_mark.Draw(time);
        //glTranslatef(5.f + i*10.f, 5.f, 5.f);

        for(int j = 0; j < 2 ; j++)
        {

            if(m_mapGrid[i][j] == 1)
            {
                glCullFace(GL_FRONT);
               glPolygonMode(GL_FRONT, GL_FILL);
                m_cob1.Draw(time);

                glCullFace(GL_BACK);
                glPolygonMode(GL_FRONT, GL_LINE);
                m_cob1.DrawBack(time);
                glTranslatef(0.f, 10.f, 0.f);
            }
        }
    }


    glFlush();
    m_window.display();
}

void AppWindow::Cleanup()
{

}
AppWindow::~AppWindow()
{
    //dtor
}
