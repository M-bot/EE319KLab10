; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 

    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB

  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
a EQU 0
LCD_OutDec
	SUB SP, #8				; allocate two variables
	STR LR,[SP,#4]			; save LR
	MOV R3, #10				; 10
	UDIV R2, R0, R3			; n / 10
	MLS R1, R2, R3, R0		; n % 10
	STR R1,[SP,#a]			; a = n % 10
	MOVS R0, R2				; n = n / 10
	BLNE LCD_OutDec			; if(n / 10 != 0) LDC_OutDec(n /10)
	LDR R0,[SP,#a]			; a
	ADD R0, #0x30			; a = a + 0x30 , ascii
	BL ST7735_OutChar		; ST7735_OutChar(a)
	ADD SP, #8				; deallocate two variables
	LDR PC,[SP,#-4]			; restore LR

;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
	SUB SP, #8			; allocate two variables
	STR LR,[SP,#4]		; save LR
	LDR R1,=9999		; max
	CMP R0, R1			; check max
	BLS S				; 
	
	MOV R0, #0x2A		; 
	BL ST7735_OutChar	; print('*')
	MOV R0, #0x2E		; 
	BL ST7735_OutChar	; print('.')
	MOV R0, #0x2A		; 
	BL ST7735_OutChar	; print('*')
	MOV R0, #0x2A		; 
	BL ST7735_OutChar	; print('*')
	MOV R0, #0x2A		; 
	BL ST7735_OutChar	; print('*')
	B E					; return

S	MOV R2, #1000			; 1000
	UDIV R1, R0, R2			; a = n / 1000
	MLS R0, R1, R2, R0		; n = n % 1000
	STR R0,[SP,#0]			; n
	MOV R0, R1
	ADD R0, #0x30
	BL ST7735_OutChar		; print(a)
	
	MOV R0, #0x2E			; 
	BL ST7735_OutChar		; print('.')
	LDR R0,[SP,#0]			; n
	
	MOV R2, #100			; 100
	UDIV R1, R0, R2			; a = n / 100
	MLS R0, R1, R2, R0		; n = n % 100
	STR R0,[SP,#0]			; n
	MOV R0, R1
	ADD R0, #0x30
	BL ST7735_OutChar		; print(a)
	LDR R0,[SP,#0]			; n
	
	MOV R2, #10				; 10
	UDIV R1, R0, R2			; a = n / 10
	MLS R0, R1, R2, R0		; n = n % 10
	STR R0,[SP,#0]			; n
	MOV R0, R1
	ADD R0, #0x30
	BL ST7735_OutChar		; print(a)
	LDR R0,[SP,#0]			; n
	
	ADD R0, #0x30			; n = a
	BL ST7735_OutChar		; print(a)
	
E	ADD SP, #8				; deallocate two variables
	LDR PC,[SP,#-4]			; restore LR
 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
