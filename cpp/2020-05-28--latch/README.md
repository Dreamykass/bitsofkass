
a counting latch (single-use non-movable non-copyable barrier)
calling thread waits (blocks) on the latch (or arrives and waits, which also decrements the counter),
until the counter reaches zero, because of: arriving, decrementation, or until
another thread calls release, which sets the counter to zero
