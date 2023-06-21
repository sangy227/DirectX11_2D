#include "yaUI_SPELL_Hammer_Sc.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaAnimation.h"
#include "yaTexture.h"
#include "yaAnimator.h"
#include "yaInput.h"
#include "yaTime.h"

namespace ya {
	UI_SPELL_Hammer_Sc::UI_SPELL_Hammer_Sc()
		: Script()
		, mTimer(0.f)
		, check(true)
	{
	}
	UI_SPELL_Hammer_Sc::~UI_SPELL_Hammer_Sc()
	{
	}
	void UI_SPELL_Hammer_Sc::Initalize()
	{
	}
	void UI_SPELL_Hammer_Sc::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Transform* cam_tr = mGameObject->GetComponent<Transform>();
		Vector3 pos = cam_tr->GetPosition();
		pos += 6.8 * cam_tr->Foward();
		pos += -2.4 * cam_tr->Up();
		pos += -6.3 * cam_tr->Right();
		tr->SetPosition(pos);

		if (Input::GetKeyDown(eKeyCode::A))
		{
			check = false;
			//Start();
		}

		if (check == false) 
		{
			mTimer += 1.0 * Time::DeltaTime();

			if (mTimer > 5.0f)
			{
				Start();
				check = true;
				mTimer = 0;
			}
		}

		
	}
	void UI_SPELL_Hammer_Sc::Render()
	{
	}
	void UI_SPELL_Hammer_Sc::OnCollisionEnter(Collider2D* collider)
	{
	}
	void UI_SPELL_Hammer_Sc::OnCollisionStay(Collider2D* collider)
	{
	}
	void UI_SPELL_Hammer_Sc::OnCollisionExit(Collider2D* collider)
	{
	}
	void UI_SPELL_Hammer_Sc::Start()
	{

		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"UI_Spell2",false);
	}
	void UI_SPELL_Hammer_Sc::Action()
	{
	}
	void UI_SPELL_Hammer_Sc::End()
	{
	}
}