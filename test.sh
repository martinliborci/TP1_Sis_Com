#!/bin/bash

assert_equals () {
  if [ "$1" = "$2" ]; then
    echo -e "$Green $Check_Mark Success $Color_Off"
  else
    echo -e "$Red Failed $Color_Off"
    echo -e "$Red Expected -$1- to equal -$2- $Color_Off"
    Errors=$((Errors  + 1))
    exit 1
  fi
}

echo "Probando suma decimal"
#valores bajos
response=$(./tp1 d 1 + 1)
assert_equals "$response" 2
#valores medios
response=$(./tp1 d 1000000000 + 1246125)
assert_equals "$response" 1001246125
#valores extremos
response=$(./tp1 d 2147483647 + 2147483647)
assert_equals "$response" 4294967294

echo "Probando resta decimal"
#valores bajos
response=$(./tp1 d 1 - 1)
assert_equals "$response" 0
#valores medios
response=$(./tp1 d 1000000000 - 1246125)
assert_equals "$response" 998753875
#valores altos
response=$(./tp1 d 2147483647 - 2147483647)
assert_equals "$response" 0
#valores negativos
response=$(./tp1 d 0 - 2147483647)
assert_equals "$response" -2147483647

echo "Probando suma binaria"
response=$(./tp1 b 1 + 1)
assert_equals "$response" 10
#valores medios
response=$(./tp1 b 1000000000 + 111111111111)
assert_equals "$response" 1000111111111
#valores extremos
response=$(./tp1 b 111111111111111111111111111111 + 111111111111111111111111111111)
assert_equals "$response" 1111111111111111111111111111110

echo "Probando resta binaria"
response=$(./tp1 b 1 - 0)
assert_equals "$response" 1
#valores medios
response=$(./tp1 b 100010101000000 - 111111111111)
assert_equals "$response" 11010101000001
#valores extremos
response=$(./tp1 b 111111111111111111111111111111 - 111111111111111111111111111110)
assert_equals "$response" 1
#valores negativos
response=$(./tp1 b 1000000000 - 111111111111)
assert_equals "$response" 1111111111111111111001000000001