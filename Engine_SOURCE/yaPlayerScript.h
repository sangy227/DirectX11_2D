#pragma once
#include "yaScript.h"
#include "yaCameraScript.h"
#include "yaCollider2D.h"

#include "yaAudioClip.h"
#include "yaAudioSource.h"
namespace ya
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

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
		
		void setCameraScript(CameraScript* sc) { mCameraSc = sc; }
		void setGameObject(GameObject* sc) { mGameObject = sc; }
		void setAttack_obj(GameObject* sc) { mAttack_Object = sc; }

		CameraScript* GetCameraScript() { return mCameraSc; }
		

		void attack_suond02();
		void attack_suond03();

		void hammer_sound01();
		void hammer_sound02();

		void painwheel_sound01();
		void painwheel_sound02();

		void Spear_sound01();
		void Spear_sound02();

		void Whirlwind_sound01();
		void Whirlwind_sound02();

		void Footstep01();
		void Footstep02();





	private:
		ePlayerState mState;
		CameraScript* mCameraSc;
		
		GameObject* mGameObject;
		GameObject* mAttack_Object;


		std::shared_ptr<AudioClip> audio[100];
		GameObject* Player_Audio_obj[100];
		AudioSource* Player_Audio_Source[100];
	};
}
