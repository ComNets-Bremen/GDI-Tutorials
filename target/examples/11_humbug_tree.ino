struct led_tree {
  uint8_t pin;
  struct led_tree *child_l;
  struct led_tree *child_r;
};

struct led_tree node_r_r = {
  .pin= 8,
  .child_l= NULL,
  .child_r= NULL,
};

struct led_tree node_r_l = {
  .pin= 7,
  .child_l= NULL,
  .child_r= NULL,
};

struct led_tree node_l_r = {
  .pin= 6,
  .child_l= NULL,
  .child_r= NULL,
};

struct led_tree node_l_l = {
  .pin= 5,
  .child_l= NULL,
  .child_r= NULL,
};

struct led_tree node_r = {
  .pin= 4,
  .child_l= &node_r_l,
  .child_r= &node_r_r,
};

struct led_tree node_l = {
  .pin= 3,
  .child_l= &node_l_l,
  .child_r= &node_l_r,
};

struct led_tree node_root = {
  .pin= 2,
  .child_l= &node_l,
  .child_r= &node_r,
};

/**
 * Set all leds in a subtree to mode OUTPUT
 */
void led_tree_pinmodes(struct led_tree *root)
{
  if(!root) return;

  pinMode(root->pin, OUTPUT);
  digitalWrite(root->pin, LOW);

  led_tree_pinmodes(root->child_l);
  led_tree_pinmodes(root->child_r);
}

/**
 * Display a hue on the RGB-LED
 * the input goes from
 * 0 (only blue) over
 * 255 (only red) and
 * 511 (only green) up to
 * 767
 */
void rgb_colorwheel(int16_t color)
{
  int16_t intens_r= 255-abs(color-255);
  int16_t intens_g= 255-abs(color-511);
  int16_t intens_b= (color > 300) ? (color-511) : (255-color);

  analogWrite(9, (intens_r > 0) ? intens_r : 0);
  analogWrite(10, (intens_g > 0) ? intens_g : 0);
  analogWrite(11, (intens_b > 0) ? intens_b : 0);
}

void setup()
{
  led_tree_pinmodes(&node_root);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.begin(115200);
}

void loop()
{
  uint16_t interval_tree= (1234562 % 10 + 1) * 1000;
  uint16_t interval_nose= interval_tree/3;

  /* Next time (in millis) the tree/nose
   * should be updated.
   * Initialized to just now.
   * This can not be replaced by
   *  for(i=0;i<3;i++) {delay(interval_nose); update_nose();}
   *  update_tree();
   * as
   *  a) updates take time and the error would accumulate
   *  b) interval_tree!= 3*interval_nose because of rounding issues */
  uint32_t next_tree= millis();
  uint32_t next_nose= next_tree;

  uint16_t cur_color= 0;
  struct led_tree *cur_node= &node_l_l;

  for(;;) {
    uint32_t now= millis();

    if(now >= next_tree) {
      /* - Turn of the led of the last node
       * - Choose a node at random
       * - Turn on the corresponding led
       * - Setup next wakeup time */

      digitalWrite(cur_node->pin, LOW);

      cur_node= random(2) ? cur_node->child_l : cur_node->child_r;
      if(!cur_node) cur_node= &node_root;

      Serial.print("Tree led: ");
      Serial.println(cur_node->pin);

      digitalWrite(cur_node->pin, HIGH);

      next_tree+= interval_tree;
    }

    if(now >= next_nose) {
      cur_color= (cur_color + 20) % 767;

      Serial.print("Color: ");
      Serial.println(cur_color);

      rgb_colorwheel(cur_color);

      next_nose+= interval_nose;
    }
  }
}
