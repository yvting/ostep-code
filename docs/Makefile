CC= latexmk
FLAGS= -pdf
TARGET= lock-proofs

.PHONY: all

all: $(TARGET).pdf
	@echo "Done."

$(TARGET).pdf: $(TARGET).tex *.sty 
	$(CC) $(FLAGS) $(TARGET)

.PHONY: clean

clean:
	$(CC) -C $(TARGET)

