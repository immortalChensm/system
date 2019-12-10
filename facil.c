//
// Created by 1655664358@qq.com on 2019/12/9.
//
struct fio_protocol_s {
    /** Called when a data is available, but will not run concurrently */
    void (*on_data)(intptr_t uuid, fio_protocol_s *protocol);
    /** called once all pending `fio_write` calls are finished. */
    void (*on_ready)(intptr_t uuid, fio_protocol_s *protocol);

    uint8_t (*on_shutdown)(intptr_t uuid, fio_protocol_s *protocol);
    /** Called when the connection was closed, but will not run concurrently */
    void (*on_close)(intptr_t uuid, fio_protocol_s *protocol);
    /** called when a connection's timeout was reached */
    void (*ping)(intptr_t uuid, fio_protocol_s *protocol);
    /** private metadata used by facil. */
    size_t rsv;
};

typedef struct {
    fio_protocol_s pr;
    intptr_t uuid;
    void *udata;
    void (*on_open)(intptr_t uuid, void *udata);
    void (*on_start)(intptr_t uuid, void *udata);
    void (*on_finish)(intptr_t uuid, void *udata);
    char *port;
    char *addr;
    size_t port_len;
    size_t addr_len;
    void *tls;
} fio_listen_protocol_s;


/** Connection data (fd_data) */
//连接结构体
typedef struct {
    /* current data to be send */
    fio_packet_s *packet;
    /** the last packet in the queue. */
    fio_packet_s **packet_last;
    /* Data sent so far */
    size_t sent;
    /* fd protocol */
    fio_protocol_s *protocol;
    /* timer handler */
    time_t active;
    /** The number of pending packets that are in the queue. */
    uint16_t packet_count;
    /* timeout settings */
    uint8_t timeout;
    /* indicates that the fd should be considered scheduled (added to poll) */
    fio_lock_i scheduled;
    /* protocol lock */
    fio_lock_i protocol_lock;
    /* used to convert `fd` to `uuid` and validate connections */
    uint8_t counter;
    /* socket lock */
    fio_lock_i sock_lock;
    /** Connection is open */
    uint8_t open;
    /** indicated that the connection should be closed. */
    uint8_t close;
    /** peer address length */
    uint8_t addr_len;
    /** peer address length */
    uint8_t addr[48];
    /** RW hooks. */
    fio_rw_hook_s *rw_hooks;
    /** RW udata. */
    void *rw_udata;
    /* Objects linked to the UUID */
    fio_uuid_links_s links;
} fio_fd_data_s;


typedef struct {
    struct timespec last_cycle;
    /* connection capacity */
    uint32_t capa;
    /* connections counted towards shutdown (NOT while running) */
    uint32_t connection_count;
    /* thread list */
    fio_ls_s thread_ids;
    /* active workers */
    uint16_t workers;
    /* timer handler */
    uint16_t threads;
    /* timeout review loop flag */
    uint8_t need_review;
    /* spinning down process */
    uint8_t volatile active;
    /* worker process flag - true also for single process */
    uint8_t is_worker;
    /* polling and global lock */
    fio_lock_i lock;
    /* The highest active fd with a protocol object */
    uint32_t max_protocol_fd;
    /* timer handler */
    pid_t parent;
#if FIO_ENGINE_POLL
    struct pollfd *poll;
#endif
    fio_fd_data_s info[];
} fio_data_s;


static fio_data_s *fio_data = NULL;

/****************************************************/
/* task node data */
typedef struct {
    void (*func)(void *, void *);
    void *arg1;
    void *arg2;
} fio_defer_task_s;

typedef struct fio_defer_queue_block_s fio_defer_queue_block_s;
struct fio_defer_queue_block_s {
    fio_defer_task_s tasks[DEFER_QUEUE_BLOCK_COUNT];
    fio_defer_queue_block_s *next;
    size_t write;
    size_t read;
    unsigned char state;
};
typedef struct { /* a lock for the state machine, used for multi-threading
                    support */
    fio_lock_i lock;
    /* current active block to pop tasks */
    fio_defer_queue_block_s *reader;
    /* current active block to push tasks */
    fio_defer_queue_block_s *writer;
    /* static, built-in, queue */
    fio_defer_queue_block_s static_queue;
} fio_task_queue_s;

/* the state machine - this holds all the data about the task queue and pool */
static fio_task_queue_s task_queue_normal = {
        .reader = &task_queue_normal.static_queue,
        .writer = &task_queue_normal.static_queue};

static fio_task_queue_s task_queue_urgent = {
        .reader = &task_queue_urgent.static_queue,
        .writer = &task_queue_urgent.static_queue};

    listen:
//结构体成员赋值
*pr = (fio_listen_protocol_s){
        .pr =
                {
                        .on_close = fio_listen_on_close,
                        .ping = mock_ping_eternal,
                        .on_data = (args.tls ? (fio_tls_alpn_count(args.tls)
                                                ? fio_listen_on_data_tls_alpn
                                                : fio_listen_on_data_tls)
                                             : fio_listen_on_data),
                },
        .uuid = uuid,
        .udata = args.udata,
        .on_open = args.on_open,
        .on_start = args.on_start,
        .on_finish = args.on_finish,
        .tls = args.tls,
        .addr_len = addr_len,
        .port_len = port_len,
        .addr = (char *)(pr + 1),
        .port = ((char *)(pr + 1) + addr_len + 1),
};
//监听地址和端口赋值
if (addr_len)
memcpy(pr->addr, args.address, addr_len + 1);
if (port_len)
memcpy(pr->port, args.port, port_len + 1);

if (fio_is_running()) {
fio_attach(pr->uuid, &pr->pr);
} else {
//给事件添加回调【存储在一个回调列表表】
fio_state_callback_add(FIO_CALL_ON_START, fio_listen_on_startup, pr);
fio_state_callback_add(FIO_CALL_ON_SHUTDOWN, fio_listen_cleanup_task, pr);
}