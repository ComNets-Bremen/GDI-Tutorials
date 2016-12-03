#define HM_NOVAL 0
#define MAX_SEQ_LEN 64

/* This is the binary sequence that
 * encodes the compressed sensor values.
 * Edit it according to the task */
char sequence[MAX_SEQ_LEN+1]= "00010011111000";

/* Define the structure of a tree node.
 * The nodes may either be a branch node
 * (value is ignored and child_0 and child_1
 *  are set)
 *
 * Or a leaf node (child_0 and child_1 are NULL
 *  and value is set to a number)
 */
struct hm_node_t {
  int16_t value;

  struct hm_node_t *child_0;
  struct hm_node_t *child_1;
};

/* Define the tree structure.
 * The name of the structs is
 * determined by their binary encoding */
struct hm_node_t node_ch100 =
  {.value= -2, .child_0= NULL, .child_1= NULL};

struct hm_node_t node_ch101 =
  {.value= 2, .child_0= NULL, .child_1= NULL};

struct hm_node_t node_ch10 =
  {.value= HM_NOVAL, .child_0= &node_ch100, .child_1= &node_ch101};

struct hm_node_t node_ch110 =
  {.value= 1, .child_0= NULL, .child_1= NULL};

struct hm_node_t node_ch111 =
  {.value= -1, .child_0= NULL, .child_1= NULL};

struct hm_node_t node_ch11 =
  {.value= HM_NOVAL, .child_0= &node_ch110, .child_1= &node_ch111};

struct hm_node_t node_ch1 =
  {.value= HM_NOVAL, .child_0= &node_ch10, .child_1= &node_ch11};

struct hm_node_t node_ch0 =
  {.value= 0, .child_0= NULL, .child_1= NULL};

struct hm_node_t node_root =
  {.value= HM_NOVAL, .child_0= &node_ch0, .child_1= &node_ch1};

/**
 * Walk the huffman tree to get the next
 * value encoded in code.
 *
 * Returns the address of the next code
 * in the sequence or NULL on error.
 */
char *hm_walk(char *code, int16_t *val)
{
  struct hm_node_t *pivot= &node_root;

  if (!code) {
    return (false);
  }

  while(*code) {
    if(*code == '0') {

      // Check for leaf node
      if (!pivot->child_0) {
        *val= pivot->value;
        return(code);
      }

      pivot= pivot->child_0;
    }
    else if (*code == '1') {

      // Check for leaf node
      if (!pivot->child_1) {
        *val= pivot->value;
        return(code);
      }

      pivot= pivot->child_1;
    }
    else {
      // Unknown symbol
      return(NULL);
    }

    code++;
  }

  if(pivot->child_0 || pivot->child_1) {
    /* panic if we are not at an leaf node
     * at the end of the sequence */

    return(NULL);
  }

  *val= pivot->value;
  return(code);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int16_t accumulator=0;
  char *pos= sequence;

  Serial.println("\nStart walking");

  /* Iterate through the sequence until
   * an error is encountered or the end */
  while(pos && *pos) {
    int16_t diff=0;

    pos= hm_walk(pos,  &diff);

    if (pos) {
      accumulator+= diff;

      Serial.print("Accumulator: ");
      Serial.println(accumulator);
    }
    else {
      Serial.println("Decoder error!");
    }
  }

  /* Read a new sequence from the serial line
   * The sequence has to be termineted by a
   * '0' or '1' character.
   * For example: 11011000; */
  size_t wpos=0;
  for(; wpos<MAX_SEQ_LEN; wpos++) {
    while(!Serial.available());

    int c= Serial.read();

    if (c!='0' && c!='1') break;

    sequence[wpos]= c;
  }

  // Zero terminate the string
  sequence[wpos]= '\0';
}
