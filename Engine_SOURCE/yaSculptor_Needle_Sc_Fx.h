


#pragma once
#include "yaScript.h"

namespace ya
{
	class Sculptor_Needle_Sc_Fx : public Script
	{
	public:


		Sculptor_Needle_Sc_Fx();
		virtual ~Sculptor_Needle_Sc_Fx();

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