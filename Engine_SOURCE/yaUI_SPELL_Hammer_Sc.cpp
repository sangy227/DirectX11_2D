#include "yaUI_SPELL_Hammer_Sc.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaAnimation.h"
#include "yaTexture.h"
#include "yaAnimator.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAudioClip.h"
#include "yaObject.h"
#include "yaAudioSource.h"
namespace ya {
	//std::shared_ptr<AudioClip> hammer_spell_ready = Resources::Load<AudioClip>(L"Hammer_SpellReady", L"Music\\Player\\SFX_UI_SpellReady_01.wav");

	UI_SPELL_Hammer_Sc::UI_SPELL_Hammer_Sc()
		: Script()
		, mTimer(0.f)
		, check(true)
		, PosX(0)
		, PosY(0)
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
		pos += -PosY * cam_tr->Up();
		pos += -PosX * cam_tr->Right();
		tr->SetPosition(pos);

		if (Input::GetKeyDown(eKeyCode::A))
		{
			check = false;
			//Start();
		}

		if (check == false) 
		{
			mTimer += 1.0 * Time::DeltaTime();

			if (mTimer > 3.0f)
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

		////std::shared_ptr<AudioClip> hammer_spell_ready = Resources::Load<AudioClip>(L"Hammer_SpellReady", L"Music\\Player\\SFX_UI_SpellReady_01.wav");
		//std::shared_ptr<AudioClip> myAudioClip = Resources::Load<AudioClip>(L"BGMmain", L"Moonscars Exterior Music.wav");
		//myAudioClip->SetVolume(1.0f);

		////Audio Object
		//audio_obj = object::Instantiate<GameObject>(eLayerType::UI);
		//Transform* audio_tr = audio_obj->GetComponent<Transform>();
		//Vector3 pos = cameratr->GetPosition();
		//pos += 10 * cameratr->Foward();
		//audio_tr->SetPosition(pos);

		//audio = audio_obj->AddComponent<AudioSource>();
		//audio->SetClip(myAudioClip);
		//audio->Play();
	}
	void UI_SPELL_Hammer_Sc::Action()
	{
	}
	void UI_SPELL_Hammer_Sc::End()
	{
	}
}