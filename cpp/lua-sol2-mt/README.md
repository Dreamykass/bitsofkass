# very simple example of {cpp + lua/sol2} integration
Also a multi-threaded safety test thing.\
It's fine as long only one context interacts with the lua virtual machine at a time, I'm sure.\
Imagine that `main()` is a game, and the `async()` calls are enemies.


## example output from (my) console
```
F:\GitHub\Dreamykass\bitsofkass\cpp\lua-sol2-mt>lua-sol2-mt/build/Debug/lua_sol2.exe
#################### hello!
[MAIN SAYS 0]
[MAIN SAYS 1]
[lua 1 loop 1 says 96]
[lua 0 loop 1 says 33]
[lua 3 loop 1 says 34]
[lua 2 loop 1 says 8]
[lua 1 loop 2 says 56]
[lua 0 loop 2 says 98]
[lua 3 loop 2 says 5]
[MAIN SAYS 2]
[lua 2 loop 2 says 50]
[lua 1 loop 3 says 25]
[lua 0 loop 3 says 94]
[lua 3 loop 3 says 18]
[lua 2 loop 3 says 21]
[lua 1 loop 4 says 27]
[lua 0 loop 4 says 78]
[lua 3 loop 4 says 25]
[lua 3 loop 5 says 38]
[lua 2 loop 4 says 36]
[lua 1 loop 5 says 87]
[lua 0 loop 5 says 76]
[MAIN SAYS 3]
[lua 2 loop 5 says 16]
[MAIN SAYS 4]
[MAIN SAYS 5]
[MAIN SAYS 6]
#################### bye...

F:\GitHub\Dreamykass\bitsofkass\cpp\lua-sol2-mt>

```



