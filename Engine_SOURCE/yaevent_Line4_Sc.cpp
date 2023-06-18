#include "yaevent_Line4_Sc.h"
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
#include "yaGameObject.h"


namespace ya {
	yaevent_Line4_Sc::yaevent_Line4_Sc()
		: Script()
	{
	}
	yaevent_Line4_Sc::~yaevent_Line4_Sc()
	{
	}
	void yaevent_Line4_Sc::Initalize()
	{
	}
	void yaevent_Line4_Sc::Update()
	{
		Transform* cameratr = GetOwner()->GetComponent<Transform>();
		Vector3 camerapos = cameratr->GetPosition();

		if (mState == eMainCameraState::MOVE) {
			camerapos += 5.0f * cameratr->Right() * Time::DeltaTime();
			cameratr->SetPosition(camerapos);
		}
	}
	void yaevent_Line4_Sc::FixedUpdate()
	{
	}
	void yaevent_Line4_Sc::Render()
	{
	}
	void yaevent_Line4_Sc::OnCollisionEnter(Collider2D* collider)
	{
		mState = eMainCameraState::MOVE;
	}
	void yaevent_Line4_Sc::OnCollisionStay(Collider2D* collider)
	{
	}
	void yaevent_Line4_Sc::OnCollisionExit(Collider2D* collider)
	{
	}
	void yaevent_Line4_Sc::Start()
	{
	}
	void yaevent_Line4_Sc::Action()
	{
	}
	void yaevent_Line4_Sc::End()
	{
	}
}