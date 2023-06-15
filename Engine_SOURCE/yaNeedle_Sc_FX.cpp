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
	{

	}


	Needle_Sc_FX::~Needle_Sc_FX()
	{
	}
	void Needle_Sc_FX::Initalize()
	{
	}
	void Needle_Sc_FX::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		GameObject* gameobj = GetOwner()->GetComponent<GameObject>();
		
		animator->GetCompleteEvent(L"needle_idle") = std::bind(&Needle_Sc_FX::Action, this);
		





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
	}
	void Needle_Sc_FX::Action()
	{
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
		Transform* ownertr = GetOwner()->GetComponent<Transform>();
		Transform* playertr = mGameObject->GetComponent<Transform>();

		Vector3 tr = playertr->GetPosition(); // 플레이어꺼
		tr += 5.6f * playertr->Up();
		//tr += 5.4f * -playertr->Up();
		ownertr->SetPosition(tr);
		ownertr->SetScale(Vector3(10.f, 10.f, 1.f));

		animator->GetCompleteEvent(L"needle_idle") = std::bind(&Needle_Sc_FX::Action, this);
		animator->Play(L"needle_idle", false); //루프 안돌림 

		
	}
}