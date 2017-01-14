#define LED_PIN 13

#define UNIT_TIME (100)
#define DOT_TIME (UNIT_TIME)
#define DASH_TIME (3*UNIT_TIME)
#define UNIT_SEP_TIME (UNIT_TIME)
#define LETTER_SEP_TIME (3*UNIT_TIME)
#define WORD_SEP_TIME (7*UNIT_TIME)

struct m_symbol {
  uint8_t len :3;
  uint8_t code :5;
};

struct m_symbol m_alphabet[]= {
  {.len=2, .code=0b00010}, // A
  {.len=4, .code=0b00001}, // B
  {.len=4, .code=0b00101}, // C
  {.len=3, .code=0b00001}, // D
  {.len=1, .code=0b00000}, // E
  {.len=4, .code=0b00100}, // F
  {.len=3, .code=0b00011}, // G
  {.len=4, .code=0b00000}, // H
  {.len=2, .code=0b00000}, // I
  {.len=4, .code=0b01110}, // J
  {.len=3, .code=0b00101}, // K
  {.len=4, .code=0b00010}, // L
  {.len=2, .code=0b00011}, // M
  {.len=2, .code=0b00001}, // N
  {.len=3, .code=0b00111}, // O
  {.len=4, .code=0b00110}, // P
  {.len=4, .code=0b01011}, // Q
  {.len=3, .code=0b00010}, // R
  {.len=3, .code=0b00000}, // S
  {.len=1, .code=0b00001}, // T
  {.len=3, .code=0b00100}, // U
  {.len=4, .code=0b01000}, // V
  {.len=3, .code=0b00110}, // W
  {.len=4, .code=0b01001}, // X
  {.len=4, .code=0b01101}, // Y
  {.len=4, .code=0b00011}, // Z
};

struct m_symbol m_numbers[]= {
  {.len=5, .code=0b00000}, // 0
  {.len=5, .code=0b00000}, // 1
  {.len=5, .code=0b00000}, // 2
  {.len=5, .code=0b00000}, // 3
  {.len=5, .code=0b00000}, // 4
  {.len=5, .code=0b00000}, // 5
  {.len=5, .code=0b00000}, // 6
  {.len=5, .code=0b00000}, // 7
  {.len=5, .code=0b00000}, // 8
  {.len=5, .code=0b00000}, // 9
};

struct m_symbol m_space= {
  .len=7, .code=0b00000  // Space
};

/**
 * Turn on the LED for
 * the specified duration
 */
void flash_led(uint16_t duration)
{
  digitalWrite(LED_PIN, HIGH);

  delay(duration);

  digitalWrite(LED_PIN, LOW);
}

/**
 * Return a morse symbol for an ASCII
 * character.
 * Unkown characters are mapped to
 * Space symbols.
 */
struct m_symbol ascii_to_morse(char a)
{
  if (a >= 'A' && a<='Z') {
    return (m_alphabet[a-'A']);
  }

  if (a >= 'a' && a<='z') {
    return (m_alphabet[a-'a']);
  }

  if (a >= '0' && a<='9') {
    return (m_numbers[a-'0']);
  }

  return (m_space);
}

/**
 * Morse a single character
 */
void morse_putc(char c)
{
  struct m_symbol m= ascii_to_morse(c);

  if (m.len == m_space.len) {
    delay(WORD_SEP_TIME);

    return;
  }

  for (; m.len; m.len--, m.code>>=1) {
    flash_led((m.code & 1) ? DASH_TIME : DOT_TIME);
    delay(UNIT_SEP_TIME);
  }

  delay(LETTER_SEP_TIME - UNIT_SEP_TIME);
}

/**
 * Morse a string s
 */
void morse_puts(char *s)
{
  for(;*s;s++) morse_putc(*s);
}

/**
 * Morse a special character
 * encoded as - and .
 */
void morse_put_special(char *s)
{
  for(;*s;s++) {
    flash_led((*s == '-') ? DASH_TIME : DOT_TIME);
    delay(UNIT_SEP_TIME);
  }

  delay(LETTER_SEP_TIME - UNIT_SEP_TIME);
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);

  // Transmission speed learning phase
  morse_puts("CRCRC");
}

void loop()
{
  morse_puts("I am Robert");
  morse_put_special(".----.");
  morse_put_special("-.--.-");
  morse_put_special("-.-.-.");
  morse_puts(" DROP TABLE Students");
  morse_put_special("-.-.-.");
  morse_put_special("-....-");
  morse_put_special("-....-");
  morse_put_special("-....-");
  morse_puts(" call me Bobby");

  delay(1000);

  morse_put_special(".--.-.");
  morse_puts("potus");
  morse_put_special("---...");
  morse_puts("no hashtags in morse is hashtag s");
  morse_put_special("----");
  morse_puts("eisse");

  delay(1000);

  morse_puts("int main");
  morse_put_special("-.--.-");
  morse_puts("int argc");
  morse_put_special("--..--");
  morse_puts("char");
  morse_put_special(".-.-.-");
  morse_put_special(".-.-.-");
  morse_put_special(".-.-.-");
  morse_puts("crap");
  morse_put_special("-.-.--");
  morse_puts(" they did not add a multiply character");

  delay(1000);

  morse_put_special(".-.-.-");
  morse_put_special(".-.-.-");
  morse_put_special(".-.-.-");
  morse_put_special("-....-");
  morse_put_special("-....-");
  morse_put_special("-....-");
  morse_put_special(".-.-.-");
  morse_put_special(".-.-.-");
  morse_put_special(".-.-.-");

  delay(1000);

  morse_puts("https");
  morse_put_special("---...");
  morse_put_special("-..-.");
  morse_put_special("-..-.");
  morse_puts("zerforscht");
  morse_put_special(".-.-.-");
  morse_puts("de");
  morse_put_special("-..-.");

  delay(1000);
}
