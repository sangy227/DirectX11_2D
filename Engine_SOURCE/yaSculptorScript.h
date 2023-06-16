
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

		void Sculptor_Needle();

		void setmGameObject(GameObject* obj) { mGameObject = obj; }
		GameObject* GetmGameObject() { return mGameObject; }

	private:
		eSculptorState mSculptorState;
		GameObject* mGameObject;


	};
};