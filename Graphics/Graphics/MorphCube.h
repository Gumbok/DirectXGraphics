#pragma once
#include "Entity.h"
class CMorphCube :
    public CEntity
{
public:
	CMorphCube(int _subDivisions, XMFLOAT3 _pos = XMFLOAT3(0, 0, 0));
	virtual ~CMorphCube();

	virtual void Update(float _deltaTime) override;

private:
	SVertexPosColor* m_cubeVertices;
	SVertexPosColor* m_sphereVertices;

	float m_timer;
};

