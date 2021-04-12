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
response=$(./tp1 d 1 + 1)
assert_equals "$response" 2

echo "Probando resta decimal"
response=$(./tp1 d 2 - 1)
assert_equals "$response" 1

echo "Probando suma binaria"
response=$(./tp1 b 100 + 1)
assert_equals "$response" 101

echo "Probando suma binaria"
response=$(./tp1 b 101 - 1)
assert_equals "$response" 100
