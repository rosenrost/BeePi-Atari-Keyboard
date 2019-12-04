Here you can find all the BeePi stuff to be installed on the Raspberry Pi to make the Atari keyboard work when you are using bash or whatever on the host system.

## Keyboard configurations

The folders etc and usr contain files to map certain characters to the proper keys on your Atari keyboard. The file structure is the same as on your SD card.

`/etc/default/keyboard` is a new keyboard definition to use a keyboard layout which you can find in `/usr/share/X11/xkb/symbols/atari` and maps certain characters to the proper keys on your Atari keyboard.

## Emulator configurations

You find configuration files for ARAnyM and Hatari in the folder emulators/config.

`hatari/keymap.[lang]` are key mapping files for Hatari. To use one of them, copy the desired file to `/home/pi/.system/hatari` and apply the following changes to the `[Keyboard]` section of `hatari.cfg`:
- Change `nKeymapType` to `2`
- Set `szMappingFileName` to the full path of the keymap file

## Issues

Due to a bug in Hatari, the "non-US-backslash" key (that is the key next to the left shift key on non-US keyboards) opens the Hatari menu instead of printing the expected character. I tried to explain it here: http://www.atari-forum.com/viewtopic.php?f=51&t=37917

The bug still exists in Hatari 2.2.1.

You can find precompiled patched versions for Hatari 2.0.0 (which is the version BeePi uses) and Hatari 2.2.1 in `emulators/patches`. Use them at your own risk. They work for me, but I cannot guarantee anything.

Or you can patch Hatari yourself by editing `src/keymap.c` and adding three lines in `Keymap_KeyDown()` and `Keymap_KeyUp()` after the `LOG_TRACE()` call:

```
if (symkey == 0 && sdlkey->scancode == 100) {
       symkey = sdlkey->sym = '<';
}
```
