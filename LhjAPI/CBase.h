#pragma once
// 기초가 될 케이스 매니저를 제외한 모든 클래스는 베이스에서 파생시킴.
// 다형성을 이용해서 모든 포인터르 가리킬수 있음. 
// 상속을 목적으로 단독객체 만들일은 없음 -> 추상클래스 

class CBase
{
private:
	static UINT g_NextID;

private:
	wstring		m_Name;
	const UINT	m_ID;

public:
	// inline 키워드 or 헤더에 함수가 구현된 경우 ==> inline 함수
	// 코드가 간결, 사용 빈도가 높을 때
	// Get, Set 류 함수들
	void SetName(const wstring& _Name) { m_Name = _Name; }
	const wstring& GetName() { return m_Name; }
	UINT GetID() { return m_ID; }
	void operator =(const CBase& _Origin) { m_Name = _Origin.m_Name; }

public:
	CBase();
	CBase(const CBase& _Origin);
	virtual ~CBase();
};

