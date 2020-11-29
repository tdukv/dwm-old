/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
//static const char *fonts[]          = { "Liberation Mono:style=Regular:pixelsize=14:antialias=true:autohint=true", "Symbola:style=Regular:pixelsize=14:antialias=true:autohint=true" };
static const char *fonts[] =
  { "Liberation Mono:style=Regular:pixelsize=14:antialias=true:autohint=true",
    "NotoEmoji Nerd Font:style=Regular:pixelsize=12:antialias=true:autohint=true",
    "Symbola:style=Regular:pixelsize=12:antialias=true:autohint=true" };
//static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char termcol0[] = "#000000"; /* black   */
static char termcol1[] = "#ff0000"; /* red     */
static char termcol2[] = "#33ff00"; /* green   */
static char termcol3[] = "#ff0099"; /* yellow  */
static char termcol4[] = "#0066ff"; /* blue    */
static char termcol5[] = "#cc00ff"; /* magenta */
static char termcol6[] = "#00ffff"; /* cyan    */
static char termcol7[] = "#d0d0d0"; /* white   */
static char termcol8[]  = "#808080"; /* black   */
static char termcol9[]  = "#ff0000"; /* red     */
static char termcol10[] = "#33ff00"; /* green   */
static char termcol11[] = "#ff0099"; /* yellow  */
static char termcol12[] = "#0066ff"; /* blue    */
static char termcol13[] = "#cc00ff"; /* magenta */
static char termcol14[] = "#00ffff"; /* cyan    */
static char termcol15[] = "#ffffff"; /* white   */
static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title   tag mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",     NULL,     NULL,        0,         1,          0,          0,        -1 },
	{ "fehfloat", NULL,     NULL,        0,         1,          0,          1,        -1 },
	{ "trmfloat", NULL,     NULL,        0,         1,          0,          1,        -1 },
	{ "Emacs",    NULL,     NULL,        0,         0,          0,          1,        -1 },
	{ "Firefox",  NULL,     NULL,   1 << 8,         0,          0,         -1,        -1 },
	{ "st",       NULL,     NULL,        0,         0,          1,         -1,        -1 },
	{ "St",       NULL,     NULL,        0,         0,          1,         -1,        -1 },
	{ "Xmessage", NULL,     NULL,        0,         1,          0,          1,        -1 },
	{ "XCalc",    NULL,     NULL,        0,         1,          0,          0,        -1 },
	{ NULL,       NULL,  "Event Tester", 0,         1,          0,          1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	//	{ "===",      bstackhoriz },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-c", scratchpadname, "-g", "120x34", NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";
static Key keys[] =
  {
   /* modifier         key        function       argument */
/*   { MODKEY,           XK_p,      spawn,         {.v = dmenucmd } }, */
   { MODKEY|ShiftMask, XK_Return, spawn,         {.v = termcmd } },
   { MODKEY,           XK_grave,  togglescratch, {.v = scratchpadcmd } },

   { MODKEY,           XK_b,      togglebar,     {0} },

   { MODKEY,           XK_Down,   focusstack,    {.i = +1 } },
   { MODKEY,           XK_Up,     focusstack,    {.i = -1 } },

   { MODKEY,           XK_i,      incnmaster,    {.i = +1 } },
   { MODKEY,           XK_d,      incnmaster,    {.i = -1 } },

   { MODKEY,           XK_Left,      setmfact,   {.f = -0.05} },
   { MODKEY,           XK_Right,     setmfact,   {.f = +0.05} },

   { MODKEY|ShiftMask, XK_Left,      setcfact,   {.f = +0.25} },
   { MODKEY|ShiftMask, XK_Right,     setcfact,   {.f = -0.25} },
   { MODKEY|ShiftMask, XK_BackSpace, setcfact,   {.f =  0.00} },

   { MODKEY,           XK_Return, zoom,           {0} },
   { MODKEY,           XK_Tab,    view,           {0} },
   { MODKEY|ShiftMask, XK_c,      killclient,     {0} },

   /* { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, */
   /* { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[1]} }, */
   /* { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[2]} }, */
   /* { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} }, */
   /* { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} }, */
   /* { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[5]} }, */
   /* { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[6]} }, */

   { MODKEY,   XK_t,   setlayout,   {.v = &layouts[0]} }, //tile
   { MODKEY,   XK_u,   setlayout,   {.v = &layouts[1]} }, //bstack
   { MODKEY,   XK_y,   setlayout,   {.v = &layouts[2]} }, //cntrmstr
   { MODKEY|ShiftMask,   XK_y,   setlayout,   {.v = &layouts[3]} }, //cftntrmstr
   { MODKEY,   XK_f,   setlayout,   {.v = &layouts[5]} }, //float
   { MODKEY,   XK_m,   setlayout,   {.v = &layouts[6]} }, //monocle

   { MODKEY,   XK_bracketleft,  cyclelayout, {.i = -1 } },
   { MODKEY,   XK_bracketright, cyclelayout, {.i = +1 } },

   { MODKEY|ShiftMask,   XK_space,  setlayout,      {0} },
   { MODKEY,             XK_space,  togglefloating, {0} },

   { MODKEY|Mod1Mask,           XK_Down,  moveresize, {.v = "0x 25y 0w 0h" } },
   { MODKEY|Mod1Mask,           XK_Up,    moveresize, {.v = "0x -25y 0w 0h" } },
   { MODKEY|Mod1Mask,           XK_Right, moveresize, {.v = "25x 0y 0w 0h" } },
   { MODKEY|Mod1Mask,           XK_Left,  moveresize, {.v = "-25x 0y 0w 0h" } },
   { MODKEY|Mod1Mask|ShiftMask, XK_Down,  moveresize, {.v = "0x 0y 0w 25h" } },
   { MODKEY|Mod1Mask|ShiftMask, XK_Up,    moveresize, {.v = "0x 0y 0w -25h" } },
   { MODKEY|Mod1Mask|ShiftMask, XK_Right, moveresize, {.v = "0x 0y 25w 0h" } },
   { MODKEY|Mod1Mask|ShiftMask, XK_Left,  moveresize, {.v = "0x 0y -25w 0h" } },
   { MODKEY|Mod1Mask|ShiftMask, XK_Page_Up,   moveresize, {.v = "0x 0y -25w -25h" } },
   { MODKEY|Mod1Mask|ShiftMask, XK_Page_Down, moveresize, {.v = "0x 0y 25w 25h" } },

   { MODKEY,             XK_0,    view,    {.ui = ~0 } },
   { MODKEY|ShiftMask,   XK_0,    tag,     {.ui = ~0 } },

   { MODKEY|ControlMask, XK_Down,    pushdown,    {0} },
   { MODKEY|ControlMask, XK_Up,      pushup,      {0} },

   { MODKEY|ControlMask, XK_Right,   shiftview,  { .i = +1 } },
   { MODKEY|ControlMask, XK_Left,    shiftview,  { .i = -1 } },

   { MODKEY,             XK_Page_Up,     focusmon,    {.i = -1 } },
   { MODKEY,             XK_Page_Down,   focusmon,    {.i = +1 } },
   { MODKEY|ShiftMask,   XK_Page_Up,     tagmon,      {.i = -1 } },
   { MODKEY|ShiftMask,   XK_Page_Down,   tagmon,      {.i = +1 } },

   { MODKEY|ShiftMask,   XK_Home,        setborderpx, {.i = -1 } },
   { MODKEY|ShiftMask,   XK_End,         setborderpx, {.i = +1 } },
   { MODKEY|ShiftMask,   XK_Delete,      setborderpx, {.i = 0 } },

   { MODKEY,               XK_F5,     xrdb,           {.v = NULL } },

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
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1 } },
	{ ClkLtSymbol,          0,              Button2,        layoutmenu,     {0} },

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

