#ifndef UNION_H
#define UNION_H

struct r_type {
  unsigned int unused : 6;
  unsigned int rs : 2;
  unsigned int imed : 1;
  unsigned int rd : 2;
  unsigned int opcode : 5;
};

struct a_type {
  unsigned int addr : 8;
  unsigned int imed : 1;
  unsigned int rd : 2;
  unsigned int opcode : 5;
};

struct i_type {
  int constant : 8;
  unsigned int imed : 1;
  unsigned int rd : 2;
  unsigned int opcode : 5;
};
struct s_type {
  unsigned int carry : 1;
  unsigned int greater : 1;
  unsigned int equal : 1;
  unsigned int less : 1;
  unsigned int overflow : 1;
  unsigned int r_status : 3;
  unsigned int io_reg : 2;
  unsigned int unused : 6;
};

union codes {
  int instr;
  r_type reg;
  a_type addr;
  i_type imed;
  s_type status;
};


#endif
