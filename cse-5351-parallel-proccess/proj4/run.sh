PROBLEM1="3dhs.c"
EXE1="3dhs"

OUTPUT_FILE="out.txt"

rm -f $EXE1 $EXE2 $EXE3 $OUTPUT_FILE

echo "Compiling $PROBLEM1..."
gcc -fopenmp -o $EXE1 $PROBLEM1 -lm
if [ $? -ne 0 ]; then
    echo "Compilation of $PROBLEM1 failed."
    exit 1
fi


echo "Running $EXE1..."
./$EXE1 > $OUTPUT_FILE
echo "$EXE1 finished."