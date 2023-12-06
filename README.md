# dwm - dynamic window manager

dwm is a minimal, extreamly fast window manager for X with no eye candies whatsoever.

These are my configuration changes while I wa s patching dwm using the patches in the `/patche` directory.. The relevent startup scripts can be found in `/scripts`.

# Requirements

in order to build dwm you need the Xlib header files along with some X11 extensions.

# Installation

install the following dependencies[^1] for dwm from your using your package manager.

    libx11-dev libxft-dev libxinerama-dev libxrandr-dev

[^1]:the above libraries are specifically for Debian.. if you on another Linux distribution the package names would be slightly different. As a workaround you can install dwm from the repositories using your package manager because then all the dependencies for your system should be installed and after that you could remove dwm or just simply let it be replaced with the initial build.


Afterwards enter the following command to build ans install dwm (if necessary as root):

    make clean install

# Starting dwm

Add the following line to your `.xinitrc` to start dwm using startx:

    exec dwm

or you can grab my [xinitrc](https://github.com/libresoul/dwm/blob/main/xinitrc)

If you are using a Display manager you may need to create a `dwm.desktop` file in `/usr/share/Xsessions` directory and symlink your `.xinitrc` to `.xprofile`

# Configuration

The configuration is done by editing your custom config.h file and recompiling the source code.
