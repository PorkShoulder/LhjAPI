#pragma once
#include "CBase.h"

class CObj :
    public CBase
{
private:
    Vec2   m_Pos;
    Vec2   m_Scale;

public:
    void Tick();        // 오브젝트가 할 일
    void Render();      // 오브젝트를 그리기

public:
    void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
    void SetPos(float _x, float _y) { m_Pos = Vec2(_x, _y); }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    void SetScale(float _x, float _y) { m_Scale = Vec2(_x, _y); }

    Vec2 GetPos() { return m_Pos; }
    Vec2 GetScale() { return m_Scale; }

public:
    CObj();
    ~CObj();
};

