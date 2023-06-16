
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
			ATTACK2,
			ATTACK3,
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
		void Sculptor_ATTACK1();
		void Sculptor_ATTACK2();
		void Sculptor_DIE();



		void setmGameObject(GameObject* obj) { mGameObject = obj; }
		GameObject* GetmGameObject() { return mGameObject; }

	private:
		eSculptorState mSculptorState;
		GameObject* mGameObject;


	};
};