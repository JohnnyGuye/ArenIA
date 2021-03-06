#include "cobble.h"

void Cobble::Draw(const sf::Time& time) const
{
        glBegin(GL_QUADS);
                DrawFace(m_points[1], m_points[7], m_points[6], m_points[2], m_color[0]);         //Front-face
                DrawFace(m_points[2], m_points[6], m_points[5], m_points[3], m_color[1]);         //Right-face
                DrawFace(m_points[3], m_points[5], m_points[4], m_points[0], m_color[2]);         //Back_face
                DrawFace(m_points[0], m_points[4], m_points[7], m_points[1], m_color[3]);         //Left-face
                DrawFace(m_points[1], m_points[2], m_points[3], m_points[0], m_color[4]);         //Top-face
                DrawFace(m_points[4], m_points[5], m_points[6], m_points[7], m_color[5]);         //Bottom-face
        glEnd();
}

void Cobble::DrawBack(const sf::Time& time) const
{
        glLineWidth(10);
        glBegin(GL_QUADS);
                DrawFace(m_points[1], m_points[7], m_points[6], m_points[2], m_profil_color);         //Front-face
                DrawFace(m_points[2], m_points[6], m_points[5], m_points[3], m_profil_color);         //Right-face
                DrawFace(m_points[3], m_points[5], m_points[4], m_points[0], m_profil_color);         //Back_face
                DrawFace(m_points[0], m_points[4], m_points[7], m_points[1], m_profil_color);         //Left-face
                DrawFace(m_points[1], m_points[2], m_points[3], m_points[0], m_profil_color);         //Top-face
                DrawFace(m_points[4], m_points[5], m_points[6], m_points[7],  m_profil_color);
        glEnd();
}

Cobble::Cobble(float aSide, float bSide, float cSide)
:       m_aSide(aSide), m_bSide(bSide), m_cSide(cSide),
        m_profil(true), m_profil_color(0.f, 0.f, 0.f)
{
        m_points[0] = Vector3(-m_aSide/2, -m_bSide/2, m_cSide/2);
        m_points[1] = Vector3(m_aSide/2, -m_bSide/2, m_cSide/2);
        m_points[2] = Vector3(m_aSide/2, m_bSide/2, m_cSide/2);
        m_points[3] = Vector3(-m_aSide/2, m_bSide/2, m_cSide/2);

        m_points[4] = Vector3(-m_aSide/2, -m_bSide/2, -m_cSide/2);
        m_points[5] = Vector3(-m_aSide/2, m_bSide/2, -m_cSide/2);
        m_points[6] = Vector3(m_aSide/2, m_bSide/2, -m_cSide/2);
        m_points[7] = Vector3(m_aSide/2, -m_bSide/2, -m_cSide/2);

        //Default set of colors
        m_color[0] = Vector3(0.5f, 0.5f, 0.2f);
        m_color[1] = Vector3(0.7f, 0.5f, 0.2f);
        m_color[2] = Vector3(.5f, 0.3f, 0.3f);
        m_color[3] = Vector3(0.7f, 0.8f, 0.2f);
        m_color[4] = Vector3(0.8f, 0.7, 1.f);
        m_color[5] = Vector3(0.7f, 0.6f, 0.2f);
}

Cobble::Cobble(float sides)
: Cobble(sides, sides, sides)
{

}
Cobble::~Cobble()
{
}

Vector3 * Cobble::GetColorset()
{
        return m_color;
}

void Cobble::SetProfilColor(Vector3 newColor)
{
                m_profil_color = newColor;
}

void Cobble::SetProfilColor(float r, float v, float b)
{
                m_profil_color.X = r;
                m_profil_color.Y = v;
                m_profil_color.Z = b;
}

void Cobble::DrawFace(const Vector3 a, const Vector3 b, const Vector3 c, Vector3 d, const Vector3 Color) const
{
        glColor3f(Color.X, Color.Y, Color.Z);
        glVertex3f(a.X, a.Y, a.Z);
        glVertex3f(b.X, b.Y, b.Z);
        glVertex3f(c.X, c.Y, c.Z);
        glVertex3f(d.X, d.Y, d.Z);
}

void Cobble::DrawLine(const Vector3 a, const Vector3 b) const
{
        glVertex3f(a.X, a.Y, a.Z);
        glVertex3f(b.X, b.Y, b.Z);
}
