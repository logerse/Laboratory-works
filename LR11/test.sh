#!/usr/bin/env expect

set testNum 1
puts "Test $testNum\r"
spawn ./a.out input.txt output.txt
expect eof
incr testNum

puts "Test $testNum\r"
spawn ./a.out input2.txt output2.txt
expect eof
incr testNum

puts "Test $testNum\r"
spawn ./a.out iAAAAWWW.txt asdasd.txt
expect eof
incr testNum

puts "Test $testNum\r"
spawn ./a.out void.txt asdasd.txt
expect eof
incr testNum
