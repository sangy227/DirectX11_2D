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

namespace ya
{
	PlayerScript::PlayerScript()
		: Script()
		, mState(eState::RIGHT_Idle)
	{
		int a = 0;
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initalize()
	{
		int a = 0;
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetStartEvent(L"skill_hammer") = std::bind(&PlayerScript::Start, this);
		animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		animator->GetEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
	}

	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 rot = tr->GetRotation();
		//rot.z += 10.0f * Time::DeltaTime();
		//tr->SetRotation(rot);
		Animator* animator = GetOwner()->GetComponent<Animator>();


		if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED) //회전
		{
			Vector3 rot = tr->GetRotation();
			rot.z += 5.0f * Time::DeltaTime();
			tr->SetRotation(rot);
		}


		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->Play(L"run02",true);
			mState = eState::RIGHT_Run;
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			animator->Play(L"Idle",true);
			mState = eState::RIGHT_Idle;

		}
		

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->Play(L"run02", true);
			mState = eState::Left_Run;
		}
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			animator->Play(L"Idle", true);
			mState = eState::Left_Idle;
		}


		if (Input::GetKey(eKeyCode::DOWN))
		{
			Vector3 pos = tr->GetPosition();
			pos.y -= 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}


		if (Input::GetKey(eKeyCode::UP))
		{
			Vector3 pos = tr->GetPosition();
			pos.y += 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}


		//idle 구현부
		if (mState == eState::RIGHT_Idle)
		{
			
		}
		if (mState == eState::Left_Idle)
		{
			
		}


		//RIGHT_Run 구현부
		if (mState == eState::RIGHT_Run)
		{
			Vector3 pos = tr->GetPosition();
			tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			pos.x += 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		//LEFT_Run 구현부
		if (mState == eState::Left_Run)
		{
			Vector3 pos = tr->GetPosition();
			tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
			pos.x -= 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}


		//Player_attack 구현부
		if (Input::GetKeyDown(eKeyCode::X))
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 24; i++)
			{
				if (mState == eState::RIGHT_Idle )
				{
					if (i>=1 && i<=4)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
					if (i >= 9 && i <= 12)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
					if (i >= 17 && i <= 20)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
				}
				if (mState == eState::Left_Idle )
				{
					if (i >= 1 && i <= 4)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
					if (i >= 9 && i <= 12)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
					if (i >= 17 && i <= 20)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
				}
			}
			animator->GetCompleteEvent(L"attack") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"attack");
		}
		
		
		//skill_hammer 구현부
		if (Input::GetKeyDown(eKeyCode::A))
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 38; i++)
			{
				if(mState == eState::RIGHT_Idle )
					animator->GetEvent(L"skill_hammer", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
				if (mState == eState::Left_Idle)
					animator->GetEvent(L"skill_hammer", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
			}
			animator->GetCompleteEvent(L"skill_hammer") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"skill_hammer");
		}
		

		//skill_Painwheel 구현부
		if (Input::GetKeyDown(eKeyCode::S))
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 14; i++)
			{
				if (mState == eState::RIGHT_Idle )
					animator->GetEvent(L"skill_Painwheel", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
				if (mState == eState::Left_Idle )
					animator->GetEvent(L"skill_Painwheel", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
			}
			animator->GetCompleteEvent(L"skill_Painwheel") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"skill_Painwheel");
		}

		//skill_Spear 구현부
		if (Input::GetKeyDown(eKeyCode::D))
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 34; i++)
			{
				if (mState == eState::RIGHT_Idle )
				{
					if (i < 16)
						animator->GetEvent(L"skill_Spear", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
				}
				if (mState == eState::Left_Idle )
				{
					if (i < 16)
						animator->GetEvent(L"skill_Spear", i) = std::bind(&PlayerScript::Skill_Moving_Left, this);
				}
				//if (i == 29)
					//animator->GetEvent(L"skill_Spear", i) = std::bind(&PlayerScript::Skill_Spear_FX, this);
			}
			animator->GetCompleteEvent(L"skill_Spear") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"skill_Spear");
		}

		//skill_Whirlwind 구현부
		if (Input::GetKeyDown(eKeyCode::F))
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 31; i++)
			{
				if (i == 12)
				{
					//여기서 추가 이펙트 로드및 진행시킴
					animator->GetEvent(L"skill_Whirlwind", i) = std::bind(&PlayerScript::Skill_Whirlwind_Fx, this);
				}
			}
			animator->GetCompleteEvent(L"skill_Whirlwind") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"skill_Whirlwind");
		}
	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
		
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
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


	void PlayerScript::Player_Idel() //스킬모션이끝나고 idel 애니메이션으로 전환
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"Idle");
	}


	void PlayerScript::Player_Run_to()
	{
		{
			Player* player_run = object::Instantiate<Player>(eLayerType::Skill_Effect);
			player_run->SetName(L"Player_run_to");

			Transform* player_run_tr = player_run->GetComponent<Transform>();
			Transform* playerRun_getplayer_tr = GetOwner()->GetComponent<Transform>();
			player_run_tr->SetPosition(playerRun_getplayer_tr->GetPosition());
			player_run_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Animator* player_run_Ani = player_run->AddComponent<Animator>();
			std::shared_ptr<Texture> skill_run = Resources::Load<Texture>(L"run", L"Player\\T_BossIrma_Run_Final.png");
			player_run_Ani->Create(L"run", skill_run, Vector2(0.0f, 0.0f), Vector2(62.0f, 53.0f), Vector2(0.03f, -0.0f), 5, 3, 14, 0.04f);

			player_run_Ani->Play(L"run",false); //루프 안돌림
			player_run_Ani->GetEndEvent(L"run") = std::bind(&PlayerScript::End, this);
			//GetEndEvent //위에껀 딱히 필요없음

			SpriteRenderer* player_run_sr = player_run->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> gameplayer_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			player_run_sr->SetMaterial(gameplayer_mateiral);
			std::shared_ptr<Mesh> gameplayer_mesh = Resources::Find<Mesh>(L"RectMesh");
			player_run_sr->SetMesh(gameplayer_mesh);
			player_run->AddComponent<SkillEffectScript>();
			//object::DontDestroyOnLoad(skilleffect);
		}
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
			Player* skilleffect = object::Instantiate<Player>(eLayerType::Skill_Effect);
			skilleffect->SetName(L"player_skill_effect_01");

			Transform* skilleffct_tr = skilleffect->GetComponent<Transform>();
			Transform* skilleffct_getplayer_tr = GetOwner()->GetComponent<Transform>();
			skilleffct_tr->SetPosition(skilleffct_getplayer_tr->GetPosition());
			skilleffct_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

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
			Player* skilleffect = object::Instantiate<Player>(eLayerType::Skill_Effect);
			skilleffect->SetName(L"player_skill_effect_02");

			Transform* skilleffct_tr = skilleffect->GetComponent<Transform>();
			Transform* skilleffct_getplayer_tr = GetOwner()->GetComponent<Transform>();
			skilleffct_tr->SetPosition(skilleffct_getplayer_tr->GetPosition());
			skilleffct_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

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

}
