# bin_pipe_throttle

```
Initial test project to control data throughput in binary pipe
```

1. It takes binary data __stdin__ via pipe, 
2. Throttle speed by __limiting__ amount of data per second.
3. Puts the binary data via __stdout__.

Use: `stdin | pipeThrottle | stdout`