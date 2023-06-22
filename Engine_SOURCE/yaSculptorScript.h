
#pragma once
#include "yaScript.h"
#include "yaCollider2D.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"
namespace ya
{
	class SculptorScript : public Script
	{
	public:
		enum eSculptorState
		{
			IDLE,
			ATTACK1,
			IDLE_TO_DIE,
			DIE,
		};

		enum eNeedleState
		{
			None,
			IDLE_Needle,
			Chenge,
			Needle1,
			Needle2,
		};

		SculptorScript();
		virtual ~SculptorScript();

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

		void Attack_Start();

		void Sculptor_IDLE();
		void Sculptor_IDLE2();
		void Sculptor_IDLE3();
		void Sculptor_ATTACK1();
		void Sculptor_IDLE_TO_DIE();
		void Sculptor_DIE();

		void Dead();

		void Sculptor_Needle();
		void Sculptor_Needle2();
		void Sculptor_Needle3();
		void Sculptor_Needle4();
		void Sculptor_Needle5();
		void Sculptor_Needle6();
		void Sculptor_Needle7();
		void Sculptor_Needle8();
		
		void Sculptor_hurt();
		void Sculptor_Attack_Sound();
		void Sculptor_Needle_Go();
		void Sculptor_first_die_Sound();
		void Sculptor_Die_Sound();



		void chenge();

		void setmGameObject(GameObject* obj) { mGameObject = obj; }
		GameObject* GetmGameObject() { return mGameObject; }

	private:
		eSculptorState mSculptorState;
		eNeedleState mNeedleState;

		GameObject* mGameObject; //플레이어꺼를 들고있음

		GameObject* HpBar_Bg_HP_obj;
		GameObject* HpBar_Bg_obj;
		float mSculptor_Hp;
		bool mbool;

		std::shared_ptr<AudioClip> audio[100];
		GameObject* Sculptor_Audio_obj[100];
		AudioSource* Sculptor_Audio_Source[100];

	};
};