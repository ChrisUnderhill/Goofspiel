#!/bin/bash

x-terminal-emulator -e ./game.out 5000 &
x-terminal-emulator -e ./client.out localhost 5000 &
sleep 2s
x-terminal-emulator -e ./client.out localhost 5000 &
