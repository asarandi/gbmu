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
    ../../../gbmu -t blargg2 "$f"
    ret=$?
    if [ $ret -eq 10 ]; then
        echo "success,\"$f\""
    elif [ $ret -eq 11 ]; then
        echo "failure,\"$f\""
    elif [ $ret -eq 12 ]; then
        echo "timeout,\"$f\""
    else
        echo "other $ret,\"$f\""
    fi
done <<< "cgb_sound/cgb_sound.gb
cgb_sound/rom_singles/01-registers.gb
cgb_sound/rom_singles/02-len ctr.gb
cgb_sound/rom_singles/03-trigger.gb
cgb_sound/rom_singles/04-sweep.gb
cgb_sound/rom_singles/05-sweep details.gb
cgb_sound/rom_singles/06-overflow on trigger.gb
cgb_sound/rom_singles/07-len sweep period sync.gb
cgb_sound/rom_singles/08-len ctr during power.gb
cgb_sound/rom_singles/09-wave read while on.gb
cgb_sound/rom_singles/10-wave trigger while on.gb
cgb_sound/rom_singles/11-regs after power.gb
cgb_sound/rom_singles/12-wave.gb
dmg_sound/dmg_sound.gb
dmg_sound/rom_singles/01-registers.gb
dmg_sound/rom_singles/02-len ctr.gb
dmg_sound/rom_singles/03-trigger.gb
dmg_sound/rom_singles/04-sweep.gb
dmg_sound/rom_singles/05-sweep details.gb
dmg_sound/rom_singles/06-overflow on trigger.gb
dmg_sound/rom_singles/07-len sweep period sync.gb
dmg_sound/rom_singles/08-len ctr during power.gb
dmg_sound/rom_singles/09-wave read while on.gb
dmg_sound/rom_singles/10-wave trigger while on.gb
dmg_sound/rom_singles/11-regs after power.gb
dmg_sound/rom_singles/12-wave write while on.gb
halt_bug.gb
interrupt_time/interrupt_time.gb
mem_timing-2/rom_singles/01-read_timing.gb
mem_timing-2/rom_singles/02-write_timing.gb
mem_timing-2/rom_singles/03-modify_timing.gb
oam_bug/oam_bug.gb
oam_bug/rom_singles/1-lcd_sync.gb
oam_bug/rom_singles/2-causes.gb
oam_bug/rom_singles/3-non_causes.gb
oam_bug/rom_singles/4-scanline_timing.gb
oam_bug/rom_singles/5-timing_bug.gb
oam_bug/rom_singles/6-timing_no_bug.gb
oam_bug/rom_singles/7-timing_effect.gb
oam_bug/rom_singles/8-instr_effect.gb"
