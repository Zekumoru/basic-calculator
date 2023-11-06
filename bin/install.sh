#!/bin/bash
# Qt6 Basic Applications Libraries Installation
# @author Zekumoru Dragonhart
# @version 1.231106

# Color variables
red="\033[0;31m"
green="\033[0;32m"
yellow="\033[0;33m"
clear="\033[0m"

qtGitHubLink=https://github.com/3AIS-E-Molinari-2023-24/qt6-libs/raw/main
qtLibraryPath=/usr/local/lib/Qt

libraries=(libicuuc.so.56 libicudata.so.56 libicui18n.so.56 libQt6Core.so.6 libQt6OpenGL.so.6 libQt6DBus.so.6 libQt6Widgets.so.6 libQt6Gui.so.6 libQt6XcbQpa.so.6 plugins/platforms/libqxcb.so)

downloadLib() {
  if [ ! -f "$qtLibraryPath/$1" ]; then
    sudo wget -P "$qtLibraryPath/$(dirname $1)" "$qtGitHubLink/$1"
  fi
}

if [ "$1" = "-r" ]; then
  sudo rm -rf $qtLibraryPath
fi

# Download all necessary libraries
for library in ${libraries[@]}; do
  downloadLib $library
done

hasDownloadedAllNecessaryLibraries=true
for library in ${libraries[@]}; do
  if [ ! -f "$qtLibraryPath/$library" ]; then
    hasDownloadedAllNecessaryLibraries=false
  fi
done


if [ "$hasDownloadedAllNecessaryLibraries" = false ]; then
  echo -e "${red}ERR: Not all necessary Qt libraries have been installed, please re-execute this script!${clear}"
  echo "Note: If you cannot open the Qt application and/or receiving 'Bus error (core dumped)', please try re-running this script passing the -r option, e.g.:"
  echo ""
  echo "    ./$0 -r"
  echo ""
else
  echo "All necessary Qt libraries have been downloaded"
fi

isBashRcModified=false

# Add Qt library path to bashrc
if ! grep -q "export LD_LIBRARY_PATH=.*:\?/usr/local/lib/Qt" ~/.bashrc; then
  echo "# set Qt library path" >> ~/.bashrc
  echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/Qt" >> ~/.bashrc
  echo "" >> ~/.bashrc
  echo "Added Qt LD_LIBRARY_PATH to user's bashrc"
  isBashRcModified=true
fi

# Add Qt plugins path to bashrc
if ! grep -q "export QT_PLUGIN_PATH=.*:\?/usr/local/lib/Qt/plugins" ~/.bashrc; then
  echo "# set Qt plugins path" >> ~/.bashrc
  echo "export QT_PLUGIN_PATH=$QT_PLUGIN_PATH:/usr/local/lib/Qt/plugins" >> ~/.bashrc
  echo "" >> ~/.bashrc
  echo "Added QT_PLUGIN_PATH to user's bashrc"
  isBashRcModified=true
fi

if [ "$isBashRcModified" = true ]; then
  echo -e "${yellow}Please restart your terminal to reflect changes in the .bashrc file${clear}"
fi
