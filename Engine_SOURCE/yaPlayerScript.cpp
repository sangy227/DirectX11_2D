#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"

namespace ya
{
	PlayerScript::PlayerScript()
		: Script()
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

		if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		{
			Vector3 rot = tr->GetRotation();
			rot.z += 10.0f * Time::DeltaTime();
			tr->SetRotation(rot);
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			Vector3 pos = tr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			Vector3 pos = tr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			Vector3 pos = tr->GetPosition();
			pos.y -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::UP))
		{
			Vector3 pos = tr->GetPosition();
			pos.y += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		
		//skill_hammer ������
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			for (size_t i = 1; i < 38; i++)
			{
				animator->GetEvent(L"skill_hammer", i) = std::bind(&PlayerScript::Skill_Moving_Right, this);
			}
			animator->GetCompleteEvent(L"skill_hammer") = std::bind(&PlayerScript::Player_Idel, this);
			animator->Play(L"skill_hammer");
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





	void PlayerScript::Player_Idel() //��ų����̳����� idel �ִϸ��̼����� ��ȯ
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"Idle");
	}
	void PlayerScript::Skill_Moving_Right() //��ų ������ ���������� �����ϱ�
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 0.05f;
		tr->SetPosition(pos);
	}
	void PlayerScript::Skill_Moving_Left() //��ų ������ �������� �����ϱ�
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x -= 0.05f;
		tr->SetPosition(pos);
	}

}
