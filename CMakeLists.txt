set(SOURCES
    src/nmtMaster.c
    src/nmtSlave.c
    src/sdo.c
    src/pdo.c
    src/states.c
    src/timer.c
    src/sync.c
    src/emcy.c
    src/objacces.c
    src/lifegrd.c
    drivers/unix/unix.c
    drivers/timers_unix/timers_unix.c
)

include_directories(include include/unix include/timers_unix)

add_library(canfestival ${SOURCES})
