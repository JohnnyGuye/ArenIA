#include "Form3D.h"

Form3D::Form3D()
: m_nbPoints(8)
{
		float m_aSide = 10, m_bSide = 10, m_cSide = 10;
		m_points = new Vector3[8];
		m_points[0] = Vector3(-m_aSide/2, -m_bSide/2, m_cSide/2);
        m_points[1] = Vector3(m_aSide/2, -m_bSide/2, m_cSide/2);
        m_points[2] = Vector3(m_aSide/2, m_bSide/2, m_cSide/2);
        m_points[3] = Vector3(-m_aSide/2, m_bSide/2, m_cSide/2);

        m_points[4] = Vector3(-m_aSide/2, -m_bSide/2, -m_cSide/2);
        m_points[5] = Vector3(-m_aSide/2, m_bSide/2, -m_cSide/2);
        m_points[6] = Vector3(m_aSide/2, m_bSide/2, -m_cSide/2);
        m_points[7] = Vector3(m_aSide/2, -m_bSide/2, -m_cSide/2);

}

Form3D::Form3D(Vector3* Points, int &nbPoints )
: m_nbPoints(nbPoints)
{
    m_points = new Vector3[nbPoints];
    for(int i = 0; i < nbPoints; i++)
	{
		m_points[i] = Points[i];
	}

	//Default set of colors
	for(int i = 0; i < 32; i++)
	{
		m_color[i] = Vector3((float)i/32, (float)i/32, (float)i/32);
	}
	m_color[1] = Vector3(.5f, .5f, .8f);
}

Form3D::~Form3D()
{
	delete [] m_points;
}

Vector3 * Form3D::GetColorset()
{
        return m_color;
}

void Form3D::SetProfilColor(Vector3 newColor)
{
                m_profil_color = newColor;
}

void Form3D::Draw(const sf::Time &time) const
{
		glBegin(GL_LINE_LOOP);
				DrawFace(m_points[0], m_points[1], m_points[2], m_color[0]);
				DrawFace(m_points[0], m_points[2], m_points[3], m_color[1]);
				DrawFace(m_points[4], m_points[5], m_points[6], m_color[0]);
				DrawFace(m_points[4], m_points[6], m_points[7], m_color[0]);
		glEnd();
}

void Form3D::SetProfilColor(float r, float v, float b)
{
                m_profil_color.X = r;
                m_profil_color.Y = v;
                m_profil_color.Z = b;
}

void Form3D::DrawFace(const Vector3 a, const Vector3 b, const Vector3 c, const Vector3 Color) const
{
        glColor3f(Color.X, Color.Y, Color.Z);
        glVertex3f(a.X, a.Y, a.Z);
        glVertex3f(b.X, b.Y, b.Z);
        glVertex3f(c.X, c.Y, c.Z);
}

void Form3D::DrawLine(const Vector3 a, const Vector3 b) const
{
        glVertex3f(a.X, a.Y, a.Z);
        glVertex3f(b.X, b.Y, b.Z);
}
