#define GUESS_RANGE (32)

uint16_t num_to_guess= 0;
uint16_t step_counter= 0;

/* Reads a single decimal number from
 * the serial input and returns it.
 * Needs a non-digit as end marker */
uint16_t number_from_serial(void)
{
  uint16_t num_in= 0;

  for(;;) {
    int char_from_pc= Serial.read();

    /* Serial.read returns -1 when there are currently
     * no received bytes in the buffer.
     * Loop until there are bytes received */
    if(char_from_pc >= 0) {

      /* Check if the received byte is a
       * decimal digit encoded in ASCII
       * if it is: add the digit to the receive buffer
       * if it is not: leave the loop */
      if(char_from_pc >= '0' && char_from_pc <= '9') {
        Serial.print(char_from_pc - '0');

        num_in*= 10;
        num_in+= char_from_pc - '0';
      }
      else {
        break;
      }
    }
  }

  return(num_in);
}

void setup()
{
  Serial.begin(9600);

  /* Rely on the A0 being a
   * floating input pin with a random
   * voltage */
  randomSeed(analogRead(A0));

  num_to_guess= random(GUESS_RANGE);
}

void loop()
{
  Serial.print("Enter an estimate for the random number: ");
  uint16_t num_cur_guess= number_from_serial();
  Serial.println(' ');

  step_counter++;

  if(num_cur_guess == num_to_guess) {
    Serial.print("Your guess is correct! The number was: ");
    Serial.println(num_to_guess);

    Serial.print("You needed ");
    Serial.print(step_counter);
    Serial.println(" steps to find the number");
  }
  else {
    Serial.print("Your guess (");
    Serial.print(num_cur_guess);
    Serial.print(") is too ");

    if(num_cur_guess < num_to_guess) {
      Serial.print("small");
    }

    if(num_cur_guess > num_to_guess) {
      Serial.print("big");
    }

    Serial.println(", try again");
  }
}
