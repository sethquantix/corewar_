.name "write"
.comment "yolo"

# 01 23 45 67
# 89 AB CD EF

ld %19088743, r2
ld %-1985229329, r3
st r2,128
st r3,127

write:
aff r2
