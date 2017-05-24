.name "zork"
.comment "I'M ALIIIIVE"

omgggggggggg:
	sti r1, %:live, %0xff
	and r1, %1, r1

 live:
	live %0XFFFFFFFF
	zjmp %:live
