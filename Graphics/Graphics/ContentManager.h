#pragma once
#include "Entity.h"
#include "Entity2D.h"
#include "Cursor.h"
#include <list>

class CContentManager
{
public:
	CContentManager();
	~CContentManager();

	void Initialize();
	void Update(float _deltaTime);
	void Render();

	bool AddEntity(CEntity* _entity);
	bool RemoveEntity(CEntity* _entity);
	bool ContainsEntity(CEntity* _entity);

	bool AddEntity(CEntity2D* _entity);
	bool RemoveEntity(CEntity2D* _entity);
	bool ContainsEntity(CEntity2D* _entity);

	SpriteBatch* m_spriteBatch;
	SpriteFont* m_spriteFont;

private:
	void CleanUp();

	std::list<CEntity*> m_entities;
	std::list<CEntity*> m_entitiesToDelete;

	std::list<CEntity2D*> m_entities2D;
	std::list<CEntity2D*> m_entities2DToDelete;

	CCursor* m_cursor;
};

