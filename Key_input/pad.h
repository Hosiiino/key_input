#pragma once
////////////////////////////////////
// Include
////////////////////////////////////
#include <GamePad.h>


////////////////////////////////////
// ���O���
////////////////////////////////////
using namespace DirectX;

////////////////////////////////////
// class
////////////////////////////////////
class Pad
{
private:
    static GamePad pad_;             // �Q�[���p�b�h�N���X
    static GamePad::State state_;    // 1P���͊i�[�\����
    static GamePad::State state2_;   // 2P���͊i�[�\����
    static GamePad::ButtonStateTracker tracker_;

public:
    static void update();           // �X�V����

    // ���͍\���̂�Ԃ�
    static const GamePad::State& getState() { return state_; }      //1P
    static const GamePad::State& getState2() { return state2_; }    //2P
    static const  GamePad::ButtonStateTracker& getKeyTracker() { return tracker_; }

};
