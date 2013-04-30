#!/bin/sh
SRC_DIR=$(cd $(dirname $1) && pwd)
SUCCEED=1

cd $(cd $(dirname $0);pwd)

function check() {
    if [ $? -ne 0 ]; then
        echo $SRC
        SUCCEED=1
        continue
    fi
}

for SRC in `find ${SRC_DIR} -name "*.lua"`; do
    CLEAN_ASM="while(<>){s/^\t(\d+)\t\[\d+\]/\t\1/;s/(main|function) <[^\]]+>/function/;s/0x[0-9a-f]+//;print}"

    # Some shell settings
    set -o pipefail

    # Check that the simplified source is functionally identical to the original.
    # echo "Step 1"
    rm -f /tmp/original.asm /tmp/simplified.asm /tmp/original.luac /tmp/simplified.luac
    check
    lua/src/luac -s -l -o /tmp/original.luac $SRC | perl -e "$CLEAN_ASM" > /tmp/original.asm
    check
    ./lua_simplifier -luac $SRC | lua/src/luac -s -l -o /tmp/simplified.luac - | perl -e "$CLEAN_ASM" > /tmp/simplified.asm
    check
    diff /tmp/original.asm /tmp/simplified.asm
    check

    # Check that the simplified source simplifies to itself.
    # echo "Step 2"
    rm -f /tmp/simplified.lua /tmp/simplified2.lua
    check
    ./lua_simplifier $SRC > /tmp/simplified.lua
    check
    ./lua_simplifier /tmp/simplified.lua > /tmp/simplified2.lua
    check
    diff /tmp/simplified.lua /tmp/simplified2.lua
    check

    # Check the simplified source.
    # echo "Step 3"
    ./lua_simplifier -emit_lines $SRC > /tmp/simplified.lua
    # ./lua_checker -const_functions /tmp/simplified.lua
    check
done

if [ $SUCCEED -eq 1 ]; then
    echo ">>>>> FAILED <<<<<"
    exit 1
fi
echo "***** SUCCEED *****"
exit 0
