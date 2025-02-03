#!/bin/bash

find "./" \( -name "*.cpp" -o -name "*.hpp" -o -name "*.inl" \) -exec clang-format -i {} +