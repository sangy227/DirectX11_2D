#include "yaSculptorScript.h"
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

namespace ya {
	SculptorScript::SculptorScript()
		: Script()
		, mSculptorState(eSculptorState::IDLE)
	{
	}
	SculptorScript::~SculptorScript()
	{
	}
	void SculptorScript::Initalize()
	{
	}
	void SculptorScript::Update()
	{
		Transform* obj_tr = GetOwner()->GetComponent<Transform>();
		Transform* player_tr = mGameObject->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();


		if (mSculptorState == eSculptorState::IDLE) {
			
		}
		if (mSculptorState == eSculptorState::ATTACK1) {

		}
		if (mSculptorState == eSculptorState::IDLE_TO_DIE) {

		}
		if (mSculptorState == eSculptorState::DIE) {

		}


		if (Input::GetKeyDown(eKeyCode::T)) //여긴 콜라이더 설정
		{
			animator->GetCompleteEvent(L"sculptor_idle") = std::bind(&SculptorScript::Sculptor_IDLE, this);
			animator->Play(L"sculptor_idle");
		}


	}
	void SculptorScript::FixedUpdate()
	{
	}
	void SculptorScript::Render()
	{
	}


	void SculptorScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void SculptorScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void SculptorScript::OnCollisionExit(Collider2D* collider)
	{
	}


	void SculptorScript::Start()
	{
	}
	void SculptorScript::Action()
	{
	}
	void SculptorScript::End()
	{
	}


	void SculptorScript::Sculptor_IDLE()
	{
		mSculptorState = eSculptorState::IDLE;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"sculptor_idle") = std::bind(&SculptorScript::Sculptor_IDLE2, this);
		animator->Play(L"sculptor_idle");

	}
	void SculptorScript::Sculptor_IDLE2()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"sculptor_idle") = std::bind(&SculptorScript::Sculptor_IDLE3, this);
		animator->Play(L"sculptor_idle");

	}
	void SculptorScript::Sculptor_IDLE3()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"sculptor_idle") = std::bind(&SculptorScript::Sculptor_ATTACK1, this);
		animator->Play(L"sculptor_idle");
	}
	void SculptorScript::Sculptor_ATTACK1()
	{
		mSculptorState = eSculptorState::ATTACK1;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"sculptor_attack") = std::bind(&SculptorScript::Sculptor_IDLE, this);

		animator->Play(L"sculptor_attack");
	}
	void SculptorScript::Sculptor_IDLE_TO_DIE()
	{
		mSculptorState = eSculptorState::IDLE;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"sculptor_idle") = std::bind(&SculptorScript::Sculptor_DIE, this);
		animator->Play(L"sculptor_idle");
	}
	void SculptorScript::Sculptor_DIE()
	{
		mSculptorState = eSculptorState::IDLE;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		
		animator->Play(L"sculptor_die",false);
	}
	void SculptorScript::Sculptor_Needle()
	{







	}
}