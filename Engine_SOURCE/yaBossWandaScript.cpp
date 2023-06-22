#include "yaBossWandaScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
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
#include "yaWanda_Dmg_UP_Sc_Fx.h"
#include "yaWanda_Dmg_Down_Sc_Fx.h"
#include "yaGrandPa_UI_Sc.h"
#include "yaTime.h"

namespace ya {
	BossWandaScript::BossWandaScript()
		: Script()
		, mState(eState::Idle)
		, Skill_index(0)
		, Garden2_index(0)
		, Garden2_bool(true)
		, hit(0)
		, mWanda_Hp(7.8f)
		, Wanda_Audio_obj{}
		, Wanda_Audio_Source{}
		, mTimer(0)
		, mTimer_Trigger(true)
	{
	}
	BossWandaScript::~BossWandaScript()
	{
	}


	void BossWandaScript::Initalize()
	{
		audio[0] = Resources::Load<AudioClip>(L"Wanda_Hurt", L"Music\\UI\\SFX_Player_Hit_Enemy_Squish_01.wav");
		audio[0]->SetVolume(5.0f);
		audio[1] = Resources::Load<AudioClip>(L"Wanda_NPC_To_Idle", L"Music\\Monster\\SFX_BossWanda_s2tonpc_Whoosh_01.wav");
		audio[2] = Resources::Load<AudioClip>(L"Wanda_Spin", L"Music\\Monster\\SFX_BossWanda_S2_Spin_Whoosh_02.wav");
		audio[3] = Resources::Load<AudioClip>(L"Wanda_chain", L"Music\\Monster\\SFX_BossWanda_S1_AOEDouble_Whoosh_03.wav");
		audio[4] = Resources::Load<AudioClip>(L"Wanda_chain_voice", L"Music\\Monster\\SFX_BossWanda_S1_AOEDouble_Voice_02.wav");
		audio[5] = Resources::Load<AudioClip>(L"Wanda_Aoe", L"Music\\Monster\\SFX_BossWanda_S2_AOE_Whoosh_02.wav");
		audio[6] = Resources::Load<AudioClip>(L"Wanda_Aoe_Voice", L"Music\\Monster\\SFX_BossWanda_S1_AOESingle_Voice_02.wav");
		audio[7] = Resources::Load<AudioClip>(L"Wanda_Garden_Intro", L"Music\\Monster\\SFX_BossWanda_S2_Garden_Intro_Whoosh_01.wav");
		audio[8] = Resources::Load<AudioClip>(L"Wanda_Garden_Loop", L"Music\\Monster\\SFX_BossWanda_S2_Garden_Loop.wav");
		audio[9] = Resources::Load<AudioClip>(L"Wanda_Garden_End", L"Music\\Monster\\SFX_BossWanda_S2_Garden_End_Whoosh_01.wav");
		audio[10] = Resources::Load<AudioClip>(L"Wanda_To_NPC", L"Music\\Monster\\SFX_BossWanda_s2tonpc_Whoosh_01.wav");
		audio[11] = Resources::Load<AudioClip>(L"Wanda_To_NPC_Voice", L"Music\\Monster\\SFX_BossWanda_s2tonpc_Voice_01.wav");
		audio[12] = Resources::Load<AudioClip>(L"Wanda_BGM_Intro", L"Music\\Infant Intro To Loop 1 2s.wav");
		audio[13] = Resources::Load<AudioClip>(L"Wanda_BGM", L"Music\\Infant Loop 2.wav");
		audio[13]->SetVolume(0.1f);
		audio[14] = Resources::Load<AudioClip>(L"Wanda_BGM_End", L"Music\\Infant Loop 1 to 2.wav");
		audio[14]->SetVolume(0.1f);
		for (size_t i = 0; i < 100; i++)
		{
			Wanda_Audio_obj[i] = object::Instantiate<GameObject>(eLayerType::UI);
		}
	}
	void BossWandaScript::Update()
	{
		if (mWanda_Hp < 0)
			Death();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 rot = tr->GetRotation();
		//rot.z += 10.0f * Time::DeltaTime();
		//tr->SetRotation(rot);
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();



		//아이들 상태일때
		if (mState == eState::Idle)
		{
			{//플레이어 tr 가져와서 몬스터기준 왼쪽에있으면 왼쪽 바라보고, 오른쪽에 있으면 오른쪽 바라보고
				Transform* wanda_tr = GetOwner()->GetComponent<Transform>();
				Transform* player_tr = mGameObject->GetComponent<Transform>();
				Vector3 firsttr = wanda_tr->GetPosition();
				Vector3 secondtr = player_tr->GetPosition();
				if (firsttr.x - secondtr.x > 0.0f)
					wanda_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //왼쪽 바라보기
				else
					wanda_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f)); //오른쪽바라보기
			}
		}

		//움직이는 상태
		if (mState == eState::Move)
		{

		}

		//일반 평타 공격
		if (mState == eState::Atack)
		{

		}

		//스킬 랜덤 셀렉트
		if (mState == eState::Skill_Selected)
		{
			srand((unsigned int)time(NULL));
			int mRand = rand() % 4;

			Skill_index = mRand;

			mState = eState::Skill_Start;
		}

		//스킬 초이스 부분
		if (mState == eState::Skill_Start)
		{
			if (Skill_index == 0)
				Wanda_Skill_Spin(); //콜라이더 완료
			if (Skill_index == 1)
				Wanda_Skill_Garden(); //콜라이더 완료
			if (Skill_index == 2)
				Wanda_Skill_Chain();
			if (Skill_index == 3)
				Wanda_Skill_Aoe();
		}

		//스킬 진행중 부분
		if (mState == eState::Skill)
		{

		}


		/*{
			wanda_idle x
			wanda_aoe_middle Y
			wanda_chain U
			wanda_s1_s2 I
			wanda_s2_aoe O
			wanda_s2_garden P
			wanda_s2_npc E
			wanda_s2_npc_idle x
			wanda_s2_skinshed R //쓰지말자
			wanda_s2_spin T
		}*/
		if (mTimer_Trigger == false)
		{
			mTimer += 1.0 * Time::DeltaTime();

			if (mTimer > 4.4f)
			{	
				Wanda_Sound_BGM_Main();
				mTimer_Trigger = true;
				mTimer = 0;
			}
		}

		if (Input::GetKeyDown(eKeyCode::E)) //시작 트리거!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
			Start();
			mTimer_Trigger = false;
		
		}

		if (Input::GetKeyDown(eKeyCode::R))
		{
			

		}
		//if (Input::GetKeyDown(eKeyCode::T)) //스킬
		//{
		//	Wanda_Skill_Spin();
		//}
		//if (Input::GetKeyDown(eKeyCode::Y)) //스킬
		//{
		//	Wanda_Skill_Middle();
		//}
		//if (Input::GetKeyDown(eKeyCode::U))//스킬
		//{
		//	Wanda_Skill_Chain();
		//}
		//if (Input::GetKeyDown(eKeyCode::I))
		//{
		//	Wanda_Skill_S2();
		//}
		//if (Input::GetKeyDown(eKeyCode::O))//스킬
		//{
		//	Wanda_Skill_Aoe();
		//}
		//if (Input::GetKeyDown(eKeyCode::P))
		//{
		//	Wanda_Skill_Garden();
		//}


	}
	void BossWandaScript::Render()
	{

	}





	void BossWandaScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetName() == L"GamePlayer")
		{
			int a = 0;
		}

		if (collider->GetOwner()->GetName() == L"Normal_Attack_Hit_Check")
		{
			mWanda_Hp -= 0.15f;
			Wanda_hurt();
		}

		if (collider->GetOwner()->GetName() == L"Hammer_Attack_Hit_Check")
		{
			Wanda_hurt();
			mWanda_Hp -= 1.2f;
		}

		if (collider->GetOwner()->GetName() == L"Painwheel_Attack_Hit_Check")
		{
			mWanda_Hp -= 0.20f;
			Wanda_hurt();
		}

		if (collider->GetOwner()->GetName() == L"Spear_Attack_Hit_Check")
		{
			Wanda_hurt();
			mWanda_Hp -= 0.9f;
		}

		if (collider->GetOwner()->GetName() == L"Whirlwind_Attack_Hit_Check")
		{
			Wanda_hurt();
			mWanda_Hp -= 0.5f;
		}


		if (mWanda_Hp < 0) {
			GrandPa_UI_Sc* Sc = HpBar_Bg_HP_obj->AddComponent<GrandPa_UI_Sc>();
			Sc->setIndex(0);
		}
		else {
			GrandPa_UI_Sc* Sc = HpBar_Bg_HP_obj->AddComponent<GrandPa_UI_Sc>();
			Sc->setIndex(mWanda_Hp);
		}






	}
	void BossWandaScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void BossWandaScript::OnCollisionExit(Collider2D* collider)
	{
		int a = 0;
	}



	void BossWandaScript::Start()
	{
		Wanda_Sound_to_Idle();
		
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"wanda_s2_npc") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->GetEndEvent(L"wanda_s2_npc") = std::bind(&BossWandaScript::Wanda_Sound_BGM_Intro, this);
		animator->GetEvent(L"wanda_s2_npc", 23) = std::bind(&BossWandaScript::CameraFowardDown, this);
		animator->Play(L"wanda_s2_npc");
		CameraFowardUp();

		//UI 보스 피통 BG
		{
			HpBar_Bg_obj = object::Instantiate<GameObject>(eLayerType::UI);
			HpBar_Bg_obj->SetName(L"Hpbar_grandpa");

			Transform* HpBar_Bg_tr = HpBar_Bg_obj->GetComponent<Transform>();
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			pos += 4.7 * tr->Up();
			pos += 1.1 * tr->Foward();

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
			pos += 4.66 * tr->Up();
			pos += 1.1 * tr->Foward();

			HpBar_Bg_tr->SetPosition(pos);
			HpBar_Bg_tr->SetScale(Vector3(7.5f, 0.07f, 0.f));


			GrandPa_UI_Sc* Ui_Sc = HpBar_Bg_HP_obj->AddComponent<GrandPa_UI_Sc>();
			Ui_Sc->setGameObject(GetOwner());
			Ui_Sc->setIndex(mWanda_Hp);
			//Ui_Sc->setdivide(2);
			Ui_Sc->setGrandPaScript(GetOwner()->GetComponent<GrandPaScript>());


			SpriteRenderer* UI_SpellRect_sr = HpBar_Bg_HP_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> UI_SpellRect_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> UI_SpellRect_material = Resources::Find<Material>(L"Bar_Boss_HEALTHMaterial");
			UI_SpellRect_sr->SetMaterial(UI_SpellRect_material);
			UI_SpellRect_sr->SetMesh(UI_SpellRect_mesh);
		}


	}
	void BossWandaScript::Action()
	{
	}
	void BossWandaScript::End()
	{
	}
	void BossWandaScript::Wanda_Idel()
	{
		mState = eState::Idle;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(13.0f, 15.0f, 1.0f));

		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

		col->SetSize(Vector2(0.1f, 0.25f));
		col->SetCenter(Vector2(-0.1f, 0.0f));

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_idle") = std::bind(&BossWandaScript::MState_Change_Skill_Selected, this);
		animator->Play(L"wanda_idle");
	}

	void BossWandaScript::MState_Change_Skill_Selected()
	{
		mState = eState::Skill_Selected;
	}






	void BossWandaScript::Wanda_Skill_Spin()
	{
		mState = eState::Skill;
		Wanda_Sound_Spin();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_spin") = std::bind(&BossWandaScript::Wanda_Skill_Spin2, this);
		animator->Play(L"wanda_s2_spin");
	}

	void BossWandaScript::Wanda_Skill_Spin2()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_spin2") = std::bind(&BossWandaScript::Wanda_Skill_Spin3, this);
		animator->Play(L"wanda_s2_spin2");

		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

		col->SetSize(Vector2(0.6f, 0.25f));



	}

	void BossWandaScript::Wanda_Skill_Spin3()
	{

		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

		col->SetSize(Vector2(0.1f, 0.25f));




		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_spin3") = std::bind(&BossWandaScript::Wanda_Skill_Spin4, this);
		animator->Play(L"wanda_s2_spin3");
	}

	void BossWandaScript::Wanda_Skill_Spin4()
	{
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

		col->SetSize(Vector2(0.6f, 0.25f));

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_spin4") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_s2_spin4");
	}









	void BossWandaScript::Wanda_Skill_Middle()
	{
		mState = eState::Skill;
		Transform* tr = GetOwner()->GetComponent<Transform>();


		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_aoe_middle") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_aoe_middle");
	}







	void BossWandaScript::Wanda_Skill_Chain()
	{
		mState = eState::Skill;
		Wanda_Sound_Chain();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_chain") = std::bind(&BossWandaScript::Wanda_Skill_Chain2, this);
		animator->Play(L"wanda_chain");
	}

	void BossWandaScript::Wanda_Skill_Chain2()
	{
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		Transform* wanda_tr = GetOwner()->GetComponent<Transform>();
		Transform* player_tr = mGameObject->GetComponent<Transform>();
		Vector3 firsttr = wanda_tr->GetPosition();
		Vector3 secondtr = player_tr->GetPosition();
		if (firsttr.x - secondtr.x > 0.0f)
		{
			//왼쪽 일떄
			col->SetCenter(Vector2(-2.5f, 0.0f));
			col->SetSize(Vector2(0.5f, 0.2f));
		}
		else
		{
			//오른쪽 일떄
			col->SetCenter(Vector2(2.5f, 0.0f));
			col->SetSize(Vector2(0.5f, 0.2f));
		}


		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_chain2") = std::bind(&BossWandaScript::Wanda_Skill_Chain3, this);
		animator->Play(L"wanda_chain2");
	}

	void BossWandaScript::Wanda_Skill_Chain3()
	{
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

		col->SetSize(Vector2(0.1f, 0.25f));
		col->SetCenter(Vector2(-0.1f, 0.0f));

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_chain3") = std::bind(&BossWandaScript::Wanda_Skill_Chain4, this);
		animator->Play(L"wanda_chain3");
	}

	void BossWandaScript::Wanda_Skill_Chain4()
	{
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();
		Transform* wanda_tr = GetOwner()->GetComponent<Transform>();
		Transform* player_tr = mGameObject->GetComponent<Transform>();
		Vector3 firsttr = wanda_tr->GetPosition();
		Vector3 secondtr = player_tr->GetPosition();
		if (firsttr.x - secondtr.x > 0.0f)
		{
			//왼쪽 일떄
			col->SetCenter(Vector2(-2.5f, 0.0f));
			col->SetSize(Vector2(0.5f, 0.2f));
			wanda_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
		}
		else
		{
			//오른쪽 일떄
			col->SetCenter(Vector2(2.5f, 0.0f));
			col->SetSize(Vector2(0.5f, 0.2f));
			wanda_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		}


		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_chain4") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_chain4");
	}









	void BossWandaScript::Wanda_Skill_S2()
	{
		mState = eState::Skill;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s1_s2") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_s1_s2");
	}






	void BossWandaScript::Wanda_Skill_Aoe()
	{
		mState = eState::Skill;
		Wanda_Sound_Aoe();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_aoe") = std::bind(&BossWandaScript::Wanda_Skill_Aoe2, this);
		animator->Play(L"wanda_s2_aoe");
	}

	void BossWandaScript::Wanda_Skill_Aoe2()
	{
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

		col->SetSize(Vector2(0.63f, 0.25f));


		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_aoe2") = std::bind(&BossWandaScript::Wanda_Skill_Aoe3, this);
		animator->Play(L"wanda_s2_aoe2");
	}

	void BossWandaScript::Wanda_Skill_Aoe3()
	{
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

		col->SetSize(Vector2(0.1f, 0.25f));

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_aoe3") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_s2_aoe3");
	}





	void BossWandaScript::Wanda_Skill_Garden()
	{
		mState = eState::Skill;
		Wanda_Sound_Garden_Intro();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_garden") = std::bind(&BossWandaScript::Wanda_Skill_Garden2, this);
		animator->Play(L"wanda_s2_garden");
	}
	void BossWandaScript::Wanda_Skill_Garden2()
	{
		Wanda_Sound_Garden_loop();

		if (Garden2_bool) //번갈아가면서 하기
		{
			Garden2_bool = true;
			Wanda_Up_fx();
		}
		else
		{
			Garden2_bool = false;
			Wanda_Down_fx();
		}

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_garden2") = std::bind(&BossWandaScript::Wanda_Skill_Garden2_Again, this);
		animator->Play(L"wanda_s2_garden2");
	}
	void BossWandaScript::Wanda_Skill_Garden2_Again()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (Garden2_bool) //번갈아가면서 하기
		{
			Garden2_bool = false;
			Wanda_Up_fx();
		}
		else
		{
			Garden2_bool = true;
			Wanda_Down_fx();
		}


		Garden2_index++; // 공격모션 얼마나 반복 시키는지
		if (Garden2_index > 6)
		{
			Garden2_index = 0;
			animator->GetCompleteEvent(L"wanda_s2_garden2") = std::bind(&BossWandaScript::Wanda_Skill_Garden3, this);
			animator->Play(L"wanda_s2_garden2");
		}
		else {
			animator->GetCompleteEvent(L"wanda_s2_garden2") = std::bind(&BossWandaScript::Wanda_Skill_Garden2, this);
			animator->Play(L"wanda_s2_garden2");
		}


	}
	void BossWandaScript::Wanda_Skill_Garden3()
	{
		Wanda_Sound_Garden_End();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_garden3") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_s2_garden3");
	}




	void BossWandaScript::Wanda_Up_fx() //T_Boss_Wanda_TentacleDamage
	{

		GameObject* wanda_dmg_obj = object::Instantiate<GameObject>(eLayerType::Attack_Object);
		wanda_dmg_obj->SetName(L"wanda_dmg_obj");

		Transform* wanda_dmg_tr = wanda_dmg_obj->GetComponent<Transform>();
		Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼	
		Vector3 tr = player_tr->GetPosition(); // 플레이어꺼

		tr += 1.6f * player_tr->Up();
		tr += 0.f * player_tr->Right();
		wanda_dmg_tr->SetPosition(tr);
		wanda_dmg_tr->SetScale(Vector3(14.0f, 14.0f, 1.0f));

		//Collider2D* wanda_dmg_col = wanda_dmg_obj->AddComponent<Collider2D>();
		//wanda_dmg_col->SetType(eColliderType::Rect);
		//wanda_dmg_col->SetSize(Vector2(0.05f, 0.3f));


		Animator* wanda_dmg_ani = wanda_dmg_obj->AddComponent<Animator>();
		std::shared_ptr<Texture> wanda_dmg = Resources::Load<Texture>(L"wanda_dmg", L"Boss\\T_Boss_Wanda_TentacleDamage.png");


		wanda_dmg_ani->Create(L"wanda_dmg", wanda_dmg, Vector2(0.0f, 0.0f), Vector2(47.0f, 168.0f), Vector2(0.0f, 0.0f), 4, 4, 8, 0.12f);
		wanda_dmg_ani->Create(L"wanda_dmg2", wanda_dmg, Vector2(0.0f, 336.0f), Vector2(47.0f, 168.0f), Vector2(0.0f, 0.0f), 4, 2, 8, 0.12f);

		wanda_dmg_ani->Play(L"wanda_dmg", false); //루프 안돌림


		SpriteRenderer* SculptorNeedle_sr = wanda_dmg_obj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
		SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
		std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
		SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

		Wanda_Dmg_UP_Sc_Fx* up_sc = wanda_dmg_obj->AddComponent<Wanda_Dmg_UP_Sc_Fx>();


	}



	void BossWandaScript::Wanda_Down_fx() //T_Boss_Wanda_TentacleDamage
	{
		GameObject* wanda_dmg_obj = object::Instantiate<GameObject>(eLayerType::Attack_Object);
		wanda_dmg_obj->SetName(L"wanda_dmg_obj");

		Transform* wanda_dmg_tr = wanda_dmg_obj->GetComponent<Transform>();
		Transform* player_tr = mGameObject->GetComponent<Transform>(); // 이건 플레이어꺼	
		Vector3 tr = player_tr->GetPosition(); // 플레이어꺼

		tr += 1.7f * player_tr->Up();
		tr += 0.f * player_tr->Right();
		wanda_dmg_tr->SetPosition(tr);
		wanda_dmg_tr->SetScale(Vector3(14.0f, 14.0f, 1.0f));
		wanda_dmg_tr->SetRotation(Vector3(180.f, 0.f, 0.f));

		/*Collider2D* wanda_dmg_col = wanda_dmg_obj->AddComponent<Collider2D>();
		wanda_dmg_col->SetType(eColliderType::Rect);
		wanda_dmg_col->SetSize(Vector2(0.05f, 0.3f));*/


		Animator* wanda_dmg_ani = wanda_dmg_obj->AddComponent<Animator>();
		std::shared_ptr<Texture> wanda_dmg = Resources::Load<Texture>(L"wanda_dmg", L"Boss\\T_Boss_Wanda_TentacleDamage.png");


		wanda_dmg_ani->Create(L"wanda_dmg", wanda_dmg, Vector2(0.0f, 0.0f), Vector2(47.0f, 168.0f), Vector2(0.0f, 0.0f), 4, 4, 8, 0.12f);
		wanda_dmg_ani->Create(L"wanda_dmg2", wanda_dmg, Vector2(0.0f, 336.0f), Vector2(47.0f, 168.0f), Vector2(0.0f, 0.0f), 4, 2, 8, 0.12f);

		wanda_dmg_ani->Play(L"wanda_dmg", false); //루프 안돌림


		SpriteRenderer* SculptorNeedle_sr = wanda_dmg_obj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> SculptorNeedle_mateiral = Resources::Find<Material>(L"SpriteMaterial");
		SculptorNeedle_sr->SetMaterial(SculptorNeedle_mateiral);
		std::shared_ptr<Mesh> SculptorNeedle_mesh = Resources::Find<Mesh>(L"RectMesh");
		SculptorNeedle_sr->SetMesh(SculptorNeedle_mesh);

		Wanda_Dmg_Down_Sc_Fx* up_sc = wanda_dmg_obj->AddComponent<Wanda_Dmg_Down_Sc_Fx>();
	}
	void BossWandaScript::CameraFowardUp()
	{
		Transform* cam_tr = mCameraObject->GetComponent<Transform>();


		Vector3 cam_pos = cam_tr->GetPosition();
		cam_pos += 3.0f * cam_tr->Foward();
		cam_tr->SetPosition(cam_pos);
	}
	void BossWandaScript::CameraFowardDown()
	{
		Transform* cam_tr = mCameraObject->GetComponent<Transform>();
		Vector3 cam_pos = cam_tr->GetPosition();

		cam_pos -= 1.5f * cam_tr->Foward();

		cam_tr->SetPosition(cam_pos);
	}
	void BossWandaScript::Death()
	{
		Wanda_Sound_BGM_Main_Stop();
		
		Wanda_Sound_Die();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(13.0f, 13.0f, 1.0f));
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_die") = std::bind(&BossWandaScript::ToDeath, this);
		animator->GetEvent(L"wanda_die",35) = std::bind(&BossWandaScript::Wanda_Sound_BGM_End, this);
		animator->Play(L"wanda_die", false);
		mWanda_Hp = 0.001;
		//wanda_die
	}
	void BossWandaScript::ToDeath()
	{
		//GetOwner()->Death();
		
		HpBar_Bg_obj->Death();

	}
	void BossWandaScript::Wanda_hurt()
	{
		Wanda_Audio_Source[0] = Wanda_Audio_obj[0]->AddComponent<AudioSource>();
		Wanda_Audio_Source[0]->SetClip(audio[0]);
		Wanda_Audio_Source[0]->Play();
	}
	void BossWandaScript::Wanda_Sound_to_Idle()
	{
		Wanda_Audio_Source[1] = Wanda_Audio_obj[1]->AddComponent<AudioSource>();
		Wanda_Audio_Source[1]->SetClip(audio[1]);
		Wanda_Audio_Source[1]->Play();
	}
	void BossWandaScript::Wanda_Sound_Spin()
	{
		Wanda_Audio_Source[2] = Wanda_Audio_obj[2]->AddComponent<AudioSource>();
		Wanda_Audio_Source[2]->SetClip(audio[2]);
		Wanda_Audio_Source[2]->Play();
	}
	void BossWandaScript::Wanda_Sound_Chain()
	{
		Wanda_Audio_Source[3] = Wanda_Audio_obj[3]->AddComponent<AudioSource>();
		Wanda_Audio_Source[3]->SetClip(audio[3]);
		Wanda_Audio_Source[3]->Play();

		Wanda_Audio_Source[4] = Wanda_Audio_obj[4]->AddComponent<AudioSource>();
		Wanda_Audio_Source[4]->SetClip(audio[4]);
		Wanda_Audio_Source[4]->Play();
	}
	void BossWandaScript::Wanda_Sound_Aoe()
	{
		Wanda_Audio_Source[5] = Wanda_Audio_obj[5]->AddComponent<AudioSource>();
		Wanda_Audio_Source[5]->SetClip(audio[5]);
		Wanda_Audio_Source[5]->Play();

		Wanda_Audio_Source[6] = Wanda_Audio_obj[6]->AddComponent<AudioSource>();
		Wanda_Audio_Source[6]->SetClip(audio[6]);
		Wanda_Audio_Source[6]->Play();
	}
	void BossWandaScript::Wanda_Sound_Garden_Intro()
	{
		Wanda_Audio_Source[7] = Wanda_Audio_obj[7]->AddComponent<AudioSource>();
		Wanda_Audio_Source[7]->SetClip(audio[7]);
		Wanda_Audio_Source[7]->Play();
	}
	void BossWandaScript::Wanda_Sound_Garden_loop()
	{
		Wanda_Audio_Source[8] = Wanda_Audio_obj[8]->AddComponent<AudioSource>();
		Wanda_Audio_Source[8]->SetClip(audio[8]);
		Wanda_Audio_Source[8]->Play();
	}
	void BossWandaScript::Wanda_Sound_Garden_End()
	{
		Wanda_Audio_Source[9] = Wanda_Audio_obj[9]->AddComponent<AudioSource>();
		Wanda_Audio_Source[9]->SetClip(audio[9]);
		Wanda_Audio_Source[9]->Play();
	}
	void BossWandaScript::Wanda_Sound_Die()
	{
		Wanda_Audio_Source[10] = Wanda_Audio_obj[10]->AddComponent<AudioSource>();
		Wanda_Audio_Source[10]->SetClip(audio[10]);
		Wanda_Audio_Source[10]->Play();

		Wanda_Audio_Source[11] = Wanda_Audio_obj[11]->AddComponent<AudioSource>();
		Wanda_Audio_Source[11]->SetClip(audio[11]);
		Wanda_Audio_Source[11]->Play();
	}
	void BossWandaScript::Wanda_Sound_BGM_Intro()
	{
		Wanda_Audio_Source[12] = Wanda_Audio_obj[12]->AddComponent<AudioSource>();
		Wanda_Audio_Source[12]->SetClip(audio[12]);
		Wanda_Audio_Source[12]->Play();
	}
	void BossWandaScript::Wanda_Sound_BGM_Main()
	{
		Wanda_Audio_Source[13] = Wanda_Audio_obj[13]->AddComponent<AudioSource>();
		Wanda_Audio_Source[13]->SetClip(audio[13]);
		Wanda_Audio_Source[13]->Play();
	}
	void BossWandaScript::Wanda_Sound_BGM_Main_Stop()
	{
		Wanda_Audio_Source[13] = Wanda_Audio_obj[13]->GetComponent<AudioSource>();
		Wanda_Audio_Source[13]->Stop();
	}
	void BossWandaScript::Wanda_Sound_BGM_End()
	{
		Wanda_Audio_Source[14] = Wanda_Audio_obj[14]->AddComponent<AudioSource>();
		Wanda_Audio_Source[14]->SetClip(audio[14]);
		Wanda_Audio_Source[14]->Play();
	}
}
				   