#pragma once
#include "yaScript.h"
#include "yaGrandPaScript.h"

namespace ya
{
	class GrandPa_UI_Sc : public Script
	{
	public:
		GrandPa_UI_Sc();
		virtual ~GrandPa_UI_Sc();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();

		void setGameObject(GameObject* sc) { mGameObject = sc; }
		void setGrandPaScript(GrandPaScript* sc) { Pa_Sc = sc; }
		void setPlayerObj(GameObject* sc) { mPlayer = sc; }
		void setIndex(float sc) { index = sc; }
		

	private:
		GameObject* mGameObject;
		GameObject* mPlayer;
		GrandPaScript* Pa_Sc;
		float index;
		float mTimer;
	};
}