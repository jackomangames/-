#include <X11/Xlib.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define OPER_WIN_WIDTH      64
#define OPER_WIN_HEIGHT     64

#define PADING_WIDTH        5

#define PLUS_POS_X          0
#define PLUS_POS_Y          0 

#define MINUS_POS_X         (OPER_WIN_WIDTH + PADING_WIDTH)
#define MINUS_POS_Y         0

#define V_POS_X             (OPER_WIN_WIDTH + PADING_WIDTH) * 2
#define V_POS_Y             0

#define H_POS_X             (OPER_WIN_WIDTH + PADING_WIDTH) * 3
#define H_POS_Y             0 

#define H_POS_X             (OPER_WIN_WIDTH + PADING_WIDTH) * 3
#define H_POS_Y             0 

#define INFO_POS_X          _G.main_win_width / 2 - OPER_WIN_WIDTH / 2
#define INFO_POS_Y          _G.main_win_height / 2 - OPER_WIN_HEIGHT / 2

#define DEFUALT_RECT_WIDTH  _G.main_win_width / 2
#define DEFUALT_RECT_HEIGHT _G.main_win_height / 2
#define DEFUALT_RECT_X      _G.main_win_width / 2 - DEFUALT_RECT_WIDTH / 2
#define DEFUALT_RECT_Y      _G.main_win_height / 2 - DEFUALT_RECT_HEIGHT / 2

typedef struct Properies {
    // Display properties
    Display* disp;
    Window root;
    int screen;
    int depth;

    // Main window properies
    Window main_win;
    GC main_gc;
    unsigned main_amask;
    XSetWindowAttributes main_attr;
    Pixmap main_pix;
    unsigned main_win_width;
    unsigned main_win_height;

    // Operate window properies
    unsigned oper_amask;
    XSetWindowAttributes oper_attr;
    Pixmap oper_pix;
    unsigned oper_win_width;
    unsigned oper_win_height;

    Window plus_win;
    GC plus_gc;
    
    Window minus_win;
    GC minus_gc;
    
    Window v_win;
    GC v_gc;

    Window h_win;
    GC h_gc;
    
    Window info_win;
    GC info_gc;
} DispProp;

DispProp _G;

void initialization(int argc, char const *argv[]);

GC create_gc(Window win);

Window create_oper_win(int x, int y);

void default_draw_main_win();
void default_draw_oper_wins();

int main(int argc, char const *argv[]) {    
    initialization(argc, argv);

    //XSetBackground(_G.disp, _G.main_gc, 255);
    //XSetForeground(_G.disp, _G.main_gc, 255);

    XSelectInput(_G.disp, _G.plus_win, ButtonPressMask | ButtonReleaseMask);
    XSelectInput(_G.disp, _G.minus_win, ButtonPressMask | ButtonReleaseMask);
    XSelectInput(_G.disp, _G.v_win, ButtonPressMask | ButtonReleaseMask);
    XSelectInput(_G.disp, _G.h_win, ButtonPressMask | ButtonReleaseMask);
    XSelectInput(_G.disp, _G.info_win, ButtonPressMask | ButtonReleaseMask);
    
    XMapWindow(_G.disp, _G.main_win);
    XMapWindow(_G.disp, _G.plus_win);
    XMapWindow(_G.disp, _G.minus_win);
    XMapWindow(_G.disp, _G.v_win);
    XMapWindow(_G.disp, _G.h_win);
    XMapWindow(_G.disp, _G.info_win);

    default_draw_main_win();
    default_draw_oper_wins();
    
    XFlush(_G.disp);

    XEvent event;
    while (1) {
        XNextEvent(_G.disp, &event);

    }

    XDestroySubwindows(_G.disp, _G.main_win);

    return 0;
}

void initialization(int argc, char const *argv[]) {
    if (argc != 3) {
        printf("Usage: program_name <width> <height>!\n");
        exit(0);
    } else {
        _G.main_win_width = atoi(argv[1]);
        _G.main_win_height = atoi(argv[2]);
        if (!_G.main_win_width || !_G.main_win_height) {
            printf("Usage: unsigned argument <width> <height>!\n");
            exit(0);
        }
    }

    _G.oper_win_width = OPER_WIN_WIDTH;
    _G.oper_win_height = OPER_WIN_HEIGHT;

    _G.disp = XOpenDisplay(NULL);
    _G.root = DefaultRootWindow(_G.disp);
    _G.screen = DefaultScreen(_G.disp);
    _G.depth = DefaultDepth(_G.disp, _G.screen);

    _G.main_amask = CWOverrideRedirect;
    _G.main_attr.override_redirect = False;
                
    _G.oper_amask = CWOverrideRedirect;
    _G.oper_attr.override_redirect = False;

    _G.main_win = XCreateSimpleWindow(_G.disp, _G.root, 0, 0, 
        _G.main_win_width, _G.main_win_height, 
        0, 0, BlackPixel(_G.disp, _G.screen));

    _G.plus_win = create_oper_win(PLUS_POS_X, PLUS_POS_Y);
    _G.minus_win = create_oper_win(MINUS_POS_X, MINUS_POS_Y);
    _G.v_win = create_oper_win(V_POS_X, V_POS_Y);
    _G.h_win = create_oper_win(H_POS_X, H_POS_Y);
    _G.info_win = create_oper_win(INFO_POS_X, INFO_POS_Y);

    _G.main_gc = create_gc(_G.main_win);
    _G.plus_gc = create_gc(_G.plus_win);
    _G.minus_gc = create_gc(_G.minus_win);
    _G.v_gc = create_gc(_G.v_win);
    _G.h_gc = create_gc(_G.h_win);
    _G.info_gc = create_gc(_G.info_win);

    //_G.main_pix = XCreatePixmap(_G.disp, _G.main_win, _G.main_win_width, _G.main_win_height, _G.depth);
    //_G.main_attr.background_pixmap = _G.main_pix;
    //_G.main_amask |= CWBackPixmap;
    //XSetWindowBackgroundPixmap(_G.disp, _G.main_win, _G.main_pix);

    //_G.oper_pix = XCreatePixmap(_G.disp, _G.oper_win, _G.oper_win_width, _G.oper_win_height, _G.depth);
    //_G.oper_attr.background_pixmap = _G.oper_pix;
    //_G.oper_amask |= CWBackPixmap;
    //XSetWindowBackgroundPixmap(_G.disp, _G.oper_win, _G.oper_pix);
              
    //_G.oper_attr.background_pixmap = _G.oper_pix;
}

Window create_oper_win(int x, int y) {
    //return XCreateWindow(_G.disp, _G.main_win, 
    //    x, y, 
    //    _G.oper_win_width, _G.oper_win_height,  1, _G.depth,
    //    InputOutput, CopyFromParent,
    //    _G.oper_amask, &_G.oper_attr);
    return XCreateSimpleWindow(_G.disp, _G.main_win, 
        x, y, 
        _G.oper_win_width, _G.oper_win_height, 
        0, 0, WhitePixel(_G.disp, _G.screen));
}

GC create_gc(Window win) {
    GC gc;
    unsigned long valuemask = 0;      
                                
    XGCValues values;         
    unsigned int line_width = 2;      
    int line_style = LineSolid;       
    int cap_style = CapButt;      
    int join_style = JoinBevel;


    gc = XCreateGC(_G.disp, win, valuemask, &values);

    //XSetLineAttributes(_G.disp, gc, line_width, line_style, cap_style, join_style);

    //XSetFillStyle(_G.disp, gc, FillSolid);

    return gc;
}

void default_draw_main_win() {
    //XSetForeground(_G.disp, _G.main_gc, WhitePixel(_G.disp, _G.screen));
    XDrawRectangle(_G.disp, _G.main_win, _G.main_gc, 
        DEFUALT_RECT_X, DEFUALT_RECT_Y, 
        DEFUALT_RECT_WIDTH, DEFUALT_RECT_HEIGHT);
}

void default_draw_oper_wins() {
    XFontStruct* font = XLoadQueryFont(_G.disp, "10x20");
    XSetFont(_G.disp, _G.plus_gc, font->fid);

    XSetForeground(_G.disp, _G.plus_gc, 255);
    XDrawString(_G.disp, _G.minus_win, _G.minus_gc, 
        0, 0, 
        "+", strlen("+"));
    XSetForeground(_G.disp, _G.minus_gc, 255);
    XDrawString(_G.disp, _G.minus_win, _G.minus_gc, 
        MINUS_POS_X, MINUS_POS_X, 
        "-", strlen("-"));
    XSetForeground(_G.disp, _G.v_gc, 255);
    XDrawString(_G.disp, _G.v_win, _G.v_gc, 
        V_POS_X, V_POS_X, 
        "v", strlen("v"));
    XSetForeground(_G.disp, _G.h_gc, 255);
    XDrawString(_G.disp, _G.h_win, _G.h_gc, 
        H_POS_X, H_POS_X, 
        "h", strlen("h"));
}
