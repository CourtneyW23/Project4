typedef enum {
    TASK_NEW = 0,
    TASK_READY,
    TASK_RUNNING,
    TASK_WAITING,
    TASK_TERMINATED
} task_state;

typedef enum { OP_CPU = 0, OP_IO, OP_TERMINATE } op_type;

typedef struct {
    op_type type;
    int time;
} op;


typedef struct pcb{
    const unsigned int pid;
    const char *name;
    const unsigned int priority;
    task_state state;
    op *pc;
    struct pcb *next;
} pcb;


