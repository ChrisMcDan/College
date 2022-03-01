; Christopher McDaniel
; 2 October 2018       COSC 2329
; This program prompts the user to enter a base 16 number
; Then it prints the number entered in both Binary, Quaternary, Octal, and Hexadecimal
    cpu  286
    org  100h

section .data
prompt1: db 	oDh,oAh, "Please enter a hexadecimal number: $"
prompt2: db 	0Dh,0Ah, "The 16-digit Binary value for the entered number is: $"
prompt3: db 	0Dh,0Ah, "The 8-digit Quaternary value for the entered number is: $"
prompt4: db 	0Dh,0Ah, "The 6-digit Octal value for the entered number is: $"
prompt5: db	0Dh,0Ah, "The 4-digit Hexadecimal value for the entered number is: $"
prompt6: db	0Dh,0Ah, "Enter another number?(Y/N) $"

section .text
start:
	mov	ah,9		; print prompt
	mov 	dx,prompt1
	int	21h

	mov	bx,0		; put input to bx
	mov	ah,1		; store input
	int	21h		; read input
top1:
	cmp	al,0Dh		; char=cr
	je	out1		; jump to out1
	sal	bx,4		; bx*= 16
	cmp	al,'9'		; is num 0-9
	ja	AtoF		; if not jump to AtoF
	and	al,0Fh		; convert ascii to bin
	jmp	addit		; jmp to addit
AtoF:
	and	al,11011111b
	sub	al,55		; if value is A-F, sub 55
addit:
	or	bl,al
	int	21h
	jmp	top1

out1:
	mov	ah,9		; section output prompt2
	mov	dx,prompt2
	int	21h

	mov	cx,16		; counts loop 16 times
top2:   rol	bx,1		; rotates out lower bit
	jc	one		; if output1 jump to one
	mov	dl,'0'		; is 0
	jmp	print		; jump to print

one:    mov	dl,'1'

print:  mov	ah,2		; print output
	int 	21h
	loop	top2
	
out2:
	mov 	ah,9
	mov	dx,prompt3
	int	21h
	mov	cx,8		; counter = 8
	
top3:   rol	bx,2		; rotate
	mov	dl,bl		; store copy in dl
	and	dl,3		; want lower 8 bits
	or	dl,30h		; process 0-3 and convert to '0'-'3'
	jmp	print2	
	
print2: mov	ah,2
	int	21h
	loop	top3
	
out3:
	mov	ah,9		; section outputs prompt4
	mov	dx,prompt4
	int	21h
	
	mov	ah,2		; conversion for base 4
	rol	bx,1
	jmp	lead0
	jmp	print3

lead0:	mov	dl,'0'		; make leading number 0
	int	21h

print3:	mov	cx,5		; counter = 5

top4:	rol	bx,3
	mov	dx,bx
	and	dx,7h
	or	dx,30h

	int	21h
	loop	top4		; repeat until counter is done
	
out4:	
	mov	ah,9		; section outputs prompt5
	mov	dx,prompt5
	int	21h
	mov	cx,4		; run loop 4 times
	
top5:   rol	bx,4		; rotate lower 4 bits
	mov	dl,bl		; store it in dl
	and	dl,0Fh
	cmp	dl,9		; is input 0-9
	ja	a2f		; if not 0-9 jump to AtoF
	or	dl,30h		; else change 0-9 to '0'-'9'
	jmp	print4		; if 0-9 end line

a2f:    add	dl,55		; if not: convert if >9 to A-F

print4:	mov	ah,2		; loop until counter done
	int	21h
	loop	top5		; loop until counter done
	
out5:	
	mov	ah,9		; print prompt6
	mov	dx,prompt6
	int	21h
	
	mov 	ah,1		; store input
	int	21h
	mov	ah,al		; move input into ah
	 
	cmp	al,'y'		; does input = y
	je	start		; jump to start

exit:
	mov	ah,04Ch		; END CODE
	mov	al,0
	int	21h