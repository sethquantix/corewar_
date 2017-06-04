.name       "don't touch my stuff"
.comment    "Can I have your stuff ?"

start:
    ld      %0, r2
    zjmp    %:begin
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start
    zjmp    %:start

begin:
    st      r1, r10
    ld      %0, r2
    sti     r2, %:start, %1
    sti     r10, %:live, %1
live:
    live    %0
    ld      %0x03700300, r3
    ld      %0x14037004, r4
    fork    %:atk
    ld      %0, r8
    zjmp    %:live

atk:
    st      r3, 20
    st      r4, 20
    st      r5, 20
    st      r6, 20
    st      r7, 20
