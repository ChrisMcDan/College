; crm-lab1 in NASM assembly
;    *  to assemble, use the command "nasm crm-lab1.asm -o crm-lab1.com"
;    *  to execute in DOSBox, type "crm-lab1"

; Header section  -- instructions to the assembler
	cpu 286			; limit code to 16 bit for 80286 and earlier
	org 100h		; program origination point
	
; EQUates section
CR	equ	0Dh		; ASCII code for carriage return
LF	equ	0Ah		; ASCII code for line feed

; initialized data goes here	
section .data
msg	db  "Christopher McDaniel", CR, LF, '$' 	; define an ASCII$ string	

; uninitialized data goes here, if any
section .bss
	; for this program there is no uninitialized data

; the program body goes here
section .text
	
main:
	mov dx,msg		; load address of ASCII$ to display
	mov ah, 9		; display string function
	int 21h			; display the string

; the program termination code goes here	
	mov ah, 4Ch		; call for sys_exit
	mov al, 0		; normal termination code
	int 21h			; return to OS
	
;  other procedures which main calls (if any) go here