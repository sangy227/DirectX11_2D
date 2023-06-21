
#pragma once
#include "yaScript.h"
#include "yaCollider2D.h"
namespace ya
{
	class RedQueenScript : public Script
	{
	public:
		enum eRedQueenState
		{
			IDLE,
		};

		RedQueenScript();
		virtual ~RedQueenScript();

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

		

		void RedQueen_IDLE();
		


		void setmGameObject(GameObject* obj) { mGameObject = obj; }
		GameObject* GetmGameObject() { return mGameObject; }

	private:
		eRedQueenState mRedQueenState;
		GameObject* mGameObject;
	

	};
};