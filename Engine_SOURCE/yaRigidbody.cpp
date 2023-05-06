#include "yaRigidbody.h"
#include "yaTime.h"
#include "yaTransform.h"
#include "yaGameObject.h"

namespace ya {
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(100.0f)
	{
		mLimitVelocity.x = 200.f;
		mLimitVelocity.y = 1000.f;
		mbGround = true;
		mGravity = Vector2(0.0f, 110.0f);
	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Initalize()
	{
	}

	void Rigidbody::Update()
	{

		mAccelation = Vector2(mForce.x / mMass, mForce.y / mMass);

		// 속도에 가속도를 더한다
		mVelocity += Vector2(mAccelation.x * Time::DeltaTime(), mAccelation.y * Time::DeltaTime());

		if (mbGround)
		{
			// 땅위에 있을때
			Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot = (gravity.x * mVelocity.x) + (gravity.y * mVelocity.y);
			mVelocity -= Vector2(gravity.x * dot, gravity.y * dot);
		}
		else
		{
			// 공중에 있을 때
			mVelocity -= Vector2(mGravity.x * Time::DeltaTime(), mGravity.y * Time::DeltaTime());
		}

		// 최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = ((mVelocity.x * gravity.x) + (mVelocity.y * gravity.y));
		gravity *= dot;

		Vector2 sideVelocity = Vector2(mVelocity.x - gravity.x, mVelocity.y - gravity.y);
		if (mLimitVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}

		if (mLimitVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = Vector2(gravity.x + sideVelocity.x, gravity.y + sideVelocity.y);

		//마찰력 조건 ( 적용된 힘이 없고, 속도가 0 이 아닐 떄)
		if (!(mVelocity == Vector2::Zero))
		{
			// 속도에 반대 방향으로 마찰력을 적용
			Vector2 friction = -mVelocity;
			friction.Normalize();
			friction *= mFriction * mMass * Time::DeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			if (mVelocity.Length() < friction.Length())
			{
				// 속도를 0 로 만든다.
				mVelocity = Vector2(0.0f, 0.0f);
			}
			else
			{
				// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
				mVelocity += friction;
			}
		}

		// 속도에 맞게 물체를 이동시킨다.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		//pos = Vector3(pos.x + mVelocity.x * Time::DeltaTime(), pos.y + mVelocity.y * Time::DeltaTime(), 1.0f);

		//tr->SetPosition(pos);
		//mForce.x = 0;
		//mForce.y = 0;
	}

	void Rigidbody::FixedUpdate()
	{
	}

	void Rigidbody::Render()
	{

	}

	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}