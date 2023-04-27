#include "yaBossWandaScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"

namespace ya {
	BossWandaScript::BossWandaScript()
		: Script()
		, mState(eState::Idle)
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

		//���̵� �����϶�
		if (mState == eState::Idle)
		{

		}

		//�����̴� ����
		if (mState == eState::Move)
		{

		}

		//�Ϲ� ��Ÿ ����
		if (mState == eState::Atack)
		{

		}

		//��ų ����
		if (mState == eState::Skill)
		{

		}
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
}