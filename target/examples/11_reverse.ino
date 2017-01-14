/**
 * read until '\n' or at most len-1 characters
 * from the serial line it into buf
 */
void read_line(char *buf, size_t len)
{
  /* len is the number of symbols that fit
   * into buf.
   * The last symbol in buf has to be
   * '\0' as this is expected by all string handling
   * functions. So we only hav len-1 symbols available */
  len--;

  while(len) {
    /* Read symbols as long as there is
     * still space in the buffer */
    int symbol= Serial.read();

    /* Ignore "no characters available"-error
     * and carriage return character */
    if(symbol>=0 && symbol!='\r') {
      if(symbol == '\n') {
        /* Quit reading characters when
         * a newline symbol is received */
        break;
      }

      *buf= symbol;

      /* Go to the next buffer slot and
       * decrement the number of available slots */
      buf++;
      len--;
    }
  }

  /* Add end of string marker */
  *buf= '\0';
}

/**
 * Expects a string in orig and
 * stores the reversed string in rev
 */
void reverse_string(char *orig, char*rev)
{
  size_t orig_len= strlen(orig);

  size_t rev_idx= 0;
  size_t fwd_idx= orig_len-1;

  // TODO
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  char fwd_buff[128]= {'\0'};
  char rev_buff[128]= {'\0'};

  Serial.println("Text to reverse: ");

  read_line(fwd_buff, 128);

  reverse_string(fwd_buff, rev_buff);

  Serial.print("txet desreveR: ");
  Serial.println(rev_buff);
}
