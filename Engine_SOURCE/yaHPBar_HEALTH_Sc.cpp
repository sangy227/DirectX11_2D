#include "yaHPBar_HEALTH_Sc.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaAnimation.h"
#include "yaTexture.h"
#include "yaAnimator.h"

namespace ya {
	HPBar_HEALTH_Sc::HPBar_HEALTH_Sc()
		: Script()
	{
	}
	HPBar_HEALTH_Sc::~HPBar_HEALTH_Sc()
	{
	}
	void HPBar_HEALTH_Sc::Initalize()
	{
	}
	void HPBar_HEALTH_Sc::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Transform* cam_tr = mGameObject->GetComponent<Transform>();
		Vector3 pos = cam_tr->GetPosition();
		pos += 6.8 * cam_tr->Foward();
		pos += -3.75 * cam_tr->Up();
		pos += -4.8 * cam_tr->Right();
		tr->SetPosition(pos);

		
	}
	void HPBar_HEALTH_Sc::Render()
	{
	}
	void HPBar_HEALTH_Sc::OnCollisionEnter(Collider2D* collider)
	{
	}
	void HPBar_HEALTH_Sc::OnCollisionStay(Collider2D* collider)
	{
	}
	void HPBar_HEALTH_Sc::OnCollisionExit(Collider2D* collider)
	{
	}
	void HPBar_HEALTH_Sc::Start()
	{
	}
	void HPBar_HEALTH_Sc::Action()
	{
	}
	void HPBar_HEALTH_Sc::End()
	{
	}
}