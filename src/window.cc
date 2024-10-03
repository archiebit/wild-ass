#include <window.hh>
#include <commctrl.h>


// Children windows' IDs
#define WID_ADD     1
#define WID_REMOVE  2
#define WID_TRASH   3

#define WID_APPEND  4
#define WID_CLEAR   5
#define WID_TEXTBOX 6

#define WID_LABEL   100 // [ 100; 100 + WINDOW_COUNT_MAX )
#define WID_DATA    200 // [ 200; 200 + WINDOW_COUNT_MAX )

// Window's layouts
#define LAYOUT_1_W  320
#define LAYOUT_1_H  32

#define LAYOUT_2_W  320
#define LAYOUT_2_H  320


namespace moo
{
    static HICON FindImage( HINSTANCE hInstance, UINT ID )
    {
        return ( HICON )LoadImageW( hInstance, MAKEINTRESOURCEW( ID ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR );
    }

    static VOID  MakeSound( HINSTANCE hInstance, UINT ID )
    {
        PlaySoundW( MAKEINTRESOURCEW( ID ), hInstance, SND_RESOURCE | SND_ASYNC );
    }

    static VOID ChangeSize( HWND hWindow, LONG cX, LONG cY )
    {
        RECT rSys;
        RECT rCli;

        GetWindowRect( hWindow, & rSys );
        GetClientRect( hWindow, & rCli );

        LONG W = ( rSys.right - rSys.left ) - ( rCli.right - rCli.left ) + cX;
        LONG H = ( rSys.bottom - rSys.top ) - ( rCli.bottom - rCli.top ) + cY;

        SetWindowPos( hWindow, NULL, 0, 0, W, H, SWP_NOZORDER | SWP_NOMOVE );
    }


    static VOID GetChildDimensions( UINT ID, COORD * Coord, SIZE * Size )
    {
        switch( ID )
        {
            case WID_ADD:
            {
                Coord->X = 4;
                Coord->Y = 4;
                Size->cx = 100;
                Size->cy = 24;

                break;
            }

            case WID_REMOVE:
            {
                Coord->X = 108;
                Coord->Y = 4;
                Size->cx = 104;
                Size->cy = 24;

                break;
            }

            case WID_TRASH:
            {
                Coord->X = 216;
                Coord->Y = 4;
                Size->cx = 100;
                Size->cy = 24;

                break;
            }


            case WID_APPEND:
            {
                Coord->X = 4;
                Coord->Y = 4;
                Size->cx = 154;
                Size->cy = 24;

                break;
            }

            case WID_CLEAR:
            {
                Coord->X = 162;
                Coord->Y = 4;
                Size->cx = 154;
                Size->cy = 24;

                break;
            }

            case WID_TEXTBOX:
            {
                Coord->X = 4;
                Coord->Y = 32;
                Size->cx = 312;
                Size->cy = 284;

                break;
            }
        }
    }

    static HWND GetChild( HWND hParent, UINT ID )
    {
        HWND hCurr = GetWindow( hParent, GW_CHILD | GW_HWNDFIRST );
        UINT uCurrID;

        while( hCurr )
        {
            uCurrID = GetWindowLongPtrW( hCurr, GWLP_ID );

            if( uCurrID == ID )
            {
                return hCurr;
            }
            else hCurr = GetWindow( hCurr, GW_HWNDNEXT );
        }

        return NULL;
    }

    static VOID CreateChild( HWND hParent, UINT ID )
    {
        HINSTANCE hInstance = ( HINSTANCE )GetWindowLongPtrW( hParent, GWLP_HINSTANCE );
        COORD         Coord;
        SIZE           Size;

        switch( ID )
        {
            case WID_ADD:
            {
                GetChildDimensions( ID, & Coord, & Size );

                HICON hIcon = ( HICON )GetWindowLongPtrW( hParent, GWLP_ICON_ADD );
                HWND hChild = CreateWindowExW
                (
                    0,
                    L"BUTTON",
                    NULL,
                    WS_CHILD | BS_ICON | BS_PUSHBUTTON,
                    Coord.X, Coord.Y,
                    Size.cx, Size.cy,
                    hParent,
                    NULL,
                    hInstance,
                    NULL
                );

                SetWindowLongPtrW( hChild, GWLP_ID, ID );

                if( hIcon )
                {
                    PostMessageW( hChild, BM_SETIMAGE, IMAGE_ICON, ( LPARAM )hIcon );
                }

                break;
            }

            case WID_REMOVE:
            {
                GetChildDimensions( ID, & Coord, & Size );

                HICON hIcon = ( HICON )GetWindowLongPtrW( hParent, GWLP_ICON_REMOVE );
                HWND hChild = CreateWindowExW
                (
                    0,
                    L"BUTTON",
                    NULL,
                    WS_CHILD | BS_ICON | BS_PUSHBUTTON,
                    Coord.X, Coord.Y,
                    Size.cx, Size.cy,
                    hParent,
                    NULL,
                    hInstance,
                    NULL
                );

                SetWindowLongPtrW( hChild, GWLP_ID, ID );

                if( hIcon )
                {
                    PostMessageW( hChild, BM_SETIMAGE, IMAGE_ICON, ( LPARAM )hIcon );
                }

                break;
            }

            case WID_TRASH:
            {
                GetChildDimensions( ID, & Coord, & Size );

                HICON hIcon = ( HICON )GetWindowLongPtrW( hParent, GWLP_ICON_TRASH );
                HWND hChild = CreateWindowExW
                (
                    0,
                    L"BUTTON",
                    NULL,
                    WS_CHILD | BS_ICON | BS_PUSHBUTTON,
                    Coord.X, Coord.Y,
                    Size.cx, Size.cy,
                    hParent,
                    NULL,
                    hInstance,
                    NULL
                );

                SetWindowLongPtrW( hChild, GWLP_ID, ID );

                if( hIcon )
                {
                    PostMessageW( hChild, BM_SETIMAGE, IMAGE_ICON, ( LPARAM )hIcon );
                }

                break;
            }


            case WID_APPEND:
            {
                GetChildDimensions( ID, & Coord, & Size );

                HFONT hFont = ( HFONT )GetWindowLongPtrW( hParent, GWLP_FONT );
                HWND hChild = CreateWindowExW
                (
                    0,
                    L"BUTTON",
                    L"Добавить",
                    WS_CHILD | BS_TEXT | BS_PUSHBUTTON,
                    Coord.X, Coord.Y,
                    Size.cx, Size.cy,
                    hParent,
                    NULL,
                    hInstance,
                    NULL
                );

                SetWindowLongPtrW( hChild, GWLP_ID, ID );

                if( hFont )
                {
                    PostMessageW( hChild, WM_SETFONT, ( WPARAM )hFont, TRUE );
                }

                break;
            }

            case WID_CLEAR:
            {
                GetChildDimensions( ID, & Coord, & Size );

                HFONT hFont = ( HFONT )GetWindowLongPtrW( hParent, GWLP_FONT );
                HWND hChild = CreateWindowExW
                (
                    0,
                    L"BUTTON",
                    L"Очистить",
                    WS_CHILD | BS_TEXT | BS_PUSHBUTTON,
                    Coord.X, Coord.Y,
                    Size.cx, Size.cy,
                    hParent,
                    NULL,
                    hInstance,
                    NULL
                );

                SetWindowLongPtrW( hChild, GWLP_ID, ID );

                if( hFont )
                {
                    PostMessageW( hChild, WM_SETFONT, ( WPARAM )hFont, TRUE );
                }

                break;
            }

            case WID_TEXTBOX:
            {
                GetChildDimensions( ID, & Coord, & Size );

                HFONT hFont = ( HFONT )GetWindowLongPtrW( hParent, GWLP_FONT );
                HWND hChild = CreateWindowExW
                (
                    0,
                    L"EDIT",
                    NULL,
                    WS_CHILD | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
                    Coord.X, Coord.Y,
                    Size.cx, Size.cy,
                    hParent,
                    NULL,
                    hInstance,
                    NULL
                );

                SetWindowLongPtrW( hChild, GWLP_ID, ID );

                if( hFont )
                {
                    PostMessageW( hChild, WM_SETFONT, ( WPARAM )hFont, TRUE );
                }

                break;
            }
        }
    }


    static VOID SetLayout( HWND hWindow, UINT uNumber )
    {
        UINT uCount = ( UINT  )GetWindowLongPtrW( hWindow, GWLP_COUNT     );
        HICON hMain = ( HICON )GetWindowLongPtrW( hWindow, GWLP_ICON_MAIN );
        HICON hEdit = ( HICON )GetWindowLongPtrW( hWindow, GWLP_ICON_EDIT );

        switch( uNumber )
        {
            case 1:
            {
                SetWindowLongPtrW( hWindow, GWLP_EDIT, FALSE );

                LONG W = LAYOUT_1_W;
                LONG H = LAYOUT_1_H + uCount * 28;

                ShowWindow( GetChild( hWindow, WID_APPEND  ), SW_HIDE );
                ShowWindow( GetChild( hWindow, WID_CLEAR   ), SW_HIDE );
                ShowWindow( GetChild( hWindow, WID_TEXTBOX ), SW_HIDE );

                ChangeSize( hWindow, W, H );

                SetWindowTextW( hWindow, L"WB Ассистент" );
                SendMessageW( hWindow, WM_SETICON, ICON_SMALL, ( LPARAM )hMain );
                SendMessageW( hWindow, WM_SETICON, ICON_BIG,   ( LPARAM )hMain );

                ShowWindow( GetChild( hWindow, WID_ADD     ), SW_SHOW );
                ShowWindow( GetChild( hWindow, WID_REMOVE  ), SW_SHOW );
                ShowWindow( GetChild( hWindow, WID_TRASH   ), SW_SHOW );

                for( UINT i = 0; i < WINDOW_COUNT_MAX; ++i )
                {
                    ShowWindow( GetChild( hWindow, WID_LABEL + i ), SW_SHOW );
                    ShowWindow( GetChild( hWindow, WID_DATA  + i ), SW_SHOW );
                }

                break;
            }

            case 2:
            {
                SetWindowLongPtrW( hWindow, GWLP_EDIT, TRUE );

                ShowWindow( GetChild( hWindow, WID_ADD     ), SW_HIDE );
                ShowWindow( GetChild( hWindow, WID_REMOVE  ), SW_HIDE );
                ShowWindow( GetChild( hWindow, WID_TRASH   ), SW_HIDE );

                for( UINT i = 0; i < WINDOW_COUNT_MAX; ++i )
                {
                    ShowWindow( GetChild( hWindow, WID_LABEL + i ), SW_HIDE );
                    ShowWindow( GetChild( hWindow, WID_DATA  + i ), SW_HIDE );
                }

                ChangeSize( hWindow, LAYOUT_2_W, LAYOUT_2_H );

                SetWindowTextW( hWindow, L"WB Ассистент - Отметка" );
                SendMessageW( hWindow, WM_SETICON, ICON_SMALL, ( LPARAM )hEdit );
                SendMessageW( hWindow, WM_SETICON, ICON_BIG,   ( LPARAM )hEdit );

                ShowWindow( GetChild( hWindow, WID_APPEND  ), SW_SHOW );
                ShowWindow( GetChild( hWindow, WID_CLEAR   ), SW_SHOW );
                ShowWindow( GetChild( hWindow, WID_TEXTBOX ), SW_SHOW );

                SetFocus( GetChild( hWindow, WID_TEXTBOX ) );

                break;
            }
        }
    }

    static UINT TranslateIndex( UINT Code )
    {
        switch( Code )
        {
            case 0x31: return  0;   // 1
            case 0x32: return  1;   // 2
            case 0x33: return  2;   // 3
            case 0x34: return  3;   // 4
            case 0x35: return  4;   // 5
            case 0x36: return  5;   // 6
            case 0x37: return  6;   // 7
            case 0x38: return  7;   // 8
            case 0x39: return  8;   // 9
            case 0x30: return  9;   // 0

            case 0x51: return 10;   // Q
            case 0x57: return 11;   // W
            case 0x45: return 12;   // E
            case 0x52: return 13;   // R
            case 0x54: return 14;   // T
            case 0x59: return 15;   // Y
            case 0x55: return 16;   // U
            case 0x49: return 17;   // I
            case 0x4F: return 18;   // O
            case 0x50: return 19;   // P
        }

        return WINDOW_COUNT_MAX;
    }

    static VOID GenTable( HWND hWindow )
    {
        static LPCWSTR lpszNames[ WINDOW_COUNT_MAX ]
        {
            L"1: ",
            L"2: ",
            L"3: ",
            L"4: ",
            L"5: ",
            L"6: ",
            L"7: ",
            L"8: ",
            L"9: ",
            L"0: ",
            L"Q: ",
            L"W: ",
            L"E: ",
            L"R: ",
            L"T: ",
            L"Y: ",
            L"U: ",
            L"I: ",
            L"O: ",
            L"P: "
        };

        HINSTANCE hInstance = ( HINSTANCE )GetWindowLongPtrW( hWindow, GWLP_HINSTANCE );
        HFONT         hFont = ( HFONT     )GetWindowLongPtrW( hWindow, GWLP_FONT      );

        for( UINT i = 0; i < WINDOW_COUNT_MAX; ++i )
        {
            INT X = 4;
            INT Y = i * 28 + 32;

            HWND hLabel = CreateWindowExW
            (
                0,
                L"STATIC",
                lpszNames[ i ],
                WS_CHILD | SS_LEFT,
                X, Y,
                24, 24,
                hWindow,
                NULL,
                hInstance,
                NULL
            );

            HWND hData = CreateWindowExW
            (
                0,
                L"STATIC",
                NULL,
                WS_CHILD | SS_LEFT,
                X + 28, Y,
                284, 24,
                hWindow,
                NULL,
                hInstance,
                NULL
            );

            SendMessageW( hLabel, WM_SETFONT, ( WPARAM )hFont, TRUE );
            SendMessageW( hData,  WM_SETFONT, ( WPARAM )hFont, TRUE );

            SetWindowLongPtrW( hLabel, GWLP_ID, WID_LABEL + i );
            SetWindowLongPtrW( hData,  GWLP_ID, WID_DATA  + i );
        }
    }

    static VOID GenReply( HWND hWindow )
    {
        SIZE_T  Total = WINDOW_REPLY_MAX * sizeof( WCHAR );
        LPWSTR String = ( LPWSTR )HeapAlloc( GetProcessHeap( ), 0, Total );

        String[ 0 ] = 0;

        SetWindowLongPtrW( hWindow, GWLP_REPLY, ( LONG_PTR )String );
    }


    static VOID AppendData( HWND hWindow, LPWSTR lpszData )
    {
        UINT uCount = ( UINT )GetWindowLongPtrW( hWindow, GWLP_COUNT );
        UINT uIndex = uCount;

        if( uCount == WINDOW_COUNT_MAX ) return;


        SetWindowTextW( GetChild( hWindow, WID_DATA + uIndex ), lpszData );
        SetWindowLongPtrW( hWindow, GWLP_COUNT, uCount + 1 );
    }

    static VOID RemoveData( HWND hWindow )
    {
        UINT uCount = ( UINT )GetWindowLongPtrW( hWindow, GWLP_COUNT );
        UINT uIndex = uCount - 1;

        if( uCount == 0 ) return;


        HWND hData = GetChild( hWindow, WID_DATA + uIndex );

        SetWindowTextW( hData, NULL );
        SetWindowLongPtrW( hWindow, GWLP_COUNT, uCount - 1 );
    }

    static VOID RemoveAllData( HWND hWindow )
    {
        UINT uCount = WINDOW_COUNT_MAX;

        while( uCount-- )
        {
            RemoveData( hWindow );
        }
    }


    static VOID CopyReply( HWND hWindow )
    {
        LPWSTR lpszReply = ( LPWSTR )GetWindowLongPtrW( hWindow, GWLP_REPLY );
        UINT     szTotal = wcslen( lpszReply );
        SIZE_T     szRaw = ( szTotal + 1 ) * sizeof( WCHAR );

        if( OpenClipboard( hWindow ) )
        {
            if( szTotal == 0 )
            {
                EmptyClipboard( );
                CloseClipboard( );

                return;
            }

            HGLOBAL Handle = GlobalAlloc( GMEM_MOVEABLE, szRaw );

            if( Handle )
            {
                LPWSTR Address = ( LPWSTR )GlobalLock( Handle );

                wcscpy( Address, lpszReply );
                GlobalUnlock( Handle );

                EmptyClipboard( );
                SetClipboardData( CF_UNICODETEXT, Handle );
            }

            CloseClipboard( );
        }
    }

    static VOID UpdateReply( HWND hWindow, UINT uIndex )
    {
        UINT      uCount = ( UINT   )GetWindowLongPtrW( hWindow, GWLP_COUNT );
        LPWSTR lpszReply = ( LPWSTR )GetWindowLongPtrW( hWindow, GWLP_REPLY );
        UINT     szTotal = wcslen( lpszReply );

        if( uIndex >= uCount ) return;


        HWND hData = GetChild( hWindow, WID_DATA + uIndex );

        if( szTotal != 0 )
        {
            lpszReply[ szTotal + 0 ] = L',';
            lpszReply[ szTotal + 1 ] = L' ';

            szTotal += 2;
        }

        WPARAM Available = WINDOW_REPLY_MAX - szTotal;
        LPARAM  Location = ( LPARAM )( lpszReply + szTotal );
        UINT     uOffset = SendMessageW( hData, WM_GETTEXT, Available, Location );

        lpszReply[ szTotal + uOffset ] = 0;

        CopyReply( hWindow );
    }

    static VOID EmptyReply( HWND hWindow )
    {
        LPWSTR lpszReply = ( LPWSTR )GetWindowLongPtrW( hWindow, GWLP_REPLY );

        lpszReply[ 0 ] = 0;

        CopyReply( hWindow );
    }
}


#if defined __clang__ or __GNUC__
namespace moo
{
    static HANDLE   hContext = INVALID_HANDLE_VALUE;
    static UINT_PTR lpCookie = 0;


    [[gnu::constructor]]
    void enable_visual_styles( )
    {
        WCHAR   Path[ MAX_PATH ];
        ACTCTXW Info
        {
            .cbSize                 = sizeof( ACTCTXW ),
            .dwFlags                = DWORD
            {
                ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID |
                ACTCTX_FLAG_RESOURCE_NAME_VALID      |
                ACTCTX_FLAG_SET_PROCESS_DEFAULT
            },
            .lpSource               = L"SHELL32.DLL",
            .wProcessorArchitecture = PROCESSOR_ARCHITECTURE_NEUTRAL,
            .wLangId                = MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL ),
            .lpAssemblyDirectory    = Path,
            .lpResourceName         = MAKEINTRESOURCEW( 124 ),
            .lpApplicationName      = NULL,
            .hModule                = NULL
        };

        GetSystemDirectoryW( Path, MAX_PATH );

        hContext = CreateActCtxW( & Info );

        if( hContext == INVALID_HANDLE_VALUE )
        {
            return SetLastError( ERROR_SUCCESS );
        }

        ActivateActCtx( hContext, & lpCookie );
    }

    [[gnu::destructor]]
    void disable_visual_styles( )
    {
        if( hContext != INVALID_HANDLE_VALUE )
        {
            DeactivateActCtx( 0, lpCookie );
            ReleaseActCtx( hContext );

            hContext = INVALID_HANDLE_VALUE;
            lpCookie = 0;
        }
    }
}
#endif


namespace moo
{
    LRESULT CALLBACK Edit( HWND hWindow, UINT uMessage, WPARAM W, LPARAM L, UINT_PTR, DWORD_PTR )
    {
        switch( uMessage )
        {
            case WM_CHAR:
            {
                if( W == L'\n' or W == L'\r' )
                {
                    return 0;
                }

                return DefSubclassProc( hWindow, uMessage, W, L );
            }

            case WM_KEYDOWN:
            {
                if( W == VK_RETURN )
                {
                    PostMessageW( GetParent( hWindow ), WM_COMMAND, WID_APPEND, 0 );

                    return 0;
                }

                if( W == VK_ESCAPE )
                {
                    SendMessageW( hWindow, WM_SETTEXT, 0, 0 );
                    SetLayout( GetParent( hWindow ), 1 );

                    return 0;
                }

                return DefSubclassProc( hWindow, uMessage, W, L );
            }

            default:
            {
                return DefSubclassProc( hWindow, uMessage, W, L );
            }
        }
    }

    LRESULT CALLBACK Proc( HWND hWindow, UINT uMessage, WPARAM W, LPARAM L )
    {
        switch( uMessage )
        {
            case WM_CREATE:
            {
                HFONT               hFont = NULL;
                HINSTANCE       hInstance = ( HINSTANCE )GetWindowLongPtrW( hWindow, GWLP_HINSTANCE );
                NONCLIENTMETRICSW Metrics
                {
                    .cbSize = sizeof( NONCLIENTMETRICSW )
                };

                if( SystemParametersInfoW( SPI_GETNONCLIENTMETRICS, sizeof( Metrics ), & Metrics, 0 ) )
                {
                    hFont = CreateFontIndirectW( & Metrics.lfMessageFont );

                    SetWindowLongPtrW( hWindow, GWLP_FONT, ( LONG_PTR )hFont );
                }

                SetWindowLongPtrW( hWindow, GWLP_COUNT, 0     );
                SetWindowLongPtrW( hWindow, GWLP_EDIT,  FALSE );

                SetWindowLongPtrW( hWindow, GWLP_ICON_MAIN,   ( LONG_PTR )FindImage( hInstance, ICON_MAIN   ) );
                SetWindowLongPtrW( hWindow, GWLP_ICON_EDIT,   ( LONG_PTR )FindImage( hInstance, ICON_EDIT   ) );
                SetWindowLongPtrW( hWindow, GWLP_ICON_ADD,    ( LONG_PTR )FindImage( hInstance, ICON_ADD    ) );
                SetWindowLongPtrW( hWindow, GWLP_ICON_REMOVE, ( LONG_PTR )FindImage( hInstance, ICON_REMOVE ) );
                SetWindowLongPtrW( hWindow, GWLP_ICON_TRASH,  ( LONG_PTR )FindImage( hInstance, ICON_TRASH  ) );

                CreateChild( hWindow, WID_ADD     );
                CreateChild( hWindow, WID_REMOVE  );
                CreateChild( hWindow, WID_TRASH   );
                CreateChild( hWindow, WID_APPEND  );
                CreateChild( hWindow, WID_CLEAR   );
                CreateChild( hWindow, WID_TEXTBOX );

                GenTable( hWindow );
                GenReply( hWindow );

                SetWindowSubclass( GetChild( hWindow, WID_TEXTBOX ), & Edit, 1, 0 );

                ShowWindow( hWindow, SW_SHOW );
                SetLayout( hWindow, 1 );

                return 0;
            }

            case WM_DESTROY:
            {
                ShowWindow( hWindow, SW_HIDE );
                RemoveWindowSubclass( GetChild( hWindow, WID_TEXTBOX ), & Edit, 1 );

                DeleteObject( ( HFONT )GetWindowLongPtrW( hWindow, GWLP_FONT ) );

                DestroyIcon( ( HICON )GetWindowLongPtrW( hWindow, GWLP_ICON_MAIN   ) );
                DestroyIcon( ( HICON )GetWindowLongPtrW( hWindow, GWLP_ICON_EDIT   ) );
                DestroyIcon( ( HICON )GetWindowLongPtrW( hWindow, GWLP_ICON_ADD    ) );
                DestroyIcon( ( HICON )GetWindowLongPtrW( hWindow, GWLP_ICON_REMOVE ) );
                DestroyIcon( ( HICON )GetWindowLongPtrW( hWindow, GWLP_ICON_TRASH  ) );

                HeapFree( GetProcessHeap( ), 0, ( LPVOID )GetWindowLongPtrW( hWindow, GWLP_REPLY ) );

                return 0;
            }

            case WM_CLOSE:
            {
                PostMessageW( hWindow, WM_DESTROY, 0, 0 );
                PostQuitMessage( 0 );

                return 0;
            }


            case WM_KEYDOWN:
            {
                HINSTANCE hInstance = ( HINSTANCE )GetWindowLongPtrW( hWindow, GWLP_HINSTANCE );
                BOOL          bEdit = ( BOOL      )GetWindowLongPtrW( hWindow, GWLP_EDIT      );

                if( bEdit == FALSE ) switch( W )
                {
                    case VK_ADD:
                    {
                        SendMessageW( hWindow, WM_COMMAND, WID_ADD, 0 );

                        break;
                    }

                    case VK_SUBTRACT:
                    {
                        SendMessageW( hWindow, WM_COMMAND, WID_REMOVE, 0 );

                        break;
                    }

                    case VK_ESCAPE:
                    {
                        EmptyReply( hWindow );
                        MakeSound( hInstance, WAVE_TRASH );

                        break;
                    }

                    default:
                    {
                        UINT uIndex = TranslateIndex( W );

                        if( uIndex != WINDOW_COUNT_MAX )
                        {
                            UpdateReply( hWindow, uIndex );
                        }

                        break;
                    }
                }

                return 0;
            }

            case WM_COMMAND:
            {
                HINSTANCE hInstance = ( HINSTANCE )GetWindowLongPtrW( hWindow, GWLP_HINSTANCE );

                switch( LOWORD( W ) )
                {
                    case WID_ADD:
                    {
                        if( GetWindowLongPtrW( hWindow, GWLP_COUNT ) != WINDOW_COUNT_MAX )
                        {
                            SetLayout( hWindow, 2 );
                        }

                        break;
                    }

                    case WID_REMOVE:
                    {
                        if( GetWindowLongPtrW( hWindow, GWLP_COUNT ) != 0 )
                        {
                            MakeSound( hInstance, WAVE_REMOVE );
                            RemoveData( hWindow );
                            SetLayout( hWindow, 1 );
                        }

                        break;
                    }

                    case WID_TRASH:
                    {
                        if( GetWindowLongPtrW( hWindow, GWLP_COUNT ) != 0 )
                        {
                            MakeSound( hInstance, WAVE_TRASH );
                            RemoveAllData( hWindow );
                            SetLayout( hWindow, 1 );
                        }

                        break;
                    }


                    case WID_APPEND:
                    {
                        HWND hTextbox = GetChild( hWindow, WID_TEXTBOX );
                        LPWSTR   Data = NULL;
                        UINT   Length = SendMessageW( hTextbox, WM_GETTEXTLENGTH, 0, 0 );

                        if( Length == 0 )
                        {
                            break;
                        }

                        Data = ( LPWSTR )HeapAlloc( GetProcessHeap( ), 0, ( Length + 1 ) * sizeof( WCHAR ) );
                        Data[ Length ] = 0;

                        SendMessageW( hTextbox, WM_GETTEXT, Length + 1, ( LPARAM )Data );
                        AppendData( hWindow, Data );

                        HeapFree( GetProcessHeap( ), 0, Data );
                        SetLayout( hWindow, 1 );
                        SendMessageW( hTextbox, WM_SETTEXT, 0, 0 );

                        break;
                    }

                    case WID_CLEAR:
                    {
                        SendMessageW( GetChild( hWindow, WID_TEXTBOX ), WM_SETTEXT, 0, 0 );

                        break;
                    }
                }

                return 0;
            }


            case WM_PAINT:
            {
                PAINTSTRUCT Paint;
                HDC           hDC = BeginPaint( hWindow, & Paint );

                FillRect( hDC, & Paint.rcPaint, HBRUSH( COLOR_WINDOW ) );
                EndPaint( hWindow, & Paint );

                return 0;
            }


            default:
            {
                return DefWindowProcW( hWindow, uMessage, W, L );
            }
        }
    }


    static ATOM aWindowClass = INVALID_ATOM;
    static HWND      hWindow = NULL;


    VOID CreateFormClass( HINSTANCE hInstance )
    {
        WNDCLASSEXW Info
        {
            .cbSize        = sizeof( WNDCLASSEXW ),
            .style         = 0,
            .lpfnWndProc   = & Proc,
            .cbClsExtra    = 0,
            .cbWndExtra    = WINDOW_EXTRA,
            .hInstance     = hInstance,
            .hIcon         = NULL,
            .hCursor       = LoadCursorW( NULL, IDC_ARROW ),
            .hbrBackground = HBRUSH( COLOR_WINDOW + 1 ),
            .lpszMenuName  = NULL,
            .lpszClassName = L"moo:wildass",
            .hIconSm       = NULL
        };

        aWindowClass = RegisterClassExW( & Info );

        if( aWindowClass == INVALID_ATOM )
        {
            MessageBoxW( NULL, L"Не удалось создать класс окна.", L"Ошибка!", MB_ICONERROR | MB_OK );
        }
    }

    VOID RemoveFormClass( HINSTANCE hInstance )
    {
        if( aWindowClass != INVALID_ATOM )
        {
            UnregisterClassW( ( LPWSTR )aWindowClass, hInstance );
        }
    }

    BOOL CreateForm( HINSTANCE hInstance )
    {
        hWindow = CreateWindowExW
        (
            0,
            ( LPWSTR )aWindowClass,
            NULL,
            WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_TILED,
            CW_USEDEFAULT, CW_USEDEFAULT,
            LAYOUT_1_W,    LAYOUT_1_H,
            NULL,
            NULL,
            hInstance,
            NULL
        );

        if( hWindow == NULL )
        {
            MessageBoxW( NULL, L"Не удалось создать окно.", L"Ошибка!", MB_ICONERROR | MB_OK );

            return FALSE;
        }

        return TRUE;
    }
}