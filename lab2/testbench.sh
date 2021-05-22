input_file="$1"
answer_file="$2"
executable_file="$3"

for i in {0..2}; do
  for j in {0..2}; do
    output_file="output-${i}-${j}.txt"
    command="${executable_file} ${i} ${j} < ${input_file} > ${output_file}"
    time=$(/usr/bin/time timeout 10 bash -c "${command}" 2>&1)
    is_timeout=$?
    diff "$answer_file" "$output_file" &>/dev/null
    diff_ok=$?
    echo "${is_timeout} ${diff_ok} ${time}"
  done
done
