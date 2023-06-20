#include "yaNeedle_Sc_FX.h"
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

namespace ya {
	Needle_Sc_FX::Needle_Sc_FX()
		: Script()
		, trigger(false)
	{

	}


	Needle_Sc_FX::~Needle_Sc_FX()
	{
	}
	void Needle_Sc_FX::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"needle_idle") = std::bind(&Needle_Sc_FX::Start, this);
	}
	void Needle_Sc_FX::Update()
	{
		GameObject* gameobj = GetOwner()->GetComponent<GameObject>();
		
		Animator* animator = GetOwner()->GetComponent<Animator>();
	
		
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (trigger) {
			Vector3 pos = tr->GetPosition();
			pos += 2.4f * tr->Up() * Time::DeltaTime();
			tr->SetPosition(pos);
		}


	}
	void Needle_Sc_FX::FixedUpdate()
	{
	}
	void Needle_Sc_FX::Render()
	{
	}



	void Needle_Sc_FX::OnCollisionEnter(Collider2D* collider)
	{
	}
	void Needle_Sc_FX::OnCollisionStay(Collider2D* collider)
	{
	}
	void Needle_Sc_FX::OnCollisionExit(Collider2D* collider)
	{
	}



	void Needle_Sc_FX::Start()
	{
		trigger = true; //아래로 내리게하는 작동 트리거

		Animator* animator = GetOwner()->GetComponent<Animator>(); 
		animator->GetCompleteEvent(L"needle_idle2") = std::bind(&Needle_Sc_FX::Action, this);
		animator->Play(L"needle_idle2"); 
	}
	void Needle_Sc_FX::Action()
	{
		trigger = false;
		Transform* ownertr = GetOwner()->GetComponent<Transform>();
		ownertr->SetScale(Vector3(2.0f, 2.0f, 1.0f));

		Animator* animator = GetOwner()->GetComponent<Animator>();\
		animator->GetCompleteEvent(L"needle_die") = std::bind(&Needle_Sc_FX::End, this);
		animator->Play(L"needle_die", false); //루프 안돌림

	}
	void Needle_Sc_FX::End()
	{
		
		GameObject* gameobj = GetOwner()->GetComponent<GameObject>();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		Transform* playertr = mGameObject->GetComponent<Transform>();
		Vector3 tr = playertr->GetPosition(); // 플레이어꺼

		Transform* ownertr = GetOwner()->GetComponent<Transform>();
		Vector3 ow_tr = ownertr->GetPosition();

		//ow_tr += (-(1000.6f) * ownertr->Up());
		//ownertr->SetPosition(ow_tr);

		//ow_tr += (-(50.6f) * ownertr->Up());
		//ownertr->SetPosition(ow_tr);
		GetOwner()->Death();

		
	}
}