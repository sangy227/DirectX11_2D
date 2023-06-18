
#pragma once
#include "yaScript.h"

#include "yafourthCameraMoveLine_Script.h"
namespace ya
{

	class fourthCameraStopLine_Script : public Script
	{
	public:


		fourthCameraStopLine_Script();
		virtual ~fourthCameraStopLine_Script();

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


		void SetCamera_Sc(fourthCameraMoveLine_Script* obj) { mGameObject = obj; }
		fourthCameraMoveLine_Script* GetCamera_Sc() { return mGameObject; }


	private:
		fourthCameraMoveLine_Script* mGameObject;

	private:


	};
};