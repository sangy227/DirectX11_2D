
#pragma once
#include "yaScript.h"


namespace ya
{
	class UI_Icon_Sc : public Script
	{
	public:
		UI_Icon_Sc();
		virtual ~UI_Icon_Sc();

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

		void setPosX(float a) { PosX = a; }
		void setPosY(float a) { PosY = a; }

	private:
		GameObject* mGameObject;
		GameObject* mPlayer;
		float mTimer;
		bool check;

		float PosX;
		float PosY;
	};
}