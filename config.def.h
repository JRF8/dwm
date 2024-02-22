/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;            /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;         /* 0 means no bar */
static const int topbar             = 1;          /* 0 means bottom bar */
static char font[]            = "Jetbrains Mono:size=10";
static char dmenufont[]       = "monospace:size=10";
static const char *fonts[]          = { font };
static char color0[]           = "#222222";
static char color1[]       = "#444444";
static char color2[]           = "#bbbbbb";
static char color3[]            = "#eeeeee";
static char color4[]        = "#005577";
static char color5[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { color0, color1, color2 },
       [SchemeSel]  = { color1,  color0,  color5  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"thunar", NULL };
const char *spcmd3[] = {"pavucontrol", NULL};
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"thunar",    spcmd2},
  {"pavucontrol", spcmd3},
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "?"};

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       tags mask     isfloating   monitor */
	{ "firefox",  		"Navigator",       NULL,       1 << 1,       0,           -1 },
	{ "Chromium",  		NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Minitube", 		NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Freetube", 		NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Kodi", 		NULL,       NULL,       1 << 3,       0,           -1 },
	{ "mpv", 		NULL,       NULL,       1 << 3,       0,           -1 },
	{ "discord", 		NULL,       NULL,       1 << 5,       0,           -1 },
	{ "Element", 		NULL,       NULL,       1 << 5,       0,           -1 },
	{ "St",       		"st",       NULL,       1 << 0,       0,           -1 },
	{ "code-oss", 		NULL,		NULL,		1 << 6,		  0,		   -1 },
	{ "Signal", 		NULL,		NULL,		1 << 5,		  0,		   -1 },
	{ "nuclear", 		NULL,		NULL,		1 << 3,		  0,		   -1 },
	{ "Meld",		NULL,		NULL,		1 << 6,		  0,		   -1 },
	{ "libreoffice",		NULL,		NULL,		1 << 6,		  0,		   -1 },
	{ "Joplin",		NULL,		NULL,		1 << 6,		  0,		   -1 },
	{ "org.remmina.Remmina", NULL,		NULL,		1 << 4,		  0,		   -1 },
	{ "xfreerdp", NULL,		NULL,		1 << 4,		  1,		   0 },
	{ "Surf",  		"surf",       NULL,       1 << 1,       0,           -1 },
	{ "Vertcoin-Qt",  		NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Lutris",  		NULL,       NULL,       1 << 7,       0,           -1 },
	{ "Chiaki",  		NULL,       NULL,       1 << 7,       0,           -1 },
	{ "explorer.exe",  		NULL,       NULL,       1 << 7,       0,           -1 },
	{ "bisq.desktop.app.BisqApp",  		NULL,       NULL,       1 << 8,       0,           -1 },
	{ "QjackCtl",  		NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Gimp",  		NULL,       NULL,       1 << 6,       0,           -1 },
	{ "Brave-browser",  		"brave-browser",       NULL,       1 << 1,       0,           -1 },
	{ "KeePassXC",  		NULL,       NULL,       1 << 2,       0,           -1 },
	{ "St",  		"spotify-tui",       NULL,       1 << 3,      0,           -1 },
	{ NULL,		  "spterm",		NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "thunar",		NULL,		SPTAG(1),		1,			 -1 },
  { NULL,     "pavucontrol", NULL,   SPTAG(2),   1,  -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *screenclipcmd[] = {"screenclip", "CLIP", NULL };
static const char *screensavecmd[] = {"screenclip", "SAVE", NULL };
// Audio Commands
static const char *mutecmd[] = { "volctl", "3", NULL };
static const char *volupcmd[] = { "volctl", "2", NULL };
static const char *voldowncmd[] = { "volctl", "1", NULL };
/* Control Media Players */
static const char *medplaypausecmd[] = { "playerctl", "play-pause", NULL };
static const char *mednextcmd[] = { "playerctl", "next", NULL };
static const char *medprevcmd[] = { "playerctl", "previous", NULL };
// brightness commands
static const char *brightupcmd[] = {"xbacklight", "-inc", "5", NULL };
static const char *brightdowncmd[] = {"xbacklight", "-dec", "5", NULL };
static const char *kbdupcmd[] = {"keylight", "up", NULL };
static const char *kbddowncmd[] = {"keylight", "down", NULL };
static const char *fnlkcmd[] = {"fnlockctl",  NULL };
//static const char *kbdupcmd[] = {"xbacklight", "-inc", "5", NULL };
//static const char *kbddowncmd[] = {"xbacklight", "-dec", "5", NULL };
// slock key
static const char *slockcmd[] = { "slock", NULL };
// wallpaper key
static const char *wallpapercmd[] = { "wallpaper", NULL };
// power key
static const char *powercmd[] = { "poweroptions", NULL};
// resolution selection
static const char *resolutioncmd[] = { "resolution", NULL};
// browser command
static const char *browsercmd[] = { "chromium", NULL};
/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "color0",        STRING,  &color0 },
		{ "color1",    STRING,  &color1 },
		{ "color2",        STRING,  &color2 },
		{ "color3",         STRING,  &color3 },
		{ "color4",     STRING,  &color4 },
		{ "color5",         STRING,  &color5 },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

#include "movestack.c"
#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_j,      movestack,	   {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_k,      movestack,	   {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[10]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_g,      spawn,          {.v = screenclipcmd } },
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = screensavecmd } },
	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	TAGKEYS(                        XK_1,                      0)
	{ MODKEY,            			XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            			XK_x,	   togglescratch,  {.ui = 2 } },
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
// Adding Audio Keys
  { 0,                XF86XK_AudioMute,        spawn,        {.v = mutecmd } },
  { 0,                XF86XK_AudioLowerVolume, spawn,        {.v = voldowncmd } },
  { 0,                XF86XK_AudioRaiseVolume, spawn,        {.v = volupcmd } },
/* Keybindings for Media play/pause/next/previous */
  { 0,		      XF86XK_AudioPlay,        spawn,        {.v = medplaypausecmd } },
  { 0,                XF86XK_AudioNext,        spawn,        {.v = mednextcmd } },
  { 0,                XF86XK_AudioPrev,        spawn,        {.v = medprevcmd } },
// Adding brightness keys
  { 0,                XF86XK_MonBrightnessUp,  spawn,        {.v = brightupcmd } },
  { 0,                XF86XK_MonBrightnessDown, spawn,      {.v = brightdowncmd } },
  { 0,                XF86XK_KbdBrightnessUp, spawn,      {.v = kbdupcmd } },
  { 0,                XF86XK_KbdBrightnessDown, spawn,      {.v = kbddowncmd } },
// Adding slock key
  { MODKEY,	      XK_slash,		spawn,		  {.v = slockcmd } },
// Adding wallpaper key
  { MODKEY,	      XK_w,		spawn,		  {.v = wallpapercmd } },
// Adding new Function lock key combination
  { MODKEY|Mod1Mask,	      XK_f,		spawn,		  {.v = fnlkcmd } },
// Adding power functions
  { 0,  XF86XK_PowerOff, spawn, { .v = powercmd } },
// Adding screen resolution selector
  { MODKEY,       XK_r, spawn, {.v = resolutioncmd } },
// Adding command to launch browser
  { MODKEY,       XK_c, spawn, {.v = browsercmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,       resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

