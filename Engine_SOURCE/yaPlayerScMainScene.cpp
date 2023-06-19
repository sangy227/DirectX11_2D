#include "yaPlayerScMainScene.h"
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
#include "yaMainCameraSc.h"

namespace ya {
	PlayerScMainScene::PlayerScMainScene()
		: Script()
		, mState(ePlayerState::RIGHT_Idle)
	{
		int a = 0;
	}
	
	PlayerScMainScene::~PlayerScMainScene()
	{
	}
	void PlayerScMainScene::Initalize()
	{
	}
	void PlayerScMainScene::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 rot = tr->GetRotation();
		//rot.z += 10.0f * Time::DeltaTime();
		//tr->SetRotation(rot);
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();




		if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED) //회전
		{
			Vector3 rot = tr->GetRotation();
			rot.z += 5.0f * Time::DeltaTime();
			tr->SetRotation(rot);
		}


		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->Play(L"run", true);
			mState = ePlayerState::RIGHT_Run;
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			animator->Play(L"Idle", true);
			mState = ePlayerState::RIGHT_Idle;

		}


		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->Play(L"run", true);
			mState = ePlayerState::Left_Run;
		}
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			animator->Play(L"Idle", true);
			mState = ePlayerState::Left_Idle;
		}


		if (Input::GetKey(eKeyCode::DOWN))
		{
			Vector3 pos = tr->GetPosition();
			//pos.y -= 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}


		if (Input::GetKey(eKeyCode::UP))
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

		//Player_dash 구현부      //리지드 바디 추가해서 튕겨 나가듯이 만들어야댐
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			for (size_t i = 1; i <= 8; i++)
			{
				{
					//이동
					Vector3 pos = tr->GetPosition();
					if (mState == ePlayerState::RIGHT_Idle || mState == ePlayerState::RIGHT_Run)
						pos.x += 0.4f;
					if (mState == ePlayerState::Left_Idle || mState == ePlayerState::Left_Run)
						pos.x -= 0.4f;
					tr->SetPosition(pos);
				}
			}

			//상태창              //아직 발동이 안댐
			if (mState == ePlayerState::RIGHT_Idle || mState == ePlayerState::Left_Idle)
				animator->GetCompleteEvent(L"dash") = std::bind(&PlayerScMainScene::Player_Idel, this);
			else if (mState == ePlayerState::RIGHT_Run || mState == ePlayerState::Left_Run)
				animator->GetCompleteEvent(L"dash") = std::bind(&PlayerScMainScene::Player_Run_to, this);

			tr->SetScale(Vector3(13.0f, 13.0f, 1.0f));
			animator->GetCompleteEvent(L"dash") = std::bind(&PlayerScMainScene::Player_Idel, this);
			animator->Play(L"dash");
		}


		//Player_jump 구현부
		if (Input::GetKeyDown(eKeyCode::C))
		{
			if (mState == ePlayerState::RIGHT_Idle || mState == ePlayerState::Left_Idle)
				animator->GetCompleteEvent(L"jump") = std::bind(&PlayerScMainScene::Player_Idel, this);
			else if (mState == ePlayerState::RIGHT_Run || mState == ePlayerState::Left_Run)
				animator->GetCompleteEvent(L"jump") = std::bind(&PlayerScMainScene::Player_Run_to, this);

			animator->Play(L"jump");

			//오류 많음 물어보자
		/*	Rigidbody* rigidbody = GetOwner()->AddComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();
			velocity.y = -0.1f;
			rigidbody->SetVelocity(velocity);

			rigidbody->SetGround(false);*/

		}

		//Player_attack 구현부
		if (Input::GetKeyDown(eKeyCode::X))
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 24; i++)
			{
				if (mState == ePlayerState::RIGHT_Idle)
				{
					if (i >= 1 && i <= 4)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScMainScene::Skill_Moving_Right, this);
					if (i >= 9 && i <= 12)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScMainScene::Skill_Moving_Right, this);
					if (i >= 17 && i <= 20)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScMainScene::Skill_Moving_Right, this);
				}
				if (mState == ePlayerState::Left_Idle)
				{
					if (i >= 1 && i <= 4)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScMainScene::Skill_Moving_Left, this);
					if (i >= 9 && i <= 12)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScMainScene::Skill_Moving_Left, this);
					if (i >= 17 && i <= 20)
						animator->GetEvent(L"attack", i) = std::bind(&PlayerScMainScene::Skill_Moving_Left, this);
				}
			}
			animator->GetCompleteEvent(L"attack") = std::bind(&PlayerScMainScene::Player_Idel, this);
			animator->Play(L"attack");
		}


		//skill_hammer 구현부
		if (Input::GetKeyDown(eKeyCode::A))
		{

			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 38; i++)
			{
				if (i == 1)
					cameraShakeSmall();
				if (mState == ePlayerState::RIGHT_Idle) {
					animator->GetEvent(L"skill_hammer", i) = std::bind(&PlayerScMainScene::Skill_Moving_Right, this);
				}
				if (mState == ePlayerState::Left_Idle) {
					animator->GetEvent(L"skill_hammer", i) = std::bind(&PlayerScMainScene::Skill_Moving_Left, this);
				}
			}
			animator->GetCompleteEvent(L"skill_hammer") = std::bind(&PlayerScMainScene::Player_Idel, this);
			animator->Play(L"skill_hammer");
		}


		//skill_Painwheel 구현부
		if (Input::GetKeyDown(eKeyCode::S))
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 14; i++)
			{
				if (mState == ePlayerState::RIGHT_Idle)
					animator->GetEvent(L"skill_Painwheel", i) = std::bind(&PlayerScMainScene::Skill_Moving_Right, this);
				if (mState == ePlayerState::Left_Idle)
					animator->GetEvent(L"skill_Painwheel", i) = std::bind(&PlayerScMainScene::Skill_Moving_Left, this);
			}
			animator->GetCompleteEvent(L"skill_Painwheel") = std::bind(&PlayerScMainScene::Player_Idel, this);
			animator->Play(L"skill_Painwheel");
		}

		//skill_Spear 구현부
		if (Input::GetKeyDown(eKeyCode::D))
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 34; i++)
			{
				if (mState == ePlayerState::RIGHT_Idle)
				{
					if (i < 16)
						animator->GetEvent(L"skill_Spear", i) = std::bind(&PlayerScMainScene::Skill_Moving_Right, this);
				}
				if (mState == ePlayerState::Left_Idle)
				{
					if (i < 16)
						animator->GetEvent(L"skill_Spear", i) = std::bind(&PlayerScMainScene::Skill_Moving_Left, this);
				}
				//if (i == 29)
					//animator->GetEvent(L"skill_Spear", i) = std::bind(&PlayerScMainScene::Skill_Spear_FX, this);
			}
			animator->GetCompleteEvent(L"skill_Spear") = std::bind(&PlayerScMainScene::Player_Idel, this);
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
					animator->GetEvent(L"skill_Whirlwind", i) = std::bind(&PlayerScMainScene::Skill_Whirlwind_Fx, this);
				}
			}
			animator->GetCompleteEvent(L"skill_Whirlwind") = std::bind(&PlayerScMainScene::Player_Idel, this);
			animator->Play(L"skill_Whirlwind");
		}
	
	}
	void PlayerScMainScene::Render()
	{
	}
	void PlayerScMainScene::OnCollisionEnter(Collider2D* collider)
	{
	}
	void PlayerScMainScene::OnCollisionStay(Collider2D* collider)
	{
	}
	void PlayerScMainScene::OnCollisionExit(Collider2D* collider)
	{
	}
	void PlayerScMainScene::Start()
	{
	}
	void PlayerScMainScene::Action()
	{
	}
	void PlayerScMainScene::End()
	{
	}



	void PlayerScMainScene::Player_Idel()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"Idle");
		cameraShakeIdel();
	}
	void PlayerScMainScene::Player_Run_to()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"run");
	}
	void PlayerScMainScene::Skill_Moving_Right()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 0.07f;
		tr->SetPosition(pos);
	}
	void PlayerScMainScene::Skill_Moving_Left()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x -= 0.07f;
		tr->SetPosition(pos);
	}
	void PlayerScMainScene::Skill_Whirlwind_Fx()
	{
		{
			Player* skilleffect = object::Instantiate<Player>(eLayerType::Player);
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
			skilleffct_Ani->GetEndEvent(L"skeffect_01") = std::bind(&PlayerScMainScene::End, this);
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
	void PlayerScMainScene::Skill_Spear_FX()
	{
	}
	void PlayerScMainScene::cameraShakeSmall()
	{
		mMainCameraSc->SetCameraState_Small_Shake();
	}
	void PlayerScMainScene::cameraShakeBig()
	{
		mMainCameraSc->SetCameraState_Big_Shake();
	}
	void PlayerScMainScene::cameraShakeIdel()
	{
		mMainCameraSc->SetCameraState_Idle();
	}
}

	