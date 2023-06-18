

#pragma once
#include "yaScript.h"


namespace ya
{

	class event_Line2_Sc : public Script
	{
	public:
		event_Line2_Sc();
		virtual ~event_Line2_Sc();

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

		void StopMove() { mState = eMainCameraState::STOP; }
		void Move() { mState = eMainCameraState::MOVE; }

		void setmGameObject(GameObject* obj) { mGameObject = obj; }
		GameObject* GetmGameObject() { return mGameObject; }


	private:
		eMainCameraState mState;
		GameObject* mGameObject;



	private:


	};
};