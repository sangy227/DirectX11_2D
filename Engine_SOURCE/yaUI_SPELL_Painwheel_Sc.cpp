#include "yaUI_SPELL_Painwheel_Sc.h"
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
	UI_SPELL_Painwheel_Sc::UI_SPELL_Painwheel_Sc()
		: Script()
		, mTimer(0.f)
		, check(true)
	{

	}
	UI_SPELL_Painwheel_Sc::~UI_SPELL_Painwheel_Sc()
	{
	}
	void UI_SPELL_Painwheel_Sc::Initalize()
	{
		std::shared_ptr<AudioClip> hammer_spell_ready = Resources::Load<AudioClip>(L"Hammer_SpellReady", L"Music\\Player\\SFX_UI_SpellReady_01.wav");
		hammer_spell_ready->SetVolume(0.5f);

		audio_obj = object::Instantiate<GameObject>(eLayerType::UI);
		audio = audio_obj->AddComponent<AudioSource>();
		audio->SetClip(hammer_spell_ready);
	}
	void UI_SPELL_Painwheel_Sc::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Transform* cam_tr = mGameObject->GetComponent<Transform>();
		Vector3 pos = cam_tr->GetPosition();
		pos += 6.8 * cam_tr->Foward();
		pos += -2.4 * cam_tr->Up();
		pos += -5.3f * cam_tr->Right();
		tr->SetPosition(pos);

		if (Input::GetKeyDown(eKeyCode::S))
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
	void UI_SPELL_Painwheel_Sc::Render()
	{
	}
	void UI_SPELL_Painwheel_Sc::OnCollisionEnter(Collider2D* collider)
	{
	}
	void UI_SPELL_Painwheel_Sc::OnCollisionStay(Collider2D* collider)
	{
	}
	void UI_SPELL_Painwheel_Sc::OnCollisionExit(Collider2D* collider)
	{
	}
	void UI_SPELL_Painwheel_Sc::Start()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"UI_Spell", false);

		//Audio Object
		Transform* audio_tr = audio_obj->GetComponent<Transform>();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		audio_tr->SetPosition(pos);

		audio = audio_obj->GetComponent<AudioSource>();
		audio->Play();
	}
	void UI_SPELL_Painwheel_Sc::Action()
	{
	}
	void UI_SPELL_Painwheel_Sc::End()
	{
	}
}