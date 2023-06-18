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


		//���¹�
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


		if (Input::GetKeyDown(eKeyCode::E)) //���� �ݶ��̴� ����
		{
			//mGrandpaState = eGrandPaState::ATTACK1;
			//Attack_index_PLUS();
			Grandpa_DIE();
		}

		if (Input::GetKeyDown(eKeyCode::R)) //���� �ݶ��̴� ����
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

			Transform* needleeffect_getobject_tr = GetOwner()->GetComponent<Transform>(); // �̰� �ҹ貨 
			Transform* player_tr = mGameObject->GetComponent<Transform>(); // �̰� �÷��̾

			Vector3 tr = needleeffect_getobject_tr->GetPosition(); // �ҹ貨

			Vector3 tr2 = player_tr->GetPosition(); // �÷��̾
			tr2 += 5.6f * player_tr->Up() ;
			needleeffect_tr->SetPosition(tr2);

			needleeffect_tr->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
			needleeffect_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Collider2D* needleeffect_col = needleeffect->AddComponent<Collider2D>();
			needleeffect_col->SetType(eColliderType::Rect);
			needleeffect_col->SetSize(Vector2(0.02f, 0.15f));
			needleeffect_col->SetCenter(Vector2(0.0f, 0.0f));


			Animator* needleeffect_Ani = needleeffect->AddComponent<Animator>();
			std::shared_ptr<Texture> needle_idle = Resources::Load<Texture>(L"needle_idle", L"GrandPa\\T_BossMoon_Needle.png");
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // �Ⱦ�
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 8, 0.1f);
			needleeffect_Ani->Create(L"needle_idle2", needle_idle, Vector2(0.0f, 123.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 3, 23, 0.1f);
			needleeffect_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);

			needleeffect_Ani->Play(L"needle_idle",false); //���� �ȵ���
			

			SpriteRenderer* needleeffect_sr = needleeffect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect_sr->SetMaterial(needleeffect_mateiral);
			std::shared_ptr<Mesh> needleeffect_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect_sr->SetMesh(needleeffect_mesh);

			Needle_Sc_FX* sc_fx = needleeffect->AddComponent<Needle_Sc_FX>();
			sc_fx->setmGameObject(mGameObject);
			
		}
		{
			Monster* needleeffect2 = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			needleeffect2->SetName(L"GrandPa_Needle_02");

			Transform* needleeffect2_tr = needleeffect2->GetComponent<Transform>();

			Transform* needleeffect_getobject2_tr = GetOwner()->GetComponent<Transform>(); // �̰� �ҹ貨 
			Transform* player2_tr = mGameObject->GetComponent<Transform>(); // �̰� �÷��̾

			Vector3 tr = needleeffect_getobject2_tr->GetPosition(); // �ҹ貨

			Vector3 tr2 = player2_tr->GetPosition(); // �÷��̾
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
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // �Ⱦ�
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect2_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 8, 0.1f);
			needleeffect2_Ani->Create(L"needle_idle2", needle_idle, Vector2(0.0f, 123.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 3, 23, 0.1f);
			needleeffect2_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);

			needleeffect2_Ani->Play(L"needle_idle", false); //���� �ȵ���


			SpriteRenderer* needleeffect2_sr = needleeffect2->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect2_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect2_sr->SetMaterial(needleeffect2_mateiral);
			std::shared_ptr<Mesh> needleeffect2_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect2_sr->SetMesh(needleeffect2_mesh);

			Needle_Sc_FX* sc2_fx = needleeffect2->AddComponent<Needle_Sc_FX>();
			sc2_fx->setmGameObject(mGameObject);

		}
		{
			Monster* needleeffect2 = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			needleeffect2->SetName(L"GrandPa_Needle_03");

			Transform* needleeffect2_tr = needleeffect2->GetComponent<Transform>();

			Transform* needleeffect_getobject2_tr = GetOwner()->GetComponent<Transform>(); // �̰� �ҹ貨 
			Transform* player2_tr = mGameObject->GetComponent<Transform>(); // �̰� �÷��̾

			Vector3 tr = needleeffect_getobject2_tr->GetPosition(); // �ҹ貨

			Vector3 tr2 = player2_tr->GetPosition(); // �÷��̾
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
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // �Ⱦ�
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect2_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 8, 0.1f);
			needleeffect2_Ani->Create(L"needle_idle2", needle_idle, Vector2(0.0f, 123.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 3, 23, 0.1f);
			needleeffect2_Ani->Create(L"needle_die2", needle_die2, Vector2(0.0f, 0.0f), Vector2(76.0f, 70.0f), Vector2(0.0f, -0.0f), 5, 5, 25, 0.10f);
			needleeffect2_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);

			needleeffect2_Ani->Play(L"needle_idle", false); //���� �ȵ���


			SpriteRenderer* needleeffect2_sr = needleeffect2->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect2_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect2_sr->SetMaterial(needleeffect2_mateiral);
			std::shared_ptr<Mesh> needleeffect2_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect2_sr->SetMesh(needleeffect2_mesh);

			Needle_Sc_FX* sc2_fx = needleeffect2->AddComponent<Needle_Sc_FX>();
			sc2_fx->setmGameObject(mGameObject);

		}

		{
			Monster* needleeffect2 = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			needleeffect2->SetName(L"GrandPa_Needle_04");

			Transform* needleeffect2_tr = needleeffect2->GetComponent<Transform>();

			Transform* needleeffect_getobject2_tr = GetOwner()->GetComponent<Transform>(); // �̰� �ҹ貨 
			Transform* player2_tr = mGameObject->GetComponent<Transform>(); // �̰� �÷��̾

			Vector3 tr = needleeffect_getobject2_tr->GetPosition(); // �ҹ貨

			Vector3 tr2 = player2_tr->GetPosition(); // �÷��̾
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
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // �Ⱦ�
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect2_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 8, 0.1f);
			needleeffect2_Ani->Create(L"needle_idle2", needle_idle, Vector2(0.0f, 123.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 3, 23, 0.1f);
			needleeffect2_Ani->Create(L"needle_die2", needle_die2, Vector2(0.0f, 0.0f), Vector2(76.0f, 70.0f), Vector2(0.0f, -0.0f), 5, 5, 25, 0.10f);
			needleeffect2_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);

			needleeffect2_Ani->Play(L"needle_idle", false); //���� �ȵ���


			SpriteRenderer* needleeffect2_sr = needleeffect2->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect2_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect2_sr->SetMaterial(needleeffect2_mateiral);
			std::shared_ptr<Mesh> needleeffect2_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect2_sr->SetMesh(needleeffect2_mesh);

			Needle_Sc_FX* sc2_fx = needleeffect2->AddComponent<Needle_Sc_FX>();
			sc2_fx->setmGameObject(mGameObject);

		}

		{
			Monster* needleeffect2 = object::Instantiate<Monster>(eLayerType::Skill_Effect);
			needleeffect2->SetName(L"GrandPa_Needle_04");

			Transform* needleeffect2_tr = needleeffect2->GetComponent<Transform>();

			Transform* needleeffect_getobject2_tr = GetOwner()->GetComponent<Transform>(); // �̰� �ҹ貨 
			Transform* player2_tr = mGameObject->GetComponent<Transform>(); // �̰� �÷��̾

			Vector3 tr = needleeffect_getobject2_tr->GetPosition(); // �ҹ貨

			Vector3 tr2 = player2_tr->GetPosition(); // �÷��̾
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
			std::shared_ptr<Texture> needle_die2 = Resources::Load<Texture>(L"needle_die2", L"GrandPa\\T_BossMoon_RayHit.png"); // �Ⱦ�
			std::shared_ptr<Texture> needle_die = Resources::Load<Texture>(L"needle_die", L"GrandPa\\T_BossMoon_AoeExplosion.png");

			needleeffect2_Ani->Create(L"needle_idle", needle_idle, Vector2(0.0f, 0.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 4, 8, 0.1f);
			needleeffect2_Ani->Create(L"needle_idle2", needle_idle, Vector2(0.0f, 123.0f), Vector2(123.0f, 123.0f), Vector2(0.0f, -0.0f), 8, 3, 23, 0.1f);
			needleeffect2_Ani->Create(L"needle_die2", needle_die2, Vector2(0.0f, 0.0f), Vector2(76.0f, 70.0f), Vector2(0.0f, -0.0f), 5, 5, 25, 0.10f);
			needleeffect2_Ani->Create(L"needle_die", needle_die, Vector2(0.0f, 0.0f), Vector2(452.0f, 450.0f), Vector2(0.0f, -0.0f), 4, 3, 10, 0.10f);

			needleeffect2_Ani->Play(L"needle_idle", false); //���� �ȵ���


			SpriteRenderer* needleeffect2_sr = needleeffect2->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> needleeffect2_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			needleeffect2_sr->SetMaterial(needleeffect2_mateiral);
			std::shared_ptr<Mesh> needleeffect2_mesh = Resources::Find<Mesh>(L"RectMesh");
			needleeffect2_sr->SetMesh(needleeffect2_mesh);

			Needle_Sc_FX* sc2_fx = needleeffect2->AddComponent<Needle_Sc_FX>();
			sc2_fx->setmGameObject(mGameObject);

		}

	}
}