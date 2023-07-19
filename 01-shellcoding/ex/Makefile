.POSIX:

all:
	for dir in 01 02 03 04; do \
		cd "$${dir}"; \
		make; \
		cd ..; \
	done

clean:
	for dir in 01 02 03 04; do \
		cd "$${dir}"; \
		make clean; \
		cd ..; \
	done
