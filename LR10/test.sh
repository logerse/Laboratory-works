#!/usr/bin/env expect

set testNum 1
puts "Test $testNum:\n"
spawn ./a.out
expect "Input"
send -- "input.txt\r"
expect "New"
send -- "output.txt\r"
expect eof
