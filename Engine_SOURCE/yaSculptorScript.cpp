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
#include "yaSculptor_UI_Sc.h"
namespace ya {
	SculptorScript::SculptorScript()
		: Script()
		, mSculptorState(eSculptorState::IDLE)
		, mNeedleState(eNeedleState::None)
		, mbool(true)
		, mSculptor_Hp(7.5)
		, Sculptor_Audio_obj{}
		, Sculptor_Audio_Source{}
	{	 

	}
	SculptorScript::~SculptorScript()
	{
	}
	void SculptorScript::Initalize()
	{
		audio[0] = Resources::Load<AudioClip>(L"Sculptor_Hurt", L"Music\\UI\\SFX_Player_Hit_Enemy_Squish_01.wav");
		audio[0]->SetVolume(5.0f);
		audio[1] = Resources::Load<AudioClip>(L"Sculptor_Cast", L"Music\\Monster\\SFX_BossTheSculptor_Cast_01.wav");
		audio[2] = Resources::Load<AudioClip>(L"Sculptor_Neddle", L"Music\\Monster\\SFX_BossTheSculptor_AOE_01.wav");
		audio[3] = Resources::Load<AudioClip>(L"Sculptor_first_die", L"Music\\Monster\\SFX_BossTheSculptor_FirstOne_Death_01.wav");
		audio[4] = Resources::Load<AudioClip>(L"Sculptor_second_die", L"Music\\Monster\\SFX_BossTheSculptor_Death_01.wav");
		for (size_t i = 0; i < 100; i++)
		{
			Sculptor_Audio_obj[i] = object::Instantiate<GameObject>(eLayerType::UI);
		}
	}
	void SculptorScript::Update()
	{
		if (mSculptor_Hp < 0)
			Sculptor_IDLE_TO_DIE();
			

		Transform* obj_tr = GetOwner()->GetComponent<Transform>();
		Transform* player_tr = mGameObject->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();


		if (mNeedleState == eNeedleState::IDLE_Needle) {
			
		}
		if (mNeedleState == eNeedleState::Chenge) {
			if (mbool) {
				mbool = false;
				mNeedleState = eNeedleState::Needle1;
			}
			else {
				mbool = true;
				mNeedleState = eNeedleState::Needle2;
			}
		}
		if (mNeedleState == eNeedleState::Needle1) {
			/*Sculptor_Needle2();
			Sculptor_Needle3();
			Sculptor_Needle4();
			Sculptor_Needle5();
			Sculptor_Needle6();
			Sculptor_Needle7();
			Sculptor_Needle8();*/
			mNeedleState = eNeedleState::IDLE_Needle;
		}
		if (mNeedleState == eNeedleState::Needle2) {
			//Sculptor_Needle2();
			mNeedleState = eNeedleState::IDLE_Needle;
		}


		if (Input::GetKeyDown(eKeyCode::T)) //여긴 콜라이더 설정
		{
			Attack_Start();
		}

		if (Input::GetKeyDown(eKeyCode::Y)) //여긴 콜라이더 설정
		{
			//Grandpa_DIE();
			/*mSculptor_Hp -= 0.3;
			if (mSculptor_Hp < 0) {
				Sculptor_UI_Sc* Sc = HpBar_Bg_HP_obj->AddComponent<Sculptor_UI_Sc>();
				Sc->setIndex(0);
			}
			else {
				Sculptor_UI_Sc* Sc = HpBar_Bg_HP_obj->AddComponent<Sculptor_UI_Sc>();
				Sc->setIndex(mSculptor_Hp);
			}*/

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
		if (collider->GetOwner()->GetName() == L"Normal_Attack_Hit_Check")
		{
			mSculptor_Hp -= 0.16f;
			Sculptor_hurt();
		}

		if (collider->GetOwner()->GetName() == L"Hammer_Attack_Hit_Check")
		{
			mSculptor_Hp -= 1.2f;
			Sculptor_hurt();

		}

		if (collider->GetOwner()->GetName() == L"Painwheel_Attack_Hit_Check")
		{
			Sculptor_hurt();
			mSculptor_Hp -= 0.2f;
		}

		if (collider->GetOwner()->GetName() == L"Spear_Attack_Hit_Check")
		{
			Sculptor_hurt();
			mSculptor_Hp -= 0.8f;
		}

		if (collider->GetOwner()->GetName() == L"Whirlwind_Attack_Hit_Check")
		{
			Sculptor_hurt();
			mSculptor_Hp -= 0.56f;
		}


		if (mSculptor_Hp < 0) {
			Sculptor_UI_Sc* Sc = HpBar_Bg_HP_obj->AddComponent<Sculptor_UI_Sc>();
			Sc->setIndex(0);
		}
		else {
			Sculptor_UI_Sc* Sc = HpBar_Bg_HP_obj->AddComponent<Sculptor_UI_Sc>();
			Sc->setIndex(mSculptor_Hp);
		}
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

	void SculptorScript::Attack_Start()
	{
		chenge();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"sculptor_idle") = std::bind(&SculptorScript::Sculptor_IDLE, this);

		//UI 보스 피통 BG
		{
			HpBar_Bg_obj = object::Instantiate<GameObject>(eLayerType::UI);
			HpBar_Bg_obj->SetName(L"Hpbar_grandpa");

			Transform* HpBar_Bg_tr = HpBar_Bg_obj->GetComponent<Transform>();
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			pos += 5.4 * tr->Up();

			HpBar_Bg_tr->SetPosition(pos);
			HpBar_Bg_tr->SetScale(Vector3(8.f, 0.5f, 0.f));

			SpriteRenderer* UI_SpellRect_sr = HpBar_Bg_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_material = Resources::Find<Material>(L"Bar_Boss_BGMaterial");
			UI_SpellRect_sr->SetMaterial(UI_SpellRect_material);
			UI_SpellRect_sr->SetMesh(UI_SpellRect_mesh);
		}

		//UI 보스 피
		{
			HpBar_Bg_HP_obj = object::Instantiate<GameObject>(eLayerType::UI);
			HpBar_Bg_HP_obj->SetName(L"Hpbar_Health_grandpa");

			Transform* HpBar_Bg_tr = HpBar_Bg_HP_obj->GetComponent<Transform>();
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			pos += 5.3 * tr->Up();
			pos += 0.1 * tr->Foward();

			HpBar_Bg_tr->SetPosition(pos);
			HpBar_Bg_tr->SetScale(Vector3(7.5f, 0.08f, 0.f));


			Sculptor_UI_Sc* Ui_Sc = HpBar_Bg_HP_obj->AddComponent<Sculptor_UI_Sc>();
			Ui_Sc->setGameObject(GetOwner());
			Ui_Sc->setIndex(mSculptor_Hp);
			//Ui_Sc->setGrandPaScript(GetOwner()->GetComponent<GrandPaScript>());


			SpriteRenderer* UI_SpellRect_sr = HpBar_Bg_HP_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_material = Resources::Find<Material>(L"Bar_Boss_HEALTHMaterial");
			UI_SpellRect_sr->SetMaterial(UI_SpellRect_material);
			UI_SpellRect_sr->SetMesh(UI_SpellRect_mesh);
		}
	}


	void SculptorScript::Sculptor_IDLE()
	{
		mSculptorState = eSculptorState::IDLE;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"sculptor_idle") = std::bind(&SculptorScript::Sculptor_IDLE3, this); 
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
		Sculptor_Attack_Sound();
		
		//Sculptor_Needle3();
		//Sculptor_Needle4();
		//Sculptor_Needle5();
		//Sculptor_Needle6();
		//Sculptor_Needle7();
		//Sculptor_Needle8();
		chenge();
		mSculptorState = eSculptorState::ATTACK1;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"sculptor_attack") = std::bind(&SculptorScript::Sculptor_IDLE, this);
		animator->GetEvent(L"sculptor_attack",3) = std::bind(&SculptorScript::Sculptor_Needle3, this);
		animator->GetEvent(L"sculptor_attack",4) = std::bind(&SculptorScript::Sculptor_Needle8, this);
		animator->GetEvent(L"sculptor_attack",7) = std::bind(&SculptorScript::Sculptor_Needle4, this);
		animator->GetEvent(L"sculptor_attack",8) = std::bind(&SculptorScript::Sculptor_Needle7, this);
		animator->GetEvent(L"sculptor_attack",9) = std::bind(&SculptorScript::Sculptor_Needle5, this);
		animator->GetEvent(L"sculptor_attack",10) = std::bind(&SculptorScript::Sculptor_Needle6, this);
		
		

		animator->Play(L"sculptor_attack");
	}
	void SculptorScript::Sculptor_IDLE_TO_DIE()
	{
		mSculptorState = eSculptorState::IDLE;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"sculptor_idle") = std::bind(&SculptorScript::Sculptor_DIE, this);
		animator->Play(L"sculptor_idle");
		mSculptor_Hp = 0.001;
	}
	void SculptorScript::Sculptor_DIE()
	{
		mSculptorState = eSculptorState::IDLE;
		Sculptor_first_die_Sound();
		Sculptor_Die_Sound();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"sculptor_die") = std::bind(&SculptorScript::Dead, this);
		animator->Play(L"sculptor_die",false);
	}

	void SculptorScript::Dead()
	{
		//GetOwner()->Death();
		HpBar_Bg_obj->Death();
	}



	void SculptorScript::Sculptor_Needle()
	{
		GameObject* gameobj = GetOwner()->GetComponent<GameObject>(); //할배꺼 가져온거

		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Attack_Object);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect1");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += 8.0f * SculptorNeedle_getobject_tr->Right();
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

	}


	void SculptorScript::Sculptor_Needle2()
	{
		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Attack_Object);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect2");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += -8.0f * SculptorNeedle_getobject_tr->Right();
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

	void SculptorScript::Sculptor_Needle3()
	{
	
		GameObject* gameobj = GetOwner()->GetComponent<GameObject>(); //할배꺼 가져온거
		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Attack_Object);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect3");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += -6.0f * SculptorNeedle_getobject_tr->Right();
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

			SculptorNeedle_Ani->GetStartEvent(L"sculptor_needle2") = std::bind(&SculptorScript::Sculptor_Needle_Go, this);

			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();


		}
	}

	void SculptorScript::Sculptor_Needle4()
	{
		

		GameObject* gameobj = GetOwner()->GetComponent<GameObject>(); //할배꺼 가져온거
		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Attack_Object);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect4");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += -4.0f * SculptorNeedle_getobject_tr->Right();
			SculptorNeedle_tr->SetPosition(tr);
			SculptorNeedle_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));


			Animator* SculptorNeedle_Ani = SculptorNeedle_effect->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_needle = Resources::Load<Texture>(L"sculptor_needle", L"BossSculptor\\T_BossMoon_HomingProjectiles.png");


			SculptorNeedle_Ani->Create(L"sculptor_needle", sculptor_needle, Vector2(0.0f, 0.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 8, 29, 0.05f);
			SculptorNeedle_Ani->Create(L"sculptor_needle1", sculptor_needle, Vector2(0.0f, 468.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 18, 0.07f);
			SculptorNeedle_Ani->Create(L"sculptor_needle2", sculptor_needle, Vector2(0.0f, 702.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 13, 0.05f);

			SculptorNeedle_Ani->GetStartEvent(L"sculptor_needle2") = std::bind(&SculptorScript::Sculptor_Needle_Go, this);

			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();


		}
	}

	void SculptorScript::Sculptor_Needle5()
	{
		

		GameObject* gameobj = GetOwner()->GetComponent<GameObject>(); //할배꺼 가져온거
		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Attack_Object);
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

			SculptorNeedle_Ani->GetStartEvent(L"sculptor_needle2") = std::bind(&SculptorScript::Sculptor_Needle_Go, this);

			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();


		}
	}

	void SculptorScript::Sculptor_Needle6()
	{
		

		GameObject* gameobj = GetOwner()->GetComponent<GameObject>(); //할배꺼 가져온거
		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Attack_Object);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect6");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += 2.0f * SculptorNeedle_getobject_tr->Right();
			SculptorNeedle_tr->SetPosition(tr);
			SculptorNeedle_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));


			Animator* SculptorNeedle_Ani = SculptorNeedle_effect->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_needle = Resources::Load<Texture>(L"sculptor_needle", L"BossSculptor\\T_BossMoon_HomingProjectiles.png");


			SculptorNeedle_Ani->Create(L"sculptor_needle", sculptor_needle, Vector2(0.0f, 0.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 8, 29, 0.05f);
			SculptorNeedle_Ani->Create(L"sculptor_needle1", sculptor_needle, Vector2(0.0f, 468.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 18, 0.07f);
			SculptorNeedle_Ani->Create(L"sculptor_needle2", sculptor_needle, Vector2(0.0f, 702.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 13, 0.05f);

			SculptorNeedle_Ani->GetStartEvent(L"sculptor_needle2") = std::bind(&SculptorScript::Sculptor_Needle_Go, this);

			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();


		}
	}

	void SculptorScript::Sculptor_Needle7()
	{
		

		GameObject* gameobj = GetOwner()->GetComponent<GameObject>(); //할배꺼 가져온거
		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Attack_Object);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect7");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += 4.0f * SculptorNeedle_getobject_tr->Right();
			SculptorNeedle_tr->SetPosition(tr);
			SculptorNeedle_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));


			Animator* SculptorNeedle_Ani = SculptorNeedle_effect->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_needle = Resources::Load<Texture>(L"sculptor_needle", L"BossSculptor\\T_BossMoon_HomingProjectiles.png");


			SculptorNeedle_Ani->Create(L"sculptor_needle", sculptor_needle, Vector2(0.0f, 0.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 8, 29, 0.05f);
			SculptorNeedle_Ani->Create(L"sculptor_needle1", sculptor_needle, Vector2(0.0f, 468.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 18, 0.07f);
			SculptorNeedle_Ani->Create(L"sculptor_needle2", sculptor_needle, Vector2(0.0f, 702.0f), Vector2(107.0f, 117.0f), Vector2(0.0f, 0.0f), 9, 2, 13, 0.05f);

			SculptorNeedle_Ani->GetStartEvent(L"sculptor_needle2") = std::bind(&SculptorScript::Sculptor_Needle_Go, this);

			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();
		

		}
	}

	void SculptorScript::Sculptor_Needle8()
	{
		

		GameObject* gameobj = GetOwner()->GetComponent<GameObject>(); //할배꺼 가져온거
		{
			Monster* SculptorNeedle_effect = object::Instantiate<Monster>(eLayerType::Attack_Object);
			SculptorNeedle_effect->SetName(L"SculptorNeedle_effect8");

			Transform* SculptorNeedle_tr = SculptorNeedle_effect->GetComponent<Transform>();

			Transform* SculptorNeedle_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = SculptorNeedle_getobject_tr->GetPosition(); // 조각가 할배꺼
			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼

			tr += 5.2f * SculptorNeedle_getobject_tr->Up();
			tr += 6.0f * SculptorNeedle_getobject_tr->Right();
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

			SculptorNeedle_Ani->GetStartEvent(L"sculptor_needle2") = std::bind(&SculptorScript::Sculptor_Needle_Go, this);

			SculptorNeedle_Ani->Play(L"sculptor_needle", false); //루프 안돌림


			SpriteRenderer* SculptorNeedle_sr = SculptorNeedle_effect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
			std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
			SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

			Sculptor_Needle_Sc_Fx* sc_fx = SculptorNeedle_effect->AddComponent<Sculptor_Needle_Sc_Fx>();


		}
	}

	void SculptorScript::Sculptor_hurt()
	{
		Sculptor_Audio_Source[0] = Sculptor_Audio_obj[0]->AddComponent<AudioSource>();
		Sculptor_Audio_Source[0]->SetClip(audio[0]);
		Sculptor_Audio_Source[0]->Play();
	}

	void SculptorScript::Sculptor_Attack_Sound()
	{
		Sculptor_Audio_Source[1] = Sculptor_Audio_obj[1]->AddComponent<AudioSource>();
		Sculptor_Audio_Source[1]->SetClip(audio[1]);
		Sculptor_Audio_Source[1]->Play();
	}

	void SculptorScript::Sculptor_Needle_Go()
	{
		Sculptor_Audio_Source[2] = Sculptor_Audio_obj[2]->AddComponent<AudioSource>();
		Sculptor_Audio_Source[2]->SetClip(audio[2]);
		Sculptor_Audio_Source[2]->Play();
	}

	void SculptorScript::Sculptor_first_die_Sound()
	{
		Sculptor_Audio_Source[3] = Sculptor_Audio_obj[3]->AddComponent<AudioSource>();
		Sculptor_Audio_Source[3]->SetClip(audio[3]);
		Sculptor_Audio_Source[3]->Play();
	}

	void SculptorScript::Sculptor_Die_Sound()
	{
		Sculptor_Audio_Source[4] = Sculptor_Audio_obj[4]->AddComponent<AudioSource>();
		Sculptor_Audio_Source[4]->SetClip(audio[4]);
		Sculptor_Audio_Source[4]->Play();
	}

	
	void SculptorScript::chenge()
	{
		mNeedleState = eNeedleState::Chenge;
	}
}