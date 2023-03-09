#include "yaAnimation.h"
#include "yaTime.h"

namespace ya
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mAtlas(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
		
	}

	Animation::~Animation()
	{
	}

	void Animation::Update()
	{
		if (mbComplete)
			return;

		// 시간 체크
		mTime += Time::DeltaTime();
		
		// 누적 시간이 해당 프레임의 유지시간을 넘어서면 다음프레임으로 이동
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;
			++mIndex;

			//
			if (mSpriteSheet.size() <= mIndex)
			{
				mbComplete = true;
				mIndex = mSpriteSheet.size() - 1;
			}
		}
	}

	void Animation::FixedUpdate()
	{
	}

	void Animation::Render()
	{
	}

	void Animation::Create(const std::wstring& name
		, std::shared_ptr<Texture> atlas
		, Vector2 leftTop, Vector2 size, Vector2 offset
		, UINT columnLegth, UINT spriteLegth, float duration)
	{
	}

	void Animation::BindShader()
	{
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

	void Animation::Clear()
	{
	}

}
