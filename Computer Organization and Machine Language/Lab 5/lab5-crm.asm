; lab5-crm in NASM assembly
;    *  to assemble, use the command "nasm lab5-crm.asm -o lab5-crm.com"
;    *  to execute in DOSBox, type "lab5-crm"
; This program will let the user enter a fraction of the form M/N where M < N and will print the expansion to 6 decimal places. 

; Header section
	org 100h	; program origination point

section .data
Prompt1    db  "Numerator: ", '$'
Prompt2    db  "Denominator: ", '$'
Prompt3    db  "Decimal output is: ", '$'
EMSG       db  "Please enter a number between 0 and 9 ", '$'

section .bss
M   RESb    1   
N   RESb    1

section .text

main:
; print user prompt 
mov     dx, Prompt1    	; get message
mov     ah, 09h     	; display string function
int     21h         	; display it
call    DEC_IN      	
mov     [M], bx     	; move numerator to memory location M

; print second prompt
mov     dl, 0Ah     	; line feed moved into char display register
mov     ah, 02h     	; char display function
int     21h         	; display line feed
mov     dl, 0Dh     	; carriage return moved into char display register
int     21h         	; display carriage return
mov     dx, Prompt2    	; get message
mov     ah, 09h     	; display string function
int     21h         	; display it
call    DEC_IN
mov     [N], bx     	; store denominator in memory location N
mov     dl, 0Ah     	; line feed moved into char display register
mov     ah, 02h     	; char display function
int     21h         	; display line feed
mov     dl, 0Dh     	; carriage return moved into char display register
int     21h         	; display carriage return
mov     dx, Prompt3    	; get message
mov     ah, 09h     	; display string function
int     21h         	; display it
mov     dl, 2Eh     	; move '.' to display char register
mov     ah, 02h     	; display char function
int     21h         	; displays it
mov     cx, 6       	; set loop to run 6 times
mov     bx, [M]     	; prepare numerator in M to be multiplied
jmp     print

DEC_IN:
; input character from keyboard, converts ASCII to appropriate binary
push    ax
xor     bx,bx
.top:
mov     ah, 01h     	; keyboard input function
int     21h         	; char input, copies char into AL
cmp     al, 0Dh     	; is the input a carriage return?
je      .done       	; user is done
cmp     al, 30h     	; compares input to ASCII code for 0
jb      error       	; if input is less than 0 jump to error
cmp     al, 39h     	; compares input to ASCII code for 9
ja      error       	; if input is greater than 9 jump to error
sub     al, 30h     	; subtracts 30h to make the ASCII code into the base 10 number
imul    bx, 10      	; in case the number is more than one digit
mov     ah, 0       	; clear AH before copy
add     bx, ax      	; store AX in BX so it can run again.
jmp     .top
.done:
pop     ax
ret

print:
; loop to print 
xor     ax, ax      	; clear AX
mov     al, 10      	; prepare for multiplication
mul     bl          	; multiply numerator in BL by 10 in AL
xor     bl, bl      	; clear bl to be used again
mov     bl, [N]     	; move denominator in to BL
div     bl          	; divide numerator * 10 in AX by denominator in BL
mov     dl, al      	; move quotient in AL to display char register
push    ax          	; save the remainder in AH
add     dl, 30h     	; convert quotient to respective ASCII symbol
xor     ax, ax      	; clear ax for function
mov     ah, 02h     	; display char function
int     21h         	; display it    
pop     ax          	; retrieve remainder in AH
mov     bl, ah      	; move remainder to BL to start loop over
loop    print
jmp     exit

error:
; displays error message then jumps back to DEC_IN
mov     dl, 0Ah     	; line feed moved into char display register
mov     ah, 02h     	; char display function
int     21h         	; display line feed
mov     dl, 0Dh     	; carriage return moved into char display register
int     21h         	; display carriage return
mov     dx, EMSG    	; moves error message into display string register
mov     ah, 09h     	; display string function
int     21h         	; displays it
mov     dl, 0Ah     	; line feed moved into char display register
mov     ah, 02h     	; char display function
int     21h         	; display line feed
mov     dl, 0Dh     	; carriage return moved into char display register
int     21h         	; display carriage return
jmp     main        

exit:
;exit to DOS
 mov     ah, 04Ch      	; Exit program 
 mov     al, 0         	; Return exit code value
 int     21h           	; Terminate program 