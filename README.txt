# CPU Process Scheduling Simulator — SJF and SRTF

## Files
- `index.html` — dashboard and GUI layout
- `style.css` — blue-and-white responsive styling
- `script.js` — interactive browser simulation for SJF and SRTF
- `scheduler.c` — standalone C implementation of SJF and SRTF

## Run the GUI in Visual Studio Code
1. Extract the ZIP file.
2. Open the `cpu_scheduler_sla` folder in VS Code.
3. Open `index.html` in a browser, or use the Live Server extension.
4. Add processes or click **Load Example**.
5. Select SJF or SRTF and click **Run Simulation**.

The browser GUI uses JavaScript for calculations because a normal browser page cannot directly execute a C program. The included `scheduler.c` implements both algorithms separately in C.

## Compile and run the C program
With GCC installed, open a terminal in this folder:

Windows:
```bash
gcc scheduler.c -o scheduler.exe
scheduler.exe
```

Linux/macOS:
```bash
gcc scheduler.c -o scheduler
./scheduler
```

## Metrics
- Completion Time (CT)
- Turnaround Time (TAT) = CT − Arrival Time
- Waiting Time (WT) = TAT − Burst Time
- Response Time = First CPU start − Arrival Time
- Average waiting and turnaround time
- CPU utilization = Total CPU busy time / final elapsed time × 100

Algorithms included: SJF (non-preemptive) and SRTF (preemptive). Round Robin is not included.

## ESRR Scheduler Lab
- ESRR is now available as an algorithm option directly in the main dashboard (`index.html`). Use the ESRR quantum and mode controls in the Run Simulation section.
- `esrr_scheduler.html` remains available as a separate comparison simulator with Round Robin, SRTF, and ESRR.
- It includes sample workloads, process add/remove controls, fixed/dynamic ESRR quantum, Gantt-style timelines, performance comparison, and per-process ESRR results.
- Open `esrr_scheduler.html` in a browser to use it.
- The original `index.html`, `style.css`, `script.js`, and `scheduler.c` remain included and unchanged. The original GUI continues to support SJF and SRTF.

## Research Papers page
- `research.html` — opened from the **Research Papers** item in the left sidebar of the dashboard. It lists all five studied papers (summary table plus a detailed section for each: problem, approach, work done, result, findings, limitations, relevance and a link to the paper).
- The papers are stored in one `PAPERS` list at the top of the script in `research.html`; edit that list to change any text.
