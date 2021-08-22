# コンパイル
avr-g++ -std=c++17 -g -O2 -mmcu=atmega328p main.cpp
avr-objcopy -j .text -j .data -O ihex a.out binary.hex

# 書き込み
write_sh="write.sh"
write_cmd="avrdude -e -c avrisp2 -p m328p -U flash:w:binary.hex -F"
echo "書き込みは次のコマンドを実行してください"
echo "source ${write_sh}"
echo ${write_cmd} > ${write_sh}
