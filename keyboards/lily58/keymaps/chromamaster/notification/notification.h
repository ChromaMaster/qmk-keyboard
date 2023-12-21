#ifndef NOTIFICATION_H
#define NOTIFICATION_H

typedef enum {
    NOTIFICATION_NONE,
    NOTIFICATION_KEY_PRESSED,
} notification_t;

void notification_write(notification_t notification);
notification_t notification_read(void);

#endif // NOTIFICATION_H