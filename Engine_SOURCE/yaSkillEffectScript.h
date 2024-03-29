#pragma once

#include "yaScript.h"
#include "yaCollider2D.h"

namespace ya
{
	class SkillEffectScript : public Script
	{
	public:
		SkillEffectScript();
		~SkillEffectScript();

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

	};
}