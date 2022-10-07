#!/bin/bash
input="4_n"
COUNT=0
TOTAL_COUNT=0
COUNT_OKS=0
MAX_COUNT=0
MIN_COUNT=999999999999
OPERATIONS="ra rb rr pa pb sa sb ss rra rrb rrr"
COUNT_LOOP=0
split_word() {

text="$1"
IFS="$2"

read -a strarr <<< "$text"
for val in "${strarr[@]}";
do
  printf "$val "
done

}

while IFS= read -r line
do
  COUNT_OK=$(./push_swap $(split_word "$line" " ") | grep KO | wc -l)
  if [ $COUNT_OK -gt 0 ]; then
	((COUNT_OKS++))
	echo "$line"
  fi
  COUNT=$(./push_swap $(split_word "$line" " ") | grep -E $(echo "$OPERATIONS" | tr " " "|")  | wc -l)
  ((TOTAL_COUNT=TOTAL_COUNT + COUNT))
  #printf "%s\n\nmoves:%s " "$line"
  #printf "\x1b[31m"%s"\x1b[0m\n" "$COUNT"
  if (($MAX_COUNT < $COUNT)); then
	MAX_COUNT=$COUNT
  fi
  if (($MIN_COUNT > $COUNT)); then
	MIN_COUNT=$COUNT
  fi
  ((COUNT_LOOP++))
done < "$input"
echo '-------------------------------------------------'
echo -e "KO: ""$COUNT_OKS"\
"\nAvg: " $(echo "$TOTAL_COUNT" / $COUNT_LOOP | bc) \
"\nMax: " "$MAX_COUNT"\
"\nMin: " "$MIN_COUNT"\
"\nTotal: " "$COUNT_LOOP"
echo '-------------------------------------------------'