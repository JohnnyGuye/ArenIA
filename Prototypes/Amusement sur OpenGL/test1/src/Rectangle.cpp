#include "Rectangle.h"

Rectangle::Rectangle()
{
    //ctor
}

Rectangle::Rectangle(float width, float height)
:   Form2D(), m_width(width), m_height(height)

{
    float verticesTmp[] = {
        -width/2, -height/2, 0.f,
        -width/2, height/2, 0.f,
        width/2, height/2, 0.f,
        width/2, -height/2, 0.f,
        };

    for(int i = 0 ; i < 12 ; i++)
    {
        m_vertices[i] = verticesTmp[i];
    }
}

void Rectangle::Update(sf::Time& time)
{

}

void Rectangle::Draw(const sf::Time& time) const
{
    Transformation(1.f, 1.f);

    glBegin(GL_QUADS);
        glColor3f(1.f, 1.f, 1.f);
        for(int i = 0; i < 12; i+=3)
        {
            glVertex3f(m_vertices[i], m_vertices[i+1], m_vertices[i+2]);
        }
    glEnd();
}

Rectangle::~Rectangle()
{
    //dtor
}
