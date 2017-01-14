int lightPin = A0;  //define a pin for Photo resistor

// mittlere helligkeitbestimmen, um zwischen an und aus zu unterscheiden.
// alles was ueber der mittleren helligkeit liegt ist an und alles was darunter liegt ist aus.
float mean_value = 0; // der mittelwert

// moving minimum
const int sequencelength_buffer_length = 16;
int sequencelength_buffer[sequencelength_buffer_length];
int sequencelength_buffer_index = 0;
int sequencelength_min = 0;

int unit_length; // das ist die laenge eines dit in schleifendurchlaeufen (vom delay am ende der loop abhaengig)
int current_sequence_length = 1; // das ist die aktuelle laenge von licht an oder licht aus.

boolean light_on=false,last_light_on=false; // aktueller zustand und zustand im letzten schleifendurchlauf

struct morse_tree { // eine baumstruktur fuer die dekodierung der daten. siehe wikipedia bild mit dem baum
  char* symbol;
  struct morse_tree *dit; // ein punkt
  struct morse_tree *dah; // ein strich
};


// hier wird der baum aufgebaut. da wir keine umlaute dekodieren, da das mit
// dem anzeigen schwieriger wird bestehen erweiterte zeichen aus mehreren buchstaben.

struct morse_tree tree_ball_bouncing_against_wall = {"þ", NULL, NULL};

struct morse_tree tree_N_with_donald_hair = {"Ñ", NULL, NULL};
struct morse_tree tree_funny_hat_G = {"Ĝ", NULL, NULL};

struct morse_tree tree_tick = {"'", NULL, NULL};

struct morse_tree tree_parens = {")", NULL, NULL};
struct morse_tree tree_funny_hat_H = {"Ĥ", NULL, &tree_parens};

struct morse_tree tree_semicolon = {";", NULL, NULL};
struct morse_tree tree_exclamation_mark = {"!", NULL, NULL};
struct morse_tree tree_dramatic_pause = {"o.O", &tree_semicolon, &tree_exclamation_mark};

struct morse_tree tree_comma = {",", NULL, &tree_comma};
struct morse_tree tree_even_more_dramatic_pause = {"O.O", NULL, &tree_comma};

struct morse_tree tree_C_with_goatee = {"Ç", NULL, NULL};

struct morse_tree tree_slash = {"/", NULL, NULL};

struct morse_tree tree_equal = {"=", NULL, NULL};

struct morse_tree tree_minus = {"-", NULL, NULL};

struct morse_tree tree_colon = {":", NULL, NULL};

struct morse_tree tree_dot = {".", NULL, NULL};
struct morse_tree tree_plus = {"+", NULL, &tree_dot};
struct morse_tree tree_A_uml = {"Ä", &tree_plus, NULL};

struct morse_tree tree_funny_hat_S = {"Ŝ", NULL, NULL};
struct morse_tree tree_funny_hat_J = {"Ĵ", NULL, NULL};

struct morse_tree tree_at = {"@", NULL, NULL};
struct morse_tree tree_strange_A = {"À", &tree_at, NULL};
struct morse_tree tree_strange_E = {"É", NULL, NULL};

struct morse_tree tree_qmark = {"?", NULL, NULL};
struct morse_tree tree_underscore = {"_", NULL, NULL};
struct morse_tree tree_D_dashed = {"Đ", &tree_qmark, &tree_underscore};

struct morse_tree tree_1 = {"1", &tree_tick, 0};
struct morse_tree tree_2 = {"2",0,0};
struct morse_tree tree_3 = {"3",0,0};
struct morse_tree tree_4 = {"4",0,0};
struct morse_tree tree_5 = {"5",0,0};
struct morse_tree tree_6 = {"6",0, &tree_minus};
struct morse_tree tree_7 = {"7",0,0};
struct morse_tree tree_8 = {"8", &tree_colon, 0};
struct morse_tree tree_9 = {"9",0,0};
struct morse_tree tree_0 = {"0",0,0};

struct morse_tree tree_Q = {"Q", &tree_funny_hat_G, &tree_N_with_donald_hair};
struct morse_tree tree_Z = {"Z", &tree_7, &tree_even_more_dramatic_pause};
struct morse_tree tree_Y = {"Y", &tree_funny_hat_H, 0};
struct morse_tree tree_C = {"C", &tree_C_with_goatee, &tree_dramatic_pause};
struct morse_tree tree_X = {"X", &tree_slash, 0};
struct morse_tree tree_B = {"B", &tree_6, &tree_equal};
struct morse_tree tree_J = {"J", &tree_funny_hat_J, &tree_1};
struct morse_tree tree_P = {"P", &tree_ball_bouncing_against_wall, &tree_strange_A};
struct morse_tree tree_L = {"L",0,0};
struct morse_tree tree_U_uml = {"Ü", &tree_D_dashed, &tree_2};
struct morse_tree tree_O_uml = {"Ö", &tree_8, NULL};
struct morse_tree tree_CH = {"CH", &tree_9, &tree_0};
struct morse_tree tree_F = {"F",&tree_strange_E,0};
struct morse_tree tree_V = {"V", &tree_funny_hat_S, &tree_3};
struct morse_tree tree_H = {"H", &tree_5, &tree_4};

struct morse_tree tree_O = {"O", &tree_O_uml, &tree_CH};
struct morse_tree tree_G = {"G", &tree_Z, &tree_Q};
struct morse_tree tree_K = {"K", &tree_C, &tree_Y};
struct morse_tree tree_D = {"D", &tree_B, &tree_X};
struct morse_tree tree_W = {"W", &tree_P, &tree_J};
struct morse_tree tree_R = {"R", &tree_L, &tree_A_uml};
struct morse_tree tree_U = {"U", &tree_F, &tree_U_uml};
struct morse_tree tree_S = {"S", &tree_H, &tree_V};

struct morse_tree tree_M = {"M",&tree_G,&tree_O};
struct morse_tree tree_N = {"N",&tree_D,&tree_K};
struct morse_tree tree_A = {"A",&tree_R,&tree_W};
struct morse_tree tree_I = {"I",&tree_S,&tree_U};

struct morse_tree tree_T = {"T",&tree_N,&tree_M};
struct morse_tree tree_E = {"E",&tree_I,&tree_A};

// die wurzel des baums.
struct morse_tree root = {"nil",&tree_E,&tree_T};

// wo wir uns gerade im baum befinden
struct morse_tree *state = &root;

void everyone_that_does_not_use_utf8_is_a_moron(char *utf8_sym)
{
  uint8_t *sym= (uint8_t *)utf8_sym;

  while(*sym) {
    if (*sym < 128) {
      Serial.write(sym, 1);

      sym++;
    }
    else {
      if(sym[0] == 0xC2) {
        Serial.write(&sym[1], 1);
      }
      else if(sym[0] == 0xC3) {
        uint8_t moron_encoding= sym[1] | 0xC0;
        Serial.write(&moron_encoding, 1);
      }
      else {
        Serial.print("moron encoding can't handle symbol");
      }

      sym+=2;
    }
  }
}

void setup()
{
  Serial.begin(9600);  //Begin serial communcation
  mean_value =  analogRead(lightPin);

  everyone_that_does_not_use_utf8_is_a_moron("Üble Scheiße\n");
}

void loop()
{
  int light_intensity = analogRead(lightPin); // aktuelle lichtintensitaet

  mean_value = 0.99*mean_value+0.01*(float)light_intensity;

  light_on = (light_intensity>mean_value);

  if (light_on==last_light_on) { // war in der letzten runde das licht im gleichen zustand?
    current_sequence_length++; // ja, also zähler hochsetzen, um zu merken wie lange es an bzw. aus war.
  }
  else {
    // hat gerade gewechselt. also sagt uns wie lange es an war was fier en zeichen es ist oder was fuer eine pause es ist.
    // zuerst updaten wir aber die unit laenge...
    sequencelength_buffer[sequencelength_buffer_index] = current_sequence_length;
    sequencelength_buffer_index++;
    if (sequencelength_buffer_index==sequencelength_buffer_length) {
      sequencelength_buffer_index = 0;
    }
    sequencelength_min = sequencelength_buffer[0];
    for (int i=1;i<sequencelength_buffer_length;i++) {
      if (sequencelength_buffer[i]>0) {
        if (sequencelength_min>sequencelength_buffer[i]) {
          sequencelength_min = sequencelength_buffer[i];
        }
      }
    }
    unit_length = sequencelength_min;
    // nun zu den zeichen ...
    if (last_light_on==true) { // war an. gucken wir ob ein - (dah) oder . (dit) gesendet wurde.
      if (current_sequence_length<2*unit_length) { // kurz ...
        if (state->dit!=0) {  // also im baum zum dit zweig gehen, wenn es eine kante gibt
          state = state->dit;
        }
        else {  // sonst baum zuruecksetzen. muss wohl was falsch gesendet oder empfangen worden sein.
          state = &root;
        }
      }
      else if (current_sequence_length>2*unit_length) { // lang ..
        if (state->dah!=0) { // also im baum den dah zweig langhangeln wenn es geht
          state = state->dah;
        }
        else { // sonst zuruecksetzen
          state = &root;
        }
      }
      else { // die lange des lichts an ist nicht fuer dit und nicht fuer dah. muss was falsch sein. also zur wurzel zurueck.
        state=&root;
      }
    }
    else { // last_light_on==OFF also eine pause. nur welche?
      if (current_sequence_length<2*unit_length) { // kurze pause (so lang wie ein dit, also ist das zeichen noch nicht zuende).
        // dit break
      }
      else if ((current_sequence_length>=2*unit_length) && (current_sequence_length<5*unit_length)) { // eine dah pause, also ist das symbol gelesen aber noch nicht das wort.
        // dah break (symbol ends)
        everyone_that_does_not_use_utf8_is_a_moron(state->symbol); // symbol ausgeben und ...
        state=&root; // baum zuruecksetzen
      }
      else if (current_sequence_length>=5*unit_length) { // sehr lange pause,also das wort ist zuende.
        // word break (word ends)
        everyone_that_does_not_use_utf8_is_a_moron(state->symbol); // letztes symbol ausgeben und ...
        Serial.print(" "); // leerzeichen ausgeben.
        state=&root;
      }
      else { // sollte nicht vorkommen. sicherheitshalber baum zuruecksetzen.
        state=&root;
      }
    }
    //Serial.println(current_sequence_length);
    current_sequence_length = 1; // wenn das licht gerade gewechselt hat,. dann auch den zähler zuruecksetzen.
  }
  last_light_on = light_on; // darf auch nciht fehlen. der alktuelle wird der letzte in der naechsten runde sein
  delay(25); //short delay for faster response. wenn geaendert, dann auch sequencemin anpassen!
}
