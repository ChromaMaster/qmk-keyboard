set dotenv-load := true
set positional-arguments

default:
    @just --list

default_km := "default"
keymap_path := "keyboards/lily58/keymaps"

# Download and sync all the submodules needed (qmk_firmware)
sync:
   git submodule update --init --recursive

# Syncs, cleans and adds the custom keymap to qmk_firmware
pre +args: sync
   ln -fs $PWD/{{keymap_path}}/chromamaster_$1 $PWD/qmk_firmware/{{keymap_path}}

# Build the custom keyboard firware
build *args=default_km: (pre args)
   qmk compile -j0 -kb lily58/rev1 -km chromamaster_$1

# Flash the custom keyboard firmware
flash: flash-left

# Flash the custom keyboard firmware
flash-left *args=default_km: (pre args)
   qmk flash -j0 -kb lily58/rev1 -km chromamaster_$1 -bl avrdude-split-left

# Flash the custom keyboard firmware
flash-right *args=default_km: (pre args)
   qmk flash -j0 -kb lily58/rev1 -km chromamaster_$1 -bl avrdude-split-right

# Format the code using clang-format
format:
    fd -E qmk_firmware -t f ".*.c|.*.h" | xargs clang-format -style=file -i

# Removes the custom keymap from qmk_firmware and cleans the build
clean:
   rm -f $PWD/qmk_firmware/{{keymap_path}}/chromamaster_{{default_km}}
   qmk clean
