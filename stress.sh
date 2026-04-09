#!/bin/bash

# Compile the files (O3 flag speeds up the brute force slightly)
echo "Compiling..."
g++ -O3 gen.cpp -o gen
g++ -O3 brute.cpp -o brute
g++ -O3 cp.cpp -o sol
echo "Running..."
# Run the test loop
for ((i = 1; ; ++i)); do
    # Generate the testcase and save it to in.txt
    ./gen > in.txt
    
    # Run both solutions
    ./sol < in.txt > out.txt
    ./brute < in.txt > brute_out.txt
    
    # Compare outputs (-w ignores trailing whitespaces/newlines)
    diff -w out.txt brute_out.txt > /dev/null || break
    
    # Print progress every 100 iterations to avoi spamming the consoled
    if (( i % 100 == 0 )); then
        echo "Passed $i tests..."
    fi
done

echo -e "\nin.txt \n"
cat in.txt
echo -e "\nbrute_out.txt \n"
cat brute_out.txt
echo -e "\nout.txt \n"
cat out.txt