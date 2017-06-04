.name		"phoque"
.comment	"phoquephoque"

start:
	or		%35, %0x70030000, r3
	ld		%8, r5

begin:
	st		r3, :front
	add		r5, r3, r3
	st		r3, -9
	and		%0x80, r3, r2
	zjmp	%:begin
	ld		%0, r2
	zjmp	%-511
front:
	zjmp %:begin


ld		%0x03700300, r8
ld		%0x24045405, r9
ld		%0x03030370, r10
ld		%0x0303fff7, r11
ld		%0x06940000, r12
ld		%0x80030209, r13 # offset of 1 (first two bytes are 0)
ld		%0xffe90290, r14
ld		%0x0209fe01, r15 # offset of 4 (ld %0)



