#include "yaPlayerScript.h"
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
#include "yaTransform.h"
#include "yaComponent.h"

namespace ya
{
	PlayerScript::PlayerScript()
		: Script()
		, mState(ePlayerState::RIGHT_Idle)
		, Player_Audio_obj{}
		, Player_Audio_Source{}
	{
		
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initalize()
	{
	
		audio[0] = Resources::Load<AudioClip>(L"P_Normal_Attack01", L"Music\\Player\\SFX_Player_Attack01_Sword_01.wav");
		audio[1] = Resources::Load<AudioClip>(L"P_Normal_Attack02", L"Music\\Player\\SFX_Player_Attack01_Sword_02.wav");
		audio[2] = Resources::Load<AudioClip>(L"P_Normal_Attack03", L"Music\\Player\\SFX_Player_Attack01_Sword_03.wav");
		audio[3] = Resources::Load<AudioClip>(L"P_Dash", L"Music\\Player\\SFX_Player_Dash_High_01.wav");
		audio[4] = Resources::Load<AudioClip>(L"P_Hammer_attack01", L"Music\\Player\\00_Player_Special_Hammer_Start_Sword_03.wav");
		audio[5] = Resources::Load<AudioClip>(L"P_Hammer_attack02", L"Music\\Player\\00_Player_Special_Hammer_Swing_Whoosh_01.wav");
		audio[6] = Resources::Load<AudioClip>(L"P_Painwheel_attack01", L"Music\\Player\\00_Player_Special_Painwheel_Attack_Sword_02.wav");
		audio[7] = Resources::Load<AudioClip>(L"P_Painwheel_attack02", L"Music\\Player\\00_Player_Special_Painwheel_Attack_Whoosh_02.wav");
		audio[8] = Resources::Load<AudioClip>(L"P_Spear_attack01", L"Music\\Player\\00_Player_Special_Spear_Attack_Whoosh_02.wav");
		audio[9] = Resources::Load<AudioClip>(L"P_Spear_attack02", L"Music\\Player\\00_Player_Special_Spear_Attack_Magic_02.wav");
		audio[10] = Resources::Load<AudioClip>(L"P_Whirlwind_attack01", L"Music\\Player\\SFX_Player_AttackWhirlwind_01_Sword_01.wav");
		audio[11] = Resources::Load<AudioClip>(L"P_Whirlwind_attack02", L"Music\\Player\\SFX_Player_AttackWhirlwind_02_Sword_01.wav");
		audio[12] = Resources::Load<AudioClip>(L"P_Footstep01", L"Music\\Player\\SFX_EnemyJumper_Footstep_03.wav");
		audio[12]->SetVolume(1.5f);
		audio[13] = Resources::Load<AudioClip>(L"P_Footstep02", L"Music\\Player\\SFX_EnemyJumper_Footstep_04.wav");
		audio[13]->SetVolume(1.5f);


		for (size_t i = 0; i < 100; i++)
		{
			Player_Audio_obj[i] = object::Instantiate<GameObject>(eLayerType::UI);
		}

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetEvent(L"run", 2) = std::bind(&PlayerScript::Footstep01, this);
		animator->GetEvent(L"run", 9) = std::bind(&PlayerScript::Footstep02, this);
	}

	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Collider2D* col = GetOwner()->GetComponent<Collider2D>();

		if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED) //회전
		{
			Vector3 rot = tr->GetRotation();
			rot.z += 5.0f * Time::DeltaTime();
			tr->SetRotation(rot);
		}


		if (Input::GetKeyDown(eKeyCode::RIGHT)) //오른쪽 이동
		{
			animator->Play(L"run",true);
			mState = ePlayerState::RIGHT_Run;
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			animator->Play(L"Idle",true);
			mState = ePlayerState::RIGHT_Idle;

		}
		

		if (Input::GetKeyDown(eKeyCode::LEFT)) //왼쪽 이동
		{
			animator->Play(L"run", true);
			mState = ePlayerState::Left_Run;
		}
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			animator->Play(L"Idle", true);
			mState = ePlayerState::Left_Idle;
		}
		

		if (Input::GetKey(eKeyCode::DOWN)) //아래쪽 이동 안씀
		{
			Vector3 pos = tr->GetPosition();
			//pos.y -= 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}


		if (Input::GetKey(eKeyCode::UP)) //위로 이동 안씀
		{
			Vector3 pos = tr->GetPosition();
			//pos.y += 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}


		//idle 구현부
		if (mState == ePlayerState::RIGHT_Idle)
		{
			
		}
		if (mState == ePlayerState::Left_Idle)
		{
			
		}


		//RIGHT_Run 구현부
		if (mState == ePlayerState::RIGHT_Run)
		{
			Vector3 pos = tr->GetPosition();
			tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			pos.x += 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);

			
			
		}

		//LEFT_Run 구현부
		if (mState == ePlayerState::Left_Run)
		{
			Vector3 pos = tr->GetPosition();
			tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
			pos.x -= 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);

			
		}






		//Player_dash 구현부    
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			Player_Audio_Source[3] = Player_Audio_obj[3]->AddComponent<AudioSource>();
			Player_Audio_Source[3]->SetClip(audio[3]);
			Player_Audio_Source[3]->Play();
			//이동
			Vector3 pos = tr->GetPosition();
			if (mState == ePlayerState::RIGHT_Idle || mState == ePlayerState::RIGHT_Run)
			{
				pos.x += 4.f;
				
			}
			if (mState == ePlayerState::Left_Idle || mState == ePlayerState::Left_Run)
			{
				pos.x -= 4.f;
				
			}

			tr->SetPosition(pos);
				

			//상태창   
			if (mState == ePlayerState::RIGHT_Idle || mState == ePlayerState::Left_Idle)
				animator->GetCompleteEvent(L"dash") = std::bind(&PlayerScript::Player_Idel, this);
			else if (mState == ePlayerState::RIGHT_Run || mState == ePlayerState::Left_Run)
				animator->GetCompleteEvent(L"dash") = std::bind(&PlayerScript::Player_Run_to, this);

			tr->SetScale(Vector3(13.0f, 13.0f, 1.0f));
			animator->GetCompleteEvent(L"dash") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"dash");
		}



		//Player_jump 구현부 //안쓰는중
		if (Input::GetKeyDown(eKeyCode::C)) 
		{
			if(mState == ePlayerState::RIGHT_Idle || mState == ePlayerState::Left_Idle)
				animator->GetCompleteEvent(L"jump") = std::bind(&PlayerScript::Player_Idel, this);
			else if(mState == ePlayerState::RIGHT_Run || mState == ePlayerState::Left_Run)
				animator->GetCompleteEvent(L"jump") = std::bind(&PlayerScript::Player_Run_to, this);

			animator->Play(L"jump");
		}


		//Player_attack 구현부
		if (Input::GetKeyDown(eKeyCode::X))
		{
			Player_Audio_Source[0] = Player_Audio_obj[0]->AddComponent<AudioSource>();
			Player_Audio_Source[0]->SetClip(audio[0]);
			Player_Audio_Source[0]->Play();

			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 24; i++)
			{
				if (mState == ePlayerState::RIGHT_Idle )
				{
					if (i>=1 && i<=4)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
					if (i >= 9 && i <= 12)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
					if (i >= 17 && i <= 20)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
				}
				if (mState == ePlayerState::Left_Idle )
				{
					if (i >= 1 && i <= 4)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
					if (i >= 9 && i <= 12)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
					if (i >= 17 && i <= 20)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
				}
			}
			animator->GetEvent(L"attack",2) = std::bind(&PlayerScript::Normal_Attack_Hit_Check, this);
			animator->GetEvent(L"attack",5) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"attack",10) = std::bind(&PlayerScript::Normal_Attack_Hit_Check, this);
			animator->GetEvent(L"attack",13) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"attack",18) = std::bind(&PlayerScript::Normal_Attack_Hit_Check, this);
			animator->GetEvent(L"attack",21) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"attack", 9) = std::bind(&PlayerScript::attack_suond02, this);
			animator->GetEvent(L"attack", 17) = std::bind(&PlayerScript::attack_suond03, this);
			animator->GetCompleteEvent(L"attack") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"attack");
		}
		
		
		//skill_hammer 구현부
		if (Input::GetKeyDown(eKeyCode::A))
		{
			hammer_sound01();
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 38; i++)
			{
				if (mState == ePlayerState::RIGHT_Idle || mState == ePlayerState::RIGHT_Run) {
					animator->GetEvent(L"skill_hammer", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
				}
				if (mState == ePlayerState::Left_Idle || mState == ePlayerState::Left_Run) {
					animator->GetEvent(L"skill_hammer", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
				}
			}
			animator->GetEvent(L"skill_hammer", 1) = std::bind(&PlayerScript::cameraShakeSmall, this);
			animator->GetEvent(L"skill_hammer", 45) = std::bind(&PlayerScript::cameraShakeBig, this);
			animator->GetEvent(L"skill_hammer", 35) = std::bind(&PlayerScript::hammer_sound02, this);
			animator->GetEvent(L"skill_hammer", 53) = std::bind(&PlayerScript::cameraShakeIdel, this);
			animator->GetEvent(L"skill_hammer", 46) = std::bind(&PlayerScript::Hammer_Attack_Hit_Check, this);
			animator->GetEvent(L"skill_hammer", 52) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetCompleteEvent(L"skill_hammer") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"skill_hammer");
		}
		

		//skill_Painwheel 구현부
		if (Input::GetKeyDown(eKeyCode::S))
		{
			painwheel_sound01();
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 14; i++)
			{
				if (mState == ePlayerState::RIGHT_Idle )
					animator->GetEvent(L"skill_Painwheel", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
				if (mState == ePlayerState::Left_Idle )
					animator->GetEvent(L"skill_Painwheel", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
			}
			animator->GetEvent(L"skill_Painwheel", 1) = std::bind(&PlayerScript::cameraShakeSmall, this);
			animator->GetEvent(L"skill_Painwheel", 16) = std::bind(&PlayerScript::cameraShakeBig, this);
			animator->GetEvent(L"skill_Painwheel", 37) = std::bind(&PlayerScript::painwheel_sound02, this);
			animator->GetEvent(L"skill_Painwheel", 17) = std::bind(&PlayerScript::Painwheel_Attack_Hit_Check, this);
			animator->GetEvent(L"skill_Painwheel", 18) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"skill_Painwheel", 23) = std::bind(&PlayerScript::Painwheel_Attack_Hit_Check, this);
			animator->GetEvent(L"skill_Painwheel", 24) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"skill_Painwheel", 26) = std::bind(&PlayerScript::Painwheel_Attack_Hit_Check, this);
			animator->GetEvent(L"skill_Painwheel", 25) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"skill_Painwheel", 32) = std::bind(&PlayerScript::Painwheel_Attack_Hit_Check, this);
			animator->GetEvent(L"skill_Painwheel", 33) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"skill_Painwheel", 38) = std::bind(&PlayerScript::Painwheel_Attack_Hit_Check, this);
			animator->GetEvent(L"skill_Painwheel", 39) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"skill_Painwheel", 41) = std::bind(&PlayerScript::Painwheel_Attack_Hit_Check, this);
			animator->GetEvent(L"skill_Painwheel", 42) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"skill_Painwheel", 46) = std::bind(&PlayerScript::cameraShakeIdel, this);
			animator->GetCompleteEvent(L"skill_Painwheel") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"skill_Painwheel");
		}

		//skill_Spear 구현부
		if (Input::GetKeyDown(eKeyCode::D))
		{
			Spear_sound01();
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 34; i++)
			{
				if (mState == ePlayerState::RIGHT_Idle )
				{
					if (i < 16)
						animator->GetEvent(L"skill_Spear", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
				}
				if (mState == ePlayerState::Left_Idle )
				{
					if (i < 16)
						animator->GetEvent(L"skill_Spear", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
				}
				
			}
			animator->GetEvent(L"skill_Spear", 17) = std::bind(&PlayerScript::cameraShakeSmall, this);
			animator->GetEvent(L"skill_Spear", 19) = std::bind(&PlayerScript::Spear_sound02, this);
			animator->GetEvent(L"skill_Spear", 21) = std::bind(&PlayerScript::Spear_Attack_Hit_Check, this);
			animator->GetEvent(L"skill_Spear", 25) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"skill_Spear", 28) = std::bind(&PlayerScript::cameraShakeIdel, this);
			animator->GetCompleteEvent(L"skill_Spear") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"skill_Spear");
		}

		//skill_Whirlwind 구현부
		if (Input::GetKeyDown(eKeyCode::F))
		{
			Whirlwind_sound01();
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 31; i++)
			{
				
				if (i == 12)
				{
					//여기서 추가 이펙트 로드및 진행시킴
					animator->GetEvent(L"skill_Whirlwind", i) = std::bind(&PlayerScript::Skill_Whirlwind_Fx, this);
				}
			}
			animator->GetEvent(L"skill_Whirlwind", 9) = std::bind(&PlayerScript::Whirlwind_sound01, this);
			animator->GetEvent(L"skill_Whirlwind", 13) = std::bind(&PlayerScript::cameraShakeSmall, this);
			animator->GetEvent(L"skill_Whirlwind", 14) = std::bind(&PlayerScript::Whirlwind_Attack_Hit_Check, this);
			animator->GetEvent(L"skill_Whirlwind", 16) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"skill_Whirlwind", 18) = std::bind(&PlayerScript::Whirlwind_Attack_Hit_Check, this);
			animator->GetEvent(L"skill_Whirlwind", 20) = std::bind(&PlayerScript::Attack_Hit_Death, this);
			animator->GetEvent(L"skill_Whirlwind", 24) = std::bind(&PlayerScript::cameraShakeIdel, this);
			animator->GetCompleteEvent(L"skill_Whirlwind") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"skill_Whirlwind");
		}
	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
		int a = 0;
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
		int a = 0;
	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
		int a = 0;
	}

	void PlayerScript::Start()
	{
		
	}

	void PlayerScript::Action()
	{
		
	}

	void PlayerScript::End()
	{
		
	}







	void PlayerScript::Normal_Attack_Hit_Check()
	{
		mAttack_Object->SetName(L"Normal_Attack_Hit_Check");

		Transform* mAttack_tr = mAttack_Object->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mAttack_tr->SetPosition(pos);

		Collider2D* mAttack_col = mAttack_Object->AddComponent<Collider2D>();
		mAttack_col->SetType(eColliderType::Rect);
		mAttack_col->SetSize(Vector2(0.3f, 1.0f));

		mAttack_tr->SetPosition(pos += 2.1f * tr->Right());
	}

	void PlayerScript::Hammer_Attack_Hit_Check()
	{
		mAttack_Object->SetName(L"Hammer_Attack_Hit_Check");

		Transform* mAttack_tr = mAttack_Object->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mAttack_tr->SetPosition(pos);

		Collider2D* mAttack_col = mAttack_Object->AddComponent<Collider2D>();
		mAttack_col->SetType(eColliderType::Rect);
		mAttack_col->SetSize(Vector2(1.5f, 0.5f));

		mAttack_tr->SetPosition(pos += 2.3f * tr->Right());

	}

	void PlayerScript::Painwheel_Attack_Hit_Check()
	{
		mAttack_Object->SetName(L"Painwheel_Attack_Hit_Check");

		Transform* mAttack_tr = mAttack_Object->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mAttack_tr->SetPosition(pos);

		Collider2D* mAttack_col = mAttack_Object->AddComponent<Collider2D>();
		mAttack_col->SetType(eColliderType::Rect);
		mAttack_col->SetSize(Vector2(1.3f, 1.3f));

		mAttack_tr->SetPosition(pos += 1.2f * tr->Right());
		mAttack_tr->SetPosition(pos += 0.4f * tr->Up());
	}

	void PlayerScript::Spear_Attack_Hit_Check()
	{
		mAttack_Object->SetName(L"Spear_Attack_Hit_Check");

		Transform* mAttack_tr = mAttack_Object->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mAttack_tr->SetPosition(pos);

		Collider2D* mAttack_col = mAttack_Object->AddComponent<Collider2D>();
		mAttack_col->SetType(eColliderType::Rect);
		mAttack_col->SetSize(Vector2(1.5f, 0.3f));

		mAttack_tr->SetPosition(pos += 2.8f * tr->Right());
		//mAttack_tr->SetPosition(pos += 0.4f * tr->Up());

	}

	void PlayerScript::Whirlwind_Attack_Hit_Check()
	{
		mAttack_Object->SetName(L"Whirlwind_Attack_Hit_Check");

		Transform* mAttack_tr = mAttack_Object->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mAttack_tr->SetPosition(pos);

		Collider2D* mAttack_col = mAttack_Object->AddComponent<Collider2D>();
		mAttack_col->SetType(eColliderType::Rect);
		mAttack_col->SetSize(Vector2(5.5f, 0.1f));

		mAttack_tr->SetPosition(pos += 0.5f * tr->Right());
		//mAttack_tr->SetPosition(pos += 0.4f * tr->Up());
	}

	void PlayerScript::Attack_Hit_Death()
	{
		Transform* mAttack_tr = mAttack_Object->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mAttack_tr->SetPosition(pos += 500.3f * tr->Up());
	}

	void PlayerScript::Player_Idel() //스킬모션이끝나고 idel 애니메이션으로 전환
	{
		cameraShakeIdel();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"Idle");
	}


	void PlayerScript::Player_Run_to()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"run");
	}


	void PlayerScript::Skill_Moving_Right() //스킬 진행중 오른쪽으로 무빙하기
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 0.07f;
		tr->SetPosition(pos);
	}
	void PlayerScript::Skill_Moving_Left() //스킬 진행중 왼쪽으로 무빙하기
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x -= 0.07f;
		tr->SetPosition(pos);
	}

	void PlayerScript::Skill_Whirlwind_Fx() 
	{
		{
			Player* skilleffect = object::Instantiate<Player>(eLayerType::Attack_Object);
			skilleffect->SetName(L"player_skill_effect_01");

			Transform* skilleffct_tr = skilleffect->GetComponent<Transform>();
			Transform* skilleffct_getplayer_tr = GetOwner()->GetComponent<Transform>();
			skilleffct_tr->SetPosition(skilleffct_getplayer_tr->GetPosition());
			if (mState == ePlayerState::Left_Idle)
				skilleffct_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
			if (mState == ePlayerState::RIGHT_Idle)
				skilleffct_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));

			skilleffct_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

			Animator* skilleffct_Ani = skilleffect->AddComponent<Animator>();
			std::shared_ptr<Texture> skill_idle = Resources::Load<Texture>(L"skill01", L"Player\\T_Player_Whirlwind_FX.png");
			skilleffct_Ani->Create(L"skeffect_01", skill_idle, Vector2(0.0f, 0.0f), Vector2(262.0f, 73.0f), Vector2(0.03f, -0.0f), 3, 6, 18, 0.04f);

			skilleffct_Ani->Play(L"skeffect_01", false); //루프 안돌림
			skilleffct_Ani->GetEndEvent(L"skeffect_01") = std::bind(&PlayerScript::End, this);
			//GetEndEvent //위에껀 딱히 필요없음

			SpriteRenderer* skilleffect_sr = skilleffect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> gameplayer_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			skilleffect_sr->SetMaterial(gameplayer_mateiral);
			std::shared_ptr<Mesh> gameplayer_mesh = Resources::Find<Mesh>(L"RectMesh");
			skilleffect_sr->SetMesh(gameplayer_mesh);
			skilleffect->AddComponent<SkillEffectScript>();
			//object::DontDestroyOnLoad(skilleffect);
		}
	}

	void PlayerScript::Skill_Spear_FX() // 잔상 안씀
	{
		{
			Player* skilleffect = object::Instantiate<Player>(eLayerType::Attack_Object);
			skilleffect->SetName(L"player_skill_effect_02");

			Transform* skilleffct_tr = skilleffect->GetComponent<Transform>();
			Transform* skilleffct_getplayer_tr = GetOwner()->GetComponent<Transform>();
			skilleffct_tr->SetPosition(skilleffct_getplayer_tr->GetPosition());
			skilleffct_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

			Animator* skilleffct_Ani = skilleffect->AddComponent<Animator>();
			std::shared_ptr<Texture> skill_idle = Resources::Load<Texture>(L"skill02", L"Player\\T_Player_Spear_FX.png");
			skilleffct_Ani->Create(L"skeffect_02", skill_idle, Vector2(0.0f, 0.0f), Vector2(129.0f, 34.0f), Vector2(0.43f, -0.0f), 2, 4, 7, 0.04f);

			skilleffct_Ani->Play(L"skeffect_02", false); //루프 안돌림
			skilleffct_Ani->GetEndEvent(L"skeffect_02") = std::bind(&PlayerScript::End, this);
			//GetEndEvent //위에껀 딱히 필요없음

			SpriteRenderer* skilleffect_sr = skilleffect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> gameplayer_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			skilleffect_sr->SetMaterial(gameplayer_mateiral);
			std::shared_ptr<Mesh> gameplayer_mesh = Resources::Find<Mesh>(L"RectMesh");
			skilleffect_sr->SetMesh(gameplayer_mesh);
			skilleffect->AddComponent<SkillEffectScript>();
			//object::DontDestroyOnLoad(skilleffect);
		}
	}

	void PlayerScript::cameraShakeSmall()
	{
		mCameraSc->SetCameraState_Small_Shake();

		
		Transform* cam_tr = mGameObject->GetComponent<Transform>();
		Vector3 cam_pos = cam_tr->GetPosition();

		cam_pos += 1.0f * cam_tr->Foward();
		cam_tr->SetPosition(cam_pos);


	}

	void PlayerScript::cameraShakeBig()
	{
		mCameraSc->SetCameraState_Big_Shake();

		Transform* cam_tr = mGameObject->GetComponent<Transform>();

		//Vector3 cam_pos = Vector3((1.0f, 1.0f, 6.0f)); //초기화
		//cam_tr->SetPosition(cam_pos);

		Vector3 cam_pos = cam_tr->GetPosition();
		cam_pos += 1.0f * cam_tr->Foward();
		cam_tr->SetPosition(cam_pos);

	}

	void PlayerScript::cameraShakeIdel()
	{
		mCameraSc->SetCameraState_Idle(); //여기서 갱신중

		
		Transform* cam_tr = mGameObject->GetComponent<Transform>();
		Vector3 cam_pos = Vector3((1.0f, 1.0f, -3.0f));

		cam_tr->SetPosition(cam_pos);
	}

	void PlayerScript::attack_suond02()
	{
		Transform* audio_tr = Player_Audio_obj[1]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[1] = Player_Audio_obj[1]->AddComponent<AudioSource>();
		Player_Audio_Source[1]->SetClip(audio[1]);
		Player_Audio_Source[1]->Play();
	}
	void PlayerScript::attack_suond03()
	{
		Transform* audio_tr = Player_Audio_obj[2]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[2] = Player_Audio_obj[2]->AddComponent<AudioSource>();
		Player_Audio_Source[2]->SetClip(audio[2]);
		Player_Audio_Source[2]->Play();
	}
	void PlayerScript::hammer_sound01()
	{
		Transform* audio_tr = Player_Audio_obj[4]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[4] = Player_Audio_obj[4]->AddComponent<AudioSource>();
		Player_Audio_Source[4]->SetClip(audio[4]);
		Player_Audio_Source[4]->Play();
	}
	void PlayerScript::hammer_sound02()
	{
		Transform* audio_tr = Player_Audio_obj[5]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[5] = Player_Audio_obj[5]->AddComponent<AudioSource>();
		Player_Audio_Source[5]->SetClip(audio[5]);
		Player_Audio_Source[5]->Play();
	}
	void PlayerScript::painwheel_sound01()
	{
		Transform* audio_tr = Player_Audio_obj[6]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[6] = Player_Audio_obj[6]->AddComponent<AudioSource>();
		Player_Audio_Source[6]->SetClip(audio[6]);
		Player_Audio_Source[6]->Play();
	}
	void PlayerScript::painwheel_sound02()
	{
		Transform* audio_tr = Player_Audio_obj[7]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[7] = Player_Audio_obj[7]->AddComponent<AudioSource>();
		Player_Audio_Source[7]->SetClip(audio[7]);
		Player_Audio_Source[7]->Play();
	}
	void PlayerScript::Spear_sound01()
	{
		Transform* audio_tr = Player_Audio_obj[8]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[8] = Player_Audio_obj[8]->AddComponent<AudioSource>();
		Player_Audio_Source[8]->SetClip(audio[8]);
		Player_Audio_Source[8]->Play();
	}
	void PlayerScript::Spear_sound02()
	{
		Transform* audio_tr = Player_Audio_obj[9]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[9] = Player_Audio_obj[9]->AddComponent<AudioSource>();
		Player_Audio_Source[9]->SetClip(audio[9]);
		Player_Audio_Source[9]->Play();
	}
	void PlayerScript::Whirlwind_sound01()
	{
		Transform* audio_tr = Player_Audio_obj[10]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[10] = Player_Audio_obj[10]->AddComponent<AudioSource>();
		Player_Audio_Source[10]->SetClip(audio[10]);
		Player_Audio_Source[10]->Play();
	}
	void PlayerScript::Whirlwind_sound02()
	{
		Transform* audio_tr = Player_Audio_obj[11]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[11] = Player_Audio_obj[11]->AddComponent<AudioSource>();
		Player_Audio_Source[11]->SetClip(audio[11]);
		Player_Audio_Source[11]->Play();
	}
	void PlayerScript::Footstep01()
	{
		Transform* audio_tr = Player_Audio_obj[12]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos += 20.0f * tr->Foward();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[12] = Player_Audio_obj[12]->AddComponent<AudioSource>();
		Player_Audio_Source[12]->SetClip(audio[12]);
		Player_Audio_Source[12]->Play();
	}
	void PlayerScript::Footstep02()
	{
		Transform* audio_tr = Player_Audio_obj[13]->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos += 20.0f * tr->Foward();
		audio_tr->SetPosition(pos);

		Player_Audio_Source[13] = Player_Audio_obj[13]->AddComponent<AudioSource>();
		Player_Audio_Source[13]->SetClip(audio[13]);
		Player_Audio_Source[13]->Play();
	}

}
