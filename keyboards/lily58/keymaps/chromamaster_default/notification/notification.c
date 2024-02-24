#include "notification.h"

static notification_t last_notification = NOTIFICATION_NONE;

void notification_write(notification_t notification) {
    last_notification = notification;
}

notification_t notification_read(void) {
    notification_t notification = last_notification;
    last_notification = NOTIFICATION_NONE;

    return notification;
}