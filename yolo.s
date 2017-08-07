.name "¯\_(ツ)_/¯"
.comment "stuff"

shrug:
sti		r1, %:live, %1
ld		%0x5f5cafc2, r1
aff		r1
ld		%0x8483e328, r1
aff		r1
ld		%0xc22f5f29, r1
aff		r1
ld		%0xaf, r1
aff		r1
ld		%0x00010004, r16

ld		%0, r1
zjmp	%:copy

train:
	ld		5, r1
	ld		%0x680e0034, r14
	train_loop:
		and		%0xff, r14, r15
		zjmp	%:live
		sub		r14, r16, r14
		st		r14, 6
		val:
			sti	r5, %0, %300
		ld		%0, r15
		zjmp	%:train_loop
	live:
		live	%0
zjmp	%278
copy:
	ld	-49, r2
	ld	-50, r3
	ld	-51, r4
	ld	-52, r5
	ld	-53, r6
	ld	-54, r7
	ld	-55, r8
	ld	-56, r9
	ld	-57, r10
	ld	-58, r11
	ld	-59, r12
	ld	-60, r13
	and	r13, %0xFFFF0000, r13

ld		%0, r1
zjmp	%:train
