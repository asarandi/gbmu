
void op_cb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: PREFIX CB
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

	printf("undefined instruction 0xcb\n");
	printf("state->cycles = %u\n", state->cycles);
	dump_registers(reg, state, mem);
	state->done = true;
}

