#pragma once
#include "yaScript.h"
#include "yaCollider2D.h"

namespace ya
{
	class BossWandaScript : public Script
	{
	public:
		enum class eState
		{
			None,

			Idle,
			Move,
			Atack,
			Skill_Selected,
			Skill_Start,
			Skill,

			End,
		};

		BossWandaScript();
		~BossWandaScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();

		void Wanda_Idel();
		void MState_Change_Skill_Selected();

		void Wanda_Skill_Spin();
		void Wanda_Skill_Spin2();
		void Wanda_Skill_Spin3();
		void Wanda_Skill_Spin4();

		void Wanda_Skill_Middle();
		
		void Wanda_Skill_Chain();
		void Wanda_Skill_Chain2();
		void Wanda_Skill_Chain3();
		void Wanda_Skill_Chain4();

		void Wanda_Skill_S2();

		void Wanda_Skill_Aoe();
		void Wanda_Skill_Aoe2();
		void Wanda_Skill_Aoe3();


		void Wanda_Skill_Garden();
		void Wanda_Skill_Garden2();
		void Wanda_Skill_Garden2_Again();
		void Wanda_Skill_Garden3();

		void Wanda_Up_fx();
		void Wanda_Down_fx();


		void CameraFowardUp();
		void CameraFowardDown();

		void Death();


		void setmGameObject(GameObject* obj) { mGameObject = obj; }
		void setCameraObject(GameObject* obj) { mCameraObject = obj; }
		GameObject* GetmGameObject() { return mGameObject; }


		
	private:
		eState mState;
		GameObject* mGameObject;
		GameObject* mCameraObject;

		GameObject* HpBar_Bg_HP_obj;
		GameObject* HpBar_Bg_obj;


		UINT Skill_index;
		UINT Garden2_index;
		bool Garden2_bool;

		int hit;
		float mWanda_Hp;
	private:
		GameObject* Spin_attack_Right;
		GameObject* Spin_attack_Left;
	};
}


//wanda_idle x
//wanda_aoe_middle Y
//wanda_chain U
//wanda_s1_s2 I
//wanda_s2_aoe O
//wanda_s2_garden P
//wanda_s2_npc E
//wanda_s2_npc_idle x
//wanda_s2_skinshed R //��������
//wanda_s2_spin T