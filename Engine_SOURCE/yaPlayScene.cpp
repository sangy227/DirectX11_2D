#include "yaPlayScene.h"
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

namespace ya
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
	{
		
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initalize()
	{
		
		
		int a = 0;



		Scene::Initalize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}
		

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;


		//Game_Main_Player
		{
			Player* gameplayer = object::Instantiate<Player>(eLayerType::Player);
			gameplayer->SetName(L"GamePlayer");
			Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
			gameplayer_tr->SetPosition(Vector3(1.0f, 1.0f, 3.0f));
			gameplayer_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
			//gameplayer_tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));

			//이거왜 Player* transform 못읽을까?
			//Collider2D* gameplayer_col = gameplayer->AddComponent<Collider2D>();
			//gameplayer_col->SetType(eColliderType::Rect);
			

			Animator* gameplayer_animator = gameplayer->AddComponent<Animator>();
			std::shared_ptr<Texture> player_idle = Resources::Load<Texture>(L"player", L"T_BossIrma_Idle_Final.png");
			std::shared_ptr<Texture> player_skill_hammer = Resources::Load<Texture>(L"player_skill_1", L"T_BossIrma_Hammer_Final.png");
			std::shared_ptr<Texture> player_skill_Painwheel = Resources::Load<Texture>(L"player_skill_2", L"T_BossIrma_Painwheel_Final.png");

			gameplayer_animator->Create(L"Idle", player_idle, Vector2(0.0f, 0.0f), Vector2(59.0f, 52.0f), Vector2::Zero, 7,4,26, 0.08f);
			gameplayer_animator->Create(L"skill_hammer", player_skill_hammer, Vector2(0.0f, 0.0f), Vector2(275.0f, 119.0f), Vector2(0.03f, -0.015f), 5, 12, 57, 0.035f);
			gameplayer_animator->Create(L"skill_Painwheel", player_skill_Painwheel, Vector2(0.0f, 0.0f), Vector2(190.0f, 85.0f), Vector2(0.03f, -0.015f), 5, 11, 54, 0.035f);
																														
			gameplayer_animator->Play(L"Idle", true);


			SpriteRenderer* gameplayer_sr = gameplayer->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> gameplayer_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			gameplayer_sr->SetMaterial(gameplayer_mateiral);
			std::shared_ptr<Mesh> gameplayer_mesh = Resources::Find<Mesh>(L"RectMesh");
			gameplayer_sr->SetMesh(gameplayer_mesh);

			gameplayer->AddComponent<PlayerScript>();
			object::DontDestroyOnLoad(gameplayer);

		
		}

		//SMILE RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"SMILE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.3f, 1.0f, 3.0f));
			


			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			object::DontDestroyOnLoad(obj);
		}
		
	}

	void PlayScene::OnExit()
	{

	}

}
