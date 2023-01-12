#pragma once
#include "Entity.h"
#include <list>

class CContentManager
{
public:
	CContentManager();
	~CContentManager();

	void Update(float _deltaTime);
	void Render();

	bool AddEntity(CEntity* _entity);
	bool RemoveEntity(CEntity* _entity);
	bool ContainsEntity(CEntity* _entity);

private:
	void CleanUp();

	std::list<CEntity*> m_entities;
	std::list<CEntity*> m_entitiesToDelete;
};

