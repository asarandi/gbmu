# gbmu



#### description:

work in progress; gameboy emulator in c;



#### building on linux:

`apt install libsdl2-dev`

`make`



#### building on macOS:

`brew install sdl2`

`make`



#### usage:

`./gbmu <gameboy_rom_file.gb>`



#### netplay:

run server instance `./gbmu --server <gameboy_rom_file.gb>`

run client instance `./gbmu --client <gameboy_rom_file.gb>`

to play over LAN edit the `include/tcp.h` and update `NETWORK_ADDRESS` value, to recompile run `make clean && make`



#### controls:

|gameboy|gbmu|
|-|-|
|directional pad|arrow keys|
|b|z|
|a|x|
|start|return|
|select|right shift|



#### screenshots

[![screenshots/screenshot1.png](screenshots/screenshot1.png "screenshots/screenshot1.png")](screenshots/screenshot1.png "screenshots/screenshot1.png")

[![screenshots/screenshot2.png](screenshots/screenshot2.png "screenshots/screenshot2.png")](screenshots/screenshot2.png "screenshots/screenshot2.png")

[![screenshots/screenshot3.png](screenshots/screenshot3.png "screenshots/screenshot3.png")](screenshots/screenshot3.png "screenshots/screenshot3.png")

[![screenshots/screenshot4.png](screenshots/screenshot4.png "screenshots/screenshot4.png")](screenshots/screenshot4.png "screenshots/screenshot4.png")

