#!/bin/sh

runClangFormatOnDir() {
    find "$1" -name "*.cpp" -o -name "*.c" -o -name "*.h" | while read fn; do
        echo "$fn"
        clang-format -style=file -i "$fn"
        # Clean trailing whitespace.
        sed -i 's/[ \t]*$//' "$fn"
    done
}
(
cd $(dirname $0)
cd ..
runClangFormatOnDir apps
runClangFormatOnDir src
runClangFormatOnDir inc
runClangFormatOnDir tests
runClangFormatOnDir examples

#echo "Press enter to continue." && read
)
