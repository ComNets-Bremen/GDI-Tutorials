#define DEBUG true

char *example_program=
  "+++++[>++<-]>[>+++++"
  "++>>>>+++>+++++<<<<<"
  "<-]>[>+>+>+<<<-]>+>-"
  "Informatik ist super"
  "->+++>++>[>+>+>+>+<<"
  "<<-]>-->->+++++>[<<<"
  "<+>>>>-]<<<<<<<<[.>]";


struct bf_state_t {
  char *program;
  size_t pc;

  uint8_t tape[256];
  uint8_t ti;
};


struct bf_instr_t {
  char opcode;
  boolean (*cb)(struct bf_state_t *);
};


boolean bf_tape_fwd(struct bf_state_t *state)
{
  // TODO

  return(true);
}

boolean bf_tape_bwd(struct bf_state_t *state)
{
  state->ti--;

  return(true);
}

boolean bf_incr(struct bf_state_t *state)
{
  state->tape[state->ti]++;

  return(true);
}

boolean bf_decr(struct bf_state_t *state)
{
  // TODO

  return(true);
}

boolean bf_print(struct bf_state_t *state)
{
  Serial.write(&state->tape[state->ti], 1);

  return(true);
}

boolean bf_read(struct bf_state_t *state)
{
  while(!Serial.available());
  state->tape[state->ti]= Serial.read();

  return(true);
}

boolean bf_pc_fwd(struct bf_state_t *state)
{
  size_t nest= 1;

  while(!state->tape[state->ti] && nest && state->program[state->pc]) {
    state->pc++;

    if (state->program[state->pc] == '[') nest++;
    if (state->program[state->pc] == ']') nest--;
  }

  return(state->program[state->pc] != 0);
}

boolean bf_pc_bwd(struct bf_state_t *state)
{
  size_t nest= 1;

  while(state->tape[state->ti] && nest && state->pc) {
    state->pc--;

    if (state->program[state->pc] == ']') nest++;
    if (state->program[state->pc] == '[') nest--;
  }

  return(true);
}

struct bf_instr_t bf_instrset[] = {
  {.opcode= '>', .cb= bf_tape_fwd},
  {.opcode= '<', .cb= bf_tape_bwd},
  {.opcode= '+', .cb= bf_incr},
  {.opcode= '-', .cb= bf_decr},
  {.opcode= '.', .cb= bf_print},
  {.opcode= ',', .cb= bf_read},
  {.opcode= '[', .cb= bf_pc_fwd},
  {.opcode= ']', .cb= bf_pc_bwd},
  {.opcode= 0}
};

void bf_exec(char *prog, struct bf_instr_t *iset) {
  struct bf_state_t state= {
    .program= prog,
    .pc= 0,
    .tape= {0},
    .ti= 0
  };

  while(state.program[state.pc]) {
    size_t pc= state.pc;

    for(size_t i=0; iset[i].opcode; i++) {
      if (iset[i].opcode == state.program[pc]) {
        if(!iset[i].cb(&state)) return;
      }
    }

    if(DEBUG) {
      Serial.write((uint8_t*)&state.program[state.pc], 1);
      Serial.print(" - ");

      uint8_t lti;

      for(lti=255; !state.tape[lti]; lti--);

      for(uint8_t ti=0; ti <= lti; ti++) {
        Serial.print(state.tape[ti]);
        Serial.write((uint8_t *)(ti==state.ti ? "* " : "  "), 2);
      }

      Serial.println("");
      delay(250);
    }

    state.pc++;
  }
}

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println("Run Brainfuck:");
  bf_exec(example_program, bf_instrset);
  Serial.println("\n\n");

  delay(10000);
}
