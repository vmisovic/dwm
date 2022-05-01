/* See LICENSE file for copyright and license details. */
//#include <X11/XF86keysym.h>
#define XF86_AudioMute			0x1008ff12
#define XF86_AudioMicMute		0x1008ffb2
#define XF86_AudioRaiseVolume	0x1008ff13
#define XF86_AudioLowerVolume	0x1008ff11
#define XF86XK_MonBrightnessUp   0x1008FF02  // Monitor/panel brightness
#define XF86XK_MonBrightnessDown 0x1008FF03  // Monitor/panel brightness

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12", "SpaceMono Nerd Font Mono:style=Regular"};
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_green[]       = "#98971a";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_green,  col_green  },
};

/* tagging */
static const char *tags[] = { "", "", "", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 6,       0,           -1 },
	{ "Viber",    NULL,       NULL,       1 << 2,       0,           -1 },
	{ "discord",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ NULL,       NULL, "Microsoft Teams",1 << 2,       0,           -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-c", "-l", "8", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *htopcmd[]  = { "st", "htop" , NULL };
static const char *ttyclockcmd[]  = { "st", "tty-clock", "-cbsB" , NULL };
static const char *firefoxcmd[] = {"firefox", NULL};
static const char *vibercmd[] = {"viber", NULL};
static const char *discordcmd[] = {"discord", NULL};
static const char *teamscmd[] = {"teams", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,				XK_a,      spawn,          {.v = firefoxcmd} },
	{ MODKEY|ShiftMask,				XK_h,      spawn,          {.v = htopcmd} },
	{ MODKEY|ShiftMask,				XK_t,      spawn,          {.v = ttyclockcmd} },	
	{ MODKEY,                       XK_F1,     spawn,          {.v = vibercmd } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = discordcmd } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = teamscmd } },

	{ 0,XF86_AudioMute,				spawn, SHCMD("pulseaudio-ctl mute; pkill -RTMIN+10 dwmblocks;")},	
	{ 0,XF86_AudioMicMute,			spawn, SHCMD("pulseaudio-ctl mute-input; pkill -RTMIN+10 dwmblocks;")},
	{ 0,XF86_AudioRaiseVolume,		spawn, SHCMD("pulseaudio-ctl up; pkill -RTMIN+10 dwmblocks;")},
	{ 0,XF86_AudioLowerVolume,		spawn, SHCMD("pulseaudio-ctl down; pkill -RTMIN+10 dwmblocks;")},
	{ 0,XF86XK_MonBrightnessUp,		spawn, SHCMD("xbacklight -inc 10; pkill -RTMIN+11 dwmblocks;")},
	{ 0,XF86XK_MonBrightnessDown,	spawn, SHCMD("xbacklight -dec 10; pkill -RTMIN+11 dwmblocks;")},
    { 0,XK_Print,                   spawn, SHCMD("maim -g 1600x900+0+0 | xclip -selection clipboard -t image/png; xclip -out -selection clipboard > ~/Pictures/Screenshots/$(date '+%F-%H-%M-%S').png")},
    { MODKEY,XK_Print,  	        spawn, SHCMD("maim -su | xclip -selection clipboard -t image/png; xclip -out -selection clipboard > ~/Pictures/Screenshots/$(date '+%F-%H-%M-%S').png")},

    { MODKEY,XK_space,              spawn, SHCMD("pkill -RTMIN+12 dwmblocks;")},
	{ MODKEY,XK_e,        spawn, SHCMD("/home/vlada/suckless/exit.sh;")},

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_s,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

