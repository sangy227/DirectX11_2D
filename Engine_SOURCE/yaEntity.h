#pragma once
#include "yaEngine.h"

//#define GETSET(__TYPE__, __TARGET__, __METHODNAME__) \
//__TYPE__ get##__METHODNAME__() \
//{ \
//return __TARGET__; \
//} \
//void set##__METHODNAME__(__TYPE__ value) \
//{ \
//__TARGET__ = value; \
//}
//
//// get 프로퍼티 매크로
//#define GET(__TYPE__, __TARGET__, __METHODNAME__) \
//__TYPE__ get##__METHODNAME__() \
//{ \
//return __TARGET__; \
//}
//
//// set 프로퍼티 매크로
//#define SET(__TYPE__, __TARGET__, __METHODNAME__) \
//void set##__METHODNAME__(__TYPE__ value) \
//{ \
//__TARGET__ = value; \
//}


namespace ya
{
	class Entity
	{
	public:
		Entity();
		Entity(const Entity& other);
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		const std::wstring& GetName() { return mName; }
		UINT32 GetID() { return mID; }

	private:
		std::wstring mName;
		const UINT32 mID;
		
	};
}


