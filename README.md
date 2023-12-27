# ct-dwm-fork

A custom build of dwm; which is an extremely fast, small, and dynamic window manager for X. Theme colours are translucent greyscale; so it should work well with any desktop theme and compositor (such as picom). Includes the following patches:

- BAR_AWESOMEBAR_PATCH
- BAR_LTSYMBOL_PATCH
- BAR_STATUS_PATCH
- BAR_STATUSBUTTON_PATCH
- BAR_TAGS_PATCH
- BAR_WINTITLE_PATCH
- BAR_ALPHA_PATCH
- BAR_CENTEREDWINDOWNAME_PATCH
- BAR_HEIGHT_PATCH
- ALWAYSCENTER_PATCH
- CYCLELAYOUTS_PATCH
- FOCUSADJACENTTAG_PATCH
- FULLSCREEN_PATCH
- PERTAG_PATCH
- TOGGLEFULLSCREEN_PATCH
- VANITYGAPS_PATCH

## Requirements

- [alacritty](https://github.com/alacritty/alacritty)
- [rofi](https://github.com/davatorium/rofi)
- Fonts:
  - MesloLGM Nerd
  - Symbola
- In order to build dwm you need the Xlib header files.

## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm

## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
