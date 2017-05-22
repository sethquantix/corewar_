.name	"12"
.comment "test"

start:
	ld	:plop, r2
	st	r2, :start

plop:
	live %0xFFFFFFFF
