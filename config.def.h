/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 8;			/* snap pixel */
static const unsigned int gappih = 20;	/* horiz inner gap between windows */
static const unsigned int gappiv = 20;	/* vert inner gap between windows */
static const unsigned int gappoh = 20;	/* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 20;	/* vert outer gap between windows and screen edge */
static const int smartgaps_fact = 1;		/* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar = 1;						/* 0 means no bar */
static const int topbar = 0;						/* 0 means bottom bar */
static const int bar_height = 25;				/* 0 means derive from font, >= 1 explicit height */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon = 'A';
static const char buttonbar[] = "";

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype = INDICATOR_NONE;
static int floatindicatortype = INDICATOR_TOP_LEFT_SQUARE;
static const char *fonts[] = {
		"MesloLGM Nerd Font:pixelsize=14:antialias=true:autohint=true",
		// Symbola font required to prevent crashes when trying to display some characters
		"Symbola:style=Regular"
		"monospace:size=11",
};
static const char dmenufont[] = "monospace:size=11";

static char c000000[] = "#000000"; // placeholder value

static char normfgcolor[] = "#bbbbbb";
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#222222";
static char normfloatcolor[] = "#222222";

static char selfgcolor[] = "#eeeeee";
static char selbgcolor[] = "#333333";
static char selbordercolor[] = "#555555";
static char selfloatcolor[] = "#333333";

static char titlenormfgcolor[] = "#bbbbbb";
static char titlenormbgcolor[] = "#222222";
static char titlenormbordercolor[] = "#222222";
static char titlenormfloatcolor[] = "#222222";

static char titleselfgcolor[] = "#eeeeee";
static char titleselbgcolor[] = "#333333";
static char titleselbordercolor[] = "#333333";
static char titleselfloatcolor[] = "#333333";

static char tagsnormfgcolor[] = "#bbbbbb";
static char tagsnormbgcolor[] = "#222222";
static char tagsnormbordercolor[] = "#222222";
static char tagsnormfloatcolor[] = "#222222";

static char tagsselfgcolor[] = "#eeeeee";
static char tagsselbgcolor[] = "#333333";
static char tagsselbordercolor[] = "#333333";
static char tagsselfloatcolor[] = "#333333";

static char hidnormfgcolor[] = "#333333";
static char hidselfgcolor[] = "#227799";
static char hidnormbgcolor[] = "#222222";
static char hidselbgcolor[] = "#222222";

static char urgfgcolor[] = "#bbbbbb";
static char urgbgcolor[] = "#222222";
static char urgbordercolor[] = "#ff0000";
static char urgfloatcolor[] = "#222222";

static const unsigned int baralpha = 60;
static const unsigned int borderalpha = 0;
static const unsigned int alphas[][3] = {
		/*                       fg      bg        border     */
		[SchemeNorm] = {OPAQUE, baralpha, borderalpha},
		[SchemeSel] = {OPAQUE, baralpha, borderalpha},
		[SchemeTitleNorm] = {OPAQUE, baralpha, borderalpha},
		[SchemeTitleSel] = {OPAQUE, baralpha, borderalpha},
		[SchemeTagsNorm] = {OPAQUE, baralpha, borderalpha},
		[SchemeTagsSel] = {OPAQUE, baralpha, borderalpha},
		[SchemeHidNorm] = {OPAQUE, baralpha, borderalpha},
		[SchemeHidSel] = {OPAQUE, baralpha, borderalpha},
		[SchemeUrg] = {OPAQUE, baralpha, borderalpha},
};

static char *colors[][ColCount] = {
		/*                       fg                bg                border                float */
		[SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor, normfloatcolor},
		[SchemeSel] = {selfgcolor, selbgcolor, selbordercolor, selfloatcolor},
		[SchemeTitleNorm] = {titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor},
		[SchemeTitleSel] = {titleselfgcolor, titleselbgcolor, titleselbordercolor, titleselfloatcolor},
		[SchemeTagsNorm] = {tagsnormfgcolor, tagsnormbgcolor, tagsnormbordercolor, tagsnormfloatcolor},
		[SchemeTagsSel] = {tagsselfgcolor, tagsselbgcolor, tagsselbordercolor, tagsselfloatcolor},
		[SchemeHidNorm] = {hidnormfgcolor, hidnormbgcolor, c000000, c000000},
		[SchemeHidSel] = {hidselfgcolor, hidselbgcolor, c000000, c000000},
		[SchemeUrg] = {urgfgcolor, urgbgcolor, urgbordercolor, urgfloatcolor},
};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][NUMTAGS] =
		{
				[DEFAULT_TAGS] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"},
				[ALTERNATIVE_TAGS] = {"A", "B", "C", "D", "E", "F", "G", "H", "I"},
				[ALT_TAGS_DECORATION] = {"<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>"},
};

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
		/* xprop(1):
		 *	WM_CLASS(STRING) = instance, class
		 *	WM_NAME(STRING) = title
		 *	WM_WINDOW_ROLE(STRING) = role
		 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
		 */
		{"zoom", NULL, NULL, NULL, 1 << 8, 0, -1},
		{"Lutris", NULL, NULL, NULL, 1 << 8, 0, -1},
		{"firefox", NULL, NULL, NULL, 1 << 4, 0, -1},
		{"qutebrowser", NULL, NULL, NULL, 1 << 4, 0, -1},
		{"Code", NULL, NULL, NULL, 1 << 3, 0, -1},
		{"Thunderbird", NULL, NULL, NULL, 1 << 2, 0, -1},
		{"Pcmanfm", NULL, NULL, NULL, 1 << 1, 0, -1},
		RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
				RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
						RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
								RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
										RULE(.class = "Gimp", .tags = 1 << 4)
												RULE(.class = "Firefox", .tags = 1 << 7)};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
		/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
		{-1, 0, BAR_ALIGN_LEFT, width_stbutton, draw_stbutton, click_stbutton, NULL, "statusbutton"},
		{-1, 0, BAR_ALIGN_LEFT, width_tags, draw_tags, click_tags, hover_tags, "tags"},
		{-1, 0, BAR_ALIGN_LEFT, width_ltsymbol, draw_ltsymbol, click_ltsymbol, NULL, "layout"},
		{statusmon, 0, BAR_ALIGN_RIGHT, width_status, draw_status, click_status, NULL, "status"},
		{-1, 0, BAR_ALIGN_NONE, width_awesomebar, draw_awesomebar, click_awesomebar, NULL, "awesomebar"},
};

/* layout(s) */
static const float mfact = 0.55;		 /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;				 /* number of clients in master area */
static const int nstack = 0;				 /* number of clients in primary stack area */
static const int resizehints = 0;		 /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
		/* symbol     arrange function, { nmaster, nstack, layout, master axis, stack axis, secondary stack axis, symbol func } */
		{" ", flextile, {-1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, TOP_TO_BOTTOM, 0, NULL}},	 // default tile layout
		{" ", flextile, {-1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL}}, // bstack
		{"󰯌 ", flextile, {-1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, MONOCLE, 0, NULL}},				 // deck
		{"󰯋 ", flextile, {-1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, MONOCLE, 0, NULL}},			 // deck
		{" ", flextile, {-1, -1, NO_SPLIT, MONOCLE, MONOCLE, 0, NULL}},
		// {"", NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                        \
	{MODKEY, KEY, view, {.ui = 1 << TAG}},                         \
			{MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}}, \
			{MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},          \
			{MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                       \
	{                                                      \
		.v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
	}

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
		"dmenu_run",
		"-m", dmenumon,
		"-fn", dmenufont,
		"-nb", normbgcolor,
		"-nf", normfgcolor,
		"-sb", selbgcolor,
		"-sf", selfgcolor,
		NULL};
static const char *termcmd[] = {"alacritty", NULL};

static const Key keys[] = {
		/* modifier                     key            function                argument */
		{MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
		{MODKEY, XK_b, togglebar, {0}},
		{MODKEY, XK_j, focusstack, {.i = +1}},
		{MODKEY, XK_k, focusstack, {.i = -1}},
		{MODKEY, XK_period, incnmaster, {.i = +1}},
		{MODKEY, XK_comma, incnmaster, {.i = -1}},
		{MODKEY, XK_h, setmfact, {.f = -0.05}},
		{MODKEY, XK_l, setmfact, {.f = +0.05}},
		{MODKEY, XK_Return, zoom, {0}},
		{MODKEY | ShiftMask, XK_equal, incrgaps, {.i = +1}},
		{MODKEY | ShiftMask, XK_minus, incrgaps, {.i = -1}},
		{MODKEY | ControlMask | ShiftMask, XK_0, togglegaps, {0}},
		{MODKEY | ControlMask | ShiftMask, XK_equal, defaultgaps, {0}},
		{MODKEY, XK_Tab, view, {0}},
		// { MODKEY|ControlMask,           XK_z,          showhideclient,         {0} },
		{MODKEY, XK_q, killclient, {0}},
		{MODKEY | ShiftMask, XK_q, quit, {0}},
		{MODKEY, XK_space, togglefloating, {0}},
		{MODKEY, XK_f, togglefullscreen, {0}},
		{MODKEY, XK_0, view, {.ui = ~0}},
		{MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
		{MODKEY, XK_bracketleft, focusmon, {.i = -1}},
		{MODKEY, XK_bracketright, focusmon, {.i = +1}},
		{MODKEY | ShiftMask, XK_bracketleft, tagmon, {.i = -1}},
		{MODKEY | ShiftMask, XK_bracketright, tagmon, {.i = +1}},
		{MODKEY | ControlMask, XK_k, viewtoleft, {0}},						 // note keybinding conflict with focusdir
		{MODKEY | ControlMask, XK_j, viewtoright, {0}},						 // note keybinding conflict with focusdir
		{MODKEY | ControlMask | ShiftMask, XK_k, tagtoleft, {0}},	 // note keybinding conflict with shifttag
		{MODKEY | ControlMask | ShiftMask, XK_j, tagtoright, {0}}, // note keybinding conflict with shifttag
		{MODKEY | ControlMask, XK_comma, cyclelayout, {.i = -1}},
		{MODKEY | ControlMask, XK_period, cyclelayout, {.i = +1}},
		TAGKEYS(XK_1, 0)
				TAGKEYS(XK_2, 1)
						TAGKEYS(XK_3, 2)
								TAGKEYS(XK_4, 3)
										TAGKEYS(XK_5, 4)
												TAGKEYS(XK_6, 5)
														TAGKEYS(XK_7, 6)
																TAGKEYS(XK_8, 7)
																		TAGKEYS(XK_9, 8)};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
		/* click                event mask           button          function        argument */
		// {ClkButton, 0, Button1, spawn, {.v = dmenucmd}},
		{ClkButton, 0, Button1, spawn, SHCMD("~/Scripts/rofi-main.sh")},
		{ClkLtSymbol, 0, Button1, setlayout, {0}},
		{ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
		// { ClkWinTitle,          0,                   Button1,        togglewin,      {0} },
		// { ClkWinTitle,          0,                   Button3,        showhideclient, {0} },
		{ClkWinTitle, 0, Button2, zoom, {0}},
		{ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
		{ClkClientWin, MODKEY, Button1, movemouse, {0}},
		{ClkClientWin, MODKEY, Button2, togglefloating, {0}},
		{ClkClientWin, MODKEY, Button3, resizemouse, {0}},
		{ClkTagBar, 0, Button1, view, {0}},
		{ClkTagBar, 0, Button3, toggleview, {0}},
		{ClkTagBar, MODKEY, Button1, tag, {0}},
		{ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
