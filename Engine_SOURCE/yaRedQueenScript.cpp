#include "yaRedQueenScript.h"
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
	RedQueenScript::RedQueenScript()
		: Script()
	{
	}
	RedQueenScript::~RedQueenScript()
	{
	}
	void RedQueenScript::Initalize()
	{
	}
	void RedQueenScript::Update()
	{
		Transform* obj_tr = GetOwner()->GetComponent<Transform>();
		Transform* player_tr = mGameObject->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		{//�÷��̾� tr �����ͼ� ���ͱ��� ���ʿ������� ���� �ٶ󺸰�, �����ʿ� ������ ������ �ٶ󺸰�
			
			Vector3 firsttr = obj_tr->GetPosition();
			Vector3 secondtr = player_tr->GetPosition();
			if (firsttr.x - secondtr.x > 0.0f)
				obj_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //���� �ٶ󺸱�
			else
				obj_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		}




	}
	void RedQueenScript::FixedUpdate()
	{
	}
	void RedQueenScript::Render()
	{
	}







	void RedQueenScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void RedQueenScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void RedQueenScript::OnCollisionExit(Collider2D* collider)
	{
	}




	void RedQueenScript::Start()
	{
	}
	void RedQueenScript::Action()
	{
	}
	void RedQueenScript::End()
	{
	}


	void RedQueenScript::RedQueen_IDLE()
	{
	}
}