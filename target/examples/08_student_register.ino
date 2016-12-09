/* Enable or disable verbose output
 * on the serial line in the
 * tree building/lookup phases */
#define DEBUG_TBUILD (true)
#define DEBUG_LOOKUP (true)

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
  struct student_t *child_lt;
  struct student_t *child_gt;
};

/* Define a list of students and their
 * matriculation number.
 * Do not build the tree structure yet */
struct student_t student_register[]= {
  {.name= "Clifford Calahan",  .mat_num= 4009336, .child_lt=NULL, .child_gt=NULL},
  {.name= "Paulette Petrone",  .mat_num= 4001246, .child_lt=NULL, .child_gt=NULL},
  {.name= "Ona Odonoghue",     .mat_num= 4013096, .child_lt=NULL, .child_gt=NULL},
  {.name= "Cyrus Carbonell",   .mat_num= 4031913, .child_lt=NULL, .child_gt=NULL},
  {.name= "Janet Joynes",      .mat_num= 4015054, .child_lt=NULL, .child_gt=NULL},
  {.name= "Clarisa Coulson",   .mat_num= 4023839, .child_lt=NULL, .child_gt=NULL},
  {.name= "Juliet Jaquez",     .mat_num= 4007416, .child_lt=NULL, .child_gt=NULL},
  {.name= "Song Sandler",      .mat_num= 4011005, .child_lt=NULL, .child_gt=NULL},
  {.name= "Angela Applewhite", .mat_num= 4034097, .child_lt=NULL, .child_gt=NULL},
  {.name= "Tyree Troche",      .mat_num= 4004535, .child_lt=NULL, .child_gt=NULL},
  {.name= "Joshua June",       .mat_num= 4026817, .child_lt=NULL, .child_gt=NULL},
  {.name= "Shelton Sarkisian", .mat_num= 4006478, .child_lt=NULL, .child_gt=NULL},
  {.name= "Elois Edmond",      .mat_num= 4030462, .child_lt=NULL, .child_gt=NULL},
  {.name= "Denver Dolph",      .mat_num= 4037371, .child_lt=NULL, .child_gt=NULL},
  {.name= "Norman Napoleon",   .mat_num= 4030020, .child_lt=NULL, .child_gt=NULL},
  {.name= "Rea Reineck",       .mat_num= 4027146, .child_lt=NULL, .child_gt=NULL},
  {.name= "Matilde Micheal",   .mat_num= 4026688, .child_lt=NULL, .child_gt=NULL},
  {.name= "Tracey Thibodeau",  .mat_num= 4029685, .child_lt=NULL, .child_gt=NULL},
  {.name= "Magnolia Meader",   .mat_num= 4025231, .child_lt=NULL, .child_gt=NULL},
  {.name= "Alix Alvarenga",    .mat_num= 4019661, .child_lt=NULL, .child_gt=NULL},
  {.name= "Marilee Meng",      .mat_num= 4006268, .child_lt=NULL, .child_gt=NULL},
  {.name= NULL, .mat_num= 0, .child_lt=NULL, .child_gt=NULL}
};

struct student_t *sr_flat= NULL;
struct student_t *sr_tree= NULL;

/**
 * This recursive function prints
 * a tree node and all of its children
 * to the serial line
 */
void sr_print_subtree(struct student_t *root, uint16_t indent)
{
  if(!root) return;

  sr_print_subtree(root->child_lt, indent+1);

  for(uint16_t i=0; i<indent; i++) {
    Serial.print("  |");
  }

  Serial.print("--+ ");
  Serial.print(root->name);
  Serial.print("(");
  Serial.print(root->mat_num);
  Serial.println(")");

  sr_print_subtree(root->child_gt, indent+1);
}

/**
 *  This function takes a list of students as
 * input argument and adds cross references
 * to the elements to arrange them in a
 * tree structure.
 * It returns the root node of the tree
 */
struct student_t *sr_generate_tree(struct student_t *flat)
{
  /* Use the first element in the
   * list as root node */
  struct student_t *root= &flat[0];

  /* Go through all remaining valid
   * elements in the list */
  for (size_t i=1; flat[i].name; i++) {
    struct student_t *pivot= root;
    struct student_t **target= NULL;
    boolean is_placed= false;

    /* Walk the tree until a free child_gt or child_lt
     * branch is found */
    while(!is_placed) {
      /* Decide whether to use child_gt or child_lt
       * to continue walking/hook the element in.
       * Use the ternary operator and pointers to make
       * that less obvious */
      target= (pivot->mat_num > flat[i].mat_num) ? &(pivot->child_gt) : &(pivot->child_lt);

      if (*target) {
        /* Branch is already set.
         * keep walking */
        pivot= *target;
      }
      else {
        /* The branch is free. Hook in the element
         * and stop walking */
        *target= &flat[i];
        is_placed= true;
      }
    }

    if(DEBUG_TBUILD) {
      Serial.print("\nHooking item ");
      Serial.print(i);
      Serial.print(" (");
      Serial.print(flat[i].name);
      Serial.print(",");
      Serial.print(flat[i].mat_num);
      Serial.println(") into the tree:");
      sr_print_subtree(root, 0);
    }
  }

  return(root);
}

/**
 * Search for a student by matriculation number
 * using a tree structure starting at root.
 */
struct student_t *sr_tree_lookup(struct student_t *root, uint32_t mat_num)
{
  struct student_t *pivot= root;

  if(DEBUG_LOOKUP) {
    Serial.print("\nLookup entry: ");
    Serial.println(mat_num);
  }

  while(pivot) {
    if(DEBUG_LOOKUP) {
      Serial.print(mat_num);
      Serial.print((mat_num == pivot->mat_num) ? " == " : (mat_num < pivot->mat_num) ? " < " : " > ");
      Serial.println(pivot->mat_num);
    }

    if(pivot->mat_num == mat_num) return(pivot);

    pivot= (pivot->mat_num > mat_num) ? pivot->child_gt : pivot->child_lt;
  }

  return(NULL);
}

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

  for (size_t i=1; flat[i].name; i++) {
    if(DEBUG_LOOKUP) {
      Serial.print(mat_num);
      Serial.print((flat[i].mat_num == mat_num) ? "==" : "!=");
      Serial.println(flat[i].mat_num);
    }


    if(flat[i].mat_num == mat_num) {
      return(&flat[i]);
    }
  }

  return(NULL);
}

/**
 *  Reads a single decimal number from
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

  return(num_in);
}

void setup()
{
  Serial.begin(9600);

  sr_flat= student_register;
  sr_tree= sr_generate_tree(sr_flat);

}

void loop()
{
  Serial.print("\nEnter a mat_num to search for: ");

  uint32_t query_num= number_from_serial();
  struct student_t *res= NULL;


  res= sr_tree_lookup(sr_tree, query_num);

  if(res) {
    Serial.print("Found student ");
    Serial.println(res->name);
  }
  else {
    Serial.println("Did not find a student");
  }
}
