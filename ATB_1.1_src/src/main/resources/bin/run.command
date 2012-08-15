#!/bin/sh
cd $(dirname "$0")
java -cp ..:../lib/* -splash:../etc/images/misc/splash.png ${application.mainClass}
osascript -e 'tell application "Terminal" to quit'
