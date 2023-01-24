#pragma once

class CEntity2D
{
public:
	CEntity2D(XMFLOAT2 _pos);
	~CEntity2D();

	virtual bool Initialize();
	virtual void Update(float _deltaTime);
	virtual void Render() = 0;		// purely virtual ^= abstrakt aus C#
	virtual void CleanUp();

	XMFLOAT2 m_position;
	float m_rotation;
	XMFLOAT2 m_size;
};

