#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 6;     /* border pixel of windows */
static const unsigned int gappx = 1;        /* gaps between windows */
static const unsigned int snap = 5;         /* snap pixel */
static const int showbar = 1;               /* 0 means no bar */
static const int topbar = 1;                /* 0 means bottom bar */
static const int usealtbar = 1;             /* 1 means use non-dwm status bar */
static const char *altbarclass = "Polybar"; /* Alternate bar class name */
static const char *alttrayname = "tray";    /* Polybar tray instance name */
static const char *altbarcmd =
    "$HOME/.dwmpobar"; /* Alternate bar launch command */
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes {
  showtab_never,
  showtab_auto,
  showtab_nmodes,
  showtab_always
};
static const int showtab = showtab_auto; /* Default tab bar show mode */
static const int toptab = False;         /* False means bottom tab bar */

static const char *fonts[] = {
    "BlexMono Nerd Font:size=9:antialias=true:autohint=true",
    "Sarasa UI SC:size=8:antialias=true:autohint=true",
    "JoyPixels:size=10:antialias=true:autohint=true"};
static const char dmenufont[] =
    "Sarasa UI SC:size=10:antialias=true:autohint=true";
static char normbgcolor[] = "#2E3440";
static char normbordercolor[] = "#3B4252";
static char normfgcolor[] = "#ECEFF4";
static char selfgcolor[] = "#D8DEE9";
static char selbordercolor[] = "#5E81AC";
static char selbgcolor[] = "#5E81AC";
static char termcol0[] = "#3b4252";  /* black   */
static char termcol1[] = "#bf616a";  /* red     */
static char termcol2[] = "#a3be8c";  /* green   */
static char termcol3[] = "#ebcb8b";  /* yellow  */
static char termcol4[] = "#81a1c1";  /* blue    */
static char termcol5[] = "#b48ead";  /* magenta */
static char termcol6[] = "#88c0d0";  /* cyan    */
static char termcol7[] = "#e5e9f0";  /* white   */
static char termcol8[] = "#4c566a";  /* black   */
static char termcol9[] = "#bf616a";  /* red     */
static char termcol10[] = "#a3be8c"; /* green   */
static char termcol11[] = "#ebcb8b"; /* yellow  */
static char termcol12[] = "#81a1c1"; /* blue    */
static char termcol13[] = "#b48ead"; /* magenta */
static char termcol14[] = "#8fbcbb"; /* cyan    */
static char termcol15[] = "#eceff4"; /* white   */
static char *termcolor[] = {
    termcol0,  termcol1,  termcol2,  termcol3,  termcol4,  termcol5,
    termcol6,  termcol7,  termcol8,  termcol9,  termcol10, termcol11,
    termcol12, termcol13, termcol14, termcol15,
};
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = {"", "", "", "", "", "", "", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class                            instance                    title tags
       mask     isfloating   monitor */
    {"jetbrains-*", "JetBrains Toolbox", NULL, 1 << 1, 1, -1},
    {"jetbrains-*", "sun-awt-X11-XFramePeer", NULL, 1 << 1, 0, -1},
    {"jetbrains-*", "jetbrains-*", "win0", 1 << 1, 1, -1},
    {"jetbrains-*", NULL, "Welcome to*", 1 << 1, 1, -1},
    {"jetbrains-*", NULL, "Welcome to*", 1 << 1, 1, -1},
    {"jetbrains-idea", NULL, NULL, 1 << 1, 0, -1},
    {"jetbrains-clion", NULL, NULL, 1 << 1, 0, -1},
    {"jetbrains-pycharm", NULL, NULL, 1 << 1, 0, -1},

    {"Google-chrome", "google-chrome", NULL, 1 << 2, 0, -1},
    {"Firefox", NULL, NULL, 1 << 2, 0, -1},
    {"Typora", NULL, NULL, 1 << 2, 0, -1},
    {"Firefox", "Toolkit", NULL, 1 << 2, 1, -1},
    {"Microsoft-edge-dev", NULL, NULL, 1 << 2, 0, -1},
    {"Microsoft-edge-beta", NULL, NULL, 1 << 2, 0, -1},
    {"crx__ikhdkkncnoglghljlkmcimlnlhkeamad", NULL, NULL, 1 << 2, 1, -1},

    {NULL, "music", NULL, 1 << 3, 0, -1},
    {NULL, "SoundConverter", NULL, 1 << 3, 0, -1},
    {"qqmusic", NULL, NULL, 1 << 3, 0, -1},
    {"Spotify", "spotify", NULL, 1 << 3, 0, -1},
    {"yesplaymusic", NULL, NULL, 1 << 3, 0, -1},
    {"Netease-cloud-music-gtk", NULL, NULL, 1 << 3, 0, -1},
    {"netease-cloud-music", NULL, NULL, 1 << 3, 0, -1},
    {"Code", NULL, NULL, 1 << 3, 0, -1},

    {"VirtualBox Machine", NULL, NULL, 1 << 4, 0, -1},
    {"VirtualBox Manager", NULL, NULL, 1 << 4, 0, -1},

    {"Qq", "qq", NULL, 1 << 5, 1, -1},
    {"Freechat", "freechat", NULL, 1 << 5, 0, -1},
    {"icalingua", "icalingua", NULL, 1 << 5, 0, -1},
    {"electron-qq", "electron-qq", NULL, 1 << 5, 0, -1},
    {"Postman", "postman", NULL, 1 << 5, 0, -1},

    {"TelegramDesktop", NULL, NULL, 1 << 6, 0, -1},

    {"qv2ray", NULL, NULL, 1 << 7, 0, -1},
    {"cfw", NULL, NULL, 1 << 7, 0, -1},
    {"qBittorrent", NULL, NULL, 1 << 7, 0, -1},
    {"glrnvim", NULL, NULL, 1 << 7, 0, -1},

    {"xdman-Main", NULL, NULL, 0, 1, -1},
    {"Nitrogen", NULL, NULL, 0, 1, -1},
    {"lxappearance", NULL, NULL, 0, 1, -1},
    {"copyq", NULL, NULL, 0, 1, -1},
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
#include "tcl.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle}, {"HHH", grid},        {"|||", tcl},
    {"TTT", bstack},  {"===", bstackhoriz},

};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }
#define CMD(cmd)                                                               \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *termcmd[] = {"kitty", "-e", "--single-instance", NULL};
static const char *termcmd[] = {"alacritty", "-e", "zellij", NULL};
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = {"st",    "-t", scratchpadname, "-g",
                                      "48x12", "-e", "cava",         NULL};

static const char *rofidruncmd[] = {"rofi", "-show", "drun", NULL};
static const char *windowswitchcmd[] = {"rofi", "-show", "window", NULL};

static const char *dmenucmd[] = {"dmenu_run_history", NULL};
static const char *clipmenucmd[] = {"clipmenu", NULL};
static const char *searchmenucmd[] = {"searchmenu", NULL};
static const char *recordmenucmd[] = {"recordmenu", NULL};

static const char *upvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "+3%",
                              NULL};
static const char *downvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "-3%",
                                NULL};
static const char *mutevol[] = {"/usr/bin/pactl", "set-sink-mute", "0",
                                "toggle", NULL};

static const char *upbrt[] = {"light", "-A", "5", NULL};
static const char *downbrt[] = {"light", "-U", "5", NULL};

static Key keys[] = {
    /* modifier                     key             function        argument */
    {MODKEY | ShiftMask, XK_Return, spawn, CMD("alacritty")},
    {Mod1Mask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_grave, togglescratch, {.v = scratchpadcmd}},
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_space, spawn, {.v = rofidruncmd}},
    {MODKEY, XK_c, spawn, {.v = clipmenucmd}},
    {MODKEY, XK_s, spawn, {.v = searchmenucmd}},
    {MODKEY, XK_r, spawn, {.v = recordmenucmd}},
    {MODKEY, XK_w, spawn, {.v = windowswitchcmd}},
    {Mod1Mask, XK_space, spawn, {.v = windowswitchcmd}},

    {MODKEY, XK_b, togglebar, {0}},

    {MODKEY | ControlMask, XK_m, focusmaster, {0}}, // 切换到主窗口

    {MODKEY, XK_n, focusstack, {.i = +1}}, // 下一个窗口
    {MODKEY, XK_m, focusstack, {.i = -1}}, // 上一个窗口

    {MODKEY, XK_minus, setmfact, {.f = -0.05}}, // 主窗口变大
    {MODKEY, XK_equal, setmfact, {.f = +0.05}}, // 主窗口变小
    {MODKEY, XK_Return, zoom, {0}},             // 放到主窗口

    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}}, // 退出窗口
    {MODKEY, XK_y, tabmode, {-1}},

    {MODKEY, XK_u, setlayout, {.v = &layouts[0]}}, // 默认模式
    {MODKEY, XK_p, setlayout, {.v = &layouts[1]}}, // 全屏（不包括状态栏）
    {MODKEY, XK_i, setlayout, {.v = &layouts[2]}}, // 上下分屏
    {MODKEY, XK_o, setlayout, {.v = &layouts[3]}}, // 浮动窗口
    {MODKEY, XK_bracketleft, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_bracketright, setlayout, {.v = &layouts[5]}},
    {MODKEY, XK_backslash, setlayout, {.v = &layouts[6]}},

    {MODKEY | ShiftMask, XK_f, fullscreen, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_F5, xrdb, {.v = NULL}},

    /* My Own App Start Ways */
    {MODKEY, XK_e, spawn, CMD("google-chrome-stable")},

    {MODKEY | ShiftMask, XK_q, spawn, CMD("xkill")},
    {MODKEY | ShiftMask, XK_s, spawn, CMD("flameshot gui")},
    {MODKEY | ShiftMask, XK_n, spawn, CMD("nemo")},

    {MODKEY | ShiftMask, XK_h, spawn, CMD("alacritty --class htop -e htop")},

    {Mod1Mask | ControlMask, XK_BackSpace, spawn, CMD("betterlockscreen -l")},

    {Mod1Mask | ShiftMask, XK_p, spawn, CMD("sh ~/.dwmpobar")},

    {Mod1Mask, XK_c, spawn, CMD("clion")},
    {Mod1Mask, XK_p, spawn, CMD("pycharm")},

    /* Switch nord and light */
    {MODKEY | ControlMask, XK_n, spawn, CMD("sh ~/.local/bin/switch n")},
    {MODKEY | ControlMask, XK_l, spawn, CMD("sh ~/.local/bin/switch l")},
    {MODKEY | ControlMask, XK_s, spawn, CMD("sh ~/.local/bin/switch-dwm")},

    /* XF86Keys */
    {0, XF86XK_AudioMute, spawn, {.v = mutevol}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = upbrt}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = downbrt}},

    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_Escape, quit, {0}},
    TAGKEYS(XK_j, 0) TAGKEYS(XK_k, 1) TAGKEYS(XK_l, 2)
        TAGKEYS(XK_semicolon, 3){MODKEY | ShiftMask, XK_r, quit, {1}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkTabBar, 0, Button1, focuswin, {0}},
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
    IPCCOMMAND(view, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(toggleview, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(tag, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(toggletag, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(tagmon, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(focusmon, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(focusstack, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(zoom, 1, {ARG_TYPE_NONE}),
    IPCCOMMAND(incnmaster, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(killclient, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(togglefloating, 1, {ARG_TYPE_NONE}),
    IPCCOMMAND(setmfact, 1, {ARG_TYPE_FLOAT}),
    IPCCOMMAND(setlayoutsafe, 1, {ARG_TYPE_PTR}),
    IPCCOMMAND(quit, 1, {ARG_TYPE_NONE})};
