#include "yaWanda_Dmg_UP_Sc_Fx.h"
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
	Wanda_Dmg_UP_Sc_Fx::Wanda_Dmg_UP_Sc_Fx()
		: Script()
	{
	}
	Wanda_Dmg_UP_Sc_Fx::~Wanda_Dmg_UP_Sc_Fx()
	{
	}
	void Wanda_Dmg_UP_Sc_Fx::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_dmg") = std::bind(&Wanda_Dmg_UP_Sc_Fx::Start, this);

	}
	void Wanda_Dmg_UP_Sc_Fx::Update()
	{
	}
	void Wanda_Dmg_UP_Sc_Fx::FixedUpdate()
	{
	}
	void Wanda_Dmg_UP_Sc_Fx::Render()
	{
	}
	void Wanda_Dmg_UP_Sc_Fx::OnCollisionEnter(Collider2D* collider)
	{
		int a = 0;
	}
	void Wanda_Dmg_UP_Sc_Fx::OnCollisionStay(Collider2D* collider)
	{
	}
	void Wanda_Dmg_UP_Sc_Fx::OnCollisionExit(Collider2D* collider)
	{
	}
	void Wanda_Dmg_UP_Sc_Fx::Start()
	{
		Collider2D* wanda_dmg_col = GetOwner()->AddComponent<Collider2D>();
		wanda_dmg_col->SetType(eColliderType::Rect);
		wanda_dmg_col->SetSize(Vector2(0.05f, 0.3f));

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"wanda_dmg2") = std::bind(&Wanda_Dmg_UP_Sc_Fx::End, this);
		animator->Play(L"wanda_dmg2",false);
	}
	void Wanda_Dmg_UP_Sc_Fx::Action()
	{
	}
	void Wanda_Dmg_UP_Sc_Fx::End()
	{
		Collider2D* wanda_dmg_col = GetOwner()->GetComponent<Collider2D>();
		wanda_dmg_col->IsTriiger_True();

		Transform* ownertr = GetOwner()->GetComponent<Transform>();
		Vector3 ow_tr = ownertr->GetPosition();

		ow_tr += (-(100.6f) * ownertr->Up());
		ownertr->SetPosition(ow_tr);
	}
}