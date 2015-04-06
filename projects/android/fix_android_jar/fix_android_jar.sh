#!/bin/bash

NEW=$1
ORG=$2

if [ "$ORG" = "" ]
then
    echo "Usage: new_android.jar sdk_android.jar"
    exit 0
fi

rm -rf new org
mkdir -p new org
unzip -d new $NEW >/dev/null
unzip -d org $ORG >/dev/null
cp -f org/resources.arsc new/resources.arsc
cd new && zip -r ../android.fix.jar * >/dev/null && cd -
rm -rf new org

echo The fixed android.jar is android.fix.jar.
