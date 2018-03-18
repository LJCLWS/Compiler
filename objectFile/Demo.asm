.data
res	DD	?
len	DD	?
wid	DD	?
tep	DD	?
t0	DD	?
t1	DD	?
t2	DD	?
t3	DD	?
t4	DD	?
t5	DD	?
t6	DD	?
t7	DD	?
.code

main PROC

MOV	EAX,5
MOV	EBX,3
MOV	ECX,EBX
ADD	EBX,1
IMUL	EBX,EAX
MOV	EDX,EBX
MOV	res,EBX
CMP	EBX,EAX
MOV	len,EAX
MOV	wid,ECX
MOV	tep,EDX
JNL	EL
MOV	EAX,len
ADD	EAX,wid
ADD	EAX,res
JMP	IFEND
EL:	
MOV	EAX,8
SUB	EAX,len
MOV	EBX,len
ADD	EBX,wid
ADD	EBX,EAX
IFEND:	

ret
main ENDP
END
