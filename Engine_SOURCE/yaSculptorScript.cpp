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
#include "yaSculptor_Needle_Sc_Fx.h"
namespace ya {
	SculptorScript::SculptorScript()
		: Script()
		, mSculptorState(eSculptorState::IDLE)
		, mNeedleState(eNeedleState::None)
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
		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();


		if (mNeedleState == eNeedleState::IDLE_Needle) {
			
		}
		if (mNeedleState == eNeedleState::Chenge) {

		}
		if (mNeedleState == eNeedleState::Needle1) {

		}
		if (mNeedleState == eNeedleState::Needle2) {

		}


		if (Input::GetKeyDown(eKeyCode::T)) //여긴 콜라이더 설정
		{
			//animator->GetCompleteEvent(L"sculptor_idle") = std::bind(&SculptorScript::Sculptor_IDLE, this);
			//animator->Play(L"sculptor_idle");
			Sculptor_Needle();
		}

		if (Input::GetKeyDown(eKeyCode::Y)) //여긴 콜라이더 설정
		{
			Sculptor_Needle2();

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
		Sculptor_Needle();
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
		GameObject* gameobj = GetOwner()->GetComponent<GameObject>(); //할배꺼 가져온거

		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect1");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += 2.0f * SculptorNeedle_getobject_tr->Right();
			SculptorNeedle_tr->SetPosition(tr);
			SculptorNeedle_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Collider2D* SculptorNeedle_effect_col = SculptorNeedle_effect->AddComponent<Collider2D>();
			SculptorNeedle_effect_col->SetType(eColliderType::Rect);
			SculptorNeedle_effect_col->SetSize(Vector2(0.05f, 0.05f));
			

			Animator* SculptorNeedle_Ani = SculptorNeedle_effect->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_needle = Resources::Load<Texture>(L"sculptor_needle", L"BossSculptor\\T_BossMoon_HomingProjectiles.png");
			

			SculptorNeedle_Ani->Create(L"sculptor_needle", sculptor_needle, Vector2(0.0f, 0.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 8, 29, 0.05f);
			SculptorNeedle_Ani->Create(L"sculptor_needle1", sculptor_needle, Vector2(0.0f, 468.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 18, 0.07f);
			SculptorNeedle_Ani->Create(L"sculptor_needle2", sculptor_needle, Vector2(0.0f, 702.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 13, 0.05f);
			

			SculptorNeedle_Ani->Play(L"sculptor_needle",false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();
			sc_fx->setmGameObject(gameobj);
			
		}

		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect5");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += 6.0f * SculptorNeedle_getobject_tr->Right();
			SculptorNeedle_tr->SetPosition(tr);
			SculptorNeedle_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));


			Animator* SculptorNeedle_Ani = SculptorNeedle_effect->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_needle = Resources::Load<Texture>(L"sculptor_needle", L"BossSculptor\\T_BossMoon_HomingProjectiles.png");


			SculptorNeedle_Ani->Create(L"sculptor_needle", sculptor_needle, Vector2(0.0f, 0.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 8, 29, 0.05f);
			SculptorNeedle_Ani->Create(L"sculptor_needle1", sculptor_needle, Vector2(0.0f, 468.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 18, 0.07f);
			SculptorNeedle_Ani->Create(L"sculptor_needle2", sculptor_needle, Vector2(0.0f, 702.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 13, 0.05f);


			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();
			

		}

		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect5");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += -2.0f * SculptorNeedle_getobject_tr->Right();
			SculptorNeedle_tr->SetPosition(tr);
			SculptorNeedle_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));


			Animator* SculptorNeedle_Ani = SculptorNeedle_effect->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_needle = Resources::Load<Texture>(L"sculptor_needle", L"BossSculptor\\T_BossMoon_HomingProjectiles.png");


			SculptorNeedle_Ani->Create(L"sculptor_needle", sculptor_needle, Vector2(0.0f, 0.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 8, 29, 0.05f);
			SculptorNeedle_Ani->Create(L"sculptor_needle1", sculptor_needle, Vector2(0.0f, 468.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 18, 0.07f);
			SculptorNeedle_Ani->Create(L"sculptor_needle2", sculptor_needle, Vector2(0.0f, 702.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 13, 0.05f);


			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();
		

		}

		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect7");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += -6.0f * SculptorNeedle_getobject_tr->Right();
			SculptorNeedle_tr->SetPosition(tr);
			SculptorNeedle_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));


			Animator* SculptorNeedle_Ani = SculptorNeedle_effect->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_needle = Resources::Load<Texture>(L"sculptor_needle", L"BossSculptor\\T_BossMoon_HomingProjectiles.png");


			SculptorNeedle_Ani->Create(L"sculptor_needle", sculptor_needle, Vector2(0.0f, 0.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 8, 29, 0.05f);
			SculptorNeedle_Ani->Create(L"sculptor_needle1", sculptor_needle, Vector2(0.0f, 468.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 18, 0.07f);
			SculptorNeedle_Ani->Create(L"sculptor_needle2", sculptor_needle, Vector2(0.0f, 702.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 13, 0.05f);


			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();
			

		}

	}


	void SculptorScript::Sculptor_Needle2()
	{
		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect2");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += 4.0f * SculptorNeedle_getobject_tr->Right();
			SculptorNeedle_tr->SetPosition(tr);
			SculptorNeedle_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Collider2D* SculptorNeedle_effect_col = SculptorNeedle_effect->AddComponent<Collider2D>();
			SculptorNeedle_effect_col->SetType(eColliderType::Rect);
			SculptorNeedle_effect_col->SetSize(Vector2(0.05f, 0.05f));


			Animator* SculptorNeedle_Ani = SculptorNeedle_effect->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_needle = Resources::Load<Texture>(L"sculptor_needle", L"BossSculptor\\T_BossMoon_HomingProjectiles.png");


			SculptorNeedle_Ani->Create(L"sculptor_needle", sculptor_needle, Vector2(0.0f, 0.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 8, 29, 0.05f);
			SculptorNeedle_Ani->Create(L"sculptor_needle1", sculptor_needle, Vector2(0.0f, 468.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 18, 0.07f);
			SculptorNeedle_Ani->Create(L"sculptor_needle2", sculptor_needle, Vector2(0.0f, 702.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 13, 0.05f);


			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();


		}


		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect2");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += -4.0f * SculptorNeedle_getobject_tr->Right();
			SculptorNeedle_tr->SetPosition(tr);
			SculptorNeedle_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Collider2D* SculptorNeedle_effect_col = SculptorNeedle_effect->AddComponent<Collider2D>();
			SculptorNeedle_effect_col->SetType(eColliderType::Rect);
			SculptorNeedle_effect_col->SetSize(Vector2(0.05f, 0.05f));


			Animator* SculptorNeedle_Ani = SculptorNeedle_effect->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_needle = Resources::Load<Texture>(L"sculptor_needle", L"BossSculptor\\T_BossMoon_HomingProjectiles.png");


			SculptorNeedle_Ani->Create(L"sculptor_needle", sculptor_needle, Vector2(0.0f, 0.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 8, 29, 0.05f);
			SculptorNeedle_Ani->Create(L"sculptor_needle1", sculptor_needle, Vector2(0.0f, 468.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 18, 0.07f);
			SculptorNeedle_Ani->Create(L"sculptor_needle2", sculptor_needle, Vector2(0.0f, 702.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 13, 0.05f);


			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();


		}

		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect2");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += 0.0f * SculptorNeedle_getobject_tr->Right();
			SculptorNeedle_tr->SetPosition(tr);
			SculptorNeedle_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Collider2D* SculptorNeedle_effect_col = SculptorNeedle_effect->AddComponent<Collider2D>();
			SculptorNeedle_effect_col->SetType(eColliderType::Rect);
			SculptorNeedle_effect_col->SetSize(Vector2(0.05f, 0.05f));


			Animator* SculptorNeedle_Ani = SculptorNeedle_effect->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_needle = Resources::Load<Texture>(L"sculptor_needle", L"BossSculptor\\T_BossMoon_HomingProjectiles.png");


			SculptorNeedle_Ani->Create(L"sculptor_needle", sculptor_needle, Vector2(0.0f, 0.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 8, 29, 0.05f);
			SculptorNeedle_Ani->Create(L"sculptor_needle1", sculptor_needle, Vector2(0.0f, 468.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 18, 0.07f);
			SculptorNeedle_Ani->Create(L"sculptor_needle2", sculptor_needle, Vector2(0.0f, 702.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 13, 0.05f);


			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();


		}
	}
}