//core_loadin_thread showcases outsourcing compute-intensive loading

import * as os from "qjs:os";

var parent = os.Worker.parent;

// When data has finished loading, we set global variable
parent.postMessage(true);

parent.onmessage = function(e) {
    const sharedProgress = new Int32Array(e.data);
    // Example: increment the progress

    let timeCounter = 0;            // Time counted in ms
    let prevTime = Date.now()     // Previous time

    // We simulate data loading with a time counter for 5 seconds
    while (timeCounter < 5000) {
        timeCounter = Math.min(Date.now() - prevTime,5000);
        Atomics.store(sharedProgress, 0, timeCounter/5);
    }
};