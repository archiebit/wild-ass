#ifndef MOO_WINDOW_HH
#define MOO_WINDOW_HH

#define  UNICODE
#define _UNICODE
#include <windows.h>


// Window data and constants.
#define GWLP_TABLE          (  0 * sizeof( LONG_PTR ) )
#define GWLP_COUNT          (  1 * sizeof( LONG_PTR ) )
#define GWLP_REPLY          (  2 * sizeof( LONG_PTR ) )
#define GWLP_EDIT           (  3 * sizeof( LONG_PTR ) )
#define GWLP_FONT           (  4 * sizeof( LONG_PTR ) )
#define GWLP_ICON_MAIN      (  5 * sizeof( LONG_PTR ) )
#define GWLP_ICON_EDIT      (  6 * sizeof( LONG_PTR ) )
#define GWLP_ICON_ADD       (  7 * sizeof( LONG_PTR ) )
#define GWLP_ICON_REMOVE    (  8 * sizeof( LONG_PTR ) )
#define GWLP_ICON_TRASH     (  9 * sizeof( LONG_PTR ) )

#define WINDOW_EXTRA        ( 10 * sizeof( LONG_PTR ) )
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

    VOID CreateForm( HINSTANCE hInstance );
}


#endif