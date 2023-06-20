

#pragma once
#include "yaScript.h"

namespace ya
{
	class GrandPaScript : public Script
	{
	public:
		enum eGrandPaState
		{
			IDLE,
			ATTACK1,
			ATTACK2,
			ATTACK3,
			DIE
		};

		GrandPaScript();
		virtual ~GrandPaScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();

		void Attack_index_PLUS();

		void Grandpa_IDLE();
		void Grandpa_IDLE2();
		void Grandpa_IDLE3();
		void Grandpa_ATTACK1();
		void Grandpa_ATTACK2();
		void Grandpa_ATTACK3();
		void Grandpa_DIE();
		void dead();

		void Needle_FX();







		void setmGameObject(GameObject* obj) { mGameObject = obj; }
		GameObject* GetmGameObject() { return mGameObject; }

	private:
		eGrandPaState mGrandpaState;
		GameObject* mGameObject;
		int Attack_index;

	};
};