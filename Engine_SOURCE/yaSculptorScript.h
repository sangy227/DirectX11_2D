
#pragma once
#include "yaScript.h"

namespace ya
{
	class SculptorScript : public Script
	{
	public:
		enum eSculptorState
		{
			IDLE,
			ATTACK1,
			IDLE_TO_DIE,
			DIE,
		};

		enum eNeedleState
		{
			None,
			IDLE_Needle,
			Chenge,
			Needle1,
			Needle2,
		};

		SculptorScript();
		virtual ~SculptorScript();

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



		void Sculptor_IDLE();
		void Sculptor_IDLE2();
		void Sculptor_IDLE3();
		void Sculptor_ATTACK1();
		void Sculptor_IDLE_TO_DIE();
		void Sculptor_DIE();

		void Dead();

		void Sculptor_Needle();
		void Sculptor_Needle2();

		void chenge();

		void setmGameObject(GameObject* obj) { mGameObject = obj; }
		GameObject* GetmGameObject() { return mGameObject; }

	private:
		eSculptorState mSculptorState;
		eNeedleState mNeedleState;

		GameObject* mGameObject; //플레이어꺼를 들고있음


		bool mbool;

	};
};