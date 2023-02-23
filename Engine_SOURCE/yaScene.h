#pragma once
#include "yaEntity.h"
#include "yaLayer.h"
#include "yaGameObject.h"

namespace ya
{
	using namespace ya::enums;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObj, const eLayerType type);
		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }


	private:
		std::vector<Layer> mLayers;
	};
}
