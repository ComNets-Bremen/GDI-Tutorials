struct node_t {
  uint32_t value;
  struct node_t *child_l;
  struct node_t *child_r;
};

struct node_t child_l_l_l = {
  .value= 2208,
  .child_l= NULL,
  .child_r= NULL
};

struct node_t child_l_l_r = {
  .value= 1190,
  .child_l= NULL,
  .child_r= NULL
};

struct node_t child_l_l = {
  .value= 2615,
  .child_l= &child_l_l_l,
  .child_r= &child_l_l_r
};

struct node_t child_l_r = {
  .value= 3917,
  .child_l= NULL,
  .child_r= NULL
};

struct node_t child_r_l = {
  .value= 49,
  .child_l= NULL,
  .child_r= NULL
};

struct node_t child_r_r = {
  .value= 4012,
  .child_l= NULL,
  .child_r= NULL
};

struct node_t child_l = {
  .value= 886,
  .child_l= &child_l_l,
  .child_r= &child_l_r
};

struct node_t child_r = {
  .value= 501,
  .child_l= &child_r_l,
  .child_r= &child_r_r
};

struct node_t root = {
  .value= 2904,
  .child_l= &child_l,
  .child_r= &child_r
};

uint32_t tree_max(struct node_t *root)
{
  uint32_t max_val= root->value;

  if(root->child_l) {
    // FIXME

    if(max_cl > max_val) max_val= max_cl;
  }

  //FIXME

  return(max_val);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("tree_max(root)= ");
  Serial.println(tree_max(&root));

  delay(5000);
}
