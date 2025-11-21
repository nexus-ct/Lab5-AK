savedcmd_hello2.mod := printf '%s\n'   hello2.o | awk '!x[$$0]++ { print("./"$$0) }' > hello2.mod
