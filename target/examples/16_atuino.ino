#define CMD_LEN_MAX (32)

void exec_cmd();

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(5000);
}

void loop()
{
  exec_cmd();
}


void atcb_at(char *param)
{
  Serial.print("OK\r\n");
}

void atcb_setout(char *param)
{
  if(*param != '=') {
    Serial.print("FAIL\r\n");
    return;
  }

  int pin= atoi(&param[1]);

  pinMode(pin, OUTPUT);

  Serial.print("OK\r\n");
}

void atcb_setin(char *param)
{
  if(*param != '=') {
    Serial.print("FAIL\r\n");
    return;
  }

  int pin= atoi(&param[1]);

  pinMode(pin, INPUT);

  Serial.print("OK\r\n");
}

void atcb_writehigh(char *param)
{
  if(*param != '=') {
    Serial.print("FAIL\r\n");
    return;
  }

  int pin= atoi(&param[1]);

  digitalWrite(pin, HIGH);

  Serial.print("OK\r\n");
}

void atcb_writelow(char *param)
{
  if(*param != '=') {
    Serial.print("FAIL\r\n");
    return;
  }

  int pin= atoi(&param[1]);

  digitalWrite(pin, LOW);

  Serial.print("OK\r\n");
}

void atcb_pinread(char *param)
{
  if(*param != '=') {
    Serial.print("FAIL\r\n");
    return;
  }

  int pin= atoi(&param[1]);

  int state= digitalRead(pin);

  Serial.print("+PIN_READ:");
  Serial.print(state);

  Serial.print("\r\nOK\r\n");
}

/* Map AT-Command names to callback functions.
 * The parameters in the AT-Command are passed as
 * as a single string to the callback. */
struct {
  char *name;
  void (*cb)(char*);
} at_commands[] = {
  {.name= "AT",            .cb= atcb_at},
  {.name= "AT+SET_OUT",    .cb= atcb_setout},
  {.name= "AT+SET_IN",     .cb= atcb_setin},
  {.name= "AT+WRITE_HIGH", .cb= atcb_writehigh},
  {.name= "AT+WRITE_LOW",  .cb= atcb_writelow},
  {.name= "AT+PIN_READ",   .cb= atcb_pinread},
  {.name= NULL, .cb=NULL}
};

void exec_cmd()
{
  char buf[CMD_LEN_MAX];
  memset(buf, 0, CMD_LEN_MAX);

  /* Read a line from the Serial port.
   * this method does not add an '\0'
   * end character */
  Serial.readBytesUntil('\n', buf, CMD_LEN_MAX-1);

  /* Check if the command matches one in the command
   * map. This is not done using strcmp() as
   *  '\r' has to be ignored and
   *  '=' separates command and argument */
  for(size_t cidx= 0; at_commands[cidx].name; cidx++) {
    for(size_t bidx= 0; ; bidx++) {
      char *a= &at_commands[cidx].name[bidx];
      char *b= &buf[bidx];

      if((*a=='\0' && (*b=='\0' || *b=='\r' || *b=='='))) {
        at_commands[cidx].cb(b);
        return;
      }

      if((*a == '\0') || (*b == '\0') || *a != *b) {
        break;
      }
    }
  }
}
