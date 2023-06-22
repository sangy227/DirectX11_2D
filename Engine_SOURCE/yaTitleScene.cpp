#include "yaTitleScene.h"
#include "yaTransform.h"
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
#include "yaInput.h"
#include "yaCollider2D.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaAnimator.h"
#include "yaPaintShader.h"
#include "yaParticleSystem.h"
#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaAudioSource.h"
namespace ya
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Tilte)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{
		

		
		

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);

		Transform* cameratr = cameraObj->GetComponent<Transform>();
		//cameraComp->RegisterCameraInRenderer();
		//cameraComp->TurnLayerMask(eLayerType::UI, false);
		//cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
		
		//Audio Object
		GameObject* audio_obj = object::Instantiate<GameObject>(eLayerType::UI);
		audio_obj->SetName(L"audio1");

		Transform* audio_tr = audio_obj->GetComponent<Transform>();
		Vector3 pos = cameratr->GetPosition();
		pos += 20 * cameratr->Foward();
		audio_tr->SetPosition(pos);

		audioTitle = audio_obj->AddComponent<AudioSource>();
		std::shared_ptr<AudioClip> TitleOst = Resources::Load<AudioClip>(L"BGM", L"BGM\\SFX_Cutscene_Intro_VO.wav");
		TitleOst->SetVolume(0.5f);
		//std::shared_ptr<AudioClip> myAudioClip =  Resources::Load<AudioClip>(L"DeathSound",L"gull_death.mp3");
		audioTitle->SetClip(TitleOst);
		
		audioTitle->Play();


		//renderer::cameras[0] = cameraComp;

		//TitleSceen
		{
			GameObject* titleBGObj = object::Instantiate<GameObject>(eLayerType::BackGround);
			titleBGObj->SetName(L"TitleBG");
			Transform* titleBGTr = titleBGObj->GetComponent<Transform>();
			titleBGTr->SetPosition(Vector3(0.99f, 1.0f, 1.7f));
			titleBGTr->SetScale(Vector3(1.5f, 0.88f, 1.0f));

			Light* bglightComp = titleBGObj->AddComponent<Light>();
			bglightComp->SetType(eLightType::Directional);
			bglightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

			SpriteRenderer* titlesr = titleBGObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> titleBGmaterial = Resources::Find<Material>(L"TitleBGMaterial");
			titlesr->SetMaterial(titleBGmaterial);
			titlesr->SetMesh(mesh);
		}

		{
			GameObject* titleLogoObj = object::Instantiate<GameObject>(eLayerType::BackGround);
			titleLogoObj->SetName(L"TitleLogo");
			Transform* titleLogoTr = titleLogoObj->GetComponent<Transform>();
			titleLogoTr->SetPosition(Vector3(1.02f, 1.28f, 1.7f));
			titleLogoTr->SetScale(Vector3(0.68f, 0.12f, 1.0f));

			Light* logolightComp = titleLogoObj->AddComponent<Light>();
			logolightComp->SetType(eLightType::Directional);
			logolightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

			SpriteRenderer* logosr = titleLogoObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> logomesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> titleLogomaterial = Resources::Find<Material>(L"TitleLogoMaterial");
			logosr->SetMaterial(titleLogomaterial);
			logosr->SetMesh(logomesh);
		}

		






		

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Main);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
		audioTitle->Stop();
		
	}
}
