#!/bin/bash

cd extras/roms/mealybug-tearoom-tests/

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
    rom="build/ppu/$f.gb"
    scr="build/ppu/$f-gbmu.png"
    ref="expected/DMG-blob/$f.png"
    rm -f "$scr"
    ../../../gbmu -t mealybug "$rom"
    res=$(compare -metric AE "$scr" "$ref" NULL: 2>&1)
    echo "$res,\"$rom\""
done <<< "m2_win_en_toggle
m3_bgp_change
m3_bgp_change_sprites
m3_lcdc_bg_en_change
m3_lcdc_bg_map_change
m3_lcdc_obj_en_change
m3_lcdc_obj_en_change_variant
m3_lcdc_obj_size_change
m3_lcdc_obj_size_change_scx
m3_lcdc_tile_sel_change
m3_lcdc_tile_sel_win_change
m3_lcdc_win_en_change_multiple
m3_lcdc_win_en_change_multiple_wx
m3_lcdc_win_map_change
m3_obp0_change
m3_scx_high_5_bits
m3_scx_low_3_bits
m3_scy_change
m3_window_timing
m3_window_timing_wx_0
m3_wx_4_change
m3_wx_4_change_sprites
m3_wx_5_change
m3_wx_6_change"
