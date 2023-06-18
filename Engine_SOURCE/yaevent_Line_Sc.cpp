#include "yaevent_Line_Sc.h"
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
	event_Line_Sc::event_Line_Sc()
		: Script()
	{
	}
	event_Line_Sc::~event_Line_Sc()
	{
	}
	void event_Line_Sc::Initalize()
	{
	}
	void event_Line_Sc::Update()
	{
		Transform* cameratr = GetOwner()->GetComponent<Transform>();
		Vector3 camerapos = cameratr->GetPosition();

		if (mState == eMainCameraState::MOVE) {
			camerapos += 5.0f * cameratr->Right() * Time::DeltaTime();
			cameratr->SetPosition(camerapos);
		}
	}
	void event_Line_Sc::FixedUpdate()
	{
	}
	void event_Line_Sc::Render()
	{
	}
	void event_Line_Sc::OnCollisionEnter(Collider2D* collider)
	{
		mState = eMainCameraState::MOVE;
		//if (mState == eMainCameraState::MOVE) {
		//	mState = eMainCameraState::STOP;
		//}
	}
	void event_Line_Sc::OnCollisionStay(Collider2D* collider)
	{
	}
	void event_Line_Sc::OnCollisionExit(Collider2D* collider)
	{
		
	}
	void event_Line_Sc::Start()
	{
	}
	void event_Line_Sc::Action()
	{
	}
	void event_Line_Sc::End()
	{
	}
}