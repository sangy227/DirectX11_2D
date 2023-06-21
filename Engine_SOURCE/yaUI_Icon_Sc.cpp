#include "yaUI_Icon_Sc.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaAnimation.h"
#include "yaTexture.h"
#include "yaAnimator.h"
#include "yaInput.h"
#include "yaTime.h"

namespace ya {
	UI_Icon_Sc::UI_Icon_Sc()
		: Script()
		, mTimer(0.f)
		, check(true)
		, PosX(0)
		, PosY(0)
	{
	}
	UI_Icon_Sc::~UI_Icon_Sc()
	{
	}
	void UI_Icon_Sc::Initalize()
	{
	}
	void UI_Icon_Sc::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Transform* cam_tr = mGameObject->GetComponent<Transform>();
		Vector3 pos = cam_tr->GetPosition();
		pos += 6.7 * cam_tr->Foward();
		pos += -PosY * cam_tr->Up();
		pos += -PosX * cam_tr->Right();
		tr->SetPosition(pos);
	}
	void UI_Icon_Sc::Render()
	{
	}
	void UI_Icon_Sc::OnCollisionEnter(Collider2D* collider)
	{
	}
	void UI_Icon_Sc::OnCollisionStay(Collider2D* collider)
	{
	}
	void UI_Icon_Sc::OnCollisionExit(Collider2D* collider)
	{
	}
	void UI_Icon_Sc::Start()
	{
	}
	void UI_Icon_Sc::Action()
	{
	}
	void UI_Icon_Sc::End()
	{
	}
}