# system-monitor

This application aims to expose the machine's CPU usage stats to the user, both via an endpoint, and visaully with a custom Grafana dashboard. The stats are scraped from the `/proc` fs of the system.

As of now, only supported for *NIX systems with a `/proc` fs.

## Requirements:
- CMake (min v3.14.2)
- GCC
- Make
- X11
- Docker (for the grafana dashboard)
- Docker Compose

## Launching system-monitor
- Grab the latest binary from the "Releases" section of this repo(unzip the downloaded file to get the binary).
- Provide execute permission for the file, by running the following command in the terminal, in the directory where the binary is downloaded:
```bash
chmod +x ./system-monitor
```
- Launch the application by executing the binary:
```bash
./system-monitor
```
This opens up port 8080 on the host machine, and emits the scraped metrics, updated every 5s, in the OpenMetrics Standard. The scraped metrics are also written into a file named `accumulated_metrics.txt` in the same directory where the binary is downloaded.
- For getting the metrics on a grafana dashboard, execute the following commands in the main project directory:
```bash
docker compose up -d
```
This launches the prometheus db application on port 9090 of the host machine, and grafana on port 3000. The default username and password for the grafana dashboard is `admin` and `admin` respectively.

## Memory Leak Tests
To run tests to find potential memory leaks that may be caused by the binary, execute the following command:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./system-monitor
```


## Directory Structure
```bash
.
|-- CMakeLists.txt
|-- Dockerfile
|-- LICENSE
|-- README.md
|-- configs
|   |-- grafana_dashboard_config.json
|   |-- grafana_dashboard_provider.yml
|   |-- grafana_datasource.yml
|   `-- prometheus_config.yml
|-- docker-compose.yml
|-- include
|   |-- accumulator_queue.h
|   |-- app_timer.h
|   |-- metrics_exporter.h
|   |-- monitor_metrics.h
|   |-- signal_handler.h
|   |-- socket_manager.h
|   |-- stat_parser.h
|   |-- thread_manager.h
|   |-- usage_calculator.h
|   `-- watchdog_timer.h
|-- main.c
|-- source
|   |-- accumulator_queue.c
|   |-- app_timer.c
|   |-- metrics_exporter.c
|   |-- monitor_metrics.c
|   |-- signal_handler.c
|   |-- socket_manager.c
|   |-- stat_parser.c
|   |-- threads
|   |   |-- accumulator_thread.c
|   |   |-- export_thread.c
|   |   |-- file_write_thread.c
|   |   `-- watchdog_thread.c
|   |-- usage_calculator.c
|   `-- watchdog_timer.c
|-- start.sh
`-- valgrind_test_results.txt

5 directories, 35 files
```

## Manually build from source
To manually build the binary from the source code, execute the following commands in the terminal, from the project root directory:
```bash
chmod +x ./start.sh
./start.sh
```
The `start.sh` script executes the binary by itself. The built binary is present in `$PROJECT_ROOT/build`. In this case, the `accumulated_metrics.txt` file is also created in the `build` directory, and the valgrind test can also be run from inside the `build` directory with the same command as above.

To change the type of build, change the `DCMAKE_BUILD_TYPE` switch in `./start.sh`. Some of the supported enums for the switch are `Release`, `Debug`, `RelWithDebugInfo`.

## Sample Valgrind Result after building from source
```bash
akshayrevankar@cuttlefish:~/system-monitor/build$ valgrind --leak-check=full --show-leak-kinds=all ./system-monitor
==22658== Memcheck, a memory error detector
==22658== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==22658== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==22658== Command: ./system-monitor
==22658==
Threads created!
==22658== Thread 2:
==22658== Conditional jump or move depends on uninitialised value(s)
==22658==    at 0x10A91C: calculate_all_cpus (in /home/akshayrevankar/system-monitor/build/system-monitor)
==22658==    by 0x109D58: monitor_metrics (in /home/akshayrevankar/system-monitor/build/system-monitor)
==22658==    by 0x10A450: accumulator_function (in /home/akshayrevankar/system-monitor/build/system-monitor)
==22658==    by 0x48F6AC2: start_thread (pthread_create.c:442)
==22658==    by 0x4987A03: clone (clone.S:100)
==22658==
^CGracefully exiting...
Threads joined, program ends!
==22658==
==22658== HEAP SUMMARY:
==22658==     in use at exit: 383 bytes in 1 blocks
==22658==   total heap usage: 48 allocs, 47 frees, 72,501 bytes allocated
==22658==
==22658== Thread 1:
==22658== 383 bytes in 1 blocks are still reachable in loss record 1 of 1
==22658==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==22658==    by 0x490A58E: strdup (strdup.c:42)
==22658==    by 0x109804: enqueue (in /home/akshayrevankar/system-monitor/build/system-monitor)
==22658==    by 0x109B51: record_metrics (in /home/akshayrevankar/system-monitor/build/system-monitor)
==22658==    by 0x10A460: accumulator_function (in /home/akshayrevankar/system-monitor/build/system-monitor)
==22658==    by 0x48F6AC2: start_thread (pthread_create.c:442)
==22658==    by 0x4987A03: clone (clone.S:100)
==22658==
==22658== LEAK SUMMARY:
==22658==    definitely lost: 0 bytes in 0 blocks
==22658==    indirectly lost: 0 bytes in 0 blocks
==22658==      possibly lost: 0 bytes in 0 blocks
==22658==    still reachable: 383 bytes in 1 blocks
==22658==         suppressed: 0 bytes in 0 blocks
==22658==
==22658== Use --track-origins=yes to see where uninitialised values come from
==22658== For lists of detected and suppressed errors, rerun with: -s
==22658== ERROR SUMMARY: 4 errors from 1 contexts (suppressed: 0 from 0)
```
