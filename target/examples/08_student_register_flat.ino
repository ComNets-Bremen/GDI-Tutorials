/* Enable or disable verbose output
 * on the serial line in the
 * tree building/lookup phases */
#define DEBUG_TBUILD (false)
#define DEBUG_LOOKUP (false)

/* Define a type that collects informations
 * about a student (name, mat_num)
 * and that can be used to build a tree structure.
 *
 *  child_lt points to another student with a lower
 *  matriculation number.
 *
 *  child_gt points to another student with a higher
 *  matriculation number. */
struct student_t {
  char *name;
  uint32_t mat_num;
};

/* Define a list of students and their
 * matriculation number.
 * Do not build the tree structure yet */
struct student_t student_register[]= {
  {.name= "Clifford Calahan",  .mat_num= 4009336},
  {.name= "Paulette Petrone",  .mat_num= 4001246},
  {.name= "Ona Odonoghue",     .mat_num= 4013096},
  {.name= "Cyrus Carbonell",   .mat_num= 4031913},
  {.name= "Janet Joynes",      .mat_num= 4015054},
  {.name= "Clarisa Coulson",   .mat_num= 4023839},
  {.name= "Juliet Jaquez",     .mat_num= 4007416},
  {.name= "Song Sandler",      .mat_num= 4011005},
  {.name= "Angela Applewhite", .mat_num= 4034097},
  {.name= "Tyree Troche",      .mat_num= 4004535},
  {.name= "Joshua June",       .mat_num= 4026817},
  {.name= "Shelton Sarkisian", .mat_num= 4006478},
  {.name= "Elois Edmond",      .mat_num= 4030462},
  {.name= "Denver Dolph",      .mat_num= 4037371},
  {.name= "Norman Napoleon",   .mat_num= 4030020},
  {.name= "Rea Reineck",       .mat_num= 4027146},
  {.name= "Matilde Micheal",   .mat_num= 4026688},
  {.name= "Tracey Thibodeau",  .mat_num= 4029685},
  {.name= "Magnolia Meader",   .mat_num= 4025231},
  {.name= "Alix Alvarenga",    .mat_num= 4019661},
  {.name= "Marilee Meng",      .mat_num= 4006268},
  {.name= NULL, .mat_num= 0}
};

/**
 * Search for a student by matriculation number
 * using a flat list structure.
 */
struct student_t *sr_flat_lookup(struct student_t *flat, uint32_t mat_num)
{
  if(DEBUG_LOOKUP) {
    Serial.print("\nLookup entry: ");
    Serial.println(mat_num);
  }

  /* TODO: Implement lookup by iterating
   * through the elements of flat[] */

  /* Hint: Check if flat[i].name and/or flat[i].mat_num
   * are zero to determine the length of the flat[] array */

  /* If an element is found return it using
   * return(&flat[i]); */

  return(NULL);
}

/**
 * Reads a single decimal number from
 * the serial input and returns it.
 * Needs a non-digit as end marker
 */
uint32_t number_from_serial(void)
{
  uint32_t num_in= 0;

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

  Serial.print("\n");

  return(num_in);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("\nEnter a mat_num to search for: ");

  uint32_t query_num= number_from_serial();

  /* Perform lookup using the flat search
   * algorith and keep track of runtime */
  uint32_t runtime_flat= micros();
  struct student_t * res_flat= sr_flat_lookup(student_register, query_num);
  runtime_flat= micros() - runtime_flat;

  if(res_flat) {
    Serial.print("Flat lookup: found student ");
    Serial.print(res_flat->name);
  }
  else {
    Serial.print("Flat lookup: did not find a student");
  }

  Serial.print(" in ");
  Serial.print(runtime_flat);
  Serial.println("us ");
}
