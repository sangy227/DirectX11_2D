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
		Skill_Effect,
		EventObjectStart,
		EventObjectLine,
		EventObjectStop,

		Particle,


		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Rigidbody, 
		Camera,
		Mesh,
		Collider,
		//Collider2,
		MeshRenerer,
		SpriteRenderer,
		Light,
		Animator,
		ParticleSystem,
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