#!/bin/sh

#
# Checks
#

if which img2txt; then
	echo "You need img2txt from caca-utils"
fi

if which ffmpeg; then
	echo "You need ffmpeg"
fi

if test $# -lt 2;
then
	echo "Usage $0 [VIDEOFILE]"
fi

if test -d ./frames; then
	echo "The ./frames subdirectory already exists please remove first"
	exit 1
fi

if test -f "./out.txt"; then
	echo "The output file ./out.txt is already present, not overwriting"
	exit 1
fi

#
# Extract all frames
#

mkdir ./frames
ffmpeg -i "$1"  -r 24 frames/%08d.jpg


# Now we use CACA utils to generate the output

echo "Generating text from images ..."

for i in ./frames/*.jpg
do
	echo "Converting '$i' to text ..." >&2
	img2txt -f utf8 -W100 -H 60 "$i"
	printf "\033[H"
done > ./out.txt

echo "Output is in out.txt"
