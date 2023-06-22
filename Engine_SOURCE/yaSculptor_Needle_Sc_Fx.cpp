#include "yaSculptor_Needle_Sc_Fx.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaPlayerScMainScene.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "yaMonster.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaSpriteRenderer.h"
#include "yaGridScript.h"
#include "yaObject.h"
#include "yaCollider2D.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaSkillEffect.h"
#include "yaSkillEffectScript.h"
#include "yaRigidbody.h"
#include "yaEnums.h"
#include "yaGameObject.h"
#include "yaSculptorScript.h"
#include "yaResources.h"
#include "yaAudioClip.h"

namespace ya {
	Sculptor_Needle_Sc_Fx::Sculptor_Needle_Sc_Fx()
		: Script()
		, trigger(false)
	{
	}
	Sculptor_Needle_Sc_Fx::~Sculptor_Needle_Sc_Fx()
	{
	}
	void Sculptor_Needle_Sc_Fx::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"sculptor_needle") = std::bind(&Sculptor_Needle_Sc_Fx::IDLE1, this);


		Sculptor_Ne_Audio_obj = object::Instantiate<GameObject>(eLayerType::UI);

		audio_Ne = Resources::Load<AudioClip>(L"Sculptor_Neddle_Needle", L"Music\\Monster\\SFX_BossTheSculptor_AOE_01.wav");
		//Sculptor_Ne_Audio_Source = Sculptor_Ne_Audio_obj->AddComponent<AudioSource>();


	}
	void Sculptor_Needle_Sc_Fx::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		GameObject* gameobj = GetOwner()->GetComponent<GameObject>();
		

		
		if (trigger) {
			Vector3 pos = tr->GetPosition();
			pos += -5.0f * tr->Up() * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		
	}
	void Sculptor_Needle_Sc_Fx::FixedUpdate()
	{
	}
	void Sculptor_Needle_Sc_Fx::Render()
	{
	}


	void Sculptor_Needle_Sc_Fx::OnCollisionEnter(Collider2D* collider)
	{
	}
	void Sculptor_Needle_Sc_Fx::OnCollisionStay(Collider2D* collider)
	{
	}
	void Sculptor_Needle_Sc_Fx::OnCollisionExit(Collider2D* collider)
	{
	}



	void Sculptor_Needle_Sc_Fx::Start()
	{
	}
	void Sculptor_Needle_Sc_Fx::Action()
	{
	}
	void Sculptor_Needle_Sc_Fx::End()
	{
		GameObject* gameobj = GetOwner()->GetComponent<GameObject>();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Transform* ownertr = GetOwner()->GetComponent<Transform>();

		Vector3 ow_tr = ownertr->GetPosition();
		

		
		GetOwner()->Death();
		
		

	}




	void Sculptor_Needle_Sc_Fx::IDLE1()
	{
		trigger = true;
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"sculptor_needle1") = std::bind(&Sculptor_Needle_Sc_Fx::IDLE2, this);
		animator->Play(L"sculptor_needle1");
	}
	void Sculptor_Needle_Sc_Fx::IDLE2()
	{
		trigger = false;
		Animator* animator = GetOwner()->GetComponent<Animator>();

		
		//Sculptor_Ne_Audio_Source->SetClip(audio_Ne);
		//Sculptor_Ne_Audio_Source->Play();

		animator->GetCompleteEvent(L"sculptor_needle2") = std::bind(&Sculptor_Needle_Sc_Fx::End, this);
		animator->Play(L"sculptor_needle2");
	}
	void Sculptor_Needle_Sc_Fx::IDLE3()
	{
	}
	void Sculptor_Needle_Sc_Fx::Die_Sound()
	{
	}
}