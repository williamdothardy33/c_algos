struct char_buf {
    int length;
    int offset;
    char data[];
};

typedef struct char_buf char_buf;

char_buf *create_char_buf();
void append(char_buf *buf, char c);
char *take_last(char_buf *buf, int count);
void show_buf(char_buf *buf);
char *peek_last(char_buf *buf);
int not_empty(char_buf *buf);