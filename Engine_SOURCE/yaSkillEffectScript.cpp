#include "yaSkillEffectScript.h"
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


namespace ya {
	SkillEffectScript::SkillEffectScript()
		: Script()
	{
	}
	SkillEffectScript::~SkillEffectScript()
	{
	}


	void SkillEffectScript::Initalize()
	{

	}
	void SkillEffectScript::Update()
	{

		Animator* animator = GetOwner()->GetComponent<Animator>();



	}
	void SkillEffectScript::Render()
	{

	}









	void SkillEffectScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void SkillEffectScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void SkillEffectScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void SkillEffectScript::Start()
	{
	}
	void SkillEffectScript::Action()
	{
	}
	void SkillEffectScript::End()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		
	}
}