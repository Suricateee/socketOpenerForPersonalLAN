amixer -D pulse set Master 50% unmute && ffplay -nodisp -nostats -hide_banner -autoexit https://www.myinstants.com/media/sounds/slender_static_AfgJiHy.mp3 &
timeout 5 eom -f https://cdn.drawception.com/images/panels/2017/6-2/tcWmQgk3ZR-1.png
for run in {1..2};do
  xrandr -o $(shuf -i 1-3 -n 1)
  sleep $(shuf -i 1-2 -n 1)
done
notify-send "Man in the dark" "You're not alone" &
xrandr -o 0
