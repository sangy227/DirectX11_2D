

#pragma once
#include "yaScript.h"
#include "yasecondCameraMoveLine_Script.h"

namespace ya
{

	class secondCameraStopLine_Script : public Script
	{
	public:


		secondCameraStopLine_Script();
		virtual ~secondCameraStopLine_Script();

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


		void SetCamera_Sc(secondCameraMoveLine_Script* obj) { mGameObject = obj; }
		secondCameraMoveLine_Script* GetCamera_Sc() { return mGameObject; }


	private:
		secondCameraMoveLine_Script* mGameObject;

	private:


	};
};