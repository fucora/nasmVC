

message:  db 'hello, world',13,10,'$'

_main:	  mov dx,message
	  mov ah,9
	  int 21h
	  mov ax,4c00h
	  int 21h
