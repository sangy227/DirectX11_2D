
#pragma once
#include "yaScript.h"
#include "yathirdCameraMoveLine_Script.h"
namespace ya
{

	class thirdCameraStopLine_Script : public Script
	{
	public:


		thirdCameraStopLine_Script();
		virtual ~thirdCameraStopLine_Script();

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


		void SetCamera_Sc(thirdCameraMoveLine_Script* obj) { mGameObject = obj; }
		thirdCameraMoveLine_Script* GetCamera_Sc() { return mGameObject; }


	private:
		thirdCameraMoveLine_Script* mGameObject;

	private:


	};
};