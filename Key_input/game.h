#pragma once
#include"stdafx.h"
#include"texture.h"
#include"sprite.h"
#include"error.h"

using namespace DirectX;
using namespace SimpleMath;

class Game
{
private:
    ID3D11ShaderResourceView* texture_;
    Vector2 position10_;
    Vector2 buttons_position_;
    Vector2 Rstick_position_;
    Vector2 Lstick_position_;
    Vector2 LB_position_;
    Vector2 RB_position_;
    Vector2 Ltriggers_position_;
    Vector2 Rtriggers_position_;

public:
    Game();
    bool init();
    void update();
    void draw();
    void destroy();
};