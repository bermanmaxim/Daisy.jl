#! /usr/bin/fish

rm -rf (ls | grep -v -E '^(.gitignore|clean.fish)$')