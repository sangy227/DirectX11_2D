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
#include "yaGrandPa_UI_Sc.h"

namespace ya {
	GrandPaScript::GrandPaScript()
		: Script()
		, mGrandpaState(eGrandPaState::IDLE)
		, Attack_index(0)
		, mGrandPa_Hp(7.5f)
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
		if (mGrandPa_Hp < 0)
			Grandpa_DIE();
		

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
			//Attack_index_PLUS();
			
			Attack_Start();
		}

		
			
		if (Input::GetKeyDown(eKeyCode::R)) //여긴 콜라이더 설정
		{
			
				//Grandpa_DIE();
				mGrandPa_Hp -= 0.3;
				if (mGrandPa_Hp < 0) {
					GrandPa_UI_Sc* Sc = HpBar_Bg_HP_obj->AddComponent<GrandPa_UI_Sc>();
					Sc->setIndex(0);
				}
				else {
					GrandPa_UI_Sc* Sc = HpBar_Bg_HP_obj->AddComponent<GrandPa_UI_Sc>();
					Sc->setIndex(mGrandPa_Hp);
				}
				
			
			
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
		if (collider->GetOwner()->GetName() == L"Hammer_Attack_Hit_Check")
		{
			mGrandPa_Hp -= 1.f;
		}

		if (mGrandPa_Hp < 0) {
			GrandPa_UI_Sc* Sc = HpBar_Bg_HP_obj->AddComponent<GrandPa_UI_Sc>();
			Sc->setIndex(0);
		}
		else {
			GrandPa_UI_Sc* Sc = HpBar_Bg_HP_obj->AddComponent<GrandPa_UI_Sc>();
			Sc->setIndex(mGrandPa_Hp);
		}

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

	void GrandPaScript::Attack_Start()
	{
		//mGrandpaState = eGrandPaState::ATTACK1;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_idle") = std::bind(&GrandPaScript::Grandpa_IDLE, this);

		animator->Play(L"grandpa_idle");


		//UI 보스 피통 BG
		{
			HpBar_Bg_obj = object::Instantiate<GameObject>(eLayerType::UI);
			HpBar_Bg_obj->SetName(L"Hpbar_grandpa");

			Transform* HpBar_Bg_tr = HpBar_Bg_obj->GetComponent<Transform>();
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			pos += 5.7 * tr->Up();
			
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
			pos += 5.6 * tr->Up();
			pos += 0.1 * tr->Foward();

			HpBar_Bg_tr->SetPosition(pos);
			HpBar_Bg_tr->SetScale(Vector3(7.5f, 0.08f, 0.f));


			GrandPa_UI_Sc* Ui_Sc = HpBar_Bg_HP_obj->AddComponent<GrandPa_UI_Sc>();
			Ui_Sc->setGameObject(GetOwner());
			Ui_Sc->setIndex(mGrandPa_Hp);
			Ui_Sc->setGrandPaScript(GetOwner()->GetComponent<GrandPaScript>());


			SpriteRenderer* UI_SpellRect_sr = HpBar_Bg_HP_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_material = Resources::Find<Material>(L"Bar_Boss_HEALTHMaterial");
			UI_SpellRect_sr->SetMaterial(UI_SpellRect_material);
			UI_SpellRect_sr->SetMesh(UI_SpellRect_mesh);
		}
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
		Needle_FX1();
		Needle_FX3();
		Needle_FX5();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_attack_1") = std::bind(&GrandPaScript::Grandpa_ATTACK2, this);
		animator->Play(L"grandpa_attack_1");
	}

	void GrandPaScript::Grandpa_ATTACK2()
	{
		//mGrandpaState = eGrandPaState::ATTACK3;
		Needle_FX2();
		Needle_FX4();
		
		
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_attack_2") = std::bind(&GrandPaScript::Grandpa_ATTACK3, this);

		animator->Play(L"grandpa_attack_2");
	}

	void GrandPaScript::Grandpa_ATTACK3()
	{
		//mGrandpaState = eGrandPaState::ATTACK3;
		Needle_FX1();
		Needle_FX2();
		Needle_FX3();
		Needle_FX4();
		Needle_FX5();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_attack_3") = std::bind(&GrandPaScript::Grandpa_IDLE, this);
		animator->Play(L"grandpa_attack_3");
	}

	void GrandPaScript::Grandpa_DIE()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"grandpa_die") = std::bind(&GrandPaScript::dead, this);
		animator->Play(L"grandpa_die",false);
		mGrandPa_Hp = 0.001;
	}

	void GrandPaScript::dead()
	{
		GetOwner()->Death();
		HpBar_Bg_obj->Death();
	}



	void GrandPaScript::Needle_FX()
	{
		
		//Needle_FX1();
		//Needle_FX2();
		//Needle_FX3();
		//Needle_FX4();
		//Needle_FX5();

	}
	void GrandPaScript::Needle_FX3()
	{
		{
			Monster* needleeffect = object::Instantiate<Monster>(eLayerType::Attack_Object);
			needleeffect->SetName(L"GrandPa_Needle_01");

			Transform* needleeffect_tr = needleeffect->GetComponent<Transform>();

			Transform* needleeffect_getobject_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = needleeffect_getobject_tr->GetPosition(); // 할배꺼

			Vector3 tr2 = player_tr->GetPosition(); // 플레이어꺼
			tr2 += 5.6f * player_tr->Up();
			needleeffect_tr->SetPosition(tr2);

			needleeffect_tr->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
			needleeffect_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Collider2D* needleeffect_col = needleeffect->AddComponent<Collider2D>();
			needleeffect_col->SetType(eColliderType::Rect);
			needleeffect_col->SetSize(Vector2(0.02f, 0.15f));
			needleeffect_col->SetCenter(Vector2(0.0f, 0.0f));


			Animator* needleeffect_Ani = needleeffect->AddComponent<Animator>();
			std::shared_ptr<Texture> needle_idle = Resources::Load<Texture>(L"needle_idle", L"GrandPa\\T_BossMoon_Needle.png");
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // 안씀
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 8, 0.05f);
			needleeffect_Ani->Create(L"needle_idle2", needle_idle, Vector2(0.0f, 123.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 3, 23, 0.1f);
			needleeffect_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);

			needleeffect_Ani->Play(L"needle_idle", false); //루프 안돌림


			SpriteRenderer* needleeffect_sr = needleeffect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect_sr->SetMaterial(needleeffect_mateiral);
			std::shared_ptr<Mesh> needleeffect_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect_sr->SetMesh(needleeffect_mesh);

			Needle_Sc_FX* sc_fx = needleeffect->AddComponent<Needle_Sc_FX>();
			sc_fx->setmGameObject(mGameObject);


		}
	}
	void GrandPaScript::Needle_FX2()
	{
		{
			Monster* needleeffect2 = object::Instantiate<Monster>(eLayerType::Attack_Object);
			needleeffect2->SetName(L"GrandPa_Needle_02");

			Transform* needleeffect2_tr = needleeffect2->GetComponent<Transform>();

			Transform* needleeffect_getobject2_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player2_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = needleeffect_getobject2_tr->GetPosition(); // 할배꺼

			Vector3 tr2 = player2_tr->GetPosition(); // 플레이어꺼
			tr2 += 5.6f * player2_tr->Up();
			tr2 += -2.0f * player2_tr->Right();
			needleeffect2_tr->SetPosition(tr2);

			needleeffect2_tr->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
			needleeffect2_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Collider2D* needleeffect_col = needleeffect2->AddComponent<Collider2D>();
			needleeffect_col->SetType(eColliderType::Rect);
			needleeffect_col->SetSize(Vector2(0.02f, 0.15f));
			needleeffect_col->SetCenter(Vector2(0.0f, 0.0f));

			Animator* needleeffect2_Ani = needleeffect2->AddComponent<Animator>();
			std::shared_ptr<Texture> needle_idle = Resources::Load<Texture>(L"needle_idle", L"GrandPa\\T_BossMoon_Needle.png");
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // 안씀
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect2_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 8, 0.05f);
			needleeffect2_Ani->Create(L"needle_idle2", needle_idle, Vector2(0.0f, 123.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 3, 23, 0.1f);
			needleeffect2_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);
		

			needleeffect2_Ani->Play(L"needle_idle", false); //루프 안돌림


			SpriteRenderer* needleeffect2_sr = needleeffect2->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect2_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect2_sr->SetMaterial(needleeffect2_mateiral);
			std::shared_ptr<Mesh> needleeffect2_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect2_sr->SetMesh(needleeffect2_mesh);

			Needle_Sc_FX* sc2_fx = needleeffect2->AddComponent<Needle_Sc_FX>();
			sc2_fx->setmGameObject(mGameObject);

		}
	}
	void GrandPaScript::Needle_FX4()
	{
		{
			Monster* needleeffect2 = object::Instantiate<Monster>(eLayerType::Attack_Object);
			needleeffect2->SetName(L"GrandPa_Needle_03");

			Transform* needleeffect2_tr = needleeffect2->GetComponent<Transform>();

			Transform* needleeffect_getobject2_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player2_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = needleeffect_getobject2_tr->GetPosition(); // 할배꺼

			Vector3 tr2 = player2_tr->GetPosition(); // 플레이어꺼
			tr2 += 5.6f * player2_tr->Up();
			tr2 += 2.0f * player2_tr->Right();
			needleeffect2_tr->SetPosition(tr2);

			needleeffect2_tr->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
			needleeffect2_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Collider2D* needleeffect_col = needleeffect2->AddComponent<Collider2D>();
			needleeffect_col->SetType(eColliderType::Rect);
			needleeffect_col->SetSize(Vector2(0.02f, 0.15f));
			needleeffect_col->SetCenter(Vector2(0.0f, 0.0f));

			Animator* needleeffect2_Ani = needleeffect2->AddComponent<Animator>();
			std::shared_ptr<Texture> needle_idle = Resources::Load<Texture>(L"needle_idle", L"GrandPa\\T_BossMoon_Needle.png");
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // 안씀
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect2_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 8, 0.05f);
			needleeffect2_Ani->Create(L"needle_idle2", needle_idle, Vector2(0.0f, 123.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 3, 23, 0.1f);
			needleeffect2_Ani->Create(L"needle_die2", needle_die2, Vector2(0.0f, 0.0f), Vector2(76.0f, 70.0f), Vector2(0.0f, -0.0f), 5, 5, 25, 0.10f);
			needleeffect2_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);

			needleeffect2_Ani->Play(L"needle_idle", false); //루프 안돌림


			SpriteRenderer* needleeffect2_sr = needleeffect2->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect2_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect2_sr->SetMaterial(needleeffect2_mateiral);
			std::shared_ptr<Mesh> needleeffect2_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect2_sr->SetMesh(needleeffect2_mesh);

			Needle_Sc_FX* sc2_fx = needleeffect2->AddComponent<Needle_Sc_FX>();
			sc2_fx->setmGameObject(mGameObject);

		}
	}
	void GrandPaScript::Needle_FX5()
	{
		{
			Monster* needleeffect2 = object::Instantiate<Monster>(eLayerType::Attack_Object);
			needleeffect2->SetName(L"GrandPa_Needle_04");

			Transform* needleeffect2_tr = needleeffect2->GetComponent<Transform>();

			Transform* needleeffect_getobject2_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player2_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = needleeffect_getobject2_tr->GetPosition(); // 할배꺼

			Vector3 tr2 = player2_tr->GetPosition(); // 플레이어꺼
			tr2 += 5.6f * player2_tr->Up();
			tr2 += 4.0f * player2_tr->Right();
			needleeffect2_tr->SetPosition(tr2);

			needleeffect2_tr->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
			needleeffect2_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Collider2D* needleeffect_col = needleeffect2->AddComponent<Collider2D>();
			needleeffect_col->SetType(eColliderType::Rect);
			needleeffect_col->SetSize(Vector2(0.02f, 0.15f));
			needleeffect_col->SetCenter(Vector2(0.0f, 0.0f));

			Animator* needleeffect2_Ani = needleeffect2->AddComponent<Animator>();
			std::shared_ptr<Texture> needle_idle = Resources::Load<Texture>(L"needle_idle", L"GrandPa\\T_BossMoon_Needle.png");
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // 안씀
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect2_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 8, 0.05f);
			needleeffect2_Ani->Create(L"needle_idle2", needle_idle, Vector2(0.0f, 123.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 3, 23, 0.1f);
			needleeffect2_Ani->Create(L"needle_die2", needle_die2, Vector2(0.0f, 0.0f), Vector2(76.0f, 70.0f), Vector2(0.0f, -0.0f), 5, 5, 25, 0.10f);
			needleeffect2_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);

			needleeffect2_Ani->Play(L"needle_idle", false); //루프 안돌림


			SpriteRenderer* needleeffect2_sr = needleeffect2->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect2_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect2_sr->SetMaterial(needleeffect2_mateiral);
			std::shared_ptr<Mesh> needleeffect2_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect2_sr->SetMesh(needleeffect2_mesh);

			Needle_Sc_FX* sc2_fx = needleeffect2->AddComponent<Needle_Sc_FX>();
			sc2_fx->setmGameObject(mGameObject);

		}
	}
	void GrandPaScript::Needle_FX1()
	{
		{
			Monster* needleeffect2 = object::Instantiate<Monster>(eLayerType::Attack_Object);
			needleeffect2->SetName(L"GrandPa_Needle_04");

			Transform* needleeffect2_tr = needleeffect2->GetComponent<Transform>();

			Transform* needleeffect_getobject2_tr = GetOwner()->GetComponent<Transform>(); // 이건 할배꺼 
			Transform* player2_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼

			Vector3 tr = needleeffect_getobject2_tr->GetPosition(); // 할배꺼

			Vector3 tr2 = player2_tr->GetPosition(); // 플레이어꺼
			tr2 += 5.6f * player2_tr->Up();
			tr2 += -4.0f * player2_tr->Right();
			needleeffect2_tr->SetPosition(tr2);

			needleeffect2_tr->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
			needleeffect2_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Collider2D* needleeffect_col = needleeffect2->AddComponent<Collider2D>();
			needleeffect_col->SetType(eColliderType::Rect);
			needleeffect_col->SetSize(Vector2(0.02f, 0.15f));
			needleeffect_col->SetCenter(Vector2(0.0f, 0.0f));

			Animator* needleeffect2_Ani = needleeffect2->AddComponent<Animator>();
			std::shared_ptr<Texture> needle_idle = Resources::Load<Texture>(L"needle_idle", L"GrandPa\\T_BossMoon_Needle.png");
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // 안씀
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect2_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 8, 0.05f);
			needleeffect2_Ani->Create(L"needle_idle2", needle_idle, Vector2(0.0f, 123.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 3, 23, 0.1f);
			needleeffect2_Ani->Create(L"needle_die2", needle_die2, Vector2(0.0f, 0.0f), Vector2(76.0f, 70.0f), Vector2(0.0f, -0.0f), 5, 5, 25, 0.10f);
			needleeffect2_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);

			needleeffect2_Ani->Play(L"needle_idle", false); //루프 안돌림


			SpriteRenderer* needleeffect2_sr = needleeffect2->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect2_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect2_sr->SetMaterial(needleeffect2_mateiral);
			std::shared_ptr<Mesh> needleeffect2_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect2_sr->SetMesh(needleeffect2_mesh);

			Needle_Sc_FX* sc2_fx = needleeffect2->AddComponent<Needle_Sc_FX>();
			sc2_fx->setmGameObject(mGameObject);

		}
	}
	void GrandPaScript::DieDieDie()
	{
		mGrandPa_Hp = 0;
	}
}