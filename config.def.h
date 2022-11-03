/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 20;       /* gap pixel between windows */
static const unsigned int gapstep   = 4;       /* gap pixel increment/decrement */
static const unsigned int snap      = 8;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int user_bh            = 25;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

static const char *fonts[]          = {
/*        "MesloLGL NF:size=13:antialias=true:autohint=true"
*/
    "Font Awesome 5 Free:size=12",
    "Sans:size=12",
};

static const char dmenufont[]       = "monospace:size=14";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#555555";
static const char col_gray3[]       = "#333333";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#222222";
static const unsigned int baralpha = 60;
static const unsigned int borderalpha = 0;
static const char *colors[][3]      = {
            /*               fg         bg         border   */
            [SchemeNorm] = { col_gray4, col_gray1, col_gray3 },
            [SchemeSel]  = { col_gray4, col_gray1,  col_gray2 },
            [SchemeStatus]  = { col_gray4, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	        [SchemeTagsSel]  = { col_gray4, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
            [SchemeTagsNorm]  = { col_gray4, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
            [SchemeInfoSel]  = { col_gray4, col_gray1,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
            [SchemeInfoNorm]  = { col_gray4, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeStatus]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm]  = { OPAQUE, baralpha, borderalpha },
    // Manually added to make info section of bar translucent
    // - Requires dwm-alpha and dwm-colorbar patches
	[SchemeInfoSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeInfoNorm]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     switchtotag	isfloating   monitor */
    // { "Gimp",     NULL,       NULL,       0,            1,			0,			-1 },
     { "Firefox",  NULL,       NULL,       1 << 4,       1,           0,			-1 },
     { "qutebrowser", NULL,    NULL,       1 << 4,       1,           0,			-1 },
     { "VSCodium", NULL,       NULL,       1 << 3,       1,           0,			-1 },
     { "Code",     NULL,       NULL,       1 << 3,       1,           0,			-1 },
     { "Thunderbird", NULL,    NULL,       1 << 2,       1,           0,			-1 },
	 { "Pcmanfm",     NULL,    NULL,       1 << 1,       1,           0,			-1 },
  // { "st-256color", NULL,    NULL,       0,            0,           0,			-1 },
};

/* layout(s) */
static const float mfact     = 0.54; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      deck },
	{ "",      monocle },
	{ "",      NULL },    /* no layout function means floating behavior */

};

/* key definitions */
#define MODKEY Mod4Mask //***
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alactritty", NULL };
#include "shift-tools.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	// { MODKEY,                       XK_d,      spawn,          SHCMD("~/Scripts/rofi-main.sh") }, //***
	// { MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("~/Scripts/rofi-scripts/rofi-powermenu.sh") }, //***
	// { MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("~/Scripts/dmenu_search.sh") }, //***
	// { MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("alacritty") }, //***
//	{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("x-terminal-emulator") }, //***
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_period, incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_comma,  incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,		                XK_q,      killclient,     {0} }, //***
//	{ MODKEY|Mod1Mask,              XK_j,	   viewtoright,    {0} }, //***
//	{ MODKEY|Mod1Mask,              XK_k,	   viewtoleft,     {0} }, //***
	{ MODKEY|ControlMask,           XK_j,	   viewtoright,    {0} }, //***
	{ MODKEY|ControlMask,           XK_k,	   viewtoleft,     {0} }, //***
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_j,	   shifttag,          { .i = +1 } }, //***
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_k,	   shifttag,          { .i = -1 } }, //***
	{ MODKEY|ControlMask|ShiftMask, XK_j,	   shifttag,          { .i = +1 } }, //***
	{ MODKEY|ControlMask|ShiftMask, XK_k,	   shifttag,          { .i = -1 } }, //***
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,		                XK_e,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} }, //***
	{ MODKEY,                       XK_space,  togglefloating, {0} }, //***
	{ MODKEY,  			            XK_f,      togglefullscr,  {0} },
//  { MODKEY|Mod1Mask,              XK_comma,  cyclelayout,    {.i = -1 } },
//  { MODKEY|Mod1Mask,              XK_period, cyclelayout,    {.i = +1 } },
    { MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
    { MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_bracketleft,  focusmon, {.i = -1 } },
	{ MODKEY,                       XK_bracketright, focusmon, {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,  tagmon,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_bracketright, tagmon,   {.i = +1 } },
//	{ MODKEY|Mod1Mask,              XK_equal,  incrgaps,       {0} }, //***
//	{ MODKEY|Mod1Mask,              XK_minus,  decrgaps,       {0} }, //***
//	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} }, //***
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, //***
	{ MODKEY|ShiftMask,             XK_equal,  incrgaps,       {0} }, //***
	{ MODKEY|ShiftMask,             XK_minus,  decrgaps,       {0} }, //***
	{ MODKEY|ControlMask|ShiftMask, XK_0,      togglegaps,     {0} }, //***
	{ MODKEY|ControlMask|ShiftMask, XK_equal,      defaultgaps,    {0} }, //***
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
	// { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("~/Scripts/i3lock-fork/i3lock-fork.sh") }, //***
//	{ ControlMask|Mod1Mask,         XK_t,      spawn,          SHCMD("alacritty -e /usr/bin/zsh") }, //***
	// { MODKEY|ControlMask,           XK_t,      spawn,          SHCMD("alacritty") }, //***
	// { MODKEY,                       XK_F1,     spawn,          SHCMD("~/Scripts/brightness-control-down.sh") }, //***
	// { MODKEY,                       XK_F2,     spawn,          SHCMD("~/Scripts/brightness-control-up.sh") }, //***
    // { MODKEY|ControlMask,           XK_F1,     spawn,          SHCMD("~/Scripts/brightness-control-off.sh") }, //***
	// { MODKEY|ControlMask,           XK_F2,     spawn,          SHCMD("~/Scripts/brightness-control-on.sh") }, //***
	// { MODKEY,                       XK_F5,     spawn,          SHCMD("~/Scripts/volume-control-down.sh") }, //***
	// { MODKEY,                       XK_F6,     spawn,          SHCMD("~/Scripts/volume-control-up.sh") }, //***
	// { MODKEY,                       XK_F4,     spawn,          SHCMD("~/Scripts/volume-toggle-mute.sh") }, //***
	// { MODKEY,                       XK_F7,     spawn,          SHCMD("~/Scripts/jabra-toggle.sh") }, //***
	// { MODKEY,                       XK_v,      spawn,          SHCMD("clipmenu") }, //***
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

