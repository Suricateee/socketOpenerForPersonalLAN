amixer -D pulse set Master 40% unmute
(ffplay -nodisp -nostats -hide_banner -autoexit https://www.myinstants.com/media/sounds/fnaf-freddys-music-box.mp3 && ffplay -nodisp -nostats -hide_banner -autoexit https://www.myinstants.com/media/sounds/power-outage-sound-effect.mp3) &
number=1.00
while (( $(bc <<< "$number >= 0") )); do
    xrandr --output $(xrandr | awk '/\yconnected\y/{print $1}') --brightness $number
    number=$(bc <<< "$number - 0.01")
    sleep 0.1
done

wait

for run in {1..25};do
  (xeyes -fg black -geometry +$(shuf -i 0-1528 -n 1)+$(shuf -i 0-887 -n 1)) &
done

ffplay -nodisp -nostats -hide_banner -autoexit https://www.myinstants.com/media/sounds/prowler-sound-effect_6bXErot.mp3 &
sleep 1
xrandr --output $(xrandr | awk '/\yconnected\y/{print $1}') --brightness 1

sleep 1

shutdown now
