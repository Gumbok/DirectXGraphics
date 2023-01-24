#pragma once
#include "Image2D.h"

class CCursor :
    public CImage2D
{
public:
    CCursor(LPCWSTR _fileName);
    ~CCursor();

    virtual void Update(float _deltaTime) override;

};

