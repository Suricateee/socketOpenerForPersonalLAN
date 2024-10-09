amixer -D pulse set Master 25% unmute && timeout 20 ffplay -nodisp -nostats -hide_banner -autoexit https://www.myinstants.com/media/sounds/daisy-bell-creepy-version.mp3 &
for run in {1..8};do
sleep $(shuf -i 0-3 -n 1)
  timeout 1 eom -f https://images-wixmp-ed30a86b8c4ca887773594c2.wixmp.com/f/c4c11f93-3679-4c5b-adbe-17751c1cc59e/dfv9czw-64d228b6-7300-456e-bf7d-e26439ed5f8a.png?token=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJ1cm46YXBwOjdlMGQxODg5ODIyNjQzNzNhNWYwZDQxNWVhMGQyNmUwIiwiaXNzIjoidXJuOmFwcDo3ZTBkMTg4OTgyMjY0MzczYTVmMGQ0MTVlYTBkMjZlMCIsIm9iaiI6W1t7InBhdGgiOiJcL2ZcL2M0YzExZjkzLTM2NzktNGM1Yi1hZGJlLTE3NzUxYzFjYzU5ZVwvZGZ2OWN6dy02NGQyMjhiNi03MzAwLTQ1NmUtYmY3ZC1lMjY0MzllZDVmOGEucG5nIn1dXSwiYXVkIjpbInVybjpzZXJ2aWNlOmZpbGUuZG93bmxvYWQiXX0.eNFQSqtyGfgD616dTKfnMq4R-nYDQ-mW00aIskvR2N0
done
