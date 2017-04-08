.name "zork"
#this is a comment !
.comment "just a living prog"
l2:
live %1
sti r1,%:live,%1
and r1,%0, r1
live: live %1
zjmp %:l2
