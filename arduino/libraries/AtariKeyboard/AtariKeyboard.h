/*
  AtariKeyboard.h

  Copyright (c) 2019, Oliver Graf
  Based on Arduino klibrary.
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef ATARI_KEYBOARD_H
#define ATARI_KEYBOARD_H


#include "HID.h"


#ifndef _USING_HID
# warning "Using legacy HID core (non pluggable)"
#else


// add new keyboard layouts here
#define ATARI_DE  1
#define ATARI_UK  2


// uncomment your keyboard layout here
#define ATARI_KEYBOARD_LAYOUT  ATARI_DE
//#define ATARI_KEYBOARD_LAYOUT  ATARI_UK


#ifndef ATARI_KEYBOARD_LAYOUT
# define ATARI_KEYBOARD_LAYOUT  ATARI_DE
#endif /* !defined ATARI_KEYBOARD_LAYOUT */

//================================================================================
//================================================================================
// Arduino Leonardo keyboard

#define START_MODIFIER_KEYS       0x80
#define START_SPECIAL_KEYS        0x88

#define IS_MODIFIER_KEY(k)       ((k) >= START_MODIFIER_KEYS && (k) < START_SPECIAL_KEYS)
#define IS_SPECIAL_KEY(k)        ((k) >= START_SPECIAL_KEYS)

#define KEY_TO_MODIFIER_MASK(k)  (1 << ((k) - START_MODIFIER_KEYS))

// Arduino Leonardo modifier bits
#define BIT_LEFT_CTRL            0
#define BIT_LEFT_SHIFT           1
#define BIT_LEFT_ALT             2
#define BIT_LEFT_META            3
#define BIT_RIGHT_CTRL           4
#define BIT_RIGHT_SHIFT          5
#define BIT_RIGHT_ALT            6
#define BIT_RIGHT_META           7

// Arduino Leonardo modifier masks
#define MOD_LEFT_CTRL            (1 << BIT_LEFT_CTRL)
#define MOD_LEFT_SHIFT           (1 << BIT_LEFT_SHIFT)
#define MOD_LEFT_ALT             (1 << BIT_LEFT_ALT)
#define MOD_LEFT_META            (1 << BIT_LEFT_META)
#define MOD_RIGHT_CTRL           (1 << BIT_RIGHT_CTRL)
#define MOD_RIGHT_SHIFT          (1 << BIT_RIGHT_SHIFT)
#define MOD_RIGHT_ALT            (1 << BIT_RIGHT_ALT)
#define MOD_RIGHT_META           (1 << BIT_RIGHT_META)

// Arduino Leonardo modifier key codes
#define ARD_LEFT_CTRL            (START_MODIFIER_KEYS + BIT_LEFT_CTRL)
#define ARD_LEFT_SHIFT           (START_MODIFIER_KEYS + BIT_LEFT_SHIFT)
#define ARD_LEFT_ALT             (START_MODIFIER_KEYS + BIT_LEFT_ALT)
#define ARD_LEFT_META            (START_MODIFIER_KEYS + BIT_LEFT_META)
#define ARD_RIGHT_CTRL           (START_MODIFIER_KEYS + BIT_RIGHT_CTRL)
#define ARD_RIGHT_SHIFT          (START_MODIFIER_KEYS + BIT_RIGHT_SHIFT)
#define ARD_RIGHT_ALT            (START_MODIFIER_KEYS + BIT_RIGHT_ALT)
#define ARD_RIGHT_META           (START_MODIFIER_KEYS + BIT_RIGHT_META)

// Arduino Leonardo special key codes
#define ARD_UP_ARROW             0xda
#define ARD_DOWN_ARROW           0xd9
#define ARD_LEFT_ARROW           0xd8
#define ARD_RIGHT_ARROW          0xd7
#define ARD_BACKSPACE            0xb2
#define ARD_TAB                  0xb3
#define ARD_RETURN               0xb0
#define ARD_ESC                  0xb1
#define ARD_INSERT               0xd1
#define ARD_DELETE               0xd4
#define ARD_PAGE_UP              0xd3
#define ARD_PAGE_DOWN            0xd6
#define ARD_HOME                 0xd2
#define ARD_END                  0xd5
#define ARD_CAPS_LOCK            0xc1
#define ARD_PRINT_SCREEN         0xce
#define ARD_SCROLL_LOCK          0xcf
#define ARD_NUMLOCK              0x53 // Keyboard Num Lock and Clear
#define ARD_F1                   0xc2
#define ARD_F2                   0xc3
#define ARD_F3                   0xc4
#define ARD_F4                   0xc5
#define ARD_F5                   0xc6
#define ARD_F6                   0xc7
#define ARD_F7                   0xc8
#define ARD_F8                   0xc9
#define ARD_F9                   0xca
#define ARD_F10                  0xcb
#define ARD_F11                  0xcc
#define ARD_F12                  0xcd
#define ARD_F13                  0xf0
#define ARD_F14                  0xf1
#define ARD_F15                  0xf2
#define ARD_F16                  0xf3
#define ARD_F17                  0xf4
#define ARD_F18                  0xf5
#define ARD_F19                  0xf6
#define ARD_F20                  0xf7
#define ARD_F21                  0xf8
#define ARD_F22                  0xf9
#define ARD_F23                  0xfa
#define ARD_F24                  0xfb

// Arduino Leonardo umlaut key codes
#define ARD_O_UMLAUT             0xbb
#define ARD_A_UMLAUT             0xbc
#define ARD_U_UMLAUT             0xb7
#define ARD_ESZETT               0xb5

// Arduino Leonardo keypad key codes
#define ARD_KPSLASH              0x54 // Keypad /
#define ARD_KPASTERISK           0x55 // Keypad *
#define ARD_KPMINUS              0x56 // Keypad -
#define ARD_KPPLUS               0x57 // Keypad +
#define ARD_KPENTER              0x58 // Keypad ENTER
#define ARD_KP1                  0x59 // Keypad 1 and End
#define ARD_KP2                  0x5a // Keypad 2 and Down Arrow
#define ARD_KP3                  0x5b // Keypad 3 and PageDn
#define ARD_KP4                  0x5c // Keypad 4 and Left Arrow
#define ARD_KP5                  0x5d // Keypad 5
#define ARD_KP6                  0x5e // Keypad 6 and Right Arrow
#define ARD_KP7                  0x5f // Keypad 7 and Home
#define ARD_KP8                  0x60 // Keypad 8 and Up Arrow
#define ARD_KP9                  0x61 // Keypad 9 and Page Up
#define ARD_KP0                  0x62 // Keypad 0 and Insert
#define ARD_KPDOT                0x63 // Keypad . and Delete


//================================================================================
//================================================================================
// Atari ST keyboard

// Atari keyboard reset pin
#define ST_KB_RESET              4

// Atari modifier key codes
#define ST_LEFT_CTRL             0x1d
#define ST_LEFT_SHIFT            0x2a
#define ST_LEFT_ALT              0x38
#define ST_RIGHT_SHIFT           0x36
#define ST_CAPS_LOCK             0x3a

#define ST_F1                    0x3b
#define ST_F2                    0x3c
#define ST_F3                    0x3d
#define ST_F4                    0x3e
#define ST_F5                    0x3f
#define ST_F6                    0x40
#define ST_F7                    0x41
#define ST_F8                    0x42
#define ST_F9                    0x43
#define ST_F10                   0x44


//================================================================================
//================================================================================


// Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct
{
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t keys[6];
} KeyReport;


class AtariKeyboard_ : public Print
{
    public:
        AtariKeyboard_(void);

        void begin(void);
        void end(void);

        size_t write(uint8_t k);
        size_t write(const uint8_t *buffer, size_t size);

        size_t press(uint8_t k, bool keypad = false);
        size_t release(uint8_t k, bool keypad = false);
        void releaseAll(void);

    private:
        KeyReport _keyReport;
        void sendReport(KeyReport* keys);

};


extern AtariKeyboard_ AtariKeyboard;


#endif /* !defined _USING_HID */


#endif /* ATARI_KEYBOARD_H */
