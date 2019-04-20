#include <ncurses.h>

void    *tui_input()
{
    int rv, flags;   
    int key_delays[8] = {0};
    int ncurses_keys[8] = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT, 'n', 'm', 'z', 'x'};    
    char key;

    flags = fcntl(STDIN_FILENO, F_GETFL, 0);

    while (true)
    {
        key = 0;
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
        read(0, &key, 1);
        fcntl(STDIN_FILENO, F_SETFL, flags);

        for (int i=0; i<8; i++) {
            if (key == ncurses_keys[i]) {
                state->buttons[i] = 1;
                key_delays[i] = 0;
            }
            key_delays[i]++;
            if (key_delays[i] > 20) {   //delay duration
                key_delays[i] = 0;
                state->buttons[i] = 0;
            }
        }
        if (key != 0) continue ;
        usleep(1000);
    }
    return NULL;
}

void    tui_input_print()
{
    addch('\n');
    for (int i=0; i<8; i++) {
        if (state->buttons[i] == 1)
            addch('1');
        else
            addch('0');
    }    
}

void    *tui_show(void *arg)
{
    char    *pixels = "o*. ";
    char    buf[144*161];
    int     key;

    (void)arg;
    while (true) {
        for (int y=0;y<144;y++) {
            for (int x=0;x<161;x++) {
                int idx = state->screen_buf[y*160+x];
                buf[y*161+x] = pixels[idx];
                if (x == 160) buf[y*161+x] = '\n';                   
            }
        }
        clear();
        addnstr(buf,144*161);
        tui_input_print();
        refresh();
        usleep(1000000 / 30);
    }
    return NULL;
}


void    tui_init()
{
    int flags;

    initscr();
    raw();
//    cbreak();
    keypad(stdscr, TRUE);
    noecho();
}
