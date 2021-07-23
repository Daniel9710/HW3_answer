#!/bin/bash

trace_dir=../traces

policies=("FIFO" "SJF" "RR" "MLFQ" "GUARANTEE")
trace_files=("test_50" "test_80" "test_100" "test_234" "test_500" "test_748"
        "test_1000" "test_7000" "test_10000" "test_20000" "test_50000")

quantum=("3" "5" "8" "11")
quantums=("2 4 6 8" "1 4 6 9" "3 4 5 6" "2 3 7 13")


for policy in "${policies[@]}"; do
    echo "============== $policy TEST =============="
    for trace_file in "${trace_files[@]}"; do
        if [ ${policy} = "FIFO" ] || [ ${policy} = "SJF" ]; 
        then
            timeout -s 9 20s ./schedule ${trace_dir}/${trace_file} ${policy} > test_result/${policy}_${trace_file}_res;
            
            DIFF=$(diff test_result/${policy}_${trace_file}_res ans/${policy}_${trace_file}_res)
            if [[ $DIFF != "" ]]; then
                echo "test ${trace_file}: FAIL"         
            else
                echo "test ${trace_file}: SUCCESS"
            fi    

        else
            for (( i=0; i<4; i++ )) do
                if [ "$policy" = "MLFQ" ]; 
                then
                    timeout -s 9 20s ./schedule ${trace_dir}/${trace_file} ${policy} ${quantums[i]} > test_result/${policy}_${trace_file}_${i}_res;
                else
                    timeout -s 9 20s ./schedule ${trace_dir}/${trace_file} ${policy} ${quantum[i]} > test_result/${policy}_${trace_file}_${i}_res;  
                fi
            
                DIFF=$(diff test_result/${policy}_${trace_file}_${i}_res ans/${policy}_${trace_file}_${i}_res)
                if [[ $DIFF != "" ]]; then
                    echo "test ${trace_file} case ${i}: FAIL"         
                else
                    echo "test ${trace_file} case ${i}: SUCCESS"
                fi  
            done
            if [ $? -ne 0 ]; then
		            echo "test ${trace_file}: TIMEOUT"
		            break
	        fi
        fi
    done
done
