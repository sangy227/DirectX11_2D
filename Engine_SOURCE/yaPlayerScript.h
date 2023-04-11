#pragma once
#include "yaScript.h"


namespace ya
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			None,
			RIGHT_Idle,
			Left_Idle,
			RIGHT_Run,
			Left_Run
		};

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


		void Player_Idel();
		void Player_Run_to();
		void Skill_Moving_Right();
		void Skill_Moving_Left();

		void Skill_Whirlwind_Fx();
		void Skill_Spear_FX();
		

	private:
		eState mState;
	};
}
