#ifdef BUILDING_EXAMPLE_DLL
#define EXAMPLE_DLL __declspec(dllexport)
#else
#define EXAMPLE_DLL __declspec(dllimport)
#endif
// The winbgim library, Version 6.0, August 9, 2004
// Written by:
//      Grant Macklem (Grant.Macklem@colorado.edu)
//      Gregory Schmelter (Gregory.Schmelter@colorado.edu)
//      Alan Schmidt (Alan.Schmidt@colorado.edu)
//      Ivan Stashak (Ivan.Stashak@colorado.edu)
//      Michael Main (Michael.Main@colorado.edu)
// CSCI 4830/7818: API Programming
// University of Colorado at Boulder, Spring 2003


// ---------------------------------------------------------------------------
//                          Notes
// ---------------------------------------------------------------------------
// * This library is still under development.
// * Please see http://www.cs.colorado.edu/~main/bgi for information on
// * using this library with the mingw32 g++ compiler.
// * This library only works with Windows API level 4.0 and higher (Windows 95, NT 4.0 and newer)
// * This library may not be compatible with 64-bit versions of Windows
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
//                          Macro Guard and Include Directives
// ---------------------------------------------------------------------------
#ifndef WINBGI_H
#define WINBGI_H
#include <windows.h>        // Provides the mouse message types
#include <limits.h>         // Provides INT_MAX
#include <sstream>          // Provides std::ostringstream
#include "keys_n_colors.hpp"

// Line thickness settings
enum line_thickness {NORM_WIDTH=1, THICK_WIDTH=3};

// Character Size and Direction
#define USER_CHAR_SIZE  0
enum text_direction {HORIZ_DIR, VERT_DIR};

// Constants for closegraph
#define CURRENT_WINDOW -1
#define ALL_WINDOWS -2
#define NO_CURRENT_WINDOW -3

// The standard Borland 16 colors
#define MAXCOLORS       15
// The standard line styles
enum line_styles { SOLID_LINE, DOTTED_LINE, CENTER_LINE, DASHED_LINE, USERBIT_LINE };

// The standard fill styles
enum fill_styles { EMPTY_FILL, SOLID_FILL, LINE_FILL, LTSLASH_FILL, SLASH_FILL,
                   BKSLASH_FILL, LTBKSLASH_FILL, HATCH_FILL, XHATCH_FILL, INTERLEAVE_FILL,
                   WIDE_DOT_FILL, CLOSE_DOT_FILL, USER_FILL };

// The various graphics drivers
enum graphics_drivers { DETECT, CGA, MCGA, EGA, EGA64, EGAMONO, IBM8514, HERCMONO,
                        ATT400, VGA, PC3270 };

// Various modes for each graphics driver
enum graphics_modes { CGAC0, CGAC1, CGAC2, CGAC3, CGAHI, 
                      MCGAC0 = 0, MCGAC1, MCGAC2, MCGAC3, MCGAMED, MCGAHI,
                      EGALO = 0, EGAHI,
                      EGA64LO = 0, EGA64HI,
                      EGAMONOHI = 3,
                      HERCMONOHI = 0,
                      ATT400C0 = 0, ATT400C1, ATT400C2, ATT400C3, ATT400MED, ATT400HI,
                      VGALO = 0, VGAMED, VGAHI,
                      PC3270HI = 0,
                      IBM8514LO = 0, IBM8514HI };

// Borland error messages for the graphics window.
#define NO_CLICK        -1      // No mouse event of the current type in getmouseclick
enum graph_errors { grInvalidVersion = -18, grInvalidDeviceNum = -15, grInvalidFontNum,
                    grInvalidFont, grIOerror, grError, grInvalidMode, grNoFontMem,
                    grFontNotFound, grNoFloodMem, grNoScanMem, grNoLoadMem,
                    grInvalidDriver, grFileNotFound, grNotDetected, grNoInitGraph,
                    grOk };

// Write modes
enum putimage_ops{ COPY_PUT, XOR_PUT, OR_PUT, AND_PUT, NOT_PUT };

// Text Modes
enum horiz_align { LEFT_TEXT, CENTER_TEXT, RIGHT_TEXT };
enum vertical_align { BOTTOM_TEXT, VCENTER_TEXT, TOP_TEXT }; // middle not needed other than as seperator
enum font_names { DEFAULT_FONT, TRIPLEX_FONT, SMALL_FONT, SANS_SERIF_FONT,
             GOTHIC_FONT, SCRIPT_FONT, SIMPLEX_FONT, TRIPLEX_SCR_FONT,
			 COMPLEX_FONT, EUROPEAN_FONT, BOLD_FONT };
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//                              Structures
// ---------------------------------------------------------------------------
// This structure records information about the last call to arc.  It is used
// by getarccoords to get the location of the endpoints of the arc.
struct EXAMPLE_DLL arccoordstype
{
    int x, y;                   // Center point of the arc
    int xstart, ystart;         // The starting position of the arc
    int xend, yend;             // The ending position of the arc.
};


// This structure defines the fill style for the current window.  Pattern is
// one of the system patterns such as SOLID_FILL.  Color is the color to
// fill with
struct EXAMPLE_DLL fillsettingstype
{
    int pattern;                // Current fill pattern
    int color;                  // Current fill color
};


// This structure records information about the current line style.
// linestyle is one of the line styles such as SOLID_LINE, upattern is a
// 16-bit pattern for user defined lines, and thickness is the width of the
// line in pixels.
struct EXAMPLE_DLL linesettingstype
{
    int linestyle;              // Current line style
    unsigned upattern;          // 16-bit user line pattern
    int thickness;              // Width of the line in pixels
};


// This structure records information about the text settings.
struct EXAMPLE_DLL textsettingstype
{
    int font;                   // The font in use
    int direction;              // Text direction
    int charsize;               // Character size
    int horiz;                  // Horizontal text justification
    int vert;                   // Vertical text justification
};


// This structure records information about the viewport
struct EXAMPLE_DLL viewporttype
{
    int left, top,              // Viewport bounding box
        right, bottom;
    int clip;                   // Whether to clip image to viewport
};


// This structure records information about the palette.
struct EXAMPLE_DLL palettetype
{
    unsigned char size;
    signed char colors[MAXCOLORS + 1];
};
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//                          API Entries
// ---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// Drawing Functions
void __stdcall EXAMPLE_DLL arc( int x, int y, int stangle, int endangle, int radius );
void __stdcall EXAMPLE_DLL bar( int left, int top, int right, int bottom );
void __stdcall EXAMPLE_DLL bar3d( int left, int top, int right, int bottom, int depth, int topflag );
void __stdcall EXAMPLE_DLL circle( int x, int y, int radius );
void __stdcall EXAMPLE_DLL cleardevice( );
void __stdcall EXAMPLE_DLL clearviewport( );
void __stdcall EXAMPLE_DLL drawpoly(int n_points, int* points);
void __stdcall EXAMPLE_DLL ellipse( int x, int y, int stangle, int endangle, int xradius, int yradius );
void __stdcall EXAMPLE_DLL fillellipse( int x, int y, int xradius, int yradius );
void __stdcall EXAMPLE_DLL fillpoly(int n_points, int* points);
void __stdcall EXAMPLE_DLL floodfill( int x, int y, int border );
void __stdcall EXAMPLE_DLL line( int x1, int y1, int x2, int y2 );
void __stdcall EXAMPLE_DLL linerel( int dx, int dy );
void __stdcall EXAMPLE_DLL lineto( int x, int y );
void __stdcall EXAMPLE_DLL pieslice( int x, int y, int stangle, int endangle, int radius );
void __stdcall EXAMPLE_DLL putpixel( int x, int y, int color );
void __stdcall EXAMPLE_DLL rectangle( int left, int top, int right, int bottom );
void __stdcall EXAMPLE_DLL sector( int x, int y, int stangle, int endangle, int xradius, int yradius );

// Miscellaneous Functions
int __stdcall EXAMPLE_DLL getdisplaycolor( int color );
int __stdcall EXAMPLE_DLL converttorgb( int color );
void __stdcall EXAMPLE_DLL _bgi_delay( int msec );
#define delay _bgi_delay
void __stdcall EXAMPLE_DLL getarccoords( arccoordstype *arccoords );
int __stdcall EXAMPLE_DLL getbkcolor( );
int __stdcall EXAMPLE_DLL getcolor( );
void __stdcall EXAMPLE_DLL getfillpattern( char *pattern );
void __stdcall EXAMPLE_DLL getfillsettings( fillsettingstype *fillinfo );
void __stdcall EXAMPLE_DLL getlinesettings( linesettingstype *lineinfo );
int __stdcall EXAMPLE_DLL getmaxcolor( );
int __stdcall EXAMPLE_DLL getmaxheight( );
int __stdcall EXAMPLE_DLL getmaxwidth( );
int __stdcall EXAMPLE_DLL getmaxx( );
int __stdcall EXAMPLE_DLL getmaxy( );
bool __stdcall EXAMPLE_DLL getrefreshingbgi( );
int __stdcall EXAMPLE_DLL getwindowheight( );
int __stdcall EXAMPLE_DLL getwindowwidth( );
int __stdcall EXAMPLE_DLL getpixel( int x, int y );
void __stdcall EXAMPLE_DLL getviewsettings( viewporttype *viewport );
int __stdcall EXAMPLE_DLL getx( );
int __stdcall EXAMPLE_DLL gety( );
void __stdcall EXAMPLE_DLL moverel( int dx, int dy );
void __stdcall EXAMPLE_DLL moveto( int x, int y );
void __stdcall EXAMPLE_DLL refreshbgi(int left, int top, int right, int bottom);
void __stdcall EXAMPLE_DLL refreshallbgi( );    
void __stdcall EXAMPLE_DLL setbkcolor( int color );
void __stdcall EXAMPLE_DLL setbkmode(int mode);
void __stdcall EXAMPLE_DLL setcolor( int color );
void __stdcall EXAMPLE_DLL setfillpattern( const char *upattern, int color );
void __stdcall EXAMPLE_DLL setfillstyle( int pattern, int color );
void __stdcall EXAMPLE_DLL setlinestyle( int linestyle, unsigned upattern, int thickness );
void __stdcall EXAMPLE_DLL setrefreshingbgi(bool value);
void __stdcall EXAMPLE_DLL setviewport( int left, int top, int right, int bottom, int clip );
void __stdcall EXAMPLE_DLL setwritemode( int mode );

// Window Creation / Graphics Manipulation
void __stdcall EXAMPLE_DLL closegraph( int wid=ALL_WINDOWS );
void __stdcall EXAMPLE_DLL detectgraph( int *graphdriver, int *graphmode );
void __stdcall EXAMPLE_DLL getaspectratio( int *xasp, int *yasp );
const char* __stdcall EXAMPLE_DLL getdrivername( );
int __stdcall EXAMPLE_DLL getgraphmode( );
int __stdcall EXAMPLE_DLL getmaxmode( );
const char* __stdcall EXAMPLE_DLL getmodename( int mode_number );
void __stdcall EXAMPLE_DLL getmoderange( int graphdriver, int *lomode, int *himode );
void __stdcall EXAMPLE_DLL graphdefaults( );
const char* __stdcall EXAMPLE_DLL grapherrormsg( int errorcode );
int __stdcall EXAMPLE_DLL graphresult( );
void __stdcall EXAMPLE_DLL initgraph( int *graphdriver, int *graphmode, const char *pathtodriver );
int __stdcall EXAMPLE_DLL initwindow
    ( int width, int height, const char* title="Windows BGI", int left=0, int top=0, bool dbflag=false, bool closeflag=true );
int __stdcall EXAMPLE_DLL installuserdriver( const char *name, int *fp );    // Not available in WinBGI
int __stdcall EXAMPLE_DLL installuserfont( const char *name );               // Not available in WinBGI
int __stdcall EXAMPLE_DLL registerbgidriver( void *driver );           // Not available in WinBGI
int __stdcall EXAMPLE_DLL registerbgifont( void *font );               // Not available in WinBGI
void __stdcall EXAMPLE_DLL restorecrtmode( );
void __stdcall EXAMPLE_DLL setaspectratio( int xasp, int yasp );
unsigned __stdcall EXAMPLE_DLL setgraphbufsize( unsigned bufsize );    // Not available in WinBGI
void __stdcall EXAMPLE_DLL setgraphmode( int mode );
void __stdcall EXAMPLE_DLL showerrorbox( const char *msg = NULL );

// User Interaction
int __stdcall EXAMPLE_DLL _bgi_getch( );
#define getch _bgi_getch
int __stdcall EXAMPLE_DLL _bgi_kbhit( );
#define kbhit _bgi_kbhit
int __stdcall EXAMPLE_DLL _bgi_controlkeystate( );
#define controlkeystate _bgi_controlkeystate

// User-Controlled Window Functions (winbgi.cpp)
int __stdcall EXAMPLE_DLL getcurrentwindow( );
void __stdcall EXAMPLE_DLL setcurrentwindow( int window );
    
// Double buffering support (winbgi.cpp)
int __stdcall EXAMPLE_DLL getactivepage( );
int __stdcall EXAMPLE_DLL getvisualpage( );
void __stdcall EXAMPLE_DLL setactivepage( int page );
void __stdcall EXAMPLE_DLL setvisualpage( int page );
void __stdcall EXAMPLE_DLL swapbuffers( );

// Image Functions (drawing.cpp)
typedef void IMAGE;
unsigned __stdcall EXAMPLE_DLL imagesize( int left, int top, int right, int bottom );
void __stdcall EXAMPLE_DLL getimage( int left, int top, int right, int bottom, IMAGE *bitmap );
void __stdcall EXAMPLE_DLL putimage( int left, int top, IMAGE *bitmap, int op );
void __stdcall EXAMPLE_DLL printimage(
    const char* title=NULL,	
    double width_inches=7, double border_left_inches=0.75, double border_top_inches=0.75,
    int left=0, int top=0, int right=INT_MAX, int bottom=INT_MAX,
    bool active=true, HWND hwnd=NULL
    );
void __stdcall EXAMPLE_DLL readimagefile(
    const char* filename=NULL,
    int left=0, int top=0, int right=INT_MAX, int bottom=INT_MAX
    );
void __stdcall EXAMPLE_DLL writeimagefile(
    const char* filename=NULL,
    int left=0, int top=0, int right=INT_MAX, int bottom=INT_MAX,
    bool active=true, HWND hwnd=NULL
    );

// Text Functions (text.cpp)
void __stdcall EXAMPLE_DLL gettextsettings(struct textsettingstype *texttypeinfo);
void __stdcall EXAMPLE_DLL outtext(const char *textstring);
void __stdcall EXAMPLE_DLL outtextxy(int x, int y, const char *textstring);
void __stdcall EXAMPLE_DLL settextjustify(int horiz, int vert);
void __stdcall EXAMPLE_DLL settextstyle(int font, int direction, int charsize);
void __stdcall EXAMPLE_DLL setusercharsize(int multx, int divx, int multy, int divy);
int __stdcall EXAMPLE_DLL textheight(const char *textstring);
int __stdcall EXAMPLE_DLL textwidth(const char *textstring);
extern EXAMPLE_DLL std::ostringstream bgiout;    
void __stdcall EXAMPLE_DLL outstream(std::ostringstream& out=bgiout);
void __stdcall EXAMPLE_DLL outstreamxy(int x, int y, std::ostringstream& out=bgiout);    
    
// Mouse Functions (mouse.cpp)
void __stdcall EXAMPLE_DLL clearmouseclick( int kind );
void __stdcall EXAMPLE_DLL clearresizeevent( );
void __stdcall EXAMPLE_DLL getmouseclick( int kind, int& x, int& y );
bool __stdcall EXAMPLE_DLL ismouseclick( int kind );
bool __stdcall EXAMPLE_DLL isresizeevent( );
int __stdcall EXAMPLE_DLL mousex( );
int __stdcall EXAMPLE_DLL mousey( );
int __stdcall EXAMPLE_DLL mousebuttons( );
void __stdcall EXAMPLE_DLL registermousehandler( int kind, void h( int, int ) );
void __stdcall EXAMPLE_DLL setmousequeuestatus( int kind, bool status=true );

// Palette Functions
palettetype* __stdcall EXAMPLE_DLL getdefaultpalette( );
void __stdcall EXAMPLE_DLL getpalette( palettetype *palette );
int __stdcall EXAMPLE_DLL getpalettesize( );
void __stdcall EXAMPLE_DLL setallpalette( palettetype *palette );
void __stdcall EXAMPLE_DLL setpalette( int colornum, int color );
void __stdcall EXAMPLE_DLL setrgbpalette( int colornum, int red, int green, int blue );

int __stdcall EXAMPLE_DLL imageheight(IMAGE *);
int __stdcall EXAMPLE_DLL imagewidth(IMAGE *);
IMAGE* __stdcall EXAMPLE_DLL createimage(int,int);
void __stdcall EXAMPLE_DLL freeimage(IMAGE *);
void __stdcall EXAMPLE_DLL imageputpixel(IMAGE *,int,int,int);
int __stdcall EXAMPLE_DLL imagegetpixel(IMAGE *,int,int);
IMAGE* __stdcall EXAMPLE_DLL loadBMP(const char *);
void __stdcall EXAMPLE_DLL saveBMP(const char *, IMAGE *);

// Color Macros
#define IS_BGI_COLOR(v)     ( ((v) >= 0) && ((v) < 16) )
#define IS_RGB_COLOR(v)     ( (v) & 0x03000000 )
#define RED_VALUE(v)        __stdcall EXAMPLE_DLL int(GetRValue( converttorgb(v) ))
#define GREEN_VALUE(v)      __stdcall EXAMPLE_DLL int(GetGValue( converttorgb(v) ))
#define BLUE_VALUE(v)       __stdcall EXAMPLE_DLL int(GetBValue( converttorgb(v) ))
#undef COLOR
int __stdcall EXAMPLE_DLL COLOR(int r, int g, int b); // No longer a macro

#ifdef __cplusplus
}
#endif
// ---------------------------------------------------------------------------

#endif // WINBGI_H

