#ifndef BRIDGE_H
# define BRIDGE_H

/* bridge */

struct gameboy;

struct player {
    struct gameboy gb;
    bool frame_blending;
};

int run();
int finish();
int load_rom_from_bytes(int player_id, void *rom_data, int rom_size);
int load_ram_from_bytes(int player_id, void *ram_data, int ram_size);
int save_ram_to_bytes(int player_id, void *buf, int size);
int set_frame_blending(int player_id, bool enabled);
void set_input(int player_id, int input);
void timer_callback();
int video_message(int player_id, char *s);
int reload_both();

int save_deserialize_from_bytes(struct gameboy *gb, uint8_t *bytes,
                                uint64_t size);
int save_serialize_to_bytes(struct gameboy *gb, uint8_t *bytes, uint64_t size);


#endif
