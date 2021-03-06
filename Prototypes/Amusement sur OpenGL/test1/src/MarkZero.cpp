#include "MarkZero.h"

MarkZero::MarkZero()
{}

void MarkZero::Update(sf::Time& time)
{

}

void MarkZero::Draw(const sf::Time& time) const
{

    glBegin(GL_LINES);
    //X-axis in red
        glColor3f(1,0,0);
        glVertex3f(0.f, 0.f, 0.f);
        glVertex3f(5.f, 0.f, 0.f);
    //Y-axis in blue
        glColor3f(0,0,1);
        glVertex3f(0.f, 0.f, 0.f);
        glVertex3f(0.f, 5.f, 0.f);

    //Z-axis in green
        glColor3f(0,1,0);
        glVertex3f(0.f, 0.f, 0.f);
        glVertex3f(0.f, 0.f, 5.f);
    glEnd();
}

MarkZero::~MarkZero()
{
    //dtor
}
