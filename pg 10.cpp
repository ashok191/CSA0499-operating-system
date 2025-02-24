#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct message {
    long msg_type;       // Message type (should be a positive number)
    char msg_text[100];  // Message content
};

int main() {
    // Generate a unique key for the message queue
    key_t key = ftok("msgqfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a new message queue (or get the identifier of an existing one)
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct message msg;

    // Producer: Send a message to the message queue
    msg.msg_type = 1; // Message type (can be any positive number)
    strcpy(msg.msg_text, "Hello, message queue!");

    // Send the message to the queue
    if (msgsnd(msgid, (void*)&msg, sizeof(msg.msg_text), IPC_NOWAIT) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Producer: Data sent to message queue: %s\n", msg.msg_text);

    // Consumer: Receive a message from the message queue
    if (msgrcv(msgid, (void*)&msg, sizeof(msg.msg_text), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    printf("Consumer: Data received from message queue: %s\n", msg.msg_text);

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

