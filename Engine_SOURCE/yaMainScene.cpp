#include "yaMainScene.h"
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
#include "yaTime.h"
#include "yaPaintShader.h"
#include "yaParticleSystem.h"
#include "yaBossWandaScript.h"
#include "yaRigidbody.h"
#include "yaMainCameraSc.h"
#include "yaPlayerScMainScene.h"
#include "yaGrandPaScript.h"
#include "yaRedQueenScript.h"
#include "yaSculptorScript.h"

namespace ya {
	MainScene::MainScene()
		: Scene(eSceneType::Main)
	{
		//Ű���� ���
		//ENTER ī�޶� ����� ����
		//UIOJKL ī�޶� �̵�
 	}
	MainScene::~MainScene()
	{
	}
	void MainScene::Initalize()
	{
		Scene::Initalize();
	}
	void MainScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();
	}
	void MainScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void MainScene::Render()
	{
		Scene::Render();
	}
	void MainScene::OnEnter()
	{

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		MainCameraSc* bcs = cameraObj->AddComponent<MainCameraSc>();
		mainCamera = cameraComp;

		Transform* cameratr = cameraObj->GetComponent<Transform>();

		cameratr->SetPosition(Vector3(1.0f, 1.0f, -3.0f));
		



		//MainSceenBG ->���ȭ�� �κ�
		//2���� ���̾�� ����
		{
			{
				//mainBgLeyer01
				GameObject* mainBGObj_01 = object::Instantiate<GameObject>(eLayerType::BackGround);
				mainBGObj_01->SetName(L"MainBG01");
				Transform* mainBGTr_01 = mainBGObj_01->GetComponent<Transform>();
				mainBGTr_01->SetPosition(Vector3(34.0f, 1.0f, 6.0f));
				mainBGTr_01->SetScale(Vector3(85.0f, 10.5f, 1.0f));

				Light* mainBGComp_01 = mainBGObj_01->AddComponent<Light>();
				mainBGComp_01->SetType(eLightType::Directional);
				mainBGComp_01->SetDiffuse(Vector4(0.5f, 0.5f, 0.5f, 1.0f));
				//mainBGComp_01->SetAmbient(Vector4(2.0f, 2.0f, 2.0f, 1.0f));

				SpriteRenderer* mainsr_01 = mainBGObj_01->AddComponent<SpriteRenderer>();
				std::shared_ptr<Mesh> mainmesh_01 = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> mainBGmaterial_01 = Resources::Find<Material>(L"mainBGMaterial01");
				mainsr_01->SetMaterial(mainBGmaterial_01);
				mainsr_01->SetMesh(mainmesh_01);
			}
			{
				//mainBgLeyer02
				GameObject* mainBGObj_02 = object::Instantiate<GameObject>(eLayerType::BackGround);
				mainBGObj_02->SetName(L"PlayBG02");
				Transform* mainBGTr_02 = mainBGObj_02->GetComponent<Transform>();
				mainBGTr_02->SetPosition(Vector3(30.0f, -2.0f, 4.0f));
				mainBGTr_02->SetScale(Vector3(110.0f, 2.55f, 1.0f));

				Light* mainBGComp_02 = mainBGObj_02->AddComponent<Light>();
				mainBGComp_02->SetType(eLightType::Directional);
				mainBGComp_02->SetDiffuse(Vector4(0.5f, 0.5f, 0.5f, 0.0f));

				SpriteRenderer* mainsr_02 = mainBGObj_02->AddComponent<SpriteRenderer>();
				std::shared_ptr<Mesh> mainmesh_02 = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> maintBGmaterial_02 = Resources::Find<Material>(L"mainBGMaterial02");
				mainsr_02->SetMaterial(maintBGmaterial_02);
				mainsr_02->SetMesh(mainmesh_02);
			}
		}



		//Game_Main_Player = �÷��̾�
		{
			gameplayer = object::Instantiate<Player>(eLayerType::Player);
			gameplayer->SetName(L"GamePlayer");
			Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
			gameplayer_tr->SetPosition(Vector3(-5.0f, -1.55f, 5.0f));
			gameplayer_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

			Light* gameplayer_light = gameplayer->AddComponent<Light>();
			gameplayer_light->SetType(eLightType::Directional);
			gameplayer_light->SetDiffuse(Vector4(0.2f, 0.2f, 0.2f, 0.0f));

			Rigidbody* gameplayer_rigid = gameplayer->AddComponent<Rigidbody>();

			//����Ǵ°� Ȯ�οϷ�
			Collider2D* gameplayer_col = gameplayer->AddComponent<Collider2D>();
			gameplayer_col->SetType(eColliderType::Rect);
			gameplayer_col->SetSize(Vector2(0.12f, 0.11f));

#pragma region Animator
			Animator* gameplayer_animator = gameplayer->AddComponent<Animator>();
			std::shared_ptr<Texture> player_idle = Resources::Load<Texture>(L"player", L"Player\\T_BossIrma_Idle_Final.png");
			std::shared_ptr<Texture> player_attack = Resources::Load<Texture>(L"player_attack", L"Player\\T_BossIrma_Attacks.png");
			std::shared_ptr<Texture> player_attack2 = Resources::Load<Texture>(L"player_attack2", L"Player\\T_BossIrma_Attacks2.png"); //��� �÷��̾� ���� �Ⱦ�
			std::shared_ptr<Texture> player_run01 = Resources::Load<Texture>(L"player_run01", L"Player\\T_BossIrma_idle_to_run.png"); // ���̵� �� �� �ε� �Ⱦ�
			std::shared_ptr<Texture> player_run02 = Resources::Load<Texture>(L"player_run02", L"Player\\T_BossIrma_Run_Final.png");
			std::shared_ptr<Texture> player_dash = Resources::Load<Texture>(L"player_Dash", L"Player\\T_BossIrma_Dash.png");
			std::shared_ptr<Texture> player_jump = Resources::Load<Texture>(L"player_jump", L"Player\\T_Player_Jump.png");

			std::shared_ptr<Texture> player_skill_hammer = Resources::Load<Texture>(L"player_skill_1", L"Player\\T_BossIrma_Hammer_Final.png");
			std::shared_ptr<Texture> player_skill_Painwheel = Resources::Load<Texture>(L"player_skill_2", L"Player\\T_BossIrma_Painwheel_Final.png");
			std::shared_ptr<Texture> player_skill_Spear = Resources::Load<Texture>(L"player_skill_3", L"Player\\T_Player_Spear_Body.png");
			std::shared_ptr<Texture> player_skill_Whirlwind = Resources::Load<Texture>(L"player_skill_4", L"Player\\T_Player_Whirlwind_Body.png");


			gameplayer_animator->Create(L"Idle", player_idle, Vector2(0.0f, 0.0f), Vector2(59.0f, 52.0f), Vector2::Zero, 7, 4, 26, 0.08f);
			gameplayer_animator->Create(L"attack", player_attack, Vector2(0.0f, 0.0f), Vector2(166.0f, 54.0f), Vector2(0.03f, 0.0f), 4, 6, 24, 0.04f);
			gameplayer_animator->Create(L"attack2", player_attack2, Vector2(0.0f, 0.0f), Vector2(143.0f, 52.0f), Vector2(0.03f, 0.0f), 5, 5, 25, 0.04f);
			gameplayer_animator->Create(L"run01", player_run01, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(0.03f, 0.0f), 4, 1, 4, 0.05f);
			gameplayer_animator->Create(L"run", player_run02, Vector2(0.0f, 0.0f), Vector2(62.0f, 53.0f), Vector2(0.03f, -0.0f), 5, 3, 14, 0.05f);
			gameplayer_animator->Create(L"dash", player_dash, Vector2(0.0f, 0.0f), Vector2(181.0f, 46.0f), Vector2(-0.18f, -0.0f), 2, 8, 12, 0.05f);
			gameplayer_animator->Create(L"jump", player_jump, Vector2(0.0f, 0.0f), Vector2(60.0f, 57.0f), Vector2(0.00f, 0.0f), 4, 4, 14, 0.05f);

			gameplayer_animator->Create(L"skill_hammer", player_skill_hammer, Vector2(0.0f, 0.0f), Vector2(275.0f, 119.0f), Vector2(0.03f, -0.015f), 5, 12, 57, 0.04f);
			gameplayer_animator->Create(L"skill_Painwheel", player_skill_Painwheel, Vector2(0.0f, 0.0f), Vector2(190.0f, 85.0f), Vector2(0.03f, -0.015f), 5, 11, 54, 0.04f);
			gameplayer_animator->Create(L"skill_Spear", player_skill_Spear, Vector2(0.0f, 0.0f), Vector2(272.0f, 71.0f), Vector2(0.03f, 0.0f), 4, 9, 34, 0.04f);
			gameplayer_animator->Create(L"skill_Whirlwind", player_skill_Whirlwind, Vector2(0.0f, 0.0f), Vector2(128.0f, 60.0f), Vector2(-0.03f, 0.0f), 4, 8, 31, 0.04f);

			gameplayer_animator->Play(L"Idle", true);
#pragma endregion

			SpriteRenderer* gameplayer_sr = gameplayer->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> gameplayer_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> gameplayer_mateiral = Resources::Find<Material>(L"SpriteMaterial");
			gameplayer_sr->SetMesh(gameplayer_mesh);
			gameplayer_sr->SetMaterial(gameplayer_mateiral);


			PlayerScMainScene* camsc = gameplayer->AddComponent<PlayerScMainScene>();
			camsc->setCameraScript(bcs);
			//gameplayer->AddComponent<PlayerScript>();
			//object::DontDestroyOnLoad(gameplayer);

		}



		//�ҹ� ����
		{
			Monster* grandpa_obj = object::Instantiate<Monster>(eLayerType::Monster);
			grandpa_obj->SetName(L"Grandpa");

			Transform* grandpa_tr = grandpa_obj->GetComponent<Transform>();
			grandpa_tr->SetPosition(Vector3(17.5f, -1.0f, 5.0f));
			grandpa_tr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
			{//�÷��̾� tr �����ͼ� ���ͱ��� ���ʿ������� ���� �ٶ󺸰�, �����ʿ� ������ ������ �ٶ󺸰�
				Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
				Vector3 firsttr = grandpa_tr->GetPosition();
				Vector3 secondtr = gameplayer_tr->GetPosition();
				if (firsttr.x - secondtr.x > 0.0f)
					grandpa_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //���� �ٶ󺸱�
				else
					grandpa_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			}

			/*Light* lightComp = wanda_obj->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 0.1f));*/

			Animator* grandpa_Animator = grandpa_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> grandpa_idle = Resources::Load<Texture>(L"grandpa", L"GrandPa\\T_NPC_FirstOne_Idle.png");
			std::shared_ptr<Texture> grandpa_attack = Resources::Load<Texture>(L"grandpa_attack", L"GrandPa\\T_NPC_FirstOne_Heal.png");
			std::shared_ptr<Texture> grandpa_die = Resources::Load<Texture>(L"grandpa_die", L"GrandPa\\T_NPC_FirstOne_Death.png");
			

			grandpa_Animator->Create(L"grandpa_idle", grandpa_idle, Vector2(0.0f, 0.0f), Vector2(36.0f, 69.0f), Vector2(-0.07f,0.05f), 4, 2, 8, 0.13f);
			grandpa_Animator->Create(L"grandpa_attack_1", grandpa_attack, Vector2(0.0f, 0.0f), Vector2(55.0f, 83.0f), Vector2::Zero, 6, 3, 10, 0.13f);
			grandpa_Animator->Create(L"grandpa_attack_2", grandpa_attack, Vector2(165.0f, 83.0f), Vector2(55.0f, 83.0f), Vector2::Zero, 3, 1, 3, 0.13f);
			grandpa_Animator->Create(L"grandpa_attack_3", grandpa_attack, Vector2(0.0f, 166.0f), Vector2(55.0f, 83.0f), Vector2::Zero, 6, 1, 6, 0.13f);
			grandpa_Animator->Create(L"grandpa_die", grandpa_die, Vector2(0.0f, 0.0f), Vector2(86.0f, 69.0f), Vector2(0.055f, 0.015f), 3, 6, 17, 0.15f);


			grandpa_Animator->Play(L"grandpa_idle", true);


			SpriteRenderer* grandpa_sr = grandpa_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> grandpa_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> grandpa_mt = Resources::Find<Material>(L"SpriteMaterial");
			grandpa_sr->SetMesh(grandpa_mesh);
			grandpa_sr->SetMaterial(grandpa_mt);
			GrandPaScript* grandpaSc = grandpa_obj->AddComponent<GrandPaScript>();
			grandpaSc->setmGameObject(gameplayer);
			//object::DontDestroyOnLoad(wanda_obj);
		}


		
		//���� ����
		{
				GameObject* chair_obj = object::Instantiate<GameObject>(eLayerType::BackGround);
				chair_obj->SetName(L"chair");

				Transform* chair_tr = chair_obj->GetComponent<Transform>();
				chair_tr->SetPosition(Vector3(34.0f, -1.0f, 5.01f));
				chair_tr->SetScale(Vector3(1.0f, 2.0f, 1.0f));

				SpriteRenderer* chair_sr = chair_obj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Mesh> chair_mesh = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> chair_material = Resources::Find<Material>(L"chairMaterial");
				chair_sr->SetMaterial(chair_material);
				chair_sr->SetMesh(chair_mesh);
			}

		//���� ���� �ɾ��ִ� ����
		{
				Monster* redqueen_obj = object::Instantiate<Monster>(eLayerType::Monster);
				redqueen_obj->SetName(L"redqueen");

				Transform* redqueen_tr = redqueen_obj->GetComponent<Transform>();
				redqueen_tr->SetPosition(Vector3(34.0f, -1.0f, 5.0f));
				redqueen_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
				{//�÷��̾� tr �����ͼ� ���ͱ��� ���ʿ������� ���� �ٶ󺸰�, �����ʿ� ������ ������ �ٶ󺸰�
					Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
					Vector3 firsttr = redqueen_tr->GetPosition();
					Vector3 secondtr = gameplayer_tr->GetPosition();
					if (firsttr.x - secondtr.x > 0.0f)
						redqueen_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //���� �ٶ󺸱�
					else
						redqueen_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
				}



				Animator* redqueen_Animator = redqueen_obj->AddComponent<Animator>();
				std::shared_ptr<Texture> redqueen_idle = Resources::Load<Texture>(L"redqueen", L"RedQueen\\T_NPC_Yadwiga_Idle.png");



				redqueen_Animator->Create(L"redqueen_idle", redqueen_idle, Vector2(0.0f, 0.0f), Vector2(99.0f, 72.0f), Vector2(0.0f, 0.0f), 5, 11, 55, 0.10f);



				redqueen_Animator->Play(L"redqueen_idle", true);


				SpriteRenderer* redqueen_sr = redqueen_obj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Mesh> redqueen_mesh = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> redqueen_mt = Resources::Find<Material>(L"SpriteMaterial");
				redqueen_sr->SetMesh(redqueen_mesh);
				redqueen_sr->SetMaterial(redqueen_mt);
				RedQueenScript* redqueenSc = redqueen_obj->AddComponent<RedQueenScript>();
				redqueenSc->setmGameObject(gameplayer);
				//object::DontDestroyOnLoad(wanda_obj);
			}

		//���� ���� ���� �����
		{
				Monster* cat_obj = object::Instantiate<Monster>(eLayerType::Monster);
				cat_obj->SetName(L"cat");

				Transform* cat_tr = cat_obj->GetComponent<Transform>();
				cat_tr->SetPosition(Vector3(36.f, -1.7f, 5.0f));
				cat_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
				{//�÷��̾� tr �����ͼ� ���ͱ��� ���ʿ������� ���� �ٶ󺸰�, �����ʿ� ������ ������ �ٶ󺸰�
					Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
					Vector3 firsttr = cat_tr->GetPosition();
					Vector3 secondtr = gameplayer_tr->GetPosition();
					if (firsttr.x - secondtr.x > 0.0f)
						cat_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //���� �ٶ󺸱�
					else
						cat_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
				}

				Animator* cat_Animator = cat_obj->AddComponent<Animator>();
				std::shared_ptr<Texture> cat_idle = Resources::Load<Texture>(L"cat", L"npc_etalag_idle.png");

				cat_Animator->Create(L"cat_idle", cat_idle, Vector2(0.0f, 0.0f), Vector2(97.f, 43.f), Vector2(0.0f, 0.0f), 5, 6, 23, 0.10f);

				cat_Animator->Play(L"cat_idle", true);


				SpriteRenderer* cat_sr = cat_obj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Mesh> cat_mesh = Resources::Find<Mesh>(L"RectMesh");
				std::shared_ptr<Material> cat_mt = Resources::Find<Material>(L"SpriteMaterial");
				cat_sr->SetMesh(cat_mesh);
				cat_sr->SetMaterial(cat_mt);
			}
		

		//���ƴٴϴ� �ҹ�
		{
			Monster* sculptor_obj = object::Instantiate<Monster>(eLayerType::Monster);
			sculptor_obj->SetName(L"sculptor");

			Transform* sculptor_tr = sculptor_obj->GetComponent<Transform>();
			sculptor_tr->SetPosition(Vector3(52.0f, -0.7f, 5.0f));
			sculptor_tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
			{//�÷��̾� tr �����ͼ� ���ͱ��� ���ʿ������� ���� �ٶ󺸰�, �����ʿ� ������ ������ �ٶ󺸰�
				Transform* gameplayer_tr = gameplayer->GetComponent<Transform>();
				Vector3 firsttr = sculptor_tr->GetPosition();
				Vector3 secondtr = gameplayer_tr->GetPosition();
				if (firsttr.x - secondtr.x > 0.0f)
					sculptor_tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f)); //���� �ٶ󺸱�
				else
					sculptor_tr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			}



			Animator* sculptor_Animator = sculptor_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> sculptor_idle = Resources::Load<Texture>(L"sculptor", L"BossSculptor\\T_BossSculptor_Idle.png");
			std::shared_ptr<Texture> sculptor_attack = Resources::Load<Texture>(L"sculptor_attack", L"BossSculptor\\T_BossSculptor_Cast.png");
			std::shared_ptr<Texture> sculptor_die = Resources::Load<Texture>(L"sculptor_die", L"BossSculptor\\T_BossSculptor_DeathBody.png");


			sculptor_Animator->Create(L"sculptor_idle", sculptor_idle, Vector2(0.0f, 0.0f), Vector2(194.0f, 139.0f), Vector2(0.0f, 0.0f), 3, 4, 12, 0.12f);
			sculptor_Animator->Create(L"sculptor_attack", sculptor_attack, Vector2(0.0f, 0.0f), Vector2(202.0f, 189.0f), Vector2(0.0f, 0.0f), 3, 5, 13, 0.12f);
			sculptor_Animator->Create(L"sculptor_die", sculptor_die, Vector2(0.0f, 0.0f), Vector2(102.0f, 135.0f), Vector2(0.0f, 0.0f), 7, 5, 35, 0.10f);


			sculptor_Animator->Play(L"sculptor_idle", true);


			SpriteRenderer* sculptor_sr = sculptor_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> sculptor_mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> sculptor_mt = Resources::Find<Material>(L"SpriteMaterial");
			sculptor_sr->SetMesh(sculptor_mesh);
			sculptor_sr->SetMaterial(sculptor_mt);
			SculptorScript* SculptorSc = sculptor_obj->AddComponent<SculptorScript>(); 
			SculptorSc->setmGameObject(gameplayer);
			
		}

	}
	void MainScene::OnExit()
	{
	}
}
