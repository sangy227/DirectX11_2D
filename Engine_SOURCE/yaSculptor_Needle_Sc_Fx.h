


#pragma once
#include "yaScript.h"
#include "yaCollider2D.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"

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

		void IDLE1();
		void IDLE2();
		void IDLE3();

		void Die_Sound();


		void setmGameObject(GameObject* obj) { mGameObject = obj; }

		GameObject* GetmGameObject() { return mGameObject; }

	private:
		GameObject* mGameObject; //여기선 지금 할배꺼 obj들고있음
		
		bool trigger;

		std::shared_ptr<AudioClip> audio_Ne;
		GameObject* Sculptor_Ne_Audio_obj;
		AudioSource* Sculptor_Ne_Audio_Source;
	};
};