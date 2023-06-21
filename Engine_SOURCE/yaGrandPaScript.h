

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

		void Attack_Start();

		void Grandpa_IDLE();
		void Grandpa_IDLE2();
		void Grandpa_IDLE3();
		void Grandpa_ATTACK1();
		void Grandpa_ATTACK2();
		void Grandpa_ATTACK3();
		void Grandpa_DIE();
		void dead();

		void Needle_FX();
		void Needle_FX1();
		void Needle_FX2();
		void Needle_FX3();
		void Needle_FX4();
		void Needle_FX5();

		void DieDieDie();






		void setmGameObject(GameObject* obj) { mGameObject = obj; }
		GameObject* GetmGameObject() { return mGameObject; }

		float GetGrandPa_Hp() { return mGrandPa_Hp; }

	private:
		eGrandPaState mGrandpaState;
		GameObject* mGameObject;

		GameObject* HpBar_Bg_HP_obj;
		GameObject* HpBar_Bg_obj;
		int Attack_index;
		float mGrandPa_Hp;
	};
};