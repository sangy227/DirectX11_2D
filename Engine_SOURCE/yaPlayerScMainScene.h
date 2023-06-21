#pragma once
#include "yaScript.h"
#include "yaMainCameraSc.h"
#include "yaCollider2D.h"

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

		void Normal_Attack_Hit_Check();
		void Hammer_Attack_Hit_Check();
		void Painwheel_Attack_Hit_Check();
		void Spear_Attack_Hit_Check();
		void Whirlwind_Attack_Hit_Check();

		void Attack_Hit_Death();


		void Player_Idel();
		void Player_Run_to();
		void Skill_Moving_Right();
		void Skill_Moving_Left();

		void Skill_Whirlwind_Fx();
		void Skill_Spear_FX();

		void cameraShakeSmall();
		void cameraShakeBig();
		void cameraShakeIdel();

		void setMainCameraSc(MainCameraSc* sc) { mCameraSc = sc; }
		void setGameObject(GameObject* sc) { mGameObject = sc; }
		void setAttack_obj(GameObject* sc) { mAttack_Object = sc; }

		MainCameraSc* GetCameraScript() { return mCameraSc; }


	private:
		ePlayerState mState;
		MainCameraSc* mCameraSc;

		GameObject* mGameObject;
		GameObject* mAttack_Object;
	};
}
