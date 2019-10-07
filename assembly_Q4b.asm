num:          dc.w    #111    |The number we are checking if it is prime
result:       ds.b    1       |result will is a byte of memory that will either be 0 if num is not prime or 1 otherwise.


                          MOVE.b  #1, D1
                          MOVE.b  #14, D3
                          MOVE.w  num, D0

                          SUB.w   #1, D0        | First check if num is 1 if so then directly move 0 to result
                          BEQ     move0
                          SUB.w   #2, D0        | Next check if num is 2 or 3, if so directly return 1 to result
                          BLE     move1
                          MOVE.w  num, D0       | return num back to D0, and shift it right. if there is a carry then it
                          ASR.w   D0            | is odd so continue, otherwise move 0 to result.
                          BCS     14shift
                          jmp     move0


            14shift:      ASL     D1            | shift the bit to the left 14 times so that D1 is the largest
                          DEC     D3            | possible power of 4 allowed in a 16-bit register.
                          BGT     14shift

                          MOVE.w  num, D0       | if D0 is already the highest power of 4 less than D0 then skip
                          SUB.w   D1, D0        | the highest4 loop and go directly to squareRoot.
                          BEG     squareRoot

            highest4:     MOVE.w  num, D0       | while D0 is not the highest power of 4 less than num, shift D0
                          ASR     D1            | to the right twice. This keeps D0 as a power of 4. once D0<num
                          ASR     D1            | the code has reached the highest possible D0 and we can leave the loop
                          MOVE.w  D1, D3
                          SUB.w   D3, D0
                          BMI     highest4

                          MOVE.w  #0, D3        | D3 will store the squareRoot so set it to zero to start.

            squareRoot:   MOVE.w  D0, D2        | subtract the current value of num (stored in D0) by D3, and D1
                          SUB.w   D3, D2        | if it num<D3+D1 then branch to lessThan, otherwise keep going
                          BMI     lessThan      | D0 is moved to D2 so that the actual value of D0 is not affected
                          SUB.w   D1, D2
                          BMI     lessThan
                          SUB.w   D3, D0        | if num>=D3+D1 then subtract the current num by (D3+D1)
                          SUB.w   D1, D0
                          ASR.w   D3
                          ADD.w   D1, D3
            check:        ASR.w   D1
                          ASR.w   D1
                          BNE     squareRoot   | if D1 is not 0 then repeat squarRoot
                          JMP     skip         | otherwise go to skip and start dividing as we found the squareRoot
            lessThan:     ASR.w   D3           | if num<D3+D1 then simply right shift D3
                          JMP     check        | go to check to know if we finished or not

            skip:         MOVE.w  num, D0       | getting ready to divide num by 3
                          MOVE.w  #3, D2

            divisorLoop:  JSR     loop          |run the loop on num and the current D2
                          DEC.w   D0            |if remainder is 0 then 0+0 will remain 0 otherwise it will be anything other than 0.
                          BMI     move0         |if it is zero then go to the end without adding 1 to D0 as num is not prime
                          MOVE.w  num, D0       |move num back to D0 to check if we should stop running the loop
                          ADD.w   #2, D2        |increment D2 to try the next divisor
                          MOVE.w  D3, D0
                          INC     D0            |increment D0, to ensure that the square root itself was tested
                          SUB.w   D2, D0        |if the divisor has reached the square root+1 we should stop.
                          BLE     move1         |if we did reach the point where divisor=num then num has no divisor less than it so it is prime, move 1 to D0 then move it result
                          MOVE.w  num, D0       |if divisor is still not equal to num then we keep going, restart by moving num back to D0
                          JMP     divisorLoop   |Call the function again and keep going until divisor=num

            loop:         SUB     D2, D0        |this block of code subtracts the divisor from dividend or num until it hits a negative. In which case the remainder is found.
                          BPL     loop          |if its still positive go to loop
                          ADD     D2, D0        |redo the last subtraction to make remainder positive
                          RTS                   |return to the statement after the function call

            move1:        MOVE.w  #1, D0        |This block of code is only accessed id num is prime, it makes D0 1 then goes to the end
                          JMP     end

            move0:        MOVE.b  #0, D0
            end:          MOVE.b  D0, result     |Move whatever is in D0 to result for the final answer.
