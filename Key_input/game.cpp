#include "game.h"
#include"pad.h"
#include"keyboard.h"

Game::Game()
{
    position10_.x = 110;
    position10_.y = 470;
    buttons_position_.x = 480;
    buttons_position_.y = 400;

}

bool Game::init()
{
    if( !(texture_ = Texture::load( L"InputChecker.png" )))
    {
        //エラー
        return false;
    }

    Rtriggers_position_.x = 495;
    Rtriggers_position_.y = 130;
    Ltriggers_position_.x = 55;
    Ltriggers_position_.y = 130;
    // Ltriggers_position_.y = 225;

    return true;
}

void Game::update()
{
    const Keyboard::State state = Key::getKeyState();
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getKeyTracker();

    //トリガー入力
    Ltriggers_position_.y = (pad.triggers.left * 100) + 130;

    Rtriggers_position_.y = (pad.triggers.right * 100) + 130;

    Rstick_position_.x = pad.thumbSticks.rightX * 20 + 400;
    Rstick_position_.y = pad.thumbSticks.rightY * -20 + 490;
    Lstick_position_.x = pad.thumbSticks.leftX * 20 + 70;
    Lstick_position_.y = pad.thumbSticks.leftY * -20 + 330;
}

void Game::draw()
{
    const Keyboard::State state = Key::getKeyState();
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getKeyTracker();
    RECT rect;
    Pad::update();
    Sprite::draw( texture_ );

    //十字キーの入力
    if( pad.dpad.down )
    {
        rect.left = 600;
        rect.right = rect.left + 120;
        rect.top = 720;
        rect.bottom = 840;

        Sprite::draw( texture_, position10_, &rect );
    }
    else if( pad.dpad.left )
    {
        rect.left = 840;
        rect.right = rect.left + 120;
        rect.top = 720;
        rect.bottom = 840;

        Sprite::draw( texture_, position10_, &rect );
    }
    else if( pad.dpad.right )
    {
        rect.left = 360;
        rect.right = rect.left + 120;
        rect.top = 720;
        rect.bottom = 840;

        Sprite::draw( texture_, position10_, &rect );
    }
    else if( pad.dpad.up )
    {
        rect.left = 120;
        rect.right = rect.left + 120;
        rect.top = 720;
        rect.bottom = 840;

        Sprite::draw( texture_, position10_, &rect );
    }

    ///////////////////////////////////////
    //ボタン
    if( pad.buttons.a )
    {
        rect.left = 1080;
        rect.right = rect.left + 50;
        rect.top = 770;
        rect.bottom = 820;
        buttons_position_.x = 480;
        buttons_position_.y = 400;
        Sprite::draw( texture_, buttons_position_, &rect );
    }
    if( pad.buttons.b )
    {
        rect.left = 1130;
        rect.right = rect.left + 50;
        rect.top = 770;
        rect.bottom = 820;
        buttons_position_.x = 530;
        buttons_position_.y = 350;
        Sprite::draw( texture_, buttons_position_, &rect );
    }
    if( pad.buttons.y )
    {
        rect.left = 1230;
        rect.right = rect.left + 50;
        rect.top = 770;
        rect.bottom = 820;
        buttons_position_.x = 480;
        buttons_position_.y = 300;
        Sprite::draw( texture_, buttons_position_, &rect );

    }
    if( pad.buttons.x )
    {
        rect.left = 1180;
        rect.right = rect.left + 50;
        rect.top = 770;
        rect.bottom = 820;
        buttons_position_.x = 430;
        buttons_position_.y = 350;
        Sprite::draw( texture_, buttons_position_, &rect );
    }

    ///////////////////////////////
    //スティック押し込み
    if( !pad.buttons.rightStick )
    {
        rect.left = 520;
        rect.right = rect.left + 60;
        rect.top = 960;
        rect.bottom = 1020;
        Sprite::draw( texture_, Rstick_position_, &rect );
    }
    if(! pad.buttons.leftStick )
    {
        rect.left = 520;
        rect.right = rect.left + 60;
        rect.top = 960;
        rect.bottom = 1020;
        Sprite::draw( texture_, Lstick_position_, &rect );
    }
    if( pad.buttons.leftShoulder )
    {
        rect.left = 0;
        rect.right = rect.left + 130;
        rect.top = 992;
        rect.bottom = 1024;
        LB_position_.x = 10;
        LB_position_.y = 249;
        Sprite::draw( texture_, LB_position_, &rect );
    }
    if( pad.buttons.rightShoulder)
    {
        rect.left = 130;
        rect.right = rect.left + 130;
        rect.top = 992;
        rect.bottom = 1024;
        LB_position_.x = 450;
        LB_position_.y = 250;
        Sprite::draw( texture_, LB_position_, &rect );
    }

    //////////////////////
    //トリガー

    rect.top = 963;
    rect.bottom = 964;
    rect.left = 1010;
    rect.right = 1053;
    Sprite::draw( texture_, Ltriggers_position_, &rect );

    rect.top = 963;
    rect.bottom = 964;
    rect.left = 1010;
    rect.right = 1053;
    Sprite::draw( texture_, Rtriggers_position_, &rect );


    /////////////////////
    //真ん中のボタン
    if( pad.buttons.view )
    {
        rect.left = 1181;
        rect.right = 1222;
        rect.top = 961;
        rect.bottom = 1002;
        Sprite::draw( texture_, Vector2( 230, 350 ), &rect );
    }

    if(pad.buttons.menu )
    {
        rect.left = 1140;
        rect.right = 1180;
        rect.top = 960;
        rect.bottom = 1002;
        Sprite::draw( texture_, Vector2( 330, 350 ), &rect );
    }
}

void Game::destroy()
{
    SAFE_RELEASE( texture_ );
}
