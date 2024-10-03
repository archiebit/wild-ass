#ifndef MOO_WINDOW_HH
#define MOO_WINDOW_HH

#define  UNICODE
#define _UNICODE
#include <windows.h>


// Window data and constants.
#define GWLP_COUNT          ( 0 * sizeof( LONG_PTR ) )
#define GWLP_REPLY          ( 1 * sizeof( LONG_PTR ) )
#define GWLP_EDIT           ( 2 * sizeof( LONG_PTR ) )
#define GWLP_FONT           ( 3 * sizeof( LONG_PTR ) )
#define GWLP_ICON_MAIN      ( 4 * sizeof( LONG_PTR ) )
#define GWLP_ICON_EDIT      ( 5 * sizeof( LONG_PTR ) )
#define GWLP_ICON_ADD       ( 6 * sizeof( LONG_PTR ) )
#define GWLP_ICON_REMOVE    ( 7 * sizeof( LONG_PTR ) )
#define GWLP_ICON_TRASH     ( 8 * sizeof( LONG_PTR ) )

#define WINDOW_EXTRA        ( 9 * sizeof( LONG_PTR ) )
#define WINDOW_COUNT_MAX    20
#define WINDOW_REPLY_MAX    2048


// Icon IDs
#define ICON_MAIN           0
#define ICON_EDIT           1
#define ICON_ADD            2
#define ICON_REMOVE         3
#define ICON_TRASH          4


// Sound IDs
#define WAVE_APPEND         5
#define WAVE_REMOVE         6
#define WAVE_TRASH          7


namespace moo
{
    VOID CreateFormClass( HINSTANCE hInstance );
    VOID RemoveFormClass( HINSTANCE hInstance );

    BOOL CreateForm( HINSTANCE hInstance );
}


#endif