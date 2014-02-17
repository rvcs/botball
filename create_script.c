

char opcodes[1024];
char * opcodes_tail = NULL;

void write_byte(b)
{
  *opcodes_tail = b;
  opcodes_tail++;
}

int num_bytes()
{
  return opcodes_tail - opcodes;
}



