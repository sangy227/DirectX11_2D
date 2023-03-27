#pragma once

namespace ya::enums
{
	enum class eSceneType
	{
		Tilte,
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

		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Camera,
		Mesh,
		Collider,
		//Collider2,
		MeshRenerer,
		SpriteRenderer,
		Light,
		Animator,
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

}