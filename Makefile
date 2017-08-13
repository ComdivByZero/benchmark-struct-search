OPTIM := -O2

SOURCE := $(wildcard source/*.c)
S :=

result/%.o : source/%.c always
	@mkdir -p result
	$(S)$(CC) $(OPTIM) -c $< -o $@

result/bench : $(SOURCE:source/%.c=result/%.o)
	$(CC) $(OPTIM) $^ -o $@
	$(S)strip result/*
	@#ls -gG result/*

clean :
	rm -rf result

bruteforce :
	make CC:=tcc S:=@; result/bench
	@for C in gcc clang g++ clang++; do \
		for O in 0 1 2 3 s; do \
			make CC:=$$C OPTIM:=-O$$O S:=@; \
			result/bench; \
		done; \
	done

.PHONY : always clean
