#!/bin/bash

cd extras/roms/blargg-gb-tests/
if [ $? -ne 0 ]; then
    echo "failed to change dir" >&2
    exit 1
fi

if [ ! -f ../../../gbmu ]; then
    echo "cannot find gbmu" >&2
    exit 1
fi

echo "result,file"
while IFS= read -r f; do
    ../../../gbmu -t blargg1 "$f"
    ret=$?
    if [ $ret -eq 10 ]; then
        echo "success,$f"
    elif [ $ret -eq 11 ]; then
        echo "failure,$f"
    elif [ $ret -eq 12 ]; then
        echo "timeout,$f"
    else
        echo "other $ret,$f"
    fi
done <<< "cpu_instrs/cpu_instrs.gb
cpu_instrs/individual/01-special.gb
cpu_instrs/individual/02-interrupts.gb
cpu_instrs/individual/03-op sp,hl.gb
cpu_instrs/individual/04-op r,imm.gb
cpu_instrs/individual/05-op rp.gb
cpu_instrs/individual/06-ld r,r.gb
cpu_instrs/individual/07-jr,jp,call,ret,rst.gb
cpu_instrs/individual/08-misc instrs.gb
cpu_instrs/individual/09-op r,r.gb
cpu_instrs/individual/10-bit ops.gb
cpu_instrs/individual/11-op a,(hl).gb
instr_timing/instr_timing.gb
mem_timing/mem_timing.gb
mem_timing/individual/01-read_timing.gb
mem_timing/individual/02-write_timing.gb
mem_timing/individual/03-modify_timing.gb"
