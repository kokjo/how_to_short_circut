#ifndef _PRINTF_H_
#define _PRINTF_H_

#define ENABLE_PERCENT_D (1)


struct output {
    void (*out)(struct output *, char);
};

struct buffer_output {
    struct output out;
    char *buf;
    size_t len;
};

void va_printf(struct output *out, char const *fmtstr, va_list va);
int snprintf(char *buf, size_t len, char const *fmtstr, ...);
int sprintf(char *buf, char const *fmtstr, ...);

#endif
