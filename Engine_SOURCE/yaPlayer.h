#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		UINT GetHp(){ return HP; }
		void SetHp(UINT index) { HP = index; }

	private:
		UINT HP;
	};
}
