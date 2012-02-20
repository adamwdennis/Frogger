#ifndef _COORD3_H_
#define _COORD3_H_

class Coord3
{
public:
	Coord3(float p_rX = 0, float p_rY = 0, float p_rZ = 0)
	{
		m_rX = p_rX;
		m_rY = p_rY;
		m_rZ = p_rZ;
	}
	~Coord3() {}

	//Overloaded operators
	Coord3 operator+ (Coord3& rhs)
	{
		return Coord3(m_rX + rhs.GetX(), m_rY + rhs.GetY(), m_rZ + rhs.GetZ());
	}

	Coord3 operator- (Coord3& rhs)
	{
		return Coord3(m_rX - rhs.GetX(), m_rY - rhs.GetY(), m_rZ - rhs.GetZ());
	}

	float GetX() { return m_rX; }
	float GetY() { return m_rY; }
	float GetZ() { return m_rZ; }

	void SetX(float p_iX) { m_rX = p_iX; }
	void SetY(float p_iY) { m_rY = p_iY; }
	void SetZ(float p_iZ) { m_rZ = p_iZ; }

	float	GetLength();
	void	Normalize();
	void	Scale(float scaler);
	Coord3	CrossProduct(Coord3 val);

private:
	float m_rX;
	float m_rY;
	float m_rZ;
};

void Coord3_copy(Coord3 src, Coord3* dst);
float Coord3_dotproduct(Coord3 v1, Coord3 v2);
//void Coord3_crossproduct(Coord3 v1, Coord3 v2, Coord3* cross);
void Coord3_add(Coord3 v1, Coord3 v2);
void Coord3_subtract(Coord3* v1, Coord3 v2);
void Coord3_rotateX(Coord3* v, float theta);
void Coord3_rotateY(Coord3* v, float theta);
void Coord3_rotateZ(Coord3* v, float theta);

void Coord3_rotate(Coord3* v, float x, float y, float z, float theta);

#endif