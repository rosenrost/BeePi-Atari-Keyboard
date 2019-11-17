/*
  AtariKeyboard.cpp

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


#include "AtariKeyboard.h"


#ifdef _USING_HID


extern uint8_t USBPutChar(uint8_t c);


//================================================================================
//================================================================================
//	Keyboard

static const uint8_t _hidReportDescriptor[] PROGMEM =
{

    //  Keyboard
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 47
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x02,                    //   REPORT_ID (2)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)

    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right META)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)

    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)

    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x73,                    //   LOGICAL_MAXIMUM (115)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)

    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x73,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0,                          // END_COLLECTION
};


AtariKeyboard_::AtariKeyboard_()
{
	static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
	HID().AppendDescriptor(&node);
}


void
AtariKeyboard_::begin()
{
}


void
AtariKeyboard_::end()
{
}


void
AtariKeyboard_::sendReport(KeyReport* keys)
{
	HID().SendReport(2, keys, sizeof(KeyReport));
}


extern const uint8_t _asciimap[128] PROGMEM;
extern const uint8_t _asciimap_numpad[128] PROGMEM;


#define SHIFT 0x80


#if ATARI_KEYBOARD_LAYOUT == ATARI_DE
    // German layout
    const uint8_t _asciimap[128] =
    {
        0x00,             // NUL
        0x00,             // SOH
        0x00,             // STX
        0x00,             // ETX
        0x00,             // EOT
        0x00,             // ENQ
        0x00,             // ACK
        0x00,             // BEL
        0x2a,             // BS   Backspace
        0x2b,             // TAB  Tab
        0x28,             // LF   Enter
        0x00,             // VT
        0x00,             // FF
        0x00,             // CR
        0x00,             // SO
        0x00,             // SI
        0x00,             // DEL
        0x00,             // DC1
        0x00,             // DC2
        0x00,             // DC3
        0x00,             // DC4
        0x00,             // NAK
        0x00,             // SYN
        0x00,             // ETB
        0x00,             // CAN
        0x00,             // EM
        0x00,             // SUB
        0x00,             // ESC
        0x00,             // FS
        0x00,             // GS
        0x00,             // RS
        0x00,             // US

        0x2c,             // 20 ' '
        0x1e | SHIFT,     // 21 !
        0x1f | SHIFT,     // 22 "
        0x35,             // 23 #
        0x21 | SHIFT,     // 24 $
        0x22 | SHIFT,     // 25 %
        0x23 | SHIFT,     // 26 &
        0x2e,             // 27 '
        0x25 | SHIFT,     // 28 (
        0x26 | SHIFT,     // 29 )
        0x30 | SHIFT,     // 2a *
        0x30,             // 2b +
        0x36,             // 2c ,
        0x38,             // 2d -
        0x37,             // 2e .
        0x24 | SHIFT,     // 2f /
        0x27,             // 30 0
        0x1e,             // 31 1
        0x1f,             // 32 2
        0x20,             // 33 3
        0x21,             // 34 4
        0x22,             // 35 5
        0x23,             // 36 6
        0x24,             // 37 7
        0x25,             // 38 8
        0x26,             // 39 9
        0x37 | SHIFT,     // 3a :
        0x36 | SHIFT,     // 3b ;
        0x64,             // 3c <
        0x27 | SHIFT,     // 3d =
        0x64 | SHIFT,     // 3e >
        0x2d | SHIFT,     // 3f ?
        0x14,             // 40 @
        0x04 | SHIFT,     // 41 A
        0x05 | SHIFT,     // 42 B
        0x06 | SHIFT,     // 43 C
        0x07 | SHIFT,     // 44 D
        0x08 | SHIFT,     // 45 E
        0x09 | SHIFT,     // 46 F
        0x0a | SHIFT,     // 47 G
        0x0b | SHIFT,     // 48 H
        0x0c | SHIFT,     // 49 I
        0x0d | SHIFT,     // 4a J
        0x0e | SHIFT,     // 4b K
        0x0f | SHIFT,     // 4c L
        0x10 | SHIFT,     // 4d M
        0x11 | SHIFT,     // 4e N
        0x12 | SHIFT,     // 4f O
        0x13 | SHIFT,     // 50 P
        0x14 | SHIFT,     // 51 Q
        0x15 | SHIFT,     // 52 R
        0x16 | SHIFT,     // 53 S
        0x17 | SHIFT,     // 54 T
        0x18 | SHIFT,     // 55 U
        0x19 | SHIFT,     // 56 V
        0x1a | SHIFT,     // 57 W
        0x1b | SHIFT,     // 58 X
        0x1d | SHIFT,     // 59 Y
        0x1c | SHIFT,     // 5a Z
        0x25,             // 5b [
        0x2d | 0x86,      // 5c bslash
        0x26,             // 5d ]
        0x35 | SHIFT,     // 5e ^
        0x38 | SHIFT,     // 5f _
        0x2e | SHIFT,     // 60 `
        0x04,             // 61 a
        0x05,             // 62 b
        0x06,             // 63 c
        0x07,             // 64 d
        0x08,             // 65 e
        0x09,             // 66 f
        0x0a,             // 67 g
        0x0b,             // 68 h
        0x0c,             // 69 i
        0x0d,             // 6a j
        0x0e,             // 6b k
        0x0f,             // 6c l
        0x10,             // 6d m
        0x11,             // 6e n
        0x12,             // 6f o
        0x13,             // 70 p
        0x14,             // 71 q
        0x15,             // 72 r
        0x16,             // 73 s
        0x17,             // 74 t
        0x18,             // 75 u
        0x19,             // 76 v
        0x1a,             // 77 w
        0x1b,             // 78 x
        0x1d,             // 79 y
        0x1c,             // 7a z
        0x2f,             // 7b {
        0x31 | SHIFT,     // 7c |
        0x2e,             // 7d }
        0x31,             // 7e ~
        0x00              // 7f DEL
    };
    const uint8_t _asciimap_numpad[128] =
    {
        0x00,             // NUL
        0x00,             // SOH
        0x00,             // STX
        0x00,             // ETX
        0x00,             // EOT
        0x00,             // ENQ
        0x00,             // ACK
        0x00,             // BEL
        0x00,             // BS   Backspace
        0x00,             // TAB  Tab
        0x00,             // LF   Enter
        0x00,             // VT
        0x00,             // FF
        ARD_KPENTER,      // CR
        0x00,             // SO
        0x00,             // SI
        0x00,             // DEL
        0x00,             // DC1
        0x00,             // DC2
        0x00,             // DC3
        0x00,             // DC4
        0x00,             // NAK
        0x00,             // SYN
        0x00,             // ETB
        0x00,             // CAN
        0x00,             // EM
        0x00,             // SUB
        0x00,             // ESC
        0x00,             // FS
        0x00,             // GS
        0x00,             // RS
        0x00,             // US
        0x00,             // 20 ' '
        0x00,             // 21 !
        0x00,             // 22 "
        0x00,             // 23 #
        0x00,             // 24 $
        0x00,             // 25 %
        0x00,             // 26 &
        0x00,             // 27 '
        0x25 | SHIFT,     // 28 (
        0x26 | SHIFT,     // 29 )
        ARD_KPASTERISK,   // 2a *
        ARD_KPPLUS,       // 2b +
        0x00,             // 2c ,
        ARD_KPMINUS,      // 2d -
        ARD_KPDOT,        // 2e .
        ARD_KPSLASH,      // 2f /
        ARD_KP0,          // 30 0
        ARD_KP1,          // 31 1
        ARD_KP2,          // 32 2
        ARD_KP3,          // 33 3
        ARD_KP4,          // 34 4
        ARD_KP5,          // 35 5
        ARD_KP6,          // 36 6
        ARD_KP7,          // 37 7
        ARD_KP8,          // 38 8
        ARD_KP9,          // 39 9
        0x00,             // 3a :
        0x00,             // 3b ;
        0x00,             // 3c <
        0x00,             // 3d =
        0x00,             // 3e >
        0x00,             // 3f ?
        0x00,             // 40 @
        0x00,             // 41 A
        0x00,             // 42 B
        0x00,             // 43 C
        0x00,             // 44 D
        0x00,             // 45 E
        0x00,             // 46 F
        0x00,             // 47 G
        0x00,             // 48 H
        0x00,             // 49 I
        0x00,             // 4a J
        0x00,             // 4b K
        0x00,             // 4c L
        0x00,             // 4d M
        0x00,             // 4e N
        0x00,             // 4f O
        0x00,             // 50 P
        0x00,             // 51 Q
        0x00,             // 52 R
        0x00,             // 53 S
        0x00,             // 54 T
        0x00,             // 55 U
        0x00,             // 56 V
        0x00,             // 57 W
        0x00,             // 58 X
        0x00,             // 59 Y
        0x00,             // 5a Z
        0x00,             // 5b [
        0x00,             // 5c bslash
        0x00,             // 5d ]
        0x00,             // 5e ^
        0x00,             // 5f _
        0x00,             // 60 `
        0x00,             // 61 a
        0x00,             // 62 b
        0x00,             // 63 c
        0x00,             // 64 d
        0x00,             // 65 e
        0x00,             // 66 f
        0x00,             // 67 g
        0x00,             // 68 h
        0x00,             // 69 i
        0x00,             // 6a j
        0x00,             // 6b k
        0x00,             // 6c l
        0x00,             // 6d m
        0x00,             // 6e n
        0x00,             // 6f o
        0x00,             // 70 p
        0x00,             // 71 q
        0x00,             // 72 r
        0x00,             // 73 s
        0x00,             // 74 t
        0x00,             // 75 u
        0x00,             // 76 v
        0x00,             // 77 w
        0x00,             // 78 x
        0x00,             // 79 y
        0x00,             // 7a z
        0x00,             // 7b {
        0x00,             // 7c |
        0x00,             // 7d }
        0x00,             // 7e ~
        0x00              // 7f DEL
    };
#elif ATARI_KEYBOARD_LAYOUT == ATARI_UK
    // British layout
    const uint8_t _asciimap[128] =
    {
        0x00,             // NUL
        0x00,             // SOH
        0x00,             // STX
        0x00,             // ETX
        0x00,             // EOT
        0x00,             // ENQ
        0x00,             // ACK
        0x00,             // BEL
        0x2a,             // BS   Backspace
        0x2b,             // TAB  Tab
        0x28,             // LF   Enter
        0x00,             // VT
        0x00,             // FF
        0x00,             // CR
        0x00,             // SO
        0x00,             // SI
        0x00,             // DEL
        0x00,             // DC1
        0x00,             // DC2
        0x00,             // DC3
        0x00,             // DC4
        0x00,             // NAK
        0x00,             // SYN
        0x00,             // ETB
        0x00,             // CAN
        0x00,             // EM
        0x00,             // SUB
        0x00,             // ESC
        0x00,             // FS
        0x00,             // GS
        0x00,             // RS
        0x00,             // US

        0x2c,             // 20 ' '
        0x1e | SHIFT,     // 21 !
        0x34 | SHIFT,     // 22 "
        0x20 | SHIFT,     // 23 #
        0x21 | SHIFT,     // 24 $
        0x22 | SHIFT,     // 25 %
        0x24 | SHIFT,     // 26 &
        0x34,             // 27 '
        0x26 | SHIFT,     // 28 (
        0x27 | SHIFT,     // 29 )
        0x25 | SHIFT,     // 2a *
        0x26 | SHIFT,     // 2b +
        0x36,             // 2c ,
        0x38,             // 2d -
        0x37,             // 2e .
        0x24 | SHIFT,     // 2f /
        0x27,             // 30 0
        0x1e,             // 31 1
        0x1f,             // 32 2
        0x20,             // 33 3
        0x21,             // 34 4
        0x22,             // 35 5
        0x23,             // 36 6
        0x24,             // 37 7
        0x25,             // 38 8
        0x26,             // 39 9
        0x33 | SHIFT,     // 3a :
        0x33,             // 3b ;
        0x36 | SHIFT,     // 3c <
        0x2e,             // 3d =
        0x37 | SHIFT,     // 3e >
        0x38 | SHIFT,     // 3f ?
        0x1f | SHIFT,     // 40 @
        0x04 | SHIFT,     // 41 A
        0x05 | SHIFT,     // 42 B
        0x06 | SHIFT,     // 43 C
        0x07 | SHIFT,     // 44 D
        0x08 | SHIFT,     // 45 E
        0x09 | SHIFT,     // 46 F
        0x0a | SHIFT,     // 47 G
        0x0b | SHIFT,     // 48 H
        0x0c | SHIFT,     // 49 I
        0x0d | SHIFT,     // 4a J
        0x0e | SHIFT,     // 4b K
        0x0f | SHIFT,     // 4c L
        0x10 | SHIFT,     // 4d M
        0x11 | SHIFT,     // 4e N
        0x12 | SHIFT,     // 4f O
        0x13 | SHIFT,     // 50 P
        0x14 | SHIFT,     // 51 Q
        0x15 | SHIFT,     // 52 R
        0x16 | SHIFT,     // 53 S
        0x17 | SHIFT,     // 54 T
        0x18 | SHIFT,     // 55 U
        0x19 | SHIFT,     // 56 V
        0x1a | SHIFT,     // 57 W
        0x1b | SHIFT,     // 58 X
        0x1c | SHIFT,     // 59 Y
        0x1d | SHIFT,     // 5a Z
        0x2f,             // 5b [
        0x31,             // 5c bslash
        0x30,             // 5d ]
        0x23 | SHIFT,     // 5e ^
        0x2d | SHIFT,     // 5f _
        0x35,             // 60 `
        0x04,             // 61 a
        0x05,             // 62 b
        0x06,             // 63 c
        0x07,             // 64 d
        0x08,             // 65 e
        0x09,             // 66 f
        0x0a,             // 67 g
        0x0b,             // 68 h
        0x0c,             // 69 i
        0x0d,             // 6a j
        0x0e,             // 6b k
        0x0f,             // 6c l
        0x10,             // 6d m
        0x11,             // 6e n
        0x12,             // 6f o
        0x13,             // 70 p
        0x14,             // 71 q
        0x15,             // 72 r
        0x16,             // 73 s
        0x17,             // 74 t
        0x18,             // 75 u
        0x19,             // 76 v
        0x1a,             // 77 w
        0x1b,             // 78 x
        0x1c,             // 79 y
        0x1d,             // 7a z
        0x2f | SHIFT,     // 7b {
        0x31 | SHIFT,     // 7c |
        0x30 | SHIFT,     // 7d }
        0x35 | SHIFT,     // 7e ~
        0x00              // 7f DEL
    };
    const uint8_t _asciimap_numpad[128] =
    {
        0x00,             // NUL
        0x00,             // SOH
        0x00,             // STX
        0x00,             // ETX
        0x00,             // EOT
        0x00,             // ENQ
        0x00,             // ACK
        0x00,             // BEL
        0x00,             // BS   Backspace
        0x00,             // TAB  Tab
        0x00,             // LF   Enter
        0x00,             // VT
        0x00,             // FF
        ARD_KPENTER,      // CR
        0x00,             // SO
        0x00,             // SI
        0x00,             // DEL
        0x00,             // DC1
        0x00,             // DC2
        0x00,             // DC3
        0x00,             // DC4
        0x00,             // NAK
        0x00,             // SYN
        0x00,             // ETB
        0x00,             // CAN
        0x00,             // EM
        0x00,             // SUB
        0x00,             // ESC
        0x00,             // FS
        0x00,             // GS
        0x00,             // RS
        0x00,             // US
        0x00,             // 20 ' '
        0x00,             // 21 !
        0x00,             // 22 "
        0x00,             // 23 #
        0x00,             // 24 $
        0x00,             // 25 %
        0x00,             // 26 &
        0x00,             // 27 '
        0x26 | SHIFT,     // 28 (
        0x27 | SHIFT,     // 29 )
        ARD_KPASTERISK,   // 2a *
        ARD_KPPLUS,       // 2b +
        0x00,             // 2c ,
        ARD_KPMINUS,      // 2d -
        ARD_KPDOT,        // 2e .
        ARD_KPSLASH,      // 2f /
        ARD_KP0,          // 30 0
        ARD_KP1,          // 31 1
        ARD_KP2,          // 32 2
        ARD_KP3,          // 33 3
        ARD_KP4,          // 34 4
        ARD_KP5,          // 35 5
        ARD_KP6,          // 36 6
        ARD_KP7,          // 37 7
        ARD_KP8,          // 38 8
        ARD_KP9,          // 39 9
        0x00,             // 3a :
        0x00,             // 3b ;
        0x00,             // 3c <
        0x00,             // 3d =
        0x00,             // 3e >
        0x00,             // 3f ?
        0x00,             // 40 @
        0x00,             // 41 A
        0x00,             // 42 B
        0x00,             // 43 C
        0x00,             // 44 D
        0x00,             // 45 E
        0x00,             // 46 F
        0x00,             // 47 G
        0x00,             // 48 H
        0x00,             // 49 I
        0x00,             // 4a J
        0x00,             // 4b K
        0x00,             // 4c L
        0x00,             // 4d M
        0x00,             // 4e N
        0x00,             // 4f O
        0x00,             // 50 P
        0x00,             // 51 Q
        0x00,             // 52 R
        0x00,             // 53 S
        0x00,             // 54 T
        0x00,             // 55 U
        0x00,             // 56 V
        0x00,             // 57 W
        0x00,             // 58 X
        0x00,             // 59 Y
        0x00,             // 5a Z
        0x00,             // 5b [
        0x00,             // 5c bslash
        0x00,             // 5d ]
        0x00,             // 5e ^
        0x00,             // 5f _
        0x00,             // 60 `
        0x00,             // 61 a
        0x00,             // 62 b
        0x00,             // 63 c
        0x00,             // 64 d
        0x00,             // 65 e
        0x00,             // 66 f
        0x00,             // 67 g
        0x00,             // 68 h
        0x00,             // 69 i
        0x00,             // 6a j
        0x00,             // 6b k
        0x00,             // 6c l
        0x00,             // 6d m
        0x00,             // 6e n
        0x00,             // 6f o
        0x00,             // 70 p
        0x00,             // 71 q
        0x00,             // 72 r
        0x00,             // 73 s
        0x00,             // 74 t
        0x00,             // 75 u
        0x00,             // 76 v
        0x00,             // 77 w
        0x00,             // 78 x
        0x00,             // 79 y
        0x00,             // 7a z
        0x00,             // 7b {
        0x00,             // 7c |
        0x00,             // 7d }
        0x00,             // 7e ~
        0x00              // 7f DEL
    };
#else
# error "Keyboard layout not supportet!"
#endif /* ATARI_KEYBOARD_LAYOUT */


// press() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way
// USB HID works, the host acts like the key remains pressed until we
// call release(), releaseAll(), or otherwise clear the report and resend.
size_t
AtariKeyboard_::press(uint8_t k, bool numpad)
{
    if (IS_SPECIAL_KEY(k)) {
        // it's a non-printing key (not a modifier)
        k = k - START_SPECIAL_KEYS;
    } else if (IS_MODIFIER_KEY(k)) {
        // it's a modifier key
        _keyReport.modifiers |= KEY_TO_MODIFIER_MASK(k);
		k = 0x00;
	} else {
        // it's a printing key

        if (numpad) {
            k = pgm_read_byte(_asciimap_numpad + k);
        } else {
		    k = pgm_read_byte(_asciimap + k);
        }

		if (k == 0x00) {
			setWriteError();
			return 0;
		}

        if ((k & SHIFT) != 0) {
            // it's a capital letter or other character reached with shift
            _keyReport.modifiers |= MOD_LEFT_SHIFT;
			k &= 0x7f;
		}
	}

	// Add k to the key report only if it's not already present
	// and if there is an empty slot.
	if (_keyReport.keys[0] != k && _keyReport.keys[1] != k &&
		_keyReport.keys[2] != k && _keyReport.keys[3] != k &&
		_keyReport.keys[4] != k && _keyReport.keys[5] != k
       )
    {
        register int i;

		for (i = 0; i < 6; ++i) {
			if (_keyReport.keys[i] == 0x00) {
				_keyReport.keys[i] = k;
				break;
			}
		}

		if (i == 6) {
			setWriteError();
			return 0;
		}
	}

	sendReport(&_keyReport);

    return 1;
}


// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t
AtariKeyboard_::release(uint8_t k, bool numpad)
{
    if (IS_SPECIAL_KEY(k)) {
        // it's a non-printing key (not a modifier)
        k = k - START_SPECIAL_KEYS;
    } else if (IS_MODIFIER_KEY(k)) {
        // it's a modifier key
        _keyReport.modifiers &= ~KEY_TO_MODIFIER_MASK(k);
        k = 0x00;
    } else {
        // it's a printing key

        if (numpad) {
            k = pgm_read_byte(_asciimap_numpad + k);
        } else {
            k = pgm_read_byte(_asciimap + k);
        }

		if (k == 0x00) {
			return 0;
		}

        if ((k & SHIFT) != 0) {
            // it's a capital letter or other character reached with shift
            _keyReport.modifiers &= ~MOD_LEFT_SHIFT;
			k &= 0x7f;
		}
	}

	// Test the key report to see if k is present.  Clear it if it exists.
	// Check all positions in case the key is present more than once (which it shouldn't be)
	for (register int i = 0; i < 6; ++i) {
		if (k != 0 && _keyReport.keys[i] == k) {
			_keyReport.keys[i] = 0x00;
		}
	}

	sendReport(&_keyReport);

	return 1;
}


void
AtariKeyboard_::releaseAll()
{
    _keyReport.keys[0]   = 0;
    _keyReport.keys[1]   = 0;
    _keyReport.keys[2]   = 0;
    _keyReport.keys[3]   = 0;
    _keyReport.keys[4]   = 0;
    _keyReport.keys[5]   = 0;
	_keyReport.modifiers = 0;

	sendReport(&_keyReport);
}


size_t
AtariKeyboard_::write(uint8_t c)
{
    uint8_t p;

    p = press(c);  // Keydown
    release(c);    // Keyup

    return p;
}


size_t
AtariKeyboard_::write(const uint8_t *buffer, size_t size)
{
	size_t n = 0;

	while (size-- > 0) {
		if (*buffer != '\r') {
			if (write(*buffer)) {
			  ++n;
			} else {
			  break;
			}
		}

		++buffer;
	}

	return n;
}


AtariKeyboard_ AtariKeyboard;


#endif /* defined _USING_HID */
