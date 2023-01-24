#pragma once
#include "Image2D.h"

class CButton2D;
typedef void(*BTNCALLBACK) (CButton2D*);

class CButton2D :
    public CImage2D
{
public:
    CButton2D(XMFLOAT2 _pos, LPCWSTR _fileName, BTNCALLBACK _callback);
    ~CButton2D();

    virtual void Update(float _deltaTime) override;

private:
    BTNCALLBACK m_callback;
    bool m_wasClicked;
};

