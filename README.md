# How I setup KeyChron C3 Pro with QMK for Tap Dance

Thought I would share the full steps on how I resolved my C3 Pro compile issue in QMK.  

Special thanks to ANDY on the Keychron discord server (https://discord.gg/aGKucVyF) for the suggestion on rebasing with upstream master!  

## Pre-Reqs / Warning
This assumes a fresh setup on Windows 11 in QMK MSYS environment.  
No guarantee with any of these commands.  It may brick your keyboard.  You have been warned.  

## References
* QMK Setup: https://docs.qmk.fm/newbs_getting_started  
* QMK MKSYS: https://msys.qmk.fm/ 
* QMK Tap Dance: https://docs.qmk.fm/features/tap_dance  
* QMK Toolbox: https://github.com/qmk/qmk_toolbox/releases  

## Clean 
Let's start with a fresh QMK environment.  *WARNING: You saved off past QMK code, right?*

```
rm -rf qmk_firmware
```

## Download and setup latest QMK
```
git clone https://github.com/qmk/qmk_firmware.git
qmk setup -y
```

## Add remote Keychron project

```
cd qmk_firmware
git remote add  Keychron https://github.com/Keychron/qmk_firmware.git
git fetch Keychron
```

I did see the following errors:
> Fetching submodule lib/chibios  
> fatal: remote error: upload-pack: not our ref c717c1b99809b9ea27a63ba955ba426170563fcb  
> Errors during submodule fetch:  
> lib/chibios  

## Show the branches available and switch to the C3 Pro branch
```
git remote show Keychron
git checkout keychron_c3_pro
```

## Rebase from upstream master

To fix some compile dependencies due to the age of the Keychron Branch, we need to rebase from the upstream QMK master branch.  

```
git rebase remotes/origin/master keychron_c3_pro
```

As of 28-Jul-2024, I ran across two conflicts that needed to be manually resolved.  The conflicts were around the config.h file in the "red" directroy.   I removed the "HEAD" lines and kept the upstream changes.  

After each merge, you will need to add the modified config.h to the rebase process.  Git may open up a txt file for changelog, but I just saved that with default wording.  I am not planning on merging this upstream.   

```
git add keyboards/keychron/c3_pro/ansi/red/config.h
git rebase --continue
```

At the end of the rebase, you will see a message like.  

```
Successfully rebased and updated refs/heads/keychron_c3_pro. 
```         

## Verify C3 Pro is known to QMK
```
qmk list-keyboards | grep -i c3_pro   ## shows c3_pro
```

## Compile with default values to verify all dependencies are correct
```
qmk compile --clean -kb keychron/c3_pro/ansi/red -km keychron
```

## FUN BEGINS - New KeyMap and Tap Dance

```
qmk new-keymap -km f-eq-ma -kb keychron/c3_pro/ansi/red
```

This will create the folder `keyboards/keychron/c3_pro/ansi/red/keymaps/f-eq-ma` with some pre-populated files.  We are going to replace them.  

First the `rules.mk` file.  The first three lines were from the "keychron" keymap, the last line is the enablement of Tap Dance.  
```
VIA_ENABLE = yes
VPATH += keyboards/keychron/common
SRC += keychron_common.c

TAP_DANCE_ENABLE = yes
```

To build my "keymap.c" file, I copied the keychron keymap, then updated to support my Tap Dance code from another project.

```
cp -p keyboards/keychron/c3_pro/ansi/red/keymaps/keychron/keyboard.c keyboards/keychron/c3_pro/ansi/red/keymaps/f-eq-ma/keyboard.c
```

You can see from the keymap.c file in this project my final setup.

Customizations:
* Removed Mac layers
* Layer 0 (Windows)
  * Tap Dance F7, F8, F9, F11, F12 - Various common strings I hate to type in
  * Tap Dance F10 - 2 taps = string1, 3 taps = string2
  * Print Screen -> F16 (remapped in Windows AutoHotKey to iTunes pause/play toggle, i.e. ctl-space)
  * Scroll Lock -> F17 (remapped in Windows AutoHotKey to iTunes mini player toggle, i.e. ctl-shift-M)
  * Pause Break -> F19 (remapped in Windows AutoHotKey to iTunes next, i.e. ctl-right arrow)
* Layer 1 (Windows Function)
  * I removed all of the Keychron functions on top row to match my other keyboard (may revisit these later).
  * I kept the Keychron mapping for the back lighting
  * I removed the Keychron toggle between Windows and Mac 
  * FN-Print Screen -> Volume Down
  * FN-Scroll Lock -> Volume Up
  * FN-Pause Break -> F14 (remapped in Windows AutoHotKey to iTunes back, i.e. ctl-left arrow)

Better understanding of my Windows AutoHotKey setup, see https://github.com/f-eq-ma/bdn9.  

## Compile for Tap Dance
```
qmk compile --clean -kb keychron/c3_pro/ansi/red -km f-eq-ma
```
This will create a binary in the "qmk_firmware" folder called "keychron_c3_pro_ansi_red_f-eq-ma.bin"

## QMK Toolbox to Flash Keyboard
Open QMK Toolbox application, browse to load the binary firmware file.

With the C3 Pro disconnected, hold down the ESC key, then plug in the keyboard.  This should activate the Flash button on the QMK toolbox.  Flash the keyboard.  Once done, close the QMK toolbox.

## Test the keys
Open Notepad++ and start tap dancing to make sure the strings you want are displayed.

## Oh Shit, it's bricked....
Follow the instructions at https://www.keychron.com/blogs/archived/how-to-factory-reset-or-flash-your-qmk-via-enabled-keychron-c3-pro-keyboard  

