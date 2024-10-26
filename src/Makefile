SRC:=$(wildcard *.c)
BIN:=TuyaESPControl
LDFLAGS:=-largp -lblobmsg_json -lubox -lubus -lserialport -llink_core -lmiddleware_implementation -lplatform_port -lutils_modules
CFLAGS:=-Wall
.PHONY:all clean

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $^ $(LDFLAGS)

clean:
	$(RM) $(BIN)