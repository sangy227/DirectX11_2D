#pragma once
#include "yaScript.h"


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

	private:
		eState mState;
	};
}

