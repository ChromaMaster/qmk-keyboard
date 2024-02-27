#include <stddef.h>  // Needed to fix issue in transactions.h
#include <stdint.h>

#include "notification/notification.h"
#include "print.h"
#include "transactions.h"

typedef struct _master_to_slave_t {
    int m2s_data;
} master_to_slave_t;

void user_sync_notification(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t* m2s = (const master_to_slave_t*)in_data;
    notification_write(m2s->m2s_data);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(SYNC_ID_NOTIFICATION, user_sync_notification);
}

void housekeeping_task_user(void) {
    if (!is_keyboard_master()) {
        return;
    }

    if (notification_read() != NOTIFICATION_KEY_PRESSED) {
        return;
    }

    master_to_slave_t m2s = {NOTIFICATION_KEY_PRESSED};
    if (transaction_rpc_send(SYNC_ID_NOTIFICATION, sizeof(m2s), &m2s)) {
        uprintf("Master sent value\n");  // this will now be 11, as the slave adds 5
    } else {
        uprintf("Master send failed!\n");
    }
}