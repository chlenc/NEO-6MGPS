#!/usr/bin/env bash

if [ -z "$0" ]
then
dev=$0
else
dev=/dev/cu.usbmodem14201
fi

if [ -z "$1" ]
then
filePath=$1
else
filePath=output.txt
fi

script -t 0 ${filePath} screen ${dev} 9600
