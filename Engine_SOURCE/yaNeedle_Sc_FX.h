
#pragma once
#include "yaScript.h"

namespace ya
{
	class Needle_Sc_FX : public Script
	{
	public:
		

		Needle_Sc_FX();
		virtual ~Needle_Sc_FX();

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

		
		void setmGameObject(GameObject* obj) { mGameObject = obj; }
		GameObject* GetmGameObject() { return mGameObject; }

	private:
		GameObject* mGameObject;
	

	private:
		

	};
};