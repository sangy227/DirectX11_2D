#include "yaGrandPaScript.h"
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
#include "yaNeedle_Sc_FX.h"

namespace ya {
	GrandPaScript::GrandPaScript()
		: Script()
		, mGrandpaState(eGrandPaState::IDLE)
		, Attack_index(0)
	{
	}
	GrandPaScript::~GrandPaScript()
	{
	}
	void GrandPaScript::Initalize()
	{
	}
	void GrandPaScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();
		Transform* player_tr = mGameObject->GetComponent<Transform>();


		//상태바
		if (mGrandpaState == eGrandPaState::IDLE)
		{
			
		}
		if (mGrandpaState == eGrandPaState::ATTACK1)
		{
			Attack_index++;
			if (Attack_index > 3) {
				Attack_index = 0;
				Attack_index++;
			}

			mGrandpaState = eGrandPaState::ATTACK2;
			
		}
		if (mGrandpaState == eGrandPaState::ATTACK2)
		{
			if (Attack_index == 1)
				Grandpa_ATTACK1();
			if (Attack_index == 2)
				Grandpa_ATTACK2();
			if (Attack_index == 3)
				Grandpa_ATTACK3();
		}
		if (mGrandpaState == eGrandPaState::ATTACK3)
		{

		}
		if (mGrandpaState == eGrandPaState::DIE)
		{

		}


		if (Input::GetKeyDown(eKeyCode::E)) //여긴 콜라이더 설정
		{
			//mGrandpaState = eGrandPaState::ATTACK1;
			Attack_index_PLUS();
		}

		if (Input::GetKeyDown(eKeyCode::R)) //여긴 콜라이더 설정
		{
			Needle_FX();
			
		}

		
		
	}
	void GrandPaScript::FixedUpdate()
	{
	}
	void GrandPaScript::Render()
	{
	}





	void GrandPaScript::OnCollisionEnter(Collider2D* collider)
	{
		int a = 0;
	}
	void GrandPaScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void GrandPaScript::OnCollisionExit(Collider2D* collider)
	{
	}





	void GrandPaScript::Start()
	{
	}
	void GrandPaScript::Action()
	{
	}
	void GrandPaScript::End()
	{
	}

	void GrandPaScript::Attack_index_PLUS()
	{
		//mGrandpaState = eGrandPaState::ATTACK1;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_idle") = std::bind(&GrandPaScript::Grandpa_IDLE, this);

		animator->Play(L"grandpa_idle");
	}







	void GrandPaScript::Grandpa_IDLE()
	{
		mGrandpaState = eGrandPaState::IDLE;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_idle") = std::bind(&GrandPaScript::Grandpa_IDLE2, this);
		animator->Play(L"grandpa_idle");
		
	}

	void GrandPaScript::Grandpa_IDLE2()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_idle") = std::bind(&GrandPaScript::Grandpa_IDLE3, this);
		animator->Play(L"grandpa_idle");
	}

	void GrandPaScript::Grandpa_IDLE3()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_idle") = std::bind(&GrandPaScript::Grandpa_ATTACK1, this);
		animator->Play(L"grandpa_idle");
	}

	void GrandPaScript::Grandpa_ATTACK1()
	{
		//mGrandpaState = eGrandPaState::ATTACK3;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_attack_1") = std::bind(&GrandPaScript::Grandpa_ATTACK2, this);
		animator->Play(L"grandpa_attack_1");
	}

	void GrandPaScript::Grandpa_ATTACK2()
	{
		//mGrandpaState = eGrandPaState::ATTACK3;
		Needle_FX();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_attack_2") = std::bind(&GrandPaScript::Grandpa_ATTACK3, this);

		animator->Play(L"grandpa_attack_2");
	}

	void GrandPaScript::Grandpa_ATTACK3()
	{
		//mGrandpaState = eGrandPaState::ATTACK3;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_attack_3") = std::bind(&GrandPaScript::Grandpa_IDLE, this);
		animator->Play(L"grandpa_attack_3");
	}

	void GrandPaScript::Grandpa_DIE()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"grandpa_die",false);
	}



	void GrandPaScript::Needle_FX()
	{
		{
			Monster* needleeffect = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			needleeffect->SetName(L"GrandPa_Needle_01");

			Transform* needleeffect_tr = needleeffect->GetComponent<Transform>();

			Transform* needleeffect_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = needleeffect_getobject_tr->GetPosition(); // 할배꺼

			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼
			tr2 += 5.6f * player_tr->Up() ;
			needleeffect_tr->SetPosition(tr2);

			needleeffect_tr->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
			needleeffect_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));


			Animator* needleeffect_Ani = needleeffect->AddComponent<Animator>();
			std::shared_ptr<Texture> needle_idle = Resources::Load<Texture>(L"needle_idle", L"GrandPa\\T_BossMoon_Needle.png");
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // 안씀
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 31, 0.1f);
			needleeffect_Ani->Create(L"needle_die2", needle_die2, Vector2(0.0f, 0.0f), Vector2(76.0f, 70.0f), Vector2(0.0f, -0.0f), 5, 5, 25, 0.10f);
			needleeffect_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);

			needleeffect_Ani->Play(L"needle_idle"); //루프 안돌림
			

			SpriteRenderer* needleeffect_sr = needleeffect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect_sr->SetMaterial(needleeffect_mateiral);
			std::shared_ptr<Mesh> needleeffect_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect_sr->SetMesh(needleeffect_mesh);

			Needle_Sc_FX* sc_fx = needleeffect->AddComponent<Needle_Sc_FX>();
			sc_fx->setmGameObject(mGameObject);
			
		}


	}
}