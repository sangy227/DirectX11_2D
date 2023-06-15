#include "yaBossWandaScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaPlayerScript.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace ya {
	BossWandaScript::BossWandaScript()
		: Script()
		, mState(eState::Idle)
		, Skill_index(0)
	{
	}
	BossWandaScript::~BossWandaScript()
	{
	}


	void BossWandaScript::Initalize()
	{

	}
	void BossWandaScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 rot = tr->GetRotation();
		//rot.z += 10.0f * Time::DeltaTime();
		//tr->SetRotation(rot);
		Animator* animator = GetOwner()->GetComponent<Animator>();


		
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
				Wanda_Skill_Spin();
			if (Skill_index == 1)
				Wanda_Skill_Middle();
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

		if (Input::GetKeyDown(eKeyCode::E)) //여긴 콜라이더 설정
		{
			animator->GetCompleteEvent(L"wanda_s2_npc") = std::bind(&BossWandaScript::Wanda_Idel, this);
			animator->Play(L"wanda_s2_npc");
		}

		//if (Input::GetKeyDown(eKeyCode::R)) // 쓰지 말자 좌표계산하기 빡셈
		//{
		//	animator->GetCompleteEvent(L"wanda_s2_skinshed") = std::bind(&BossWandaScript::Wanda_Idel, this);
		//	animator->Play(L"wanda_s2_skinshed");
		//}
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
	}
	void BossWandaScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BossWandaScript::OnCollisionExit(Collider2D* collider)
	{
	}



	void BossWandaScript::Start()
	{
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

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_spin") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_s2_spin");
	}

	void BossWandaScript::Wanda_Skill_Middle()
	{
		mState = eState::Skill;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_aoe_middle") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_aoe_middle");
	}

	void BossWandaScript::Wanda_Skill_Chain()
	{
		mState = eState::Skill;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_chain") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_chain");
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

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_aoe") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_s2_aoe");
	}

	void BossWandaScript::Wanda_Skill_Garden()
	{
		mState = eState::Skill;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_s2_garden") = std::bind(&BossWandaScript::Wanda_Idel, this);
		animator->Play(L"wanda_s2_garden");
	}
}