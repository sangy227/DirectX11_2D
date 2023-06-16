#include "yaSculptorScript.h"
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

namespace ya {
	SculptorScript::SculptorScript()
		: Script()
	{
	}
	SculptorScript::~SculptorScript()
	{
	}
	void SculptorScript::Initalize()
	{
	}
	void SculptorScript::Update()
	{
		Transform* obj_tr = GetOwner()->GetComponent<Transform>();
		Transform* player_tr = mGameObject->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();


	}
	void SculptorScript::FixedUpdate()
	{
	}
	void SculptorScript::Render()
	{
	}


	void SculptorScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void SculptorScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void SculptorScript::OnCollisionExit(Collider2D* collider)
	{
	}


	void SculptorScript::Start()
	{
	}
	void SculptorScript::Action()
	{
	}
	void SculptorScript::End()
	{
	}


	void SculptorScript::Sculptor_IDLE()
	{
	}
	void SculptorScript::Sculptor_ATTACK1()
	{
	}
	void SculptorScript::Sculptor_ATTACK2()
	{
	}
	void SculptorScript::Sculptor_DIE()
	{
	}
}