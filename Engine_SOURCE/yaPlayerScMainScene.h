
#pragma once
#include "yaScript.h"
#include "yaMainCameraSc.h"

namespace ya
{
	class PlayerScMainScene : public Script
	{
	public:
		PlayerScMainScene();
		~PlayerScMainScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();


		void Player_Idel();
		void Player_Run_to();
		void Skill_Moving_Right();
		void Skill_Moving_Left();

		void Skill_Whirlwind_Fx();
		void Skill_Spear_FX();

		void cameraShakeSmall();
		void cameraShakeBig();
		void cameraShakeIdel();

		void setCameraScript(MainCameraSc* sc) { mMainCameraSc = sc; }
		MainCameraSc* GetCameraScript() { return mMainCameraSc; }

	private:
		ePlayerState mState;
		MainCameraSc* mMainCameraSc;
	};
}