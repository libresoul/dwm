#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 1;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
/*static const char *fonts[]          = { "Jetbrains Mono:size=10", "Font Awesome 6 Brands:size=10" }; */
static const char *fonts[]          = { "Jetbrains Mono:size=10", "Noto Sans Sinhala:size=10", "Font Awesome 6 Brands:size=10" };
/* static const char *fonts[]          = { "monospace:size=10" };  */
static const char dmenufont[]       = "Jetbrains Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#4c566a";
static const char col_border[]      = "#eeeeee";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { "1", "2", "3", "4", "5" }; 

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class    		instance	title           	     tags mask  isfloating  isterminal  noswallow  monitor */                  		 
	{ "Gimp",               NULL,           NULL,           	     0,         1,          0,           0,        -1 },
	{ "Firefox",            NULL,           NULL,           	     0,    	0,          0,          -1,        -1 },
	{ "discord",            NULL,           NULL,           	     2,    	0,          0,          -1,        -1 },
	{ "st-256color",      	NULL,           NULL,           	     0,         0,          1,           0,        -1 },
	{ "konsole",      	NULL,           NULL,           	     0,         0,          0,           0,        -1 },
	{ "Pavucontrol",      	NULL,           NULL,           	     0,         1,          0,           0,        -1 },
	{ "Thunar",      	NULL,           NULL,           	     0,         1,          0,           0,        -1 },
	{ "feh",      		NULL,           NULL,           	     0,         1,          0,           0,        -1 },
	{ "vlc",      		NULL,           "Current Media Information", 0,         1,          0,           0,        -1 },
	{ NULL,      		NULL,           "Picture in picture",	     0,         1,          0,           0,        -1 },
	{ "steam",      	NULL,           NULL,          		     4,         0,          0,          -1,        -1 }, 
	{ "steam",     		NULL,           "Steam Settings",            4,         1,          0,          -1,        -1 },  
	{ "steam",              NULL,           "Friends List",              4,         1,          0,          -1,        -1 },
	{ "steam",              NULL,           "Steam - Browser",           4,         1,          0,          -1,        -1 },
	{ "steam_app_.*",      	NULL,           NULL,          		     0,         0,          0,          -1,        -1 }, 
	{ NULL,     		NULL,           "Event Tester",	             0,         0,          0,           1,        -1 }, /* xev */ 
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int statusall   = 1;    /* 1 means status is shown in all bars, not just active monitor */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define WINKEY Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|WINKEY,                KEY,      nview,          {.ui = 1 << TAG} }, \
	{ MODKEY|WINKEY|ControlMask,    KEY,      ntoggleview,    {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *brupcmd[] = { "brightnessctl", "set", "10%+", NULL };
static const char *brfineupcmd[] = { "brightnessctl", "set", "5%+", NULL };
static const char *brdowncmd[] = { "brightnessctl", "set", "10%-", NULL };
static const char *brfinedowncmd[] = { "brightnessctl", "set", "5%-", NULL };
static const char *volupcmd[] = { "amixer", "-D", "pulse", "sset", "Master", "10%+", NULL };
static const char *volfineupcmd[] = { "amixer", "-D", "pulse", "sset", "Master", "5%+", NULL };
static const char *voldowncmd[] = { "amixer", "-D", "pulse", "sset", "Master", "10%-", NULL };
static const char *volfinedowncmd[] = { "amixer", "-D", "pulse", "sset", "Master", "5%-", NULL };
static const char *voltogglecmd[] = { "amixer", "-q", "set", "Master", "toggle", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          {.v = volupcmd } },
	{ ShiftMask,         XF86XK_AudioRaiseVolume,      spawn,          {.v = volfineupcmd } },
	{ 0,         XF86XK_AudioLowerVolume,      spawn,          {.v = voldowncmd } },
	{ ShiftMask,         XF86XK_AudioLowerVolume,      spawn,          {.v = volfinedowncmd } },
	{ 0,         	    XF86XK_AudioMute,      spawn,          {.v = voltogglecmd } },
	{ 0,          XF86XK_MonBrightnessUp,      spawn,          {.v = brupcmd } },
	{ 0,        XF86XK_MonBrightnessDown,      spawn,          {.v = brdowncmd } },
	{ ShiftMask,          XF86XK_MonBrightnessUp,      spawn,          {.v = brfineupcmd } },
	{ ShiftMask,        XF86XK_MonBrightnessDown,      spawn,          {.v = brfinedowncmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_s, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,    swapfocus,      {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,             		XK_e,      spawn,          SHCMD("thunar") },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("discord") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("celluloid") },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("thorium-browser") },
	{ MODKEY|ControlMask|ShiftMask, XK_b,      spawn,          SHCMD("thorium-browser --incognito") },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("pavucontrol") },
	{ MODKEY,                       XK_v,      spawn,          SHCMD("xfce4-clipman-history") },
	{ 0,                  		XK_Print,  spawn,          SHCMD("xfce4-screenshooter") },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("pkill -u $USER") },
	{ MODKEY,            XF86XK_AudioPrev,     spawn,          SHCMD("~/.scripts/powermenu.sh") },
	{ MODKEY,                  	XK_F4,     spawn,          SHCMD("~/.scripts/powermenu.sh") },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkMonNum,            0,              Button1,        focusmon,       {.i = +1} },
	{ ClkMonNum,            0,              Button3,        focusmon,       {.i = -1} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY|WINKEY,  Button1,        nview,          {0} },
	{ ClkTagBar,            MODKEY|WINKEY,  Button3,        ntoggleview,    {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

