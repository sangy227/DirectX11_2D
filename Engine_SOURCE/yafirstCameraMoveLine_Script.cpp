#include "yafirstCameraMoveLine_Script.h"
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
	firstCameraMoveLine_Script::firstCameraMoveLine_Script()
		: Script()
		, mState(eMainCameraState::IDLE)
	{
	}
	firstCameraMoveLine_Script::~firstCameraMoveLine_Script()
	{
	}


	void firstCameraMoveLine_Script::Initalize()
	{
	}
	void firstCameraMoveLine_Script::Update()
	{
		Transform* cameratr = mGameObject->GetComponent<Transform>();
		Vector3 camerapos = cameratr->GetPosition();

		if (mState == eMainCameraState::MOVE) {
			camerapos += 5.0f * cameratr->Right() * Time::DeltaTime();
			cameratr->SetPosition(camerapos);
		}


		
	}
	void firstCameraMoveLine_Script::FixedUpdate()
	{
	}
	void firstCameraMoveLine_Script::Render()
	{
	}


	void firstCameraMoveLine_Script::OnCollisionEnter(Collider2D* collider)
	{
		mState = eMainCameraState::MOVE;
		//mMainCameraSc->SetMainCameraState_Move();
	}
	void firstCameraMoveLine_Script::OnCollisionStay(Collider2D* collider)
	{
	}
	void firstCameraMoveLine_Script::OnCollisionExit(Collider2D* collider)
	{
	}


	void firstCameraMoveLine_Script::Start()
	{
	}
	void firstCameraMoveLine_Script::Action()
	{
	}
	void firstCameraMoveLine_Script::End()
	{
	}
}