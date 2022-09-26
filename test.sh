#!/bin/bash
input="4_n"
COUNT=0
TOTAL_COUNT=0
COUNT_OKS=0
OPERATIONS="ra rb rr pa pb sa sb ss rra rrb rrr"

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
  echo "$line" - "moves:" $COUNT
  if [ $COUNT -gt 11 ]; then
	echo "$line" > 5_more
  fi
done < "$input"
echo "KO: ""$COUNT_OKS" \n "Total: " "$TOTAL_COUNT"