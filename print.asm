section .text

global _print

_print:
    ;mov ecx, [esp + 4]
	
	
	mov [myebx], ebx
	mov [myebp], ebp
	mov [myesp], esp
	mov [myesi], esi
	mov [myedi], edi
    mov dl,0
    mov [flagPlus],dl
    mov [flagMinus],dl
    mov [flagSpace],dl
    mov [flagZero],dl
    mov [commonSign],dl
    mov [sign],dl
           
	mov eax, 0	
    mov [tekStartPos],eax
    mov [lengthNumber],eax
    mov [flagWidth],eax	
    xor edx, edx
	mov ecx, [esp + 8]
	mov ebx,0
	getLen_Width:
      mov edi, eax 
      cmp byte [ecx + eax], 0
      je startFormat   
      cmp byte [ecx + eax], 49
	  
	  jae getWidth
	  inc eax
	  jmp getLen_Width	

	getWidth:
	   mov dl, [ecx + eax]
	   cmp dl, 48
	   jae recordWidth
	   mov [flagWidth], ebx


	   jmp startFormat

	recordWidth:
	   inc eax
	   mov esi, ebx
	   sub dl, 48	  
	    
	   
	   add ebx, esi  ;*2
	   add ebx, esi  ;*3
	   add ebx, esi  ;*4
	   add ebx, esi  ;*5
	   add ebx, esi  ;*6
	   add ebx, esi  ;*7
	   add ebx, esi  ;*8
	   add ebx, esi  ;*9
	   add ebx, esi  ;*10

	   add ebx, edx   
	   jmp getWidth
	  
	  
	  startFormat: dec edi
	  mov eax, edi
	format:
	   cmp eax, -1
	   je also

	   cmp byte [ecx + eax], 45
	   je  setFlagMinus

	   cmp byte [ecx + eax], 43
	   je  setFlagPlus 

	   cmp byte [ecx + eax], 32
	   je  setFlagSpace 

	   cmp byte [ecx + eax], 48
	   je  setFlagZero


	setFlagMinus:
	   mov dl,1
	   mov [flagMinus], dl
	   dec eax
	   jmp format

	setFlagPlus:
	   mov dl,1
	   mov [flagPlus], dl
	   mov [commonSign], dl
	   mov dl, 0
	   mov [flagSpace], dl
	   dec eax
	   jmp format

	setFlagSpace:
	   mov dl,1
	   mov [flagSpace], dl
	   dec eax
	   jmp format

	setFlagZero:
	   mov dl,1
	   mov [flagZero], dl
	   dec eax
	   jmp format

  also:
	mov eax, 0	
	xor edx, edx

	mov ecx, [esp + 12]

	mov esi, 0
	mov bl,[ecx]
	mov bl,'-'
	cmp  [ecx], bl
	je minus
    mov bl,0

	xor eax, eax

	getLen_in:	    
		cmp byte [ecx + eax], 0x0
		je getLen_out
		inc eax
		jmp getLen_in

	
	getLen_out:
	dec eax
	mov ebx, 0
	mov esi, 0
	jne getChar
	 
	getChar:
	    cmp eax, -1    
		je Null
		mov dl, [ecx + eax] 

	    sub dl, 0x30
		cmp dl, 9
		
		jbe record 

		sub dl, 7
		cmp dl, 15
		jbe record

		sub dl, 32
		jbe record
		
	
	record:	  
	  dec eax
	  xor esi, 1

	  jnz oneRecord
	  shl dl, 4	  

	  or dl, [ptr + ebx]
	  mov [ptr + ebx], dl
	  inc ebx
	  jmp getChar
	
	oneRecord:
	  mov [ptr + ebx], dl 	  
	  jmp getChar

    Null:
	  mov esi, 624 ;ìàêñèìàëüíàÿ ñòåïåíü 10 -1
	  mov ebp, 0 ; 
      jmp invercia
	  
     minusZero:
     mov dl,0
     mov [sign],dl
     
     jmp nextOperation	  
	  
	  

	invercia:
	  mov eax, [ptr + 12]     
      mov ebx,[ptr]
      add eax,ebx
      mov ebx,[ptr + 4]
      add eax,ebx
      mov ebx, [ptr + 8]
      add eax,ebx
       mov ebx,0
	  mov edx,0
	  mov dl,0
      cmp eax, 0
      je minusZero
      mov eax, [ptr + 12]
	  and eax,0x80000000
	 
	  mov ebx,0
	  mov edx,0
	  mov dl,0

	  jz setCommonSign
	  mov eax, [ptr]
	  not eax
	  add eax, 1
	  mov [ptr],eax

	  mov eax, [ptr + 4]
	  not eax
	  adc eax,0
	  mov [ptr + 4],eax

	  mov eax, [ptr + 8]
	  not eax
	  adc eax,0
	  mov [ptr + 8], eax

	  mov eax, [ptr + 12]
	  not eax
	  adc eax,0
	  mov [ptr + 12], eax

	  mov dl,[sign]
	  cmp dl,0
	  jne haveSign
	  inc dl
	  mov [sign],dl
	  mov [commonSign],dl
	  mov dl,0
	  jmp nextOperation
	  
	  setCommonSign:
	  mov bl,[sign]
      cmp bl,1
      jne nextOperation
	  mov [commonSign],bl
	  jmp nextOperation
   haveSign: 
	  dec dl
	  mov [sign],dl
	  mov dl,0
	nextOperation:
	 
	 ;while esi >0
	 ;mov bl,[sign]
	 cmp esi, 0
	 je write
	 mov ebx, [pow + 628]
	 mov eax, [ptr]

	 mov ebx, [pow + esi]
	 sub eax, ebx
	 mov [first], eax

	 mov eax, [ptr + 4]
	 mov ebx, [pow + esi + 4]
	 sbb eax, ebx
	 mov [second], eax

	 mov eax, [ptr + 8]
	 mov ebx, [pow + esi + 8]
	 sbb eax, ebx
	 mov [third], eax

	 mov eax, [ptr + 12]
	 mov ebx, [pow + esi + 12]
	 sbb eax, ebx
	 mov [four], eax
	 
	 jc recordDegree
	 jnc change 

   recordDegree:
	 shr esi, 4
	 mov [ans + esi], dl
	 ;mov [ans + 40],dl
	 mov dl, 0
	
	 shl esi, 4
	 sub esi, 16
	 jmp nextOperation

  change:
   
    mov eax,[first]
	mov [ptr], eax 
	
	mov eax,[second]
	mov [ptr + 4], eax

	mov eax,[third]
	mov [ptr + 8], eax

	mov eax,[four]
	mov [ptr + 12], eax

	inc dl
	jmp nextOperation

  write:

    mov edx, 40	
    mov eax,0
    jmp next
    setLengthForZero: mov edx,1
    jmp L6
	
 next:
    dec edx
    cmp edx, -1
    je setLengthForZero
	mov al, [ans + edx]
    cmp al, 0
	je next


	

	L6:
	mov eax, 0
	mov ecx, [esp + 4]
	mov bl,[sign]
	cmp bl,0
	je ifPlus


	L0:
	add eax,edx
	add eax,ebx
	mov ebx,0
	mov bl, [commonSign]
	cmp bl, 1
	je deleteSpaceTwo

	LTek:

	mov bl, [flagSpace]
	add eax,ebx
    mov [lengthNumber], eax
	mov ebx,[flagWidth]
	cmp eax,ebx
	jae changeWidth


	L1:
	  mov bl, [flagZero]
	  mov dl, [flagMinus]
	  cmp dl,bl
	  jae deleteZero
	L2:
	  mov bl, [flagSpace]
	  mov dl, [flagPlus]
	  cmp dl,bl
	  ja deleteSpace

	L3:	 
		mov eax,0	
		mov dl,[flagZero]
		cmp dl, 1
		je fillZero
		jmp fillSpaceTwo

	L4:  
	  mov dl, [flagSpace]
	  cmp dl, 1
	  je writeOneSpace 

	L5:
	mov dl, [ecx +2]
	  mov eax,[tekStartPos]
	   mov dl, [flagMinus]
	   cmp dl, 1
	   je writeSign
	   	  
	   mov dl,[flagZero]
	   cmp dl, 1      
	   je writeSign

	   mov ebx, 0
	   mov edx, [flagWidth]
	   mov eax, [lengthNumber]
	   mov bl,[flagSpace]
	   sub eax, ebx
	   sub edx, eax
	   mov ebx,0
	   ;mov bl, [commonSign]
	   ;add edx, ebx
	   mov eax,edx
	   jmp writeSign
	   
    getStartPos:	
	  mov ecx, [esp + 4]
	  mov dl, [ecx + 3]   
	   mov dl, [flagZero]
	   cmp dl, 1
	   jne begin
	   mov edx, [flagWidth]
	   mov eax, [lengthNumber]
	   mov bl,[flagSpace]
	   sub eax, ebx
	   sub edx, eax
	   mov ebx,0
	   mov bl,[commonSign]
	   add edx, ebx
	   mov eax, edx	   

	begin:

	mov edx, [lengthNumber]
	mov bl, [commonSign]
	sub edx, ebx
	mov bl, [flagSpace]
	sub edx, ebx
	;dec edx
	mov ecx, [esp + 4]
	mov bl, [ecx ]	
	
    only_write:
	   
       cmp edx, 0
	   je end

	   mov bl,[ans + edx]
	   add bl, 48
	   mov [ecx + eax], bl
	   mov bl,[ecx+3]
	   inc eax
	   dec edx
	   jmp only_write

	writeMinus:
	   mov bl, 45
	   mov [ecx + eax],bl
	   inc eax
	   jmp getStartPos

	writePlus:
	   mov bl, 43
	   mov ecx, [esp + 4]
	   mov [ecx + eax],bl
	   inc eax
	   jmp getStartPos
	writeSign:
	   mov bl,[sign]
	   cmp bl, 1
	   je writeMinus
	   mov bl,[flagPlus]
	   cmp bl,1
	   je writePlus
	   jmp getStartPos
  end:
	mov bl,0
    mov eax,[flagWidth]	
	mov [ecx + eax], bl

	mov ebx, [myebx]
	mov ebp, [myebp]
	mov esp, [myesp]
	mov esi, [myesi]
	mov edi, [myedi]
	
    ret

	minus: 
		mov dl, 1 
		mov [sign],dl
		
		;mov dl,0
		;mov [flagSpace], dl
		mov edx, 0
		mov esi,0
		inc ecx
		jmp getLen_in

	changeWidth:
	    mov[flagWidth], eax
		mov eax,0
		mov ebx,0
		jmp L1

	deleteZero:
	    mov dl,0
		mov [flagZero],dl
		mov ecx,[esp + 4]
		mov eax, [flagWidth]
		dec eax
		mov dl, 32
		fillSpace:
		    mov [ecx + eax], dl
			dec eax
			cmp eax,-1
			jne fillSpace
		mov eax, 0
	   jmp L2
	deleteSpace:
	   mov dl,0
	   mov [flagSpace],dl
	   jmp L3
	deleteSpaceTwo:
	   mov dl,0
	   mov [flagSpace],dl
	   jmp LTek
	fillZero:
	  mov eax,[flagWidth]
	  dec eax
	  mov dl, 48
	  mov ecx,[esp + 4]
	  onlyFill:
	     mov [ecx + eax], dl
		 dec eax
		 cmp eax,-1
		jne onlyFill
	 jmp L4

	fillSpaceTwo:
	  mov eax,[flagWidth]
	  dec eax
	  mov dl, 32
	  mov ecx,[esp + 4]
	  onlyFillTwo:
	     mov [ecx + eax], dl
		 dec eax
		 cmp eax,-1
		jne onlyFillTwo
	 mov eax,0
	 jmp L4
	writeOneSpace:
	  mov dl, 32
	  mov ecx,[esp + 4]
	  mov [ecx],dl
	  mov eax,1
	  mov [tekStartPos],eax
      jmp L5

	 ifPlus:
	   mov bl,[flagPlus]	   
	   jmp L0

	    
	   

section .rdata

pow dq 0x0,0x0,0x1,0x0,0xa,0x0,0x64,0x0,0x3e8,0x0,0x2710,0x0,0x186a0,0x0,0xf4240,0x0,0x989680,0x0,0x5f5e100,0x0,0x3b9aca00,0x0,0x2540be400,0x0,0x174876e800,0x0,0xe8d4a51000,0x0,0x9184e72a000,0x0,0x5af3107a4000,0x0,0x38d7ea4c68000,0x0,0x2386f26fc10000,0x0,0x16345785d8a0000,0x0,0xde0b6b3a7640000,0x0,0x8ac7230489e80000,0x0,0x6bc75e2d63100000,0x5,0x35c9adc5dea00000,0x36,0x19e0c9bab2400000,0x21e,0x2c7e14af6800000,0x152d,0x1bcecceda1000000,0xd3c2,0x161401484a000000,0x84595,0xdcc80cd2e4000000,0x52b7d2,0x9fd0803ce8000000,0x33b2e3c,0x3e25026110000000,0x204fce5e,0x6d7217caa0000000,0x1431e0fae,0x4674edea40000000,0xc9f2c9cd0,0xc0914b2680000000,0x7e37be2022,0x85acef8100000000,0x4ee2d6d415b,0x38c15b0a00000000,0x314dc6448d93,0x378d8e6400000000,0x1ed09bead87c0,0x2b878fe800000000,0x13426172c74d82,0xb34b9f1000000000,0xc097ce7bc90715,0xf436a000000000,0x785ee10d5da46d9,0x98a224000000000,0x4b3b4ca85a86c47a

section .bss
  first resb 4
  second resb 4
  third resb 4
  four resb 4

	myebx resb 4
	myebp resb 4
	myesp resb 4
	myesi resb 4
	myedi resb 4

ptr resb 16

ans resb 40
sign resb 1

flagPlus resb 1
flagMinus resb 1
flagZero resb 1
flagSpace resb 1
flagWidth resb 4

lengthNumber resb 4
commonSign resb 1
tekStartPos resb 4
