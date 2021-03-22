//*
//* Gameboy Hardware definitions
//*
//* Based on Jones' hardware.inc
//* And based on Carsten Sorensen's ideas.
//*
//* Rev 1.1 - 15-Jul-97 : Added define check
//* Rev 1.2 - 18-Jul-97 : Added revision check macro
//* Rev 1.3 - 19-Jul-97 : Modified for RGBASM V1.05
//* Rev 1.4 - 27-Jul-97 : Modified for new subroutine prefixes
//* Rev 1.5 - 15-Aug-97 : Added _HRAM, PAD, CART defines
//*                     :  and Nintendo Logo
//* Rev 1.6 - 30-Nov-97 : Added rDIV, rTIMA, rTMA, & rTAC
//* Rev 1.7 - 31-Jan-98 : Added _SCRN0, _SCRN1
//* Rev 1.8 - 15-Feb-98 : Added rSB, rSC
//* Rev 1.9 - 16-Feb-98 : Converted I/O registers to $FFXX format
//* Rev 2.0 -           : Added GBC registers
//* Rev 2.1 -           : Added MBC5 & cart RAM enable/disable defines
//* Rev 2.2 -           : Fixed NR42,NR43, & NR44 equates
//* Rev 2.3 -           : Fixed incorrect _HRAM equate
//* Rev 2.4 - 27-Apr-13 : Added some cart defines (AntonioND)
//* Rev 2.5 - 03-May-15 : Fixed format (AntonioND)
//* Rev 2.6 - 09-Apr-16 : Added GBC OAM and cart defines (AntonioND)
//* Rev 2.7 - 19-Jan-19 : Added rPCMXX (ISSOtm)
//* Rev 2.8 - 03-Feb-19 : Added audio registers flags (Álvaro Cuesta)
//* Rev 2.9 - 28-Feb-20 : Added utility rP1 constants
//* Rev 3.0 - 27-Aug-20 : Register ordering, byte-based sizes, OAM additions, general cleanup (Blitter Object)

// If all of these are already defined, don't do it again.
//
#ifndef HARDWARE_H
# define HARDWARE_H
//
//rev_Check_hardware_inc : MACRO
//;NOTE: REVISION NUMBER CHANGES MUST BE ADDED
//;TO SECOND PARAMETER IN FOLLOWING LINE.
//    IF  \1 > 3.0 ;PUT REVISION NUMBER HERE
//        WARN    "Version \1 or later of 'hardware.inc' is required."
//    ENDC
//ENDM

#define _VRAM        0x8000 // $8000->$9FFF
#define _VRAM8000   _VRAM
#define _VRAM8800   _VRAM+0x800
#define _VRAM9000   _VRAM+0x1000
#define _SCRN0       0x9800 // $9800->$9BFF
#define _SCRN1       0x9C00 // $9C00->$9FFF
#define _SRAM        0xA000 // $A000->$BFFF
#define _RAM         0xC000 // $C000->$CFFF / $C000->$DFFF
#define _RAMBANK     0xD000 // $D000->$DFFF
#define _OAMRAM      0xFE00 // $FE00->$FE9F
#define _IO          0xFF00 // $FF00->$FF7F,$FFFF
#define _AUD3WAVERAM 0xFF30 // $FF30->$FF3F
#define _HRAM        0xFF80 // $FF80->$FFFE

// *** MBC5 Equates ***

#define rRAMG        0x0000 // $0000->$1fff
#define rROMB0       0x2000 // $2000->$2fff
#define rROMB1       0x3000 // $3000->$3fff - If more than 256 ROM banks are present.
#define rRAMB        0x4000 // $4000->$5fff - Bit 3 enables rumble (if present)


//***************************************************************************
//*
//* Custom registers
//*
//***************************************************************************

// --
// -- P1 ($FF00)
// -- Register for reading joy pad info. (R/W)
// --
#define rP1 0xFF00

#define P1F_5 0b00100000 // P15 out port, set to 0 to get buttons
#define P1F_4 0b00010000 // P14 out port, set to 0 to get dpad
#define P1F_3 0b00001000 // P13 in port
#define P1F_2 0b00000100 // P12 in port
#define P1F_1 0b00000010 // P11 in port
#define P1F_0 0b00000001 // P10 in port

#define P1F_GET_DPAD P1F_5
#define P1F_GET_BTN  P1F_4
#define P1F_GET_NONE P1F_4 | P1F_5


// --
// -- SB ($FF01)
// -- Serial Transfer Data (R/W)
// --
#define rSB 0xFF01


// --
// -- SC ($FF02)
// -- Serial I/O Control (R/W)
// --
#define rSC 0xFF02


// --
// -- DIV ($FF04)
// -- Divider register (R/W)
// --
#define rDIV 0xFF04


// --
// -- TIMA ($FF05)
// -- Timer counter (R/W)
// --
#define rTIMA 0xFF05


// --
// -- TMA ($FF06)
// -- Timer modulo (R/W)
// --
#define rTMA 0xFF06


// --
// -- TAC ($FF07)
// -- Timer control (R/W)
// --
#define rTAC 0xFF07

#define TACF_START  0b00000100
#define TACF_STOP   0b00000000
#define TACF_4KHZ   0b00000000
#define TACF_16KHZ  0b00000011
#define TACF_65KHZ  0b00000010
#define TACF_262KHZ 0b00000001


// --
// -- IF ($FF0F)
// -- Interrupt Flag (R/W)
// --
#define rIF 0xFF0F


// --
// -- AUD1SWEEP/NR10 ($FF10)
// -- Sweep register (R/W)
// --
// -- Bit 6-4 - Sweep Time
// -- Bit 3   - Sweep Increase/Decrease
// --           0: Addition    (frequency increases???)
// --           1: Subtraction (frequency increases???)
// -- Bit 2-0 - Number of sweep shift (# 0-7)
// -- Sweep Time: (n*7.8ms)
// --
#define rNR10 0xFF10
#define rAUD1SWEEP rNR10

#define AUD1SWEEP_UP   0b00000000
#define AUD1SWEEP_DOWN 0b00001000


// --
// -- AUD1LEN/NR11 ($FF11)
// -- Sound length/Wave pattern duty (R/W)
// --
// -- Bit 7-6 - Wave Pattern Duty (00:12.5% 01:25% 10:50% 11:75%)
// -- Bit 5-0 - Sound length data (# 0-63)
// --
#define rNR11 0xFF11
#define rAUD1LEN rNR11


// --
// -- AUD1ENV/NR12 ($FF12)
// -- Envelope (R/W)
// --
// -- Bit 7-4 - Initial value of envelope
// -- Bit 3   - Envelope UP/DOWN
// --           0: Decrease
// --           1: Range of increase
// -- Bit 2-0 - Number of envelope sweep (# 0-7)
// --
#define rNR12 0xFF12
#define rAUD1ENV rNR12


// --
// -- AUD1LOW/NR13 ($FF13)
// -- Frequency low byte (W)
// --
#define rNR13 0xFF13
#define rAUD1LOW rNR13


// --
// -- AUD1HIGH/NR14 ($FF14)
// -- Frequency high byte (W)
// --
// -- Bit 7   - Initial (when set, sound restarts)
// -- Bit 6   - Counter/consecutive selection
// -- Bit 2-0 - Frequency's higher 3 bits
// --
#define rNR14 0xFF14
#define rAUD1HIGH rNR14


// --
// -- AUD2LEN/NR21 ($FF16)
// -- Sound Length; Wave Pattern Duty (R/W)
// --
// -- see AUD1LEN for info
// --
#define rNR21 0xFF16
#define rAUD2LEN rNR21


// --
// -- AUD2ENV/NR22 ($FF17)
// -- Envelope (R/W)
// --
// -- see AUD1ENV for info
// --
#define rNR22 0xFF17
#define rAUD2ENV rNR22


// --
// -- AUD2LOW/NR23 ($FF18)
// -- Frequency low byte (W)
// --
#define rNR23 0xFF18
#define rAUD2LOW rNR23


// --
// -- AUD2HIGH/NR24 ($FF19)
// -- Frequency high byte (W)
// --
// -- see AUD1HIGH for info
// --
#define rNR24 0xFF19
#define rAUD2HIGH rNR24


// --
// -- AUD3ENA/NR30 ($FF1A)
// -- Sound on/off (R/W)
// --
// -- Bit 7   - Sound ON/OFF (1=ON,0=OFF)
// --
#define rNR30 0xFF1A
#define rAUD3ENA rNR30


// --
// -- AUD3LEN/NR31 ($FF1B)
// -- Sound length (R/W)
// --
// -- Bit 7-0 - Sound length
// --
#define rNR31 0xFF1B
#define rAUD3LEN rNR31


// --
// -- AUD3LEVEL/NR32 ($FF1C)
// -- Select output level
// --
// -- Bit 6-5 - Select output level
// --           00: 0/1 (mute)
// --           01: 1/1
// --           10: 1/2
// --           11: 1/4
// --
#define rNR32 0xFF1C
#define rAUD3LEVEL rNR32


// --
// -- AUD3LOW/NR33 ($FF1D)
// -- Frequency low byte (W)
// --
// -- see AUD1LOW for info
// --
#define rNR33 0xFF1D
#define rAUD3LOW rNR33


// --
// -- AUD3HIGH/NR34 ($FF1E)
// -- Frequency high byte (W)
// --
// -- see AUD1HIGH for info
// --
#define rNR34 0xFF1E
#define rAUD3HIGH rNR34


// --
// -- AUD4LEN/NR41 ($FF20)
// -- Sound length (R/W)
// --
// -- Bit 5-0 - Sound length data (# 0-63)
// --
#define rNR41 0xFF20
#define rAUD4LEN rNR41


// --
// -- AUD4ENV/NR42 ($FF21)
// -- Envelope (R/W)
// --
// -- see AUD1ENV for info
// --
#define rNR42 0xFF21
#define rAUD4ENV rNR42


// --
// -- AUD4POLY/NR43 ($FF22)
// -- Polynomial counter (R/W)
// --
// -- Bit 7-4 - Selection of the shift clock frequency of the (scf)
// --           polynomial counter (0000-1101)
// --           freq=drf*1/2^scf (not sure)
// -- Bit 3 -   Selection of the polynomial counter's step
// --           0: 15 steps
// --           1: 7 steps
// -- Bit 2-0 - Selection of the dividing ratio of frequencies (drf)
// --           000: f/4   001: f/8   010: f/16  011: f/24
// --           100: f/32  101: f/40  110: f/48  111: f/56  (f=4.194304 Mhz)
// --
#define rNR43 0xFF22
#define rAUD4POLY rNR43


// --
// -- AUD4GO/NR44 ($FF23)
// --
// -- Bit 7 -   Inital
// -- Bit 6 -   Counter/consecutive selection
// --
#define rNR44 0xFF23
#define rAUD4GO rNR44


// --
// -- AUDVOL/NR50 ($FF24)
// -- Channel control / ON-OFF / Volume (R/W)
// --
// -- Bit 7   - Vin->SO2 ON/OFF (Vin??)
// -- Bit 6-4 - SO2 output level (volume) (# 0-7)
// -- Bit 3   - Vin->SO1 ON/OFF (Vin??)
// -- Bit 2-0 - SO1 output level (volume) (# 0-7)
// --
#define rNR50 0xFF24
#define rAUDVOL rNR50

#define AUDVOL_VIN_LEFT  0b10000000 // SO2
#define AUDVOL_VIN_RIGHT 0b00001000 // SO1


// --
// -- AUDTERM/NR51 ($FF25)
// -- Selection of Sound output terminal (R/W)
// --
// -- Bit 7   - Output sound 4 to SO2 terminal
// -- Bit 6   - Output sound 3 to SO2 terminal
// -- Bit 5   - Output sound 2 to SO2 terminal
// -- Bit 4   - Output sound 1 to SO2 terminal
// -- Bit 3   - Output sound 4 to SO1 terminal
// -- Bit 2   - Output sound 3 to SO1 terminal
// -- Bit 1   - Output sound 2 to SO1 terminal
// -- Bit 0   - Output sound 0 to SO1 terminal
// --
#define rNR51 0xFF25
#define rAUDTERM rNR51

// SO2
#define AUDTERM_4_LEFT  0b10000000
#define AUDTERM_3_LEFT  0b01000000
#define AUDTERM_2_LEFT  0b00100000
#define AUDTERM_1_LEFT  0b00010000
// SO1
#define AUDTERM_4_RIGHT 0b00001000
#define AUDTERM_3_RIGHT 0b00000100
#define AUDTERM_2_RIGHT 0b00000010
#define AUDTERM_1_RIGHT 0b00000001


// --
// -- AUDENA/NR52 ($FF26)
// -- Sound on/off (R/W)
// --
// -- Bit 7   - All sound on/off (sets all audio regs to 0!)
// -- Bit 3   - Sound 4 ON flag (read only)
// -- Bit 2   - Sound 3 ON flag (read only)
// -- Bit 1   - Sound 2 ON flag (read only)
// -- Bit 0   - Sound 1 ON flag (read only)
// --
#define rNR52 0xFF26
#define rAUDENA rNR52

#define AUDENA_ON    0b10000000
#define AUDENA_OFF   0b00000000  // sets all audio regs to 0!


// --
// -- LCDC ($FF40)
// -- LCD Control (R/W)
// --
#define rLCDC 0xFF40

#define LCDCF_OFF     0b00000000 // LCD Control Operation
#define LCDCF_ON      0b10000000 // LCD Control Operation
#define LCDCF_WIN9800 0b00000000 // Window Tile Map Display Select
#define LCDCF_WIN9C00 0b01000000 // Window Tile Map Display Select
#define LCDCF_WINOFF  0b00000000 // Window Display
#define LCDCF_WINON   0b00100000 // Window Display
#define LCDCF_BG8800  0b00000000 // BG & Window Tile Data Select
#define LCDCF_BG8000  0b00010000 // BG & Window Tile Data Select
#define LCDCF_BG9800  0b00000000 // BG Tile Map Display Select
#define LCDCF_BG9C00  0b00001000 // BG Tile Map Display Select
#define LCDCF_OBJ8    0b00000000 // OBJ Construction
#define LCDCF_OBJ16   0b00000100 // OBJ Construction
#define LCDCF_OBJOFF  0b00000000 // OBJ Display
#define LCDCF_OBJON   0b00000010 // OBJ Display
#define LCDCF_BGOFF   0b00000000 // BG Display
#define LCDCF_BGON    0b00000001 // BG Display
// "Window Character Data Select" follows BG


// --
// -- STAT ($FF41)
// -- LCDC Status   (R/W)
// --
#define rSTAT 0xFF41

#define STATF_LYC     0b01000000 // LYC=LY Coincidence (Selectable)
#define STATF_MODE10  0b00100000 // Mode 10
#define STATF_MODE01  0b00010000 // Mode 01 (V-Blank)
#define STATF_MODE00  0b00001000 // Mode 00 (H-Blank)
#define STATF_LYCF    0b00000100 // Coincidence Flag
#define STATF_HBL     0b00000000 // H-Blank
#define STATF_VBL     0b00000001 // V-Blank
#define STATF_OAM     0b00000010 // OAM-RAM is used by system
#define STATF_LCD     0b00000011 // Both OAM and VRAM used by system
#define STATF_BUSY    0b00000010 // When set, VRAM access is unsafe


// --
// -- SCY ($FF42)
// -- Scroll Y (R/W)
// --
#define rSCY 0xFF42


// --
// -- SCX ($FF43)
// -- Scroll X (R/W)
// --
#define rSCX 0xFF43


// --
// -- LY ($FF44)
// -- LCDC Y-Coordinate (R)
// --
// -- Values range from 0->153. 144->153 is the VBlank period.
// --
#define rLY 0xFF44


// --
// -- LYC ($FF45)
// -- LY Compare (R/W)
// --
// -- When LY==LYC, STATF_LYCF will be set in STAT
// --
#define rLYC 0xFF45


// --
// -- DMA ($FF46)
// -- DMA Transfer and Start Address (W)
// --
#define rDMA 0xFF46


// --
// -- BGP ($FF47)
// -- BG Palette Data (W)
// --
// -- Bit 7-6 - Intensity for %11
// -- Bit 5-4 - Intensity for %10
// -- Bit 3-2 - Intensity for %01
// -- Bit 1-0 - Intensity for %00
// --
#define rBGP 0xFF47


// --
// -- OBP0 ($FF48)
// -- Object Palette 0 Data (W)
// --
// -- See BGP for info
// --
#define rOBP0 0xFF48


// --
// -- OBP1 ($FF49)
// -- Object Palette 1 Data (W)
// --
// -- See BGP for info
// --
#define rOBP1 0xFF49


// --
// -- WY ($FF4A)
// -- Window Y Position (R/W)
// --
// -- 0 <= WY <= 143
// -- When WY = 0, the window is displayed from the top edge of the LCD screen.
// --
#define rWY 0xFF4A


// --
// -- WX ($FF4B)
// -- Window X Position (R/W)
// --
// -- 7 <= WX <= 166
// -- When WX = 7, the window is displayed from the left edge of the LCD screen.
// -- Values of 0-6 and 166 are unreliable due to hardware bugs.
// --
#define rWX 0xFF4B


// --
// -- SPEED ($FF4D)
// -- Select CPU Speed (R/W)
// --
#define rKEY1 0xFF4D
#define rSPD  rKEY1

#define KEY1F_DBLSPEED 0b10000000 // 0=Normal Speed, 1=Double Speed (R)
#define KEY1F_PREPARE  0b00000001 // 0=No, 1=Prepare (R/W)


// --
// -- VBK ($FF4F)
// -- Select Video RAM Bank (R/W)
// --
// -- Bit 0 - Bank Specification (0: Specify Bank 0; 1: Specify Bank 1)
// --
#define rVBK 0xFF4F


// --
// -- HDMA1 ($FF51)
// -- High byte for Horizontal Blanking/General Purpose DMA source address (W)
// -- CGB Mode Only
// --
#define rHDMA1 0xFF51


// --
// -- HDMA2 ($FF52)
// -- Low byte for Horizontal Blanking/General Purpose DMA source address (W)
// -- CGB Mode Only
// --
#define rHDMA2 0xFF52


// --
// -- HDMA3 ($FF53)
// -- High byte for Horizontal Blanking/General Purpose DMA destination address (W)
// -- CGB Mode Only
// --
#define rHDMA3 0xFF53


// --
// -- HDMA4 ($FF54)
// -- Low byte for Horizontal Blanking/General Purpose DMA destination address (W)
// -- CGB Mode Only
// --
#define rHDMA4 0xFF54


// --
// -- HDMA5 ($FF55)
// -- Transfer length (in tiles minus 1)/mode/start for Horizontal Blanking, General Purpose DMA (R/W)
// -- CGB Mode Only
// --
#define rHDMA5 0xFF55

#define HDMA5F_MODE_GP  0b00000000 // General Purpose DMA (W)
#define HDMA5F_MODE_HBL 0b10000000 // HBlank DMA (W)

// -- Once DMA has started, use HDMA5F_BUSY to check when the transfer is complete
#define HDMA5F_BUSY 0b10000000 // 0=Busy (DMA still in progress), 1=Transfer complete (R)


// --
// -- RP ($FF56)
// -- Infrared Communications Port (R/W)
// -- CGB Mode Only
// --
#define rRP 0xFF56

#define rPF_ENREAD   0b11000000
#define rPF_DATAIN   0b00000010 // 0=Receiving IR Signal, 1=Normal
#define rPF_WRITE_HI 0b00000001
#define rPF_WRITE_LO 0b00000000


// --
// -- BCPS ($FF68)
// -- Background Color Palette Specification (R/W)
// --
#define rBCPS 0xFF68

#define BCPSF_AUTOINC 0b10000000 // Auto Increment (0=Disabled, 1=Increment after Writing)


// --
// -- BCPD ($FF69)
// -- Background Color Palette Data (R/W)
// --
#define rBCPD 0xFF69


// --
// -- OCPS ($FF6A)
// -- Object Color Palette Specification (R/W)
// --
#define rOCPS 0xFF6A

#define OCPSF_AUTOINC 0b10000000 // Auto Increment (0=Disabled, 1=Increment after Writing)


// --
// -- OCPD ($FF6B)
// -- Object Color Palette Data (R/W)
// --
#define rOCPD 0xFF6B


// --
// -- SMBK/SVBK ($FF70)
// -- Select Main RAM Bank (R/W)
// --
// -- Bit 2-0 - Bank Specification (0,1: Specify Bank 1; 2-7: Specify Banks 2-7)
// --
#define rSVBK 0xFF70
#define rSMBK rSVBK


// --
// -- PCM12 ($FF76)
// -- Sound channel 1&2 PCM amplitude (R)
// --
// -- Bit 7-4 - Copy of sound channel 2's PCM amplitude
// -- Bit 3-0 - Copy of sound channel 1's PCM amplitude
// --
#define rPCM12 0xFF76


// --
// -- PCM34 ($FF77)
// -- Sound channel 3&4 PCM amplitude (R)
// --
// -- Bit 7-4 - Copy of sound channel 4's PCM amplitude
// -- Bit 3-0 - Copy of sound channel 3's PCM amplitude
// --
#define rPCM34 0xFF77


// --
// -- IE ($FFFF)
// -- Interrupt Enable (R/W)
// --
#define rIE 0xFFFF

#define IEF_HILO   0b00010000 // Transition from High to Low of Pin number P10-P13
#define IEF_SERIAL 0b00001000 // Serial I/O transfer end
#define IEF_TIMER  0b00000100 // Timer Overflow
#define IEF_LCDC   0b00000010 // LCDC (see STAT)
#define IEF_VBLANK 0b00000001 // V-Blank


//***************************************************************************
//*
//* Flags common to multiple sound channels
//*
//***************************************************************************

// --
// -- Square wave duty cycle
// --
// -- Can be used with AUD1LEN and AUD2LEN
// -- See AUD1LEN for more info
// --
#define AUDLEN_DUTY_12_5    0b00000000 // 12.5%
#define AUDLEN_DUTY_25      0b01000000 // 25%
#define AUDLEN_DUTY_50      0b10000000 // 50%
#define AUDLEN_DUTY_75      0b11000000 // 75%


// --
// -- Audio envelope flags
// --
// -- Can be used with AUD1ENV, AUD2ENV, AUD4ENV
// -- See AUD1ENV for more info
// --
#define AUDENV_UP           0b00001000
#define AUDENV_DOWN         0b00000000


// --
// -- Audio trigger flags
// --
// -- Can be used with AUD1HIGH, AUD2HIGH, AUD3HIGH
// -- See AUD1HIGH for more info
// --

#define AUDHIGH_RESTART     0b10000000
#define AUDHIGH_LENGTH_ON   0b01000000
#define AUDHIGH_LENGTH_OFF  0b00000000


//***************************************************************************
//*
//* CPU values on bootup (a=type, b=qualifier)
//*
//***************************************************************************

#define BOOTUP_A_DMG    0x01 // Dot Matrix Game
#define BOOTUP_A_CGB    0x11 // Color GameBoy
#define BOOTUP_A_MGB    0xFF // Mini GameBoy (Pocket GameBoy)

// if a=BOOTUP_A_CGB, bit 0 in b can be checked to determine if real CGB or
// other system running in GBC mode
#define BOOTUP_B_CGB    0b00000000
#define BOOTUP_B_AGB    0b00000001   // GBA, GBA SP, Game Boy Player, or New GBA SP


//***************************************************************************
//*
//* Cart related
//*
//***************************************************************************

// $0143 Color GameBoy compatibility code
#define CART_COMPATIBLE_DMG     0x00
#define CART_COMPATIBLE_DMG_GBC 0x80
#define CART_COMPATIBLE_GBC     0xC0

// $0146 GameBoy/Super GameBoy indicator
#define CART_INDICATOR_GB       0x00
#define CART_INDICATOR_SGB      0x03

// $0147 Cartridge type
#define CART_ROM                     0x00
#define CART_ROM_MBC1                0x01
#define CART_ROM_MBC1_RAM            0x02
#define CART_ROM_MBC1_RAM_BAT        0x03
#define CART_ROM_MBC2                0x05
#define CART_ROM_MBC2_BAT            0x06
#define CART_ROM_RAM                 0x08
#define CART_ROM_RAM_BAT             0x09
#define CART_ROM_MMM01               0x0B
#define CART_ROM_MMM01_RAM           0x0C
#define CART_ROM_MMM01_RAM_BAT       0x0D
#define CART_ROM_MBC3_BAT_RTC        0x0F
#define CART_ROM_MBC3_RAM_BAT_RTC    0x10
#define CART_ROM_MBC3                0x11
#define CART_ROM_MBC3_RAM            0x12
#define CART_ROM_MBC3_RAM_BAT        0x13
#define CART_ROM_MBC5                0x19
#define CART_ROM_MBC5_BAT            0x1A
#define CART_ROM_MBC5_RAM_BAT        0x1B
#define CART_ROM_MBC5_RUMBLE         0x1C
#define CART_ROM_MBC5_RAM_RUMBLE     0x1D
#define CART_ROM_MBC5_RAM_BAT_RUMBLE 0x1E
#define CART_ROM_MBC7_RAM_BAT_GYRO   0x22
#define CART_ROM_POCKET_CAMERA       0xFC
#define CART_ROM_BANDAI_TAMA5        0xFD
#define CART_ROM_HUDSON_HUC3         0xFE
#define CART_ROM_HUDSON_HUC1         0xFF

// $0148 ROM size
// these are kilobytes
#define CART_ROM_32KB   0x00 // 2 banks
#define CART_ROM_64KB   0x01 // 4 banks
#define CART_ROM_128KB  0x02 // 8 banks
#define CART_ROM_256KB  0x03 // 16 banks
#define CART_ROM_512KB  0x04 // 32 banks
#define CART_ROM_1024KB 0x05 // 64 banks
#define CART_ROM_2048KB 0x06 // 128 banks
#define CART_ROM_4096KB 0x07 // 256 banks
#define CART_ROM_8192KB 0x08 // 512 banks
#define CART_ROM_1152KB 0x52 // 72 banks
#define CART_ROM_1280KB 0x53 // 80 banks
#define CART_ROM_1536KB 0x54 // 96 banks

// $0149 SRAM size
// these are kilobytes
#define CART_SRAM_NONE  0
#define CART_SRAM_2KB   1 // 1 incomplete bank
#define CART_SRAM_8KB   2 // 1 bank
#define CART_SRAM_32KB  3 // 4 banks
#define CART_SRAM_128KB 4 // 16 banks

#define CART_SRAM_ENABLE  0x0A
#define CART_SRAM_DISABLE 0x00

// $014A Destination code
#define CART_DEST_JAPANESE     0x00
#define CART_DEST_NON_JAPANESE 0x01


//***************************************************************************
//*
//* Keypad related
//*
//***************************************************************************

#define PADF_DOWN   0x80
#define PADF_UP     0x40
#define PADF_LEFT   0x20
#define PADF_RIGHT  0x10
#define PADF_START  0x08
#define PADF_SELECT 0x04
#define PADF_B      0x02
#define PADF_A      0x01

#define PADB_DOWN   0x7
#define PADB_UP     0x6
#define PADB_LEFT   0x5
#define PADB_RIGHT  0x4
#define PADB_START  0x3
#define PADB_SELECT 0x2
#define PADB_B      0x1
#define PADB_A      0x0


//***************************************************************************
//*
//* Screen related
//*
//***************************************************************************

#define SCRN_X    160 // Width of screen in pixels
#define SCRN_Y    144 // Height of screen in pixels
#define SCRN_X_B  20  // Width of screen in bytes
#define SCRN_Y_B  18  // Height of screen in bytes

#define SCRN_VX   256 // Virtual width of screen in pixels
#define SCRN_VY   256 // Virtual height of screen in pixels
#define SCRN_VX_B 32  // Virtual width of screen in bytes
#define SCRN_VY_B 32  // Virtual height of screen in bytes


//***************************************************************************
//*
//* OAM related
//*
//***************************************************************************

// OAM attributes
// each entry in OAM RAM is 4 bytes (sizeof_OAM_ATTRS)
struct OAM_ATTRS {
    unsigned char OAMA_Y;                 // y pos
    unsigned char OAMA_X;                 // x pos
    unsigned char OAMA_TILEID;            // tile id
    unsigned char OAMA_FLAGS;             // flags (see below)
};

#define OAM_COUNT           40  // number of OAM entries in OAM RAM

// flags
#define OAMF_PRI        0b10000000 // Priority
#define OAMF_YFLIP      0b01000000 // Y flip
#define OAMF_XFLIP      0b00100000 // X flip
#define OAMF_PAL0       0b00000000 // Palette number; 0,1 (DMG)
#define OAMF_PAL1       0b00010000 // Palette number; 0,1 (DMG)
#define OAMF_BANK0      0b00000000 // Bank number; 0,1 (GBC)
#define OAMF_BANK1      0b00001000 // Bank number; 0,1 (GBC)

#define OAMF_PALMASK    0b00000111 // Palette (GBC)

#define OAMB_PRI        7 // Priority
#define OAMB_YFLIP      6 // Y flip
#define OAMB_XFLIP      5 // X flip
#define OAMB_PAL1       4 // Palette number; 0,1 (DMG)
#define OAMB_BANK1      3 // Bank number; 0,1 (GBC)


//*
//* Nintendo scrolling logo
//* (Code won't work on a real GameBoy)
//* (if next lines are altered.)
//NINTENDO_LOGO : MACRO
//    DB  $CE,$ED,$66,$66,$CC,$0D,$00,$0B,$03,$73,$00,$83,$00,$0C,$00,$0D
//    DB  $00,$08,$11,$1F,$88,$89,$00,$0E,$DC,$CC,$6E,$E6,$DD,$DD,$D9,$99
//    DB  $BB,$BB,$67,$63,$6E,$0E,$EC,$CC,$DD,$DC,$99,$9F,$BB,$B9,$33,$3E
//ENDM
//
#endif
