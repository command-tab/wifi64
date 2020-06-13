# wifi64

Playing with the 64drive Wi-Fi module and libdragon

## Building

1. Install [libdragon-docker](https://github.com/anacierdem/libdragon-docker)
1. Clone this repo
1. Run `cd wifi64`
1. Run `libdragon make` to build the [.z64](http://n64dev.org/romformats.html) ROM

## Running

1. Power off the Nintendo 64 console and plug in the 64drive USB cable
1. Build and make [64drive-usb-linux](https://github.com/RenaKunisaki/64drive-usb-linux/) available on your `$PATH`
1. Run `64drive -c 6102 -v -l wifi64.z64` to load the ROM into the 64drive's SDRAM
1. Power on the console to run the ROM
