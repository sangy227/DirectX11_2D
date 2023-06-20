#pragma once

namespace ya::enums
{
	enum class eSceneType
	{
		Tilte,
		Main,
		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		BackGround,
		Grid,
		Monster,
		Player,
		Attack_Object,
		Player_Attack_Object,






		EventObjectStart,
		EventObjectLine,
		EventObjectStop,

		
		EventObjectLine2,
		EventObjectStop2,

		Particle,


		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // ��ġ ������ �����ϴ� ������Ʈ
		Rigidbody, 
		Camera,
		Mesh,
		Collider,
		//Collider2,
		MeshRenerer,
		SpriteRenderer,
		Animator,
		ParticleSystem,
		AudioListener,
		AudioSource,
		Light,
		UI,
		//FadeOut,FadeIn
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		AudioClip,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};

	enum class eCameraState {
		IDLE,
		IDLE_LE,
		SMALL_SHAKE,
		BIG_SHAKE,
		END
	};

	enum class eMainCameraState {
		IDLE,
		MOVE,
		STOP
	};

	enum class ePlayerState
	{
		None,
		RIGHT_Idle,
		Left_Idle,
		RIGHT_Run,
		Left_Run
	};

}