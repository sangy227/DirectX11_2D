

#pragma once
#include "yaScript.h"


namespace ya
{
	class UI_SPELL_Spear_Sc : public Script
	{
	public:
		UI_SPELL_Spear_Sc();
		virtual ~UI_SPELL_Spear_Sc();

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
		void setPlayerObj(GameObject* sc) { mPlayer = sc; }


	private:
		GameObject* mGameObject;
		GameObject* mPlayer;
		float mTimer;
		bool check;
	};
}