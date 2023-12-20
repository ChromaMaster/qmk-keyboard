set dotenv-load := true

default:
    @just --list

default_km := "chromamaster"
keymap_path := "keyboards/lily58/keymaps"

# Download and sync all the submodules needed (qmk_firmware)
sync:
   git submodule update --init --recursive

# Syncs, cleans and adds the custom keymap to qmk_firmware
pre: sync
   ln -fs $PWD/{{keymap_path}}/{{default_km}} $PWD/qmk_firmware/{{keymap_path}}

# Build the custom keyboard firware
build: pre
   qmk compile -j0 -kb lily58/rev1 -km {{default_km}}

# Flash the custom keyboard firmware
flash: pre
   qmk flash -j0 -kb lily58/rev1 -km {{default_km}}

# Removes the custom keymap from qmk_firmware and cleans the build
clean:
   rm -f $PWD/qmk_firmware/{{keymap_path}}/{{default_km}}
   qmk clean
