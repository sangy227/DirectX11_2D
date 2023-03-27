#pragma once

#include "yaGameObject.h"

namespace ya {
	class SkillEffect : public GameObject
	{
	public:
		SkillEffect();
		virtual ~SkillEffect();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}

