#include <window.hh>


INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT nShowCmd )
{
    ( void )hPrevInstance;
    ( void )lpszCmdLine;
    ( void )nShowCmd;

    MSG Message;

    moo::CreateFormClass( hInstance );

    if( moo::CreateForm( hInstance ) )
    {
        while( GetMessageW( & Message, NULL, 0, 0 ) > 0 )
        {
            TranslateMessage( & Message );
            DispatchMessageW( & Message );
        }
    }

    moo::RemoveFormClass( hInstance );

    return 0;
}