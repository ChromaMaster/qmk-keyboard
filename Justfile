set dotenv-load := true

default:
    @just --list

default_km := "chromamaster"
keymap_path := "keyboards/lily58/keymaps"

sync:
   git submodule update --init --recursive

pre: sync clean
   ln -s $PWD/{{keymap_path}}/{{default_km}} $PWD/qmk_firmware/{{keymap_path}}

build: pre
   qmk compile -j0 -kb lily58/rev1 -km {{default_km}}

flash: pre
   qmk flash -j0 -kb lily58/rev1 -km {{default_km}}

clean:
   rm -f $PWD/qmk_firmware/{{keymap_path}}/{{default_km}}
   qmk clean
