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

namespace ya {
	Sculptor_Needle_Sc_Fx::Sculptor_Needle_Sc_Fx()
		: Script()
	{
	}
	Sculptor_Needle_Sc_Fx::~Sculptor_Needle_Sc_Fx()
	{
	}
	void Sculptor_Needle_Sc_Fx::Initalize()
	{
	}
	void Sculptor_Needle_Sc_Fx::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		GameObject* gameobj = GetOwner()->GetComponent<GameObject>();

		animator->GetCompleteEvent(L"sculptor_needle") = std::bind(&Sculptor_Needle_Sc_Fx::End, this);


		
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
		Transform* playertr = mGameObject->GetComponent<Transform>();

		Vector3 ow_tr = ownertr->GetPosition();
		Vector3 tr = playertr->GetPosition(); // 플레이어꺼

		//여기는 반복으로 계속 나타나게 하는것
		{
			//tr += 5.6f * playertr->Up();
			////tr += 5.4f * -playertr->Up();
			//ownertr->SetPosition(tr);
			//ownertr->SetScale(Vector3(10.f, 10.f, 1.f));

			//animator->GetCompleteEvent(L"needle_idle") = std::bind(&Needle_Sc_FX::Action, this);
			//animator->Play(L"needle_idle", false); //루프 안돌림 
		}

		ow_tr += (-(10.6f) * ownertr->Up());
		ownertr->SetPosition(ow_tr);
	}
}