generator="$1"
executable="$2"

opcount=5000000
maxint=5000000

for mode in {0..2}; do
  bash -c "${generator} ${opcount} ${mode} ${maxint}"
  /usr/bin/time bash -c "${executable} 0 < input.txt >/dev/null"
  /usr/bin/time bash -c "${executable} 1 < input.txt >/dev/null"
done
