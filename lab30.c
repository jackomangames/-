/* As 0-X game with computer pathner */
/* Graphic Functions */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <stdio.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

static Display* dpy;     /* X Display */
static GC gc[2];         /* Graphic Context */
static Window root;      /* Main root window */
static Window** box;     /* box (NYxNX) window array address */
static Window* row;      /* NY row window  box containe array  */ 
static unsigned** pos;   /* Marker position NYx2 array address */
static int X0=0;         /* main root wintow x-location */
static int Y0=0;         /* main root wintow y-location */
static unsigned NX=4;   /* Default Boxes' number in each row */
static unsigned NY=2;    /* Default Row's number in game desk */
static char mark[20]; /* Marker symbols */
static int X1 = 0;
static int Y1 = 0;
static int dx[4]={0,0,-1,1};
static int dy[4]={-1,1,0,0};
static int BW=45;     /* Box width */
static int BH=45;     /* Box height */
static unsigned AW=40;     /* Arrow width */
static unsigned AH=40;     /* Arrow height */
static int SW = 16;
static int SH = 16;
static int CPW = 8;
static int IX=0;     /* indicator xcoord */
static int IY=0;     /* indicator ycoord */

int relink(void** p, void* r, void** b) {
pos = (unsigned**) p;
row = (Window* ) r;
box = (Window**) b;
return(0);
} /* relink */

/* redraw exposed markered box  */
int movebox(int ddx,int ddy)
{
	int i=0;
	XMoveWindow(dpy, box[0][0], X1=MAX(MIN(X1+ddx,SW-BW),0),Y1=MAX(MIN(Y1+ddy,SH-BH),0));
	i=sprintf(mark,"%d:%d",X1,Y1);
	XClearWindow(dpy, box[0][0]);
	XDrawString(dpy, box[0][0], gc[0], IX, IY, mark, i);
	return 0;
}



int rebox(XEvent* ev) {
int i, ddx,ddy,bx,by;

for(i=0; i < NX; i++)
{
    if(ev->xexpose.window == box[1][i])
    {
	ddx=dx[i];
	ddy=dy[i];
	movebox(ddx,ddy);
    }
    if(ev->xexpose.window == box[0][0])
    {
	bx = ev->xbutton.x;
	by = ev->xbutton.y;
	if ((bx<IX+15&&bx>IX-15)&&(by>IY-7&&by<IY+7))
		return 1;
    }
    
}

XDrawString(dpy, box[1][0], gc[0], 12, 16, "Up", 2);
XDrawString(dpy, box[1][1], gc[0], 8, 16, "Down", 4);
XDrawString(dpy, box[1][2], gc[0], 8, 16, "Left", 4);
XDrawString(dpy, box[1][3], gc[0], 8, 16, "Right", 5);
return 0;
} /* rebox */


int xcustom() {
static unsigned XSP=4;     /* x-space between 2 boxes in any row */
static unsigned YSP=4;     /* y-space between 2 rows */

int x, y;                  /* windows' location */ 
unsigned w, h;             /* windows' size */
int dx, dy;                /* interwindow distance */ 
int src;                   /* screen number */
int depth;                 /* screen depth */
XSetWindowAttributes attr; /* created Window attributes */
XSizeHints hint;           /* WM connection structure */ 
XFontStruct* fn;           /* Font parameters structure */
char* fontname = "6x12";   /* default font name */
int i,j;                   /* windows' index */

/* get X defaults */

src = DefaultScreen(dpy);
depth = DefaultDepth(dpy, src);
gc[0] = DefaultGC(dpy, src);

/* Font custom */

if((fn = XLoadQueryFont(dpy, fontname)) == NULL)
  return(puts("Incorrect FontStruct id"));
XSetFont(dpy, gc[0], fn->fid);



/* Main root window */

SW = MIN(BW*18,800);
SH = MIN(BH*14,600);
CPW = AW*3.7;
IX=BW/2-15;
IY=BH/2;


w = SW+CPW;
h = SH;
attr.override_redirect = False;
attr.background_pixel = WhitePixel(dpy, src);
x = X0; y = Y0;
root = XCreateWindow(dpy, DefaultRootWindow(dpy), x, y, w, h,
                     1, depth, InputOutput, CopyFromParent,
                     (CWOverrideRedirect | CWBackPixel),  &attr);
hint.flags = (PMinSize | PMaxSize | PPosition);
hint.min_width = hint.max_width = w;
hint.min_height = hint.max_height = h;
hint.x = x; hint.y = y;
XSetNormalHints(dpy, root, &hint);

/* box row  root's subwindow */

attr.override_redirect = True;
attr.background_pixel = WhitePixel(dpy, src);
attr.event_mask = (ButtonPressMask | KeyPressMask);

//create main window
row[0] = XCreateWindow(dpy, root, 0, 0, SW, SH, 0, depth,
                         InputOutput, CopyFromParent,
           (CWOverrideRedirect | CWBackPixel | CWEventMask),  &attr);
attr.background_pixel = 0x00AAAA;
//create control panel
row[1] = XCreateWindow(dpy, root, SW, 0, CPW, SH, 0, depth,
                         InputOutput, CopyFromParent,
           (CWOverrideRedirect | CWBackPixel | CWEventMask),  &attr);

/* Box row's subwindows */

attr.override_redirect = True;
attr.background_pixel = 0x00FFFF; /* WhitePixel(dpy, src); */
attr.event_mask = (KeyPressMask | ExposureMask |ButtonPressMask);
w = BW; h = BH; 

//moving box
box[0][0] = XCreateWindow(dpy, row[0], 0, 0, BW, BH, 1,
                              depth, InputOutput, CopyFromParent,
                (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);

//arrows
attr.background_pixel = 0xAAFFAA;
box[1][0] = XCreateWindow(dpy, row[1], AW/5+AW+4, AH, AW, AH, 1,
                              depth, InputOutput, CopyFromParent,
                (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
XDrawString(dpy, box[1][0], gc[0], 12, 12, "Up", 2);
box[1][1] = XCreateWindow(dpy, row[1], AW/5+AW+4, AH*2+4, AW, AH, 1,
                              depth, InputOutput, CopyFromParent,
                (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
XDrawString(dpy, box[1][1], gc[0], 2, 16, "Down", 4);
box[1][2] = XCreateWindow(dpy, row[1], AW/5, AH*2+4, AW, AH, 1,
                              depth, InputOutput, CopyFromParent,
                (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
XDrawString(dpy, box[1][2], gc[0], 2, 16, "Left", 4);
box[1][3] = XCreateWindow(dpy, row[1], AW/5+2*AW+8, AH*2+4, AW, AH, 1,
                              depth, InputOutput, CopyFromParent,
                (CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
XDrawString(dpy, box[1][3], gc[0], 2, 16, "Right", 5);
/* Display windows */

XMapWindow(dpy, root);
XMapSubwindows(dpy, root);
for(i=0; i<NY; i++)
  XMapSubwindows(dpy, row[i]);

XStoreName(dpy, root, "lab3");

/* Create clear GC */

gc[1] = XCreateGC(dpy, root, 0, 0);
XCopyGC(dpy, gc[0], GCFont, gc[1]);
XSetForeground(dpy, gc[1], 0x00FFFF); /* WhitePixel(dpy, src)); */

return(0);
}

/* KeyBoard Driver */

int kbdrive(XEvent* ev) {
KeySym sym;
int i;
XLookupString((XKeyEvent*) ev, NULL, 0, &sym, NULL);

switch(sym) {
  case XK_Escape: 
                  break;
  case XK_q:
  case XK_Q: if(ev->xkey.state & ControlMask)   
               return(1);
             break;
  case XK_Down: movebox(0,1);
	     return(0);
	     break;
  case XK_Up: movebox(0,-1);
	     return(0);
	     break;
  case XK_Right: movebox(1,0);
	     return(0);
	     break;
  case XK_Left: movebox(-1,0);
	     return(0);
	     break;

  default:   break;
}
return(0);
}

/* Event dispatcher */

int dispatch() {
XEvent event;      /* Event structure */
int flag = 0;      /* exit flag */
while(flag == 0) {
  XNextEvent(dpy, &event);
  switch(event.type) {
    case Expose:      rebox(&event);
                      break;
    case KeyPress: { flag = kbdrive(&event); break; }
                   
    case ButtonPress: flag=rebox(&event);
                      break;

    default: break;
  } /* switch */
} /* while */
return(0);
} /* dispatch */

/* Main function */

int main(int argc, char* argv[]) {
if(argc < 3)
  fprintf(stderr, "Default: xpat 16x4+0+0\n");  
else
{
	BH=atoi(argv[1]);
	BW=atoi(argv[2]);
}
alloc(NX, NY);
dpy = XOpenDisplay(NULL);
if(xcustom() > 0)
  return(1);

dispatch();
XDestroySubwindows(dpy, root);
XDestroyWindow(dpy, root);
XCloseDisplay(dpy);
dealloc(pos, box, row);
return(0);
} /* main */
