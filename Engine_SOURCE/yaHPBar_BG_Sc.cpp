#include "yaHPBar_BG_Sc.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaAnimation.h"
#include "yaTexture.h"
#include "yaAnimator.h"


namespace ya {
	HPBar_BG_Sc::HPBar_BG_Sc()
		: Script()
	{
	}
	HPBar_BG_Sc::~HPBar_BG_Sc()
	{
	}
	void HPBar_BG_Sc::Initalize()
	{
	}
	void HPBar_BG_Sc::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Transform* cam_tr = mGameObject->GetComponent<Transform>();
		Vector3 pos = cam_tr->GetPosition();
		pos += 6.9 * cam_tr->Foward();
		pos += -3.8 * cam_tr->Up();
		pos += -4.9 * cam_tr->Right();
		tr->SetPosition(pos);
	}
	void HPBar_BG_Sc::Render()
	{
	}
	void HPBar_BG_Sc::OnCollisionEnter(Collider2D* collider)
	{
	}
	void HPBar_BG_Sc::OnCollisionStay(Collider2D* collider)
	{
	}
	void HPBar_BG_Sc::OnCollisionExit(Collider2D* collider)
	{
	}
	void HPBar_BG_Sc::Start()
	{
	}
	void HPBar_BG_Sc::Action()
	{
	}
	void HPBar_BG_Sc::End()
	{
	}
}