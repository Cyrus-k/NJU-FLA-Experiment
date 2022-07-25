; input: a string of 1m01n, eg '11110111',the key is to use continuous minus, first copy first part of 1's to tape 2 and the second part to tape3
; then delete 1 on tape2 and 1 on tape3 at the same time,then find out which part is fewer then use the remain 1's to replace the corresponding part then start altogether again

; the finite set of states
#Q = {q0,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,q12,q13,q14}

; the finite set of input symbols
#S = {0,1}

; the complete set of tape symbols
#G = {0,1,_}

; the start state
#q0 = q0

; the blank symbol
#B = _

; the set of final states
#F = {q14}

; the number of tapes
#N = 3 

; the transition functions

; State q0: begin and copy the string left to 0 to the 2nd tape
q0 1__ 11_ rr* q0
q0 0__ 0__ rl* q1

; State q1: copy the string right to 0 to the 3nd tape 
q1 11_ 111 r*r q1
q1 _1_ _1_ l*l q2


; State q2: finish copying and start cmp
q2 111 1__ lll q2
q2 01_ 01_ l*r q3
q2 1_1 1_1 lrl q6
q2 0__ ___ rrr q12

; State q3: tape3 has been emptied start to clear tape2
q3 11_ 1__ ll* q3
q3 1__ ___ lr* q4

; State q4: tape3 has been cleared start to clear extra 1 on tape1
q4 1__ ___ l** q4
q4 ___ ___ r** q5

; State q5: fix head on tape1 and start again
q5 ___ ___ r** q5
q5 1__ 11_ rr* q0

; State q6: tape2 has been emptied start to clear tape3
q6 1_1 1_1 l*l q6
q6 0__ 0__ r*r q7

; State q7: copy tape 3 to right side of tape1
q7 1_1 1__ r*r q7
q7 1__ ___ r*l q8

; State q8: tape 3 has been cleared and clear extra 1 on tape1
q8 1__ ___ r** q8
q8 ___ ___ l** q9

; State q9: fix head to the most left on tape1 and find head on tape3
q9 ___ ___ l** q9
q9 1__ 1__ l** q10

; State q10: fix head to the most left on tape1 and fix head on tape3
q10 1__ 1__ l*l q10
q10 0__ 0__ l*r q11

; State q11: fix head to the most left on tape1
q11 1__ 1__ l** q11
q11 ___ ___ r** q0

; State q12: get gcd
q12 1__ ___ r** q12
q12 ___ ___ l** q13

; State q13: fix head on tape1
q13 ___ ___ l** q13
q13 1__ 1__ *** q14
