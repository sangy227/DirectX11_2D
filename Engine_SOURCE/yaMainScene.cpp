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
#include "yafirstCameraMoveLine_Script.h"
#include "yaevent_Line_Sc.h"
#include "yafirstCameraStopLine_Script.h"
#include "yasecondCameraMoveLine_Script.h"
#include "yaevent_Line2_Sc.h"
#include "yasecondCameraStopLine_Script.h"
#include "yathirdCameraMoveLine_Script.h"
#include "yaevent_Line3_Sc.h"
#include "yathirdCameraStopLine_Script.h"

namespace ya {
	MainScene::MainScene()
		: Scene(eSceneType::Main)
	{
		//Ű���� ���
		//ENTER ī�޶� ����� ����
		//UIOJKL ī�޶� �̵�
		//ER �ҹ� Ű���
		//TY �������ҹ� Ű ���
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
			gameplayer_col->SetSize(Vector2(0.03f, 0.11f));
			gameplayer_col->SetCenter(Vector2(0.2f, 0.0f));

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

			Collider2D* grandpa_col = grandpa_obj->AddComponent<Collider2D>();
			grandpa_col->SetType(eColliderType::Rect);
			grandpa_col->SetSize(Vector2(0.07f, 0.11f));
			grandpa_col->SetCenter(Vector2(0.3f, 0.0f));
			grandpa_col->IsTriiger();


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


				Collider2D* redqueen_col = redqueen_obj->AddComponent<Collider2D>();
				redqueen_col->SetType(eColliderType::Rect);
				redqueen_col->SetSize(Vector2(0.35f, 0.2f));
				redqueen_col->SetCenter(Vector2(0.7f, 0.0f));


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

		//���� ���� ���� ������
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
		
		//���ƴٴϴ� �ҹ� == ����������
		{
			Monster* sculptor_obj = object::Instantiate<Monster>(eLayerType::Monster);
			sculptor_obj->SetName(L"sculptor");

			Transform* sculptor_tr = sculptor_obj->GetComponent<Transform>();
			sculptor_tr->SetPosition(Vector3(51.5f, -0.7f, 5.0f));
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

			Collider2D* sculptor_col = sculptor_obj->AddComponent<Collider2D>();
			sculptor_col->SetType(eColliderType::Rect);
			sculptor_col->SetSize(Vector2(0.1f, 0.25f));
			sculptor_col->SetCenter(Vector2(0.0f, 0.0f));



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

#pragma region �̺�Ʈ �ݶ��̴� ���� ����
		//�̺�Ʈ ���� ��
		GameObject* event_line = object::Instantiate<GameObject>(eLayerType::EventObjectLine);
		event_line->SetName(L"event_Line");

		Transform* event_Line_tr = event_line->GetComponent<Transform>();
		event_Line_tr->SetPosition(Vector3(7.51f, 1.0f, 5.0f));


		Collider2D* event_Line_col = event_line->AddComponent<Collider2D>();
		event_Line_col->SetType(eColliderType::Rect);
		event_Line_col->SetSize(Vector2(0.01f, 7.f));
		event_Line_col->SetCenter(Vector2(0.7f, 0.0f));

		event_Line_Sc* event_line_Sc = event_line->AddComponent<event_Line_Sc>();
		//event_line_Sc->setmGameObject(cameraObj);
		
		//ù��°ī�޶� �����ϱ����� �ݶ��̴�
		GameObject* firstCameraMoveLine = object::Instantiate<GameObject>(eLayerType::EventObjectStart);
		firstCameraMoveLine->SetName(L"firstCameraMoveLine");

		Transform* firstCameraMoveLine_tr = firstCameraMoveLine->GetComponent<Transform>();
		firstCameraMoveLine_tr->SetPosition(Vector3(7.5f, 1.0f, 5.0f));

		Collider2D* firstCameraMoveLine_col = firstCameraMoveLine->AddComponent<Collider2D>();
		firstCameraMoveLine_col->SetType(eColliderType::Rect);
		firstCameraMoveLine_col->SetSize(Vector2(0.005f, 7.0f));
		firstCameraMoveLine_col->SetCenter(Vector2(0.7f, 0.0f));

		firstCameraMoveLine_Script* firstCameraMoveLineSc = firstCameraMoveLine->AddComponent<firstCameraMoveLine_Script>();
		firstCameraMoveLineSc->setmGameObject(cameraObj);


		//ù��°ī�޶� ���߱� ���� �ݶ��̴�
		GameObject* firstCameraStopLine = object::Instantiate<GameObject>(eLayerType::EventObjectStop);
		firstCameraStopLine->SetName(L"firstCameraMoveLine");

		Transform* firstCameraStopLine_tr = firstCameraStopLine->GetComponent<Transform>();
		firstCameraStopLine_tr->SetPosition(Vector3(23.5f, 1.0f, 5.0f));
	
		Collider2D* firstCameraStopLine_col = firstCameraStopLine->AddComponent<Collider2D>();
		firstCameraStopLine_col->SetType(eColliderType::Rect);
		firstCameraStopLine_col->SetSize(Vector2(0.005f, 7.0f));
		firstCameraStopLine_col->SetCenter(Vector2(0.7f, 0.0f));

		firstCameraStopLine_Script* firstCameraStopLineSc = firstCameraStopLine->AddComponent<firstCameraStopLine_Script>();
		firstCameraStopLineSc->SetCamera_Sc(firstCameraMoveLineSc);





		//�ι�° �̺�Ʈ ���� ��
		GameObject* event_line2 = object::Instantiate<GameObject>(eLayerType::EventObjectLine);
		event_line2->SetName(L"event_Line2");

		Transform* event_Line_tr2 = event_line2->GetComponent<Transform>();
		event_Line_tr2->SetPosition(Vector3(23.6f, 1.0f, 5.0f));

		Collider2D* event_Line_col2 = event_line2->AddComponent<Collider2D>();
		event_Line_col2->SetType(eColliderType::Rect);
		event_Line_col2->SetSize(Vector2(0.01f, 7.f));
		event_Line_col2->SetCenter(Vector2(0.7f, 0.0f));

		event_Line2_Sc* event_line_Sc2 = event_line2->AddComponent<event_Line2_Sc>();


		//�ι�°ī�޶� �����ϱ����� �ݶ��̴�
		GameObject* secondCameraMoveLine = object::Instantiate<GameObject>(eLayerType::EventObjectStart);
		secondCameraMoveLine->SetName(L"secondCameraMoveLine");

		Transform* secondCameraMoveLine_tr = secondCameraMoveLine->GetComponent<Transform>();
		secondCameraMoveLine_tr->SetPosition(Vector3(23.7f, 1.0f, 5.0f));

		Collider2D* secondCameraMoveLine_col = secondCameraMoveLine->AddComponent<Collider2D>();
		secondCameraMoveLine_col->SetType(eColliderType::Rect);
		secondCameraMoveLine_col->SetSize(Vector2(0.005f, 7.0f));
		secondCameraMoveLine_col->SetCenter(Vector2(0.7f, 0.0f));

		secondCameraMoveLine_Script* secondCameraMoveLineSc = secondCameraMoveLine->AddComponent<secondCameraMoveLine_Script>();
		secondCameraMoveLineSc->setmGameObject(cameraObj);


		//�ι�°ī�޶� ���߱� ���� �ݶ��̴�
		GameObject* secondCameraStopLine = object::Instantiate<GameObject>(eLayerType::EventObjectStop);
		secondCameraStopLine->SetName(L"secondCameraMoveLine");

		Transform* secondCameraStopLine_tr = secondCameraStopLine->GetComponent<Transform>();
		secondCameraStopLine_tr->SetPosition(Vector3(40.5f, 1.0f, 5.0f));

		Collider2D* secondCameraStopLine_col = secondCameraStopLine->AddComponent<Collider2D>();
		secondCameraStopLine_col->SetType(eColliderType::Rect);
		secondCameraStopLine_col->SetSize(Vector2(0.005f, 7.0f));
		secondCameraStopLine_col->SetCenter(Vector2(0.7f, 0.0f));

		secondCameraStopLine_Script* secondCameraStopLineSc = secondCameraStopLine->AddComponent<secondCameraStopLine_Script>();
		secondCameraStopLineSc->SetCamera_Sc(secondCameraMoveLineSc);
		

		
		//����° �̺�Ʈ ���� ��
		GameObject* event_line3 = object::Instantiate<GameObject>(eLayerType::EventObjectLine);
		event_line3->SetName(L"event_Line3");

		Transform* event_Line_tr3 = event_line3->GetComponent<Transform>();
		event_Line_tr3->SetPosition(Vector3(40.6f, 1.0f, 5.0f));

		Collider2D* event_Line_col3 = event_line3->AddComponent<Collider2D>();
		event_Line_col3->SetType(eColliderType::Rect);
		event_Line_col3->SetSize(Vector2(0.01f, 7.f));
		event_Line_col3->SetCenter(Vector2(0.7f, 0.0f));

		event_Line3_Sc* event_line_Sc3 = event_line3->AddComponent<event_Line3_Sc>();


		//����°ī�޶� �����ϱ����� �ݶ��̴�
		GameObject* thirdCameraMoveLine = object::Instantiate<GameObject>(eLayerType::EventObjectStart);
		thirdCameraMoveLine->SetName(L"thirdCameraMoveLine");

		Transform* thirdCameraMoveLine_tr = thirdCameraMoveLine->GetComponent<Transform>();
		thirdCameraMoveLine_tr->SetPosition(Vector3(40.7f, 1.0f, 5.0f));

		Collider2D* thirdCameraMoveLine_col = thirdCameraMoveLine->AddComponent<Collider2D>();
		thirdCameraMoveLine_col->SetType(eColliderType::Rect);
		thirdCameraMoveLine_col->SetSize(Vector2(0.005f, 7.0f));
		thirdCameraMoveLine_col->SetCenter(Vector2(0.7f, 0.0f));

		thirdCameraMoveLine_Script* thirdCameraMoveLineSc = thirdCameraMoveLine->AddComponent<thirdCameraMoveLine_Script>();
		thirdCameraMoveLineSc->setmGameObject(cameraObj);


		//����°ī�޶� ���߱� ���� �ݶ��̴�
		GameObject* thirdCameraStopLine = object::Instantiate<GameObject>(eLayerType::EventObjectStop);
		thirdCameraStopLine->SetName(L"thirdCameraMoveLine");

		Transform* thirdCameraStopLine_tr = thirdCameraStopLine->GetComponent<Transform>();
		thirdCameraStopLine_tr->SetPosition(Vector3(58.f, 1.0f, 5.0f));

		Collider2D* thirdCameraStopLine_col = thirdCameraStopLine->AddComponent<Collider2D>();
		thirdCameraStopLine_col->SetType(eColliderType::Rect);
		thirdCameraStopLine_col->SetSize(Vector2(0.005f, 7.0f));
		thirdCameraStopLine_col->SetCenter(Vector2(0.7f, 0.0f));

		thirdCameraStopLine_Script* thirdCameraStopLineSc = thirdCameraStopLine->AddComponent<thirdCameraStopLine_Script>();
		thirdCameraStopLineSc->SetCamera_Sc(thirdCameraMoveLineSc);
		
		
		
		
#pragma endregion



		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::EventObjectStart, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::EventObjectLine, true);
		CollisionManager::CollisionLayerCheck(eLayerType::EventObjectStop, eLayerType::EventObjectLine, true);

	}
	void MainScene::OnExit()
	{
		

	}
}