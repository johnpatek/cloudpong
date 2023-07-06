#!/bin/bash

# GOTO for bash, based upon https://stackoverflow.com/a/31269848/5353461
goto() {
  label=$1
  cmd=$(sed -En "/^[[:space:]]*#[[:space:]]*$label:[[:space:]]*#/{:a;n;p;ba};" "$0")
  eval "$cmd"
  exit
}

if [ ! -e  ]
then
    echo "ok"
else
    echo "nok"
fi

