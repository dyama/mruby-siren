#!/bin/bash
# coding: utf-8

SCRIPT_DIR=$(cd $(dirname $0); pwd)
TARGET_DIR="$SCRIPT_DIR/.."
find "$TARGET_DIR" -type f -name '*~' -exec rm {} \;

