echo "Let's go :)"
echo -n "Build => "

if [ ! -f ./zappy_server ]; then
  make zappy_server > /dev/null || exit 1
fi

if [ ! -f ./zappy_ai ]; then
  make zappy_ai > /dev/null || exit 1
fi

if [ ! -f ./zappy_graphic ]; then
  make zappy_graphic > /dev/null || exit 1
fi

echo "Success :)"

echo "Launch server"
./zappy_server -p 4242 -x 10 -y 10 -n team1 team2 -c 4 -t 100 > /dev/null &
sleep 1
for((i=0;i<2;i++))
do
  echo "Launch client " $i " team1"
  ./zappy_ai -n team1 -p 4242 > /dev/null &
  sleep 0.5
  echo "Launch client " $i " team2"
  ./zappy_ai -n team2 -p 4242 > /dev/null &
  sleep 0.5
done

echo "Launch graphic inerface (Close window for stop game)"

./zappy_graphic localhost 4242 > /dev/null

pkill -f zappy_server
pkill -f zappy_ai
make clean

echo "It's over :'("
