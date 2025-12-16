==35288== Memcheck, a memory error detector
==35288== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==35288== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==35288== Command: ./my_radar ./test.rdr
==35288== 
==35288== Conditional jump or move depends on uninitialised value(s)
==35288==    at 0x488D90E: sfText_setFont (in /usr/lib/x86_64-linux-gnu/libcsfml-graphics.so.2.6.0)
==35288==    by 0x10CB9E: create_time_text (src/objets/time.c:21)
==35288==    by 0x10A595: create_game (src/create.c:18)
==35288==    by 0x10AA16: main (src/main.c:33)
==35288== 
==35288== Conditional jump or move depends on uninitialised value(s)
==35288==    at 0x10A719: destroy_text (src/destroy.c:26)
==35288==    by 0x10A5E6: destroy_game (src/destroy.c:50)
==35288==    by 0x10AA6C: main (src/main.c:42)
==35288== 
SFML warning: trying to use a null font object
==35288== 
==35288== HEAP SUMMARY:
==35288==     in use at exit: 268,026 bytes in 3,665 blocks
==35288==   total heap usage: 64,983 allocs, 61,318 frees, 46,427,892 bytes allocated
==35288== 
==35288== 9,936 (248 direct, 9,688 indirect) bytes in 1 blocks are definitely lost in loss record 2,712 of 2,714
==35288==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==35288==    by 0x4882F80: sfFont_createFromFile (in /usr/lib/x86_64-linux-gnu/libcsfml-graphics.so.2.6.0)
==35288==    by 0x10CB79: create_time_text (src/objets/time.c:18)
==35288==    by 0x10A595: create_game (src/create.c:18)
==35288==    by 0x10AA16: main (src/main.c:33)
==35288== 
==35288== LEAK SUMMARY:
==35288==    definitely lost: 248 bytes in 1 blocks
==35288==    indirectly lost: 9,688 bytes in 59 blocks
==35288==      possibly lost: 0 bytes in 0 blocks
==35288==    still reachable: 258,090 bytes in 3,605 blocks
==35288==         suppressed: 0 bytes in 0 blocks
==35288== Reachable blocks (those to which a pointer was found) are not shown.
==35288== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==35288== 
==35288== Use --track-origins=yes to see where uninitialised values come from
==35288== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
==35288== 
==35288== 1 errors in context 1 of 3:
==35288== Conditional jump or move depends on uninitialised value(s)
==35288==    at 0x10A719: destroy_text (src/destroy.c:26)
==35288==    by 0x10A5E6: destroy_game (src/destroy.c:50)
==35288==    by 0x10AA6C: main (src/main.c:42)
==35288== 
==35288== 
==35288== 1 errors in context 2 of 3:
==35288== Conditional jump or move depends on uninitialised value(s)
==35288==    at 0x488D90E: sfText_setFont (in /usr/lib/x86_64-linux-gnu/libcsfml-graphics.so.2.6.0)
==35288==    by 0x10CB9E: create_time_text (src/objets/time.c:21)
==35288==    by 0x10A595: create_game (src/create.c:18)
==35288==    by 0x10AA16: main (src/main.c:33)
==35288== 
==35288== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
