for run in {1..10};do
  (amixer -D pulse set Master 100% unmute && timeout 5 xeyes -fg black -geometry +$(shuf -i 0-1528 -n 1)+$(shuf -i 0-887 -n 1) & ffplay -nodisp -nostats -hide_banner -autoexit https://www.myinstants.com/media/sounds/minecraft-cave-sound-6.mp3 || amixer -D pulse set Master 0% mute) &
sleep 3
done
