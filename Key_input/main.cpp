////////////////////////////////////
// Include
////////////////////////////////////

#include "direct3d.h"
#include "sprite.h"
#include "common.h"
#include "pad.h"
#include "keyboard.h"
#include"stdafx.h"
#include"game.h"

////////////////////////////////////
// ���O���
////////////////////////////////////
using namespace DirectX;
using namespace SimpleMath;


////////////////////////////////////
// �񋓑�
////////////////////////////////////
 //�V�[���ǉ�(ed��)�ɂ����enum�̒��̕ϐ���ǉ�
enum
{
    kTitleInit,     // �^�C�g����ʏ�����
    kTitleUpdate,   // �^�C�g����ʍX�V(�`��)
    kTutorialInit,  // �`���[�g���A����ʏ�����
    kTutorialUpdate,// �`���[�g���A����ʍX�V(�`��)
    kGameInit,      // �Q�[����ʏ�����
    kGameUpdate,    // �Q�[����ʍX�V(�`��)
    kResultInit,    // ���U���g��ʏ�����
    kResultUpdate,  // ���U���g��ʍX�V(�`��)
};


////////////////////////////////////
// �v���g�^�C�v�錾
////////////////////////////////////
LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

////////////////////////////////////
// WINMAIN
////////////////////////////////////
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

#ifdef  _DEBUG

    //���������[�N�̃`�F�b�N
    //_CrtSetBreakAlloc(); ���������[�N�̏ꏊ����������
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

#endif //  _DEBUG

    //�~���[�e�b�N�X�̍쐬
    HANDLE mutex = CreateMutex( NULL, false, "TETRIS_HOSINO" );

    //���d�N���̃`�F�b�N
    if( GetLastError() == ERROR_ALREADY_EXISTS )
    {
        //�N�����Ă���
        return 0;
    }

    // �E�B���h�E�N���X�̍쐬
    WNDCLASSEX wnd;
    ZeroMemory( &wnd, sizeof( WNDCLASSEX ) );
    wnd.cbSize = sizeof( WNDCLASSEX );                               // �\���̃T�C�Y
    wnd.style = CS_HREDRAW | CS_VREDRAW;                             // �X�^�C��
    wnd.hInstance = hInstance;                                       // �A�v���P�[�V�����C���X�g�[��
    wnd.lpszClassName = "ClassName";                                 // �N���X��
    wnd.hCursor = LoadCursor( NULL, IDC_ARROW );                     // �J�[�\���`��ǂݍ���
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);  // �E�B���h�E�J���[
    wnd.lpfnWndProc = WinProc;                                       // �E�B���h�E�v���V�[�W���ւ̊֐��|�C���^

    // �o�^
    if( !RegisterClassEx( &wnd ) )
    {
        // �G���[(��L�̊֐���0���Ԃ��Ă����Ƃ�)
        return 0;
    }

    // �E�B���h�E�T�C�Y������
    RECT rect;
    rect.left = rect.top = 0L;
    rect.right = 1280L;
    rect.bottom = 720L;
    const DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME  &  ~WS_MAXIMIZEBOX;
    const DWORD ex_style = WS_EX_OVERLAPPEDWINDOW;
    AdjustWindowRectEx( &rect, style, false, ex_style );// �E�B���h�E�̃T�C�Y�̍��W�̃Y����������邽�߂̊֐�

    //�E�B���h�E�̍쐬
    const HWND hWnd = CreateWindowEx(
        ex_style,               // �g���E�B���h�E�X�^�C��
        "ClassName",            // �N���X��
        "Title",                // �E�B���h�E�^�C�g��
        style,                  // �E�B���h�E�X�^�C��
        CW_USEDEFAULT,          // �\�����W�w 
        CW_USEDEFAULT,          // �\�����W�x
        rect.right - rect.left, // �E�B���h�E����
        rect.bottom - rect.top, // �E�B���h�E�c��
        NULL,                   // �e���j���[�ւ̃n���h�� 
        NULL,                   // ���j���[�n���h��
        hInstance,              // �A�v���P�[�V�����C���X�^���X
        NULL                    // �E�B���h�E�쐬�f�[�^
    );

    // NULL�`�F�b�N
    if( hWnd == NULL )
    {
        //�G���[
        return 0;
    }

    // Direct3D������
    if( !Direct3D::init( hWnd ) )
    {
        // �G���[
        return 0;
    }

    // COM���C�u�����̏�����
    if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
    {
        // �G���[
        return 0;
    }

    // SpriteBatch�N���X�̏�����
    if( !Sprite::init() )
    {
        // �G���[
        return 0;
    }

    // CommonStates�N���X�̏�����
    if( !Common::init() )
    {
        // �G���[
        return 0;
    }

    // �E�B���h�E�̕\��
    ShowWindow( hWnd, SW_SHOWNORMAL );

    // ���C�����[�v
    MSG msg = { NULL };

    //���Ԍv��
    DWORD t1, t2, t3 = 0L, dt;
    t1 = timeGetTime();
    t2 = timeGetTime();

    Game game;
    if( !game.init() )
    {
        return 0;
    }

    while( msg.message != WM_QUIT )
    {
        float x = static_cast<float>(0.1);

        // ���b�Z�[�W�����@// DXlib�ł�ProcessMessage()
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            // �t���[�����[�g����
            t1 = timeGetTime();     // ���݂̎���
            dt = (t1 - t2) + t3;    // �O��̍X�V����̍������v�Z

            // ��16�~���b�o�߂��Ă����珈�����s��
            // 10000/1�~���b/60fps=16.666...
            if( dt > 16 )
            {
                t2 = t1;            // ���̎��Ԃ�O��̎��ԂƂ���
                t3 = dt % 16;       // �덷�����z��   // �O�̗]��

                game.update();

                Direct3D::clear();  // ��ʃN���A
                Sprite::begin();    // �X�v���C�g�`��J�n

                game.draw();

                Sprite::end();      // �X�v���C�g�`��I��
                Direct3D::present();// ��ʍX�V
            }
        }
    }
    // COM���C�u�����̏�����
    CoUninitialize();

    // �S�ẴC���^�[�t�F�C�X�̉��
    game.destroy();
    Common::destroy();
    Sprite::destroy();
    Direct3D::destroy();

    return 0;
}


////////////////////////////////////
// CALLBACK
////////////////////////////////////
// �X�C�b�`�����̎w��̃L�[�������ꂽ����s�����֐� CALLBACK
LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( Msg )
    {
    case WM_PAINT:
        hdc = BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        break;

        // �A�v���P�[�V�������N��������
    case WM_ACTIVATEAPP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;

        // ������Ă��邩�A�����ꂽ�u�ԁA����݂̂Ȃ�
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYUP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;


    case WM_KEYDOWN:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        // �����̃L�[�������ꂽ�����
        switch( wParam )
        {
        case VK_ESCAPE:
            // ESC���������烋�[�v���I������
            PostMessage( hWnd, WM_CLOSE, 0, 0 );
            break;
        }
        break;

    case WM_DESTROY:
        // �v���O�������I���������ɌĂяo����郁�b�Z�[�W
        PostQuitMessage( 0 );
        break;
    }

    return DefWindowProc( hWnd, Msg, wParam, lParam );
}