#include <AtariKeyboard.h>

/*
* -------------------------------------------------------------------------
* Interface Atari ST Keyboard to USB HID Keyboard
* -------------------------------------------------------------------------
* Initial idea and some original code provided by user 'joska' of
* http://www.atari-forum.com - license unknown
* -------------------------------------------------------------------------
* Based on the sketch provided by Kevin Peat <kevin@kevinpeat.com>
* -------------------------------------------------------------------------
* Copyright Oliver Graf 2019
* atari@oliver-graf.eu
* My changes and additions are licensed public domain
* -------------------------------------------------------------------------
* Developed for use with an Arduino Leonardo as it is able to act directly
* as a USB keyboard controller so doesn't require the Arduino firmware to
* be modified as some of the other Arduinos (eg. Uno) would do
* -------------------------------------------------------------------------
*/

// uncomment to get debug messages on serial monitor
//#define DEBUG


// Keyboard auto-repeat

static uint8_t       m_last_make;       // Last make char
static unsigned long m_last_make_time;  // Last make time (milliseconds)

#define AUTO_REPEAT_DELAY  500          // Keyboard auto-repeat delay (milliseconds)
#define AUTO_REPEAT_RATE   25           // Keyboard auto-repeat rate (milliseconds)


// Keep track of modifier keys

static uint8_t m_pressed_modifiers = 0x00;

#define CONTROL                0x01
#define LEFT_ALT               0x02
#define RIGHT_ALT              0x04
#define LEFT_SHIFT             0x08
#define RIGHT_SHIFT            0x10

#define control_pressed()      ((m_pressed_modifiers & CONTROL)     != 0)
#define left_alt_pressed()     ((m_pressed_modifiers & LEFT_ALT)    != 0)
#define right_alt_pressed()    ((m_pressed_modifiers & RIGHT_ALT)   != 0)
#define left_shift_pressed()   ((m_pressed_modifiers & LEFT_SHIFT)  != 0)
#define right_shift_pressed()  ((m_pressed_modifiers & RIGHT_SHIFT) != 0)

#define press_control()        (AtariKeyboard.press(ARD_LEFT_CTRL),   m_pressed_modifiers |= CONTROL)
#define press_left_alt()       (AtariKeyboard.press(ARD_LEFT_ALT),    m_pressed_modifiers |= LEFT_ALT)
#define press_right_alt()      (AtariKeyboard.press(ARD_RIGHT_ALT),   m_pressed_modifiers |= RIGHT_ALT)
#define press_left_shift()     (AtariKeyboard.press(ARD_LEFT_SHIFT),  m_pressed_modifiers |= LEFT_SHIFT)
#define press_right_shift()    (AtariKeyboard.press(ARD_RIGHT_SHIFT), m_pressed_modifiers |= RIGHT_SHIFT)

#define release_control()      (AtariKeyboard.release(ARD_LEFT_CTRL),   m_pressed_modifiers &= ~CONTROL)
#define release_left_alt()     (AtariKeyboard.release(ARD_LEFT_ALT),    m_pressed_modifiers &= ~LEFT_ALT)
#define release_right_alt()    (AtariKeyboard.release(ARD_RIGHT_ALT),   m_pressed_modifiers &= ~RIGHT_ALT)
#define release_left_shift()   (AtariKeyboard.release(ARD_LEFT_SHIFT),  m_pressed_modifiers &= ~LEFT_SHIFT)
#define release_right_shift()  (AtariKeyboard.release(ARD_RIGHT_SHIFT), m_pressed_modifiers &= ~RIGHT_SHIFT)


// Key scancodes
// Use ST scancode as index to find the corresponding USB scancode.
// Make-codes are single byte, with some exceptions.
// These are escaped with a 0xe0 (keypad keys) byte, when this appear
// in this table a simple switch is used to look up the correct scancode.

#define KEYPAD_KEY  0xe0


#if ATARI_KEYBOARD_LAYOUT == ATARI_DE
    // German layout
    uint8_t m_scan_codes[128] =
    {
      0x00,            // (Nothing)
      ARD_ESC,         // Esc
      '1',             // 1
      '2',             // 2
      '3',             // 3
      '4',             // 4
      '5',             // 5
      '6',             // 6
      '7',             // 7
      '8',             // 8
      '9',             // 9
      '0',             // 0
      ARD_ESZETT,      // ß
      '\'',            // '
      ARD_BACKSPACE,   // Backspace
      ARD_TAB,         // Tab
      'q',             // q
      'w',             // w
      'e',             // e
      'r',             // r
      't',             // t
      'z',             // z
      'u',             // u
      'i',             // i
      'o',             // o
      'p',             // p
      ARD_U_UMLAUT,    // ü
      '+',             // +
      ARD_RETURN,      // Enter
      ARD_LEFT_CTRL,   // Control
      'a',             // a
      's',             // s
      'd',             // d
      'f',             // f
      'g',             // g
      'h',             // h
      'j',             // j
      'k',             // k
      'l',             // l
      ARD_O_UMLAUT,    // ö
      ARD_A_UMLAUT,    // ä
      '#',             // #
      ARD_LEFT_SHIFT,  // Lshift
      '~',             // ~
      'y',             // y
      'x',             // x
      'c',             // c
      'v',             // v
      'b',             // b
      'n',             // n
      'm',             // m
      ',',             // ,
      '.',             // .
      '-',             // -
      ARD_RIGHT_SHIFT, // Rshift
      0x00,            // (unused)
      ARD_LEFT_ALT,    // Alternate
      ' ',             // Space
      ARD_CAPS_LOCK,   // CapsLock
      ARD_F1,          // F1
      ARD_F2,          // F2
      ARD_F3,          // F3
      ARD_F4,          // F4
      ARD_F5,          // F5
      ARD_F6,          // F6
      ARD_F7,          // F7
      ARD_F8,          // F8
      ARD_F9,          // F9
      ARD_F10,         // F10
      0x00,            // (unused)
      0x00,            // (unused)
      ARD_HOME,        // Clr/Home
      ARD_UP_ARROW,    // Up Arrow
      0x00,            // (unused)
      KEYPAD_KEY,      // KP-
      ARD_LEFT_ARROW,  // Left Arrow
      0x00,            // (unused)
      ARD_RIGHT_ARROW, // Right Arrow
      KEYPAD_KEY,      // KP+
      0x00,            // (unused)
      ARD_DOWN_ARROW,  // Down Arrow
      0x00,            // (unused)
      ARD_INSERT,      // Insert
      ARD_DELETE,      // Delete
      0x00,            // Shift+F1
      0x00,            // Shift+F2
      0x00,            // Shift+F3
      0x00,            // Shift+F4
      0x00,            // Shift+F5
      0x00,            // Shift+F6
      0x00,            // Shift+F7
      0x00,            // Shift+F8
      0x00,            // Shift+F9
      0x00,            // Shift+F10
      0x00,            // (unused)
      0x00,            // (unused)
      '<',             // ISO Key
      ARD_F12,         // Undo (mapped to F12)
      ARD_F11,         // Help (mapped to F11)
      KEYPAD_KEY,      // KP(
      KEYPAD_KEY,      // KP)
      KEYPAD_KEY,      // KP/
      KEYPAD_KEY,      // KP*
      KEYPAD_KEY,      // KP7
      KEYPAD_KEY,      // KP8
      KEYPAD_KEY,      // KP9
      KEYPAD_KEY,      // KP4
      KEYPAD_KEY,      // KP5
      KEYPAD_KEY,      // KP6
      KEYPAD_KEY,      // KP1
      KEYPAD_KEY,      // KP2
      KEYPAD_KEY,      // KP3
      KEYPAD_KEY,      // KP0
      KEYPAD_KEY,      // KP.
      KEYPAD_KEY,      // KPEnter
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00
    };
#elif ATARI_KEYBOARD_LAYOUT == ATARI_UK
    // British layout
    uint8_t m_scan_codes[128] =
    {
      0x00,            // (Nothing)
      ARD_ESC,         // Esc
      '1',             // 1
      '2',             // 2
      '3',             // 3
      '4',             // 4
      '5',             // 5
      '6',             // 6
      '7',             // 7
      '8',             // 8
      '9',             // 9
      '0',             // 0
      '-',             // -
      '=',             // =
      ARD_BACKSPACE,   // Backspace
      ARD_TAB,         // Tab
      'q',             // q
      'w',             // w
      'e',             // e
      'r',             // r
      't',             // t
      'y',             // y
      'u',             // u
      'i',             // i
      'o',             // o
      'p',             // p
      '[',             // [
      ']',             // ]
      ARD_RETURN,      // Enter
      ARD_LEFT_CTRL,   // Control
      'a',             // a
      's',             // s
      'd',             // d
      'f',             // f
      'g',             // g
      'h',             // h
      'j',             // j
      'k',             // k
      'l',             // l
      ';',             // ;
      '\'',            // '
      '`',             // `
      ARD_LEFT_SHIFT,  // Lshift
      '~',             // ~
      'z',             // z
      'x',             // x
      'c',             // c
      'v',             // v
      'b',             // b
      'n',             // n
      'm',             // m
      ',',             // ,
      '.',             // .
      '/',             // /
      ARD_RIGHT_SHIFT, // Rshift
      0x00,            // (unused)
      ARD_LEFT_ALT,    // Alternate
      ' ',             // Space
      ARD_CAPS_LOCK,   // CapsLock
      ARD_F1,          // F1
      ARD_F2,          // F2
      ARD_F3,          // F3
      ARD_F4,          // F4
      ARD_F5,          // F5
      ARD_F6,          // F6
      ARD_F7,          // F7
      ARD_F8,          // F8
      ARD_F9,          // F9
      ARD_F10,         // F10
      0x00,            // (unused)
      0x00,            // (unused)
      ARD_HOME,        // Clr/Home
      ARD_UP_ARROW,    // Up Arrow
      0x00,            // (unused)
      KEYPAD_KEY,      // KP-
      ARD_LEFT_ARROW,  // Left Arrow
      0x00,            // (unused)
      ARD_RIGHT_ARROW, // Right Arrow
      KEYPAD_KEY,      // KP+
      0x00,            // (unused)
      ARD_DOWN_ARROW,  // Down Arrow
      0x00,            // (unused)
      ARD_INSERT,      // Insert
      ARD_DELETE,      // Delete
      0x00,            // Shift+F1
      0x00,            // Shift+F2
      0x00,            // Shift+F3
      0x00,            // Shift+F4
      0x00,            // Shift+F5
      0x00,            // Shift+F6
      0x00,            // Shift+F7
      0x00,            // Shift+F8
      0x00,            // Shift+F9
      0x00,            // Shift+F10
      0x00,            // (unused)
      0x00,            // (unused)
      '\\',            // ISO Key
      ARD_F12,         // Undo (mapped to F12)
      ARD_F11,         // Help (mapped to F11)
      KEYPAD_KEY,      // KP(
      KEYPAD_KEY,      // KP)
      KEYPAD_KEY,      // KP/
      KEYPAD_KEY,      // KP*
      KEYPAD_KEY,      // KP7
      KEYPAD_KEY,      // KP8
      KEYPAD_KEY,      // KP9
      KEYPAD_KEY,      // KP4
      KEYPAD_KEY,      // KP5
      KEYPAD_KEY,      // KP6
      KEYPAD_KEY,      // KP1
      KEYPAD_KEY,      // KP2
      KEYPAD_KEY,      // KP3
      KEYPAD_KEY,      // KP0
      KEYPAD_KEY,      // KP.
      KEYPAD_KEY,      // KPEnter
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00,            // (unused)
      0x00
    };
#else
# error "Keyboard layout not supportet!"
#endif /* ATARI_KEYBOARD_LAYOUT */


uint8_t
get_keypad_key(uint8_t key)
{
    // convert keypad scan code to ascii value

    #define KEYPAD_1_BEGIN  0x4a
    #define KEYPAD_1_END    0x4e
    #define KEYPAD_1_COUNT  (KEYPAD_1_END - KEYPAD_1_BEGIN + 1)

    static uint8_t kp1[KEYPAD_1_COUNT] = { '-', 0x00, 0x00, 0x00, '+' };

    #define KEYPAD_2_BEGIN  0x63
    #define KEYPAD_2_END    0x72
    #define KEYPAD_2_COUNT  (KEYPAD_2_END - KEYPAD_2_BEGIN + 1)

    static uint8_t kp2[KEYPAD_2_COUNT] = { '(', ')', '/', '*', '7', '8', '9', '4'
                                         , '5', '6', '1', '2', '3', '0', '.', '\r'
                                         };

    if (key >= KEYPAD_1_BEGIN && key <= KEYPAD_1_END) {
        key = kp1[key - KEYPAD_1_BEGIN];
    } else if (key >= KEYPAD_2_BEGIN && key <= KEYPAD_2_END) {
        key = kp2[key - KEYPAD_2_BEGIN];
    } else {
        key = 0x00;
    }

    return key;
}


void
setup(void)
{
    // Initialize keyboard:
    AtariKeyboard.begin();

    // Open serial port from Atari keyboard
    Serial1.begin(7812);

#ifdef DEBUG
    // Open serial port to PC
    Serial.begin(9600);
#endif

    // Reset ST keyboard
    delay(200);
    reset_st_keyboard();
    delay(200);

    // Empty serial buffer before starting
    while (Serial1.available() > 0) {
        Serial1.read();
    }
}


void
loop(void)
{
    // Process incoming Atari keypresses
    if (Serial1.available() > 0) {
        process_keypress(Serial1.read());
    }

    // Handle keyboard auto-repeat
    auto_repeat();
}


// Reset ST Keyboard
void
reset_st_keyboard(void)
{
    Serial1.print("\200\001");

    pinMode(ST_KB_RESET, OUTPUT);

    digitalWrite(ST_KB_RESET, HIGH);
    delay(20);

    digitalWrite(ST_KB_RESET, LOW);
    delay(20);

    digitalWrite(ST_KB_RESET, HIGH);
}


// Process each keypress
void
process_keypress(uint8_t key)
{
    // Keypress

    uint8_t k = key & 0x7f;

    if (k > 0x00 && k < 0x73) {
        // Break codes (other than modifiers) do not need to be sent
        // to the PC as the Leonardo keyboard interface handles that

        if ((key & 0x80) != 0) {
            // Break

            m_last_make      = 0;
            m_last_make_time = 0;

            process_modifier(key);
        } else {
            // Make

            m_last_make      = key;
            m_last_make_time = millis();
            convert_scancode(key);
        }
    }
}


// Convert from ST scancode to PC scancode
void
convert_scancode(uint8_t key)
{
    uint8_t pc_code = m_scan_codes[key & 0x7f];

#ifdef DEBUG
    uint8_t break_code = key & 0x80;
    Serial.print("Atari scancode: 0x");
    Serial.println(key, HEX);
    Serial.print("ASCII code: 0x");
    Serial.println(pc_code, HEX);
    Serial.print("Break code: 0x");
    Serial.println(break_code, HEX);

    if (m_pressed_modifiers != 0) {
        if (control_pressed())     Serial.print("CTRL ");
        if (left_alt_pressed())    Serial.print("LALT ");
        if (right_alt_pressed())   Serial.print("RALT ");
        if (left_shift_pressed())  Serial.print("LSHIFT ");
        if (right_shift_pressed()) Serial.print("RSHIFT ");
        Serial.println("");
    }
#endif

    // Handle modifier key presses

    if (!process_modifier(key)) {
        if (pc_code == KEYPAD_KEY) {
            // Special handling required for keypad keypresses

            uint8_t keypad_key = get_keypad_key(key);

#ifdef DEBUG
            Serial.print("KeyPad key: 0x");
            Serial.print(keypad_key, HEX);
            Serial.println("");
#endif

            AtariKeyboard.press(keypad_key, true);
            AtariKeyboard.release(keypad_key, true);
        } else {
            AtariKeyboard.write(pc_code);
        }
    }
}


// Process modifier keypresses
boolean
process_modifier(uint8_t key)
{
    boolean rc = false;

    // Modifier key press

    switch (key) {
        case ST_LEFT_CTRL:
            press_control();
            rc = true;
            break;

        case ST_LEFT_SHIFT:
            press_left_shift();
            rc = true;
            break;

        case ST_LEFT_ALT:
            press_left_alt();
            rc = true;
            break;

        case ST_RIGHT_SHIFT:
            press_right_shift();
            rc = true;
            break;

        case ST_CAPS_LOCK:
            if (right_shift_pressed()) {
#ifdef DEBUG
                Serial.println("RIGHT ALT");
#endif
                release_right_shift();
                press_right_alt();
            } else {
#ifdef DEBUG
                Serial.println("CAPS LOCK");
#endif
                AtariKeyboard.press(ARD_CAPS_LOCK);
            }

            rc = true;

            break;

        default:
            break;

    }

    if (!rc) {
        // Modifier key release

        switch (key & 0x7f) {
            case ST_LEFT_CTRL:
                release_control();
                rc = true;
                break;

            case ST_LEFT_SHIFT:
                release_left_shift();
                rc = true;
                break;

            case ST_LEFT_ALT:
                release_left_alt();
                rc = true;
                break;

            case ST_RIGHT_SHIFT:
                if (right_alt_pressed()) {
                    release_right_alt();
                } else {
                    release_right_shift();
                }

                rc = true;

                break;

            case ST_CAPS_LOCK:
                if (right_alt_pressed()) {
                    release_right_alt();
                } else {
                    AtariKeyboard.release(ARD_CAPS_LOCK);
                }

                rc = true;

                break;

            default:
                break;

        }
    }

    return rc;
}


// Keyboard auto repeat
void
auto_repeat(void)
{
    static unsigned long last_repeat;
    static boolean key_repeating = false;  // true if key being repeated

    // Don't want to repeat modifiers
    switch (m_last_make) {
        case ST_LEFT_CTRL:
        case ST_LEFT_SHIFT:
        case ST_RIGHT_SHIFT:
        case ST_LEFT_ALT:
        case ST_CAPS_LOCK:
        case 0x00: // No key held down
            key_repeating = false;
            return;

        default:
            if (left_alt_pressed() && m_scan_codes[m_last_make & 0x7f] == KEYPAD_KEY) {
                // Alternate + keypad key
                key_repeating = false;
                return;
            }

            break;

    }

    unsigned long m = millis();

    // Delay to first repeat
    if (!key_repeating && (m - m_last_make_time > AUTO_REPEAT_DELAY)) {
        key_repeating = true;
        last_repeat   = m;
    } else if (key_repeating && (m - last_repeat > AUTO_REPEAT_RATE)) {
        // Start repeating
        last_repeat = m;
        convert_scancode(m_last_make);
    }
}
