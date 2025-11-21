savedcmd_hello1.mod := printf '%s\n'   hello1.o | awk '!x[$$0]++ { print("./"$$0) }' > hello1.mod
