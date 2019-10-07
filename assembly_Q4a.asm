quotient:     dc.w    #-1       |this will store the amount of times dividend can be divided by divisor, it starts at -1 as it is incremented later on
dividend:     dc.w    #32       |number being divided
divisor:      dc.w    #5        |The divisor


                        MOVE.w  dividend, D0  |D0 will store the remainder
                        MOVE.w  quotient, D1  |D1 will store the answer
                        MOVE.w  divisor, D2   |D2 will store the divisor

            loop:       INC     D1            |Increment the answer by 1
                        SUB     D2, D0        |subtract the remaining n by d
                        BPL     loop          |if its still positive go to loop
                        ADD     D2, D0        |remainder cannot be negative so redo the last subtraction to make remainder positive

|Extra explanation-----------------------------------------------------------------------------------------------------------------------------------------

| quotient started at -1 as if it started at 0 then it will be incremented to be 1. And if in the first step D0-D2 is negative then the quotient will be 1
| When it is supposed to be 0. For example:
| dividend = 1
| divisor = 5
| 1/5 is 0 remainder 5

|if quotient started at 0 it would return 1 rather than 0.
|Another way to solve this is to subtract quotient by 1 in the end.
