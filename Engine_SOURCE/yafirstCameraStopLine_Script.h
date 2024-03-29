
#pragma once
#include "yaScript.h"
#include "yafirstCameraMoveLine_Script.h"
#include "yaGrandPaScript.h"

namespace ya
{

	class firstCameraStopLine_Script : public Script
	{
	public:


		firstCameraStopLine_Script();
		virtual ~firstCameraStopLine_Script();

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


		void SetCamera_Sc(firstCameraMoveLine_Script* obj) { mGameObject = obj; }
		firstCameraMoveLine_Script* GetCamera_Sc() { return mGameObject; }

		void SetGrandPa_Sc(GrandPaScript* obj) { mGrandpa_Obj = obj; }


	private:
		firstCameraMoveLine_Script* mGameObject;
		GrandPaScript* mGrandpa_Obj;

	private:


	};
};