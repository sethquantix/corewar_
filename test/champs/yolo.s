.name "test"
.comment "yolo"


fork %:living_chieur
ld %0, r2
live %1
live %1
st r2, :chieur
sti r2, %:chieur, %2
zjmp %:youpi
living_chieur:
live %1
chieur:
fork %:chieur
aff r2
youpi:
sti r1, %:live, %1
live:
live %1
ld %0, r2
zjmp %:live
