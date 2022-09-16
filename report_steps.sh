#!/bin/bash

FILE_NAME_STEPS="steps"
ALL_STEPS="sa,sb,ss,pa,pb,ra,rb,rr,rra,rrb,rrr"
TOTAL_MOVES=$(cat "$FILE_NAME_STEPS" | wc -l)
QTY=1000
BIN="push_swap"

create_random_numbers() {
	seq $QTY | shuf | awk 'NR % 2' | tr '\n' ' ' > random_numbers
}

run_push_swap () {
	./push_swap $(cat random_numbers) > steps
}

count_of_steps() {
	STEP=$1
	COUNT_OF_MOVES=$(cat "$FILE_NAME_STEPS" | grep "$STEP" | wc -l)
	if [ $COUNT_OF_MOVES -gt 0 ]; then
		PERCENTAGE=$(echo "scale=4;$COUNT_OF_MOVES/$TOTAL_MOVES" | bc | sed 's/\.//g' )
		printf "%s= %d - (%s%%)\n" $STEP $COUNT_OF_MOVES $(echo "scale=1;$PERCENTAGE / 100" | bc)
	fi
}


create_random_numbers
run_push_swap
sleep 2

for s in $(echo $ALL_STEPS | tr ',' ' '); do
	count_of_steps $s
done

echo $TOTAL_MOVES