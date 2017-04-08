.name "ld"
.comment "is carry set to zero when coding byte is wrong"

# 80 00 00 01 == -2147483647
# 50 00 00 01 == 1342177281
# 09 00 00 00 == 150994944
# 54 00 00 01 == 1409286145
# 94 00 00 00 == -1811939328
# 40 00 00 00 == 1073741824


ld %1073741824, r2
ld %150994944, r3
sti r2, %:ld, %1
sti r3, %:ld, %6
ld %0, r3
ld: ld %0, r2 #comment
zjmp %:end
end:
aff r2
