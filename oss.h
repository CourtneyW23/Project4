union semun {   /* Used in calls to semctl() */
      int val;
      struct semid_ds *buf;
      unsigned short *array;
      #if defined(__linux__)
      struct seminfo *__buf;
      #endif
};

struct shmseg {
   int cntr;
   int write_complete;
   int read_complete;
};

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;


