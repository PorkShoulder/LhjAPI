#pragma once
#include "CUI.h"

class CPanelUI :
    public CUI
{
private:
    Vec2    m_DownPos; // �ڽ��� ���콺 ���� Ŭ�� �Ǿ��� �� ��ǥ ���

public:    
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

    virtual void MouseLBtnDown() override;
    virtual void MouseLBtnClikced() override;

public:
    CPanelUI();
    ~CPanelUI();
};
