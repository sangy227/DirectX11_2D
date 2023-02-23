#pragma once
#include "yaComponent.h"

namespace ya
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		//std::vector<Script*> mScripts;
		//state jump;
		//state Attack;
	};
}
