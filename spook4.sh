amixer -D pulse set Master 75% unmute
(ffplay -nodisp -nostats -hide_banner -autoexit https://www.myinstants.com/media/sounds/fnaf-freddys-music-box.mp3 && ffplay -nodisp -nostats -hide_banner -autoexit https://www.myinstants.com/media/sounds/power-outage-sound-effect.mp3) &
number=1.00
while (( $(bc <<< "$number >= 0") )); do
    xrandr --output $(xrandr | awk '/\yconnected\y/{print $1}') --brightness $number
    number=$(bc <<< "$number - 0.01")
    sleep 0.1
done

sleep 1

shutdown now
