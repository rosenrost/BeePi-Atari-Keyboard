This sketch and library enable your Arduino Leonardo to process the scan codes from a native Atari ST keyboard to suitable scan codes for the Pi running BeePi.

At the moment, only the German keyboard layout is available. I also tried to add a UK layout, but due to lack of such a device, it may have some issues.

Feel free to add your preferred layout!

The sketch is based on Kevin Peat's sketch, the library is based on the standard Arduino keyboard library.

Some new features of this sketch:

- Help is mapped to F11, Undo to F12.
- AltGr (aka right Alt) can be simulated by holding right Shift first and then CapsLock. This is useful for Hatari which allows only keys that are not available on the Atari keyboard as modifier. And, of course, non-Anglo/American users may need this key to access certain characters when using other applications on the host system (e.g. bash).
- The numpad keys are mapped to their PC counterparts (except the brackets, of course), which lets you type ASCII values to enter characters not available on your keyboard.
