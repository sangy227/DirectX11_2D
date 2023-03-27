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
#include "yaSkillEffect.h"
#include "yaSkillEffectScript.h"

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
		/*if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}*/
		

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
		{
			/*GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));*/
		}

		{
			/*GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));*/
			//Light* lightComp = directionalLight->AddComponent<Light>();
			//lightComp->SetType(eLightType::Point);
			//lightComp->SetRadius(10.0f);
			//lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

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
			//하나더 만들어서 레이어 타입 플레이어 뒤쪽에 생성 , 이펙트 cpp하나 만들고 특정 컷 이벤트에 집어넣어서 잔상 만들기
			//이펙트 를 플레이어가 들게만들거나 ,  플레이어를 싱글턴 패턴으로 전역으로 올려서 여기저기 쓰게 만들어서 transfome을 가져오게 하기
			gameplayer = object::Instantiate<Player>(eLayerType::Player);
			gameplayer->SetName(L"GamePlayer");
			Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
			gameplayer_tr->SetPosition(Vector3(1.0f, 1.0f, 3.0f));
			gameplayer_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
			//gameplayer_tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));

			Light* lightComp = gameplayer->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(0.9f, 0.9f, 0.9f, 0.9f));

			//이거왜 Player* transform 못읽을까?
			//Collider2D* gameplayer_col = gameplayer->AddComponent<Collider2D>();
			//gameplayer_col->SetType(eColliderType::Rect);
			

			Animator* gameplayer_animator = gameplayer->AddComponent<Animator>();
			std::shared_ptr<Texture> player_idle = Resources::Load<Texture>(L"player", L"T_BossIrma_Idle_Final.png");
			std::shared_ptr<Texture> player_skill_hammer = Resources::Load<Texture>(L"player_skill_1", L"T_BossIrma_Hammer_Final.png");
			std::shared_ptr<Texture> player_skill_Painwheel = Resources::Load<Texture>(L"player_skill_2", L"T_BossIrma_Painwheel_Final.png");
			std::shared_ptr<Texture> player_skill_Spear = Resources::Load<Texture>(L"player_skill_3", L"T_Player_Spear_Body.png");
			//std::shared_ptr<Texture> player_skill_Spear = Resources::Load<Texture>(L"player_skill_3", L"test.png");
			std::shared_ptr<Texture> player_skill_Whirlwind = Resources::Load<Texture>(L"player_skill_4", L"T_Player_Whirlwind_Body.png");
			
			gameplayer_animator->Create(L"Idle", player_idle, Vector2(0.0f, 0.0f), Vector2(59.0f, 52.0f), Vector2::Zero, 7,4,26, 0.08f);
			gameplayer_animator->Create(L"skill_hammer", player_skill_hammer, Vector2(0.0f, 0.0f), Vector2(275.0f, 119.0f), Vector2(0.03f, -0.015f), 5, 12, 57, 0.04f);
			gameplayer_animator->Create(L"skill_Painwheel", player_skill_Painwheel, Vector2(0.0f, 0.0f), Vector2(190.0f, 85.0f), Vector2(0.03f, -0.015f), 5, 11, 54, 0.04f);
			gameplayer_animator->Create(L"skill_Spear", player_skill_Spear, Vector2(0.0f, 0.0f), Vector2(272.0f, 71.0f), Vector2(0.03f, 0.0f), 4, 9, 34, 0.04f);
			gameplayer_animator->Create(L"skill_Whirlwind", player_skill_Whirlwind, Vector2(0.0f, 0.0f), Vector2(128.0f, 60.0f), Vector2(-0.03f, 0.0f), 4, 8, 31, 0.04f);
			
			
			gameplayer_animator->Play(L"Idle", true);

			
			SpriteRenderer* gameplayer_sr = gameplayer->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> gameplayer_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> gameplayer_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			gameplayer_sr->SetMesh(gameplayer_mesh);
			gameplayer_sr->SetMaterial(gameplayer_mateiral);

			gameplayer->AddComponent<PlayerScript>();
			object::DontDestroyOnLoad(gameplayer);

		}

		//SKILL EFFECT
		/*{
			
			SkillEffect* skilleffect = object::Instantiate<SkillEffect>(eLayerType::Skill_Effect);
			skilleffect->SetName(L"player_skill_effect");

			Light* lightComp = skilleffect->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(0.9f, 0.9f, 0.9f, 0.9f));

			Transform* skilleffct_tr = skilleffect->GetComponent<Transform>();
			Transform* skilleffct_getplayer_tr = gameplayer->GetComponent<Transform>();
			skilleffct_tr->SetPosition(skilleffct_getplayer_tr->GetPosition());
			skilleffct_tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			Animator* skilleffct_Ani = skilleffect->AddComponent<Animator>();
			std::shared_ptr<Texture> skill_idle = Resources::Load<Texture>(L"skill01", L"T_Player_Whirlwind_FX.png");
			skilleffct_Ani->Create(L"skeffect", skill_idle, Vector2(0.0f, 0.0f), Vector2(262.0f, 73.0f), Vector2(0.03f, -0.015f), 3,6,17, 0.04f);

			skilleffct_Ani->Play(L"skeffect", true);


			SpriteRenderer* skilleffect_sr = skilleffect->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> gameplayer_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			skilleffect_sr->SetMaterial(gameplayer_mateiral);
			std::shared_ptr<Mesh> gameplayer_mesh = Resources::Find<Mesh>(L"RectMesh");
			skilleffect_sr->SetMesh(gameplayer_mesh);
			skilleffect->AddComponent<SkillEffectScript>();
			object::DontDestroyOnLoad(skilleffect);

		}*/
		//SMILE RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"SMILE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(5.3f, 1.0f, 3.1f));
			tr->SetScale(Vector3(0.5f, 1.5f, 1.0f));

			
			Light* lightComp = obj->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(5.0f);
			lightComp->SetDiffuse(Vector4(1.0f, 2.0f, 2.0f, 1.0f));

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
